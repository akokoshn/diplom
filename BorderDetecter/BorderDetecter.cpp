#include "BorderDetecter.h"

using namespace cv;

BorderDetecter::BorderDetecter()
{
        Gx = new int[9];
        Gy = new int[9];

        Gx[0] = -1; Gx[1] = 0; Gx[2] = 1;
        Gx[3] = -2; Gx[4] = 0; Gx[5] = 2;
        Gx[6] = -1; Gx[7] = 0; Gx[8] = 1;

        Gy[0] = -1; Gy[1] = -2; Gy[2] = -1;
        Gy[3] = 0;  Gy[4] = 0;  Gy[5] = 0;
        Gy[6] = 1;  Gy[7] = 2;  Gy[8] = 1;

}

BorderDetecter::~BorderDetecter()
{
        delete Gx;
        delete Gy;
}

void BorderDetecter::prepare(Mat* src, Mat* dst)
{
        for (int i = 0; i < src->rows; i++)
        {
            for (int j = 0; j < src->cols; j++)
            {
                if (src->at<signed int>(i, j) > val)
                    dst->at<signed int>(i, j) = val;
                if (src->at<signed int>(i, j) < -val)
                    dst->at<signed int>(i, j) = -val;
                dst->at<signed int>(i, j) = src->at<signed int>(i, j);
            }
        }
}

CvPoint2D32f BorderDetecter::CalcNormal(CvPoint p, Mat* img)
{
        CvPoint2D32f normal;
        float dx = 0;
        float dy = 0;
        int a;
        if ( ((p.x == 0) || (p.x == (img->cols - 1) )) ||
             ((p.y == 0) || (p.y == (img->rows - 1) )) )
        {
            normal.x = 0;
            normal.y = 0;
            return normal;
        }
        for (int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
            {
                a = img->at<signed int>((p.x + (j-1)),(p.y + (i-1)));
                dx = dx + Gx[3*i + j]*img->at<signed int>((p.x + (j-1)),(p.y + (i-1)));
                dy = dy + Gy[3*i + j]*img->at<signed int>((p.x + (j-1)),(p.y + (i-1)));
            }
        normal.x = dx/sqrt(dx*dx + dy*dy);
        normal.y = dy/sqrt(dx*dx + dy*dy);
        return normal;
}

void BorderDetecter::Detect(std::list<Mat> *buff, CvPoint centr, int num, int insert, float treshold, int ignore, float _val1, float _val2, int x1, int y1, int x2, int y2)
    {
        Mat img;
        val = _val2 - _val1;
        int all_len = (num - 1)*insert + num;
        CvPoint2D32f Center;
        Center.x = centr.x;
        Center.y = centr.y;
		MainBox _box = MainBox(treshold, ignore);
		Rays _rays(Center, num, treshold, ignore);
        _rays.SetWindow(_val1, _val2);
        std::list<CvPoint> p;
        std::list<CvPoint2D32f> all_normals;
        int k;
        float alpha=20/100.0f; 
        float beta=20/100.0f; 
        float gamma=20/100.0f; 
        int length = all_len;
        CvSize size;
        CvTermCriteria criteria;
        IplImage pre_image;

        std::list<Mat>::iterator it;
        for (it = buff->begin(); it != buff->end(); it++)
        {
            img  = Mat(it->cols, it->rows, CV_32SC1);
            prepare(&(*it), &img);
            //_rays.Detect(img, Center, 2, 0, x1, y1, x2, y2);
            //_rays.NormExSurf(50);
            //p = _rays.GetBorderPoints();
            //all_len = p.size();
            //set border points
            k = 0;
			_box.Create(&img);

            //cvsnake
            alpha=20/100.0f; 
            beta=20/100.0f; 
            gamma=20/100.0f; 
            length = all_len;
            size.width=3; 
            size.height=3; 
            criteria.type=CV_TERMCRIT_ITER; 
            criteria.max_iter=1000; 
            criteria.epsilon=0.0001;

            Mat pre_show = Mat(img.rows, img.cols, CV_8UC1);
            for (int i = 0; i < img.rows; i++)
                for(int j = 0; j < img.cols; j++)
                {
                    if (img.at<signed int>(i,j) < _val1)
                        pre_show.at<unsigned char>(i, j) = 0;
                    else if (img.at<signed int>(i,j) > _val2)
                        pre_show.at<unsigned char>(i, j) = 255;
                    else
                       pre_show.at<unsigned char>(i, j) = (int)(((img.at<signed int>(i,j) + _val1)/(val - 1))*255);
                                           
                }

            pre_image = IplImage(pre_show);
            //cvSnakeImage( &pre_image, all_points,length,&alpha,&beta,&gamma,CV_VALUE,size,criteria,0 );
            //calc normals
            //for (std::list<CvPoint>::iterator it = p.begin(); it != p.end(); it++)
            //{
                //all_normals.push_back(CalcNormal(*(it), &img));
            //}
            //*/
            Mat show = Mat(img.rows, img.cols, CV_8UC3);
            for (int i = 0; i < show.rows; i++)
                for(int j = 0; j < show.cols; j++)
                {
                    show.at<Vec3b>(i, j)[0] = pre_show.at<unsigned char>(i, j);
                    show.at<Vec3b>(i, j)[1] = pre_show.at<unsigned char>(i, j);
                    show.at<Vec3b>(i, j)[2] = pre_show.at<unsigned char>(i, j);
                }
			for (int i = 0; i < show.rows; i++)
			{
				show.at<Vec3b>(i, _box.GetMain().x)[0] = 0;
				show.at<Vec3b>(i, _box.GetMain().x)[1] = 255;
				show.at<Vec3b>(i, _box.GetMain().x)[2] = 0;
				///left box y=const
				show.at<Vec3b>(i, _box.GetLeft().GetLeftTop().x)[0] = 255;
				show.at<Vec3b>(i, _box.GetLeft().GetLeftTop().x)[1] = 0;
				show.at<Vec3b>(i, _box.GetLeft().GetLeftTop().x)[2] = 0;
				///right box y=const
				show.at<Vec3b>(i, _box.GetRight().GetRightButt().x)[0] = 255;
				show.at<Vec3b>(i, _box.GetRight().GetRightButt().x)[1] = 0;
				show.at<Vec3b>(i, _box.GetRight().GetRightButt().x)[2] = 0;
			}
			for (int i = 0; i < show.cols; i++)
			{
				show.at<Vec3b>(_box.GetMain().y, i)[0] = 0;
				show.at<Vec3b>(_box.GetMain().y, i)[1] = 255;
				show.at<Vec3b>(_box.GetMain().y, i)[2] = 0;
				
			}
			for (int i = 0; i < _box.GetMain().x; i++)
			{
				///left box x=const, top
				show.at<Vec3b>(_box.GetLeft().GetLeftTop().y, i)[0] = 255;
				show.at<Vec3b>(_box.GetLeft().GetLeftTop().y, i)[1] = 0;
				show.at<Vec3b>(_box.GetLeft().GetLeftTop().y, i)[2] = 0;
				///left box x=const, butt
				show.at<Vec3b>(_box.GetLeft().GetRightButt().y, i)[0] = 255;
				show.at<Vec3b>(_box.GetLeft().GetRightButt().y, i)[1] = 0;
				show.at<Vec3b>(_box.GetLeft().GetRightButt().y, i)[2] = 0;
			}
			for (int i = _box.GetMain().x + 1; i < show.cols; i++)
			{
				///right box x=const, top
				show.at<Vec3b>(_box.GetRight().GetLeftTop().y, i)[0] = 255;
				show.at<Vec3b>(_box.GetRight().GetLeftTop().y, i)[1] = 0;
				show.at<Vec3b>(_box.GetRight().GetLeftTop().y, i)[2] = 0;
				///right box x=const, butt
				show.at<Vec3b>(_box.GetRight().GetRightButt().y, i)[0] = 255;
				show.at<Vec3b>(_box.GetRight().GetRightButt().y, i)[1] = 0;
				show.at<Vec3b>(_box.GetRight().GetRightButt().y, i)[2] = 0;
			}
			std::list<CvPoint> BoxKeyPoints = _box.GetLeft().GetKeyPoints();
			BoxKeyPoints.splice(BoxKeyPoints.end(), _box.GetRight().GetKeyPoints());
			for (std::list<CvPoint>::iterator it = BoxKeyPoints.begin(); it != BoxKeyPoints.end(); it++)
			{
				show.at<Vec3b>(it->y, it->x)[0] = 0;
				show.at<Vec3b>(it->y, it->x)[1] = 0;
				show.at<Vec3b>(it->y, it->x)[2] = 255;
			}

			std::list<CvPoint> Centers = _box.GetLeftCenters();
			for (std::list<CvPoint>::iterator it = Centers.begin(); it != Centers.end(); it++)
			{
				Center.x = it->x;
				Center.y = it->y;
				_rays.Detect(&img, Center, 2, 0, x1, y1, x2, y2);
				show.at<Vec3b>(it->y, it->x)[0] = 0;
				show.at<Vec3b>(it->y, it->x)[1] = 255;
				show.at<Vec3b>(it->y, it->x)[2] = 0;
			}
			Centers = _box.GetRightCenters();
			for (std::list<CvPoint>::iterator it = Centers.begin(); it != Centers.end(); it++)
			{
				Center.x = it->x;
				Center.y = it->y;
				//_rays.Detect(img, Center, 2, 0, x1, y1, x2, y2);
				show.at<Vec3b>(it->y, it->x)[0] = 0;
				show.at<Vec3b>(it->y, it->x)[1] = 255;
				show.at<Vec3b>(it->y, it->x)[2] = 0;
			}
			
			
			p = _rays.GetBorderPoints();
            //show border
            for (std::list<CvPoint>::iterator it = p.begin(); it != p.end(); it++)
            {
                show.at<Vec3b>(it->y, it->x)[0] = 0;
                show.at<Vec3b>(it->y, it->x)[1] = 255;
                show.at<Vec3b>(it->y, it->x)[2] = 255;
            }

           //show detail
            /*std::list<Detail>* p_list = _rays.GetDetails();
            CvPoint tmp_point;
            int tmp_size = 0;
            for (std::list<Detail>::iterator _it = p_list->begin(); _it != p_list->end(); _it++)
            {
                tmp_size = _it->GetSize();
                for (int i = 0; i < tmp_size; i++)
                {
                    tmp_point = _it->GetPoint();
                    show.at<Vec3b>(tmp_point.y, tmp_point.x)[0] = 0;
                    show.at<Vec3b>(tmp_point.y, tmp_point.x)[1] = 255;
                    show.at<Vec3b>(tmp_point.y, tmp_point.x)[2] = 0;
                }
            }
            _rays.Clear();*/

            IplImage image(show);
            cvNamedWindow("Output",0);
            cvShowImage("Output",&image);
            cvWaitKey(0);
            cvDestroyWindow("Output");

        }
}