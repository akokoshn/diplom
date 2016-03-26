#include "MainBox.h"

MainBox::MainBox(float _criteria, int _thickness)
{
	LeftBox = Box();
	RightBox = Box();
	criteria = _criteria;
	thickness = _thickness;
	MainLineX = 0;
	MainLineY = 0;
	greed_size = 1;
}
MainBox::~MainBox()
{
	
}
Box MainBox::GetLeft()
{
	return LeftBox;
}
Box MainBox::GetRight()
{
	return RightBox;
}
CvPoint MainBox::GetMain()
{
	CvPoint p;
	p.x = MainLineX;
	p.y = MainLineY;
	return p;
}
void MainBox::Create(Mat *img)
{
	
	MainLineX = img->cols / 2;
	int top, butt, counter;
	std::list<CvPoint> t_list;
	Rays *Left_Ray =  new Rays(CvPoint2D32f(), 0, criteria, thickness);
	Rays *Right_Ray = new Rays(CvPoint2D32f(), 0, criteria, thickness);
	CvPoint2D32f center;
	center.x = MainLineX;
	center.y = 0;

	//create left box
	for (int i = 0; i < (img->rows / greed_size); i++) //rays
	{
		center.y = i;
		Left_Ray->SingleRay(img, center, 2, -1, 0, 0, (MainLineX + 2), img->rows);
	}
	t_list = std::list<CvPoint>(Left_Ray->GetBorderPoints());
	LeftBox.SetKeyPoints(Left_Ray->GetBorderPoints());
	LeftBox.Create();

	//create right box
	for (int i = 0; i < (img->rows / greed_size); i++) //rays
	{
		center.y = i;
		Right_Ray->SingleRay(img, center, 2, 1, (MainLineX - 2), 0, img->cols, img->rows);
	}
	t_list.splice(t_list.end(), Right_Ray->GetBorderPoints());
	RightBox.SetKeyPoints(Right_Ray->GetBorderPoints());
	RightBox.Create();

	counter = 0;
	for (std::list<CvPoint>::iterator it = t_list.begin(); it != t_list.end(); it++)
	{
		MainLineY = (MainLineY + it->y);
		counter++;
	}
	MainLineY = MainLineY / counter;
	center.y = MainLineY;
	
	//create left box
	for (int i = 0; i < (MainLineX / greed_size); i++) //rays
	{
		center.x = i;
		Left_Ray->SingleRay(img, center, -2, -1, 0, 0, (MainLineX + 2), (MainLineY + 2));
		Left_Ray->SingleRay(img, center, -2, 1, 0, (MainLineY - 2), (MainLineX + 2), img->rows);
	}
	LeftBox.SetKeyPoints(Left_Ray->GetBorderPoints());
	LeftBox.Create();

	//create right box
	for (int i = MainLineX; i < (img->cols / greed_size); i++) //rays
	{
		center.x = i;
		Right_Ray->SingleRay(img, center, -2, -1, (MainLineX - 2), 0, img->cols, (MainLineY + 2));
		Right_Ray->SingleRay(img, center, -2, 1, (MainLineX - 2), (MainLineY - 2), img->cols, img->rows);
	}
	RightBox.SetKeyPoints(Right_Ray->GetBorderPoints());
	RightBox.Create();

	set_centers();
}
void MainBox::Create(Mat *img, MainBox *_box)
{

}

std::list<CvPoint> MainBox::GetLeftCenters()
{
	return Left_Centers;
}
std::list<CvPoint> MainBox::GetRightCenters()
{
	return Right_Centers;
}


void MainBox::set_centers()
{
	//left
	CvPoint p1 = LeftBox.GetLeftTop();
	CvPoint p2 = LeftBox.GetRightButt();
	CvPoint t_center;
	t_center.x = p1.x + (p2.x - p1.x)/2;
	t_center.y = p1.y + (p2.y - p1.y)/4;
	Left_Centers.push_back(t_center);
	t_center.x = p1.x + (p2.x - p1.x) / 2;
	t_center.y = p1.y + (p2.y - p1.y) / 2;
	Left_Centers.push_back(t_center);
	t_center.x = p1.x + (p2.x - p1.x) / 2;
	t_center.y = p1.y + ((p2.y - p1.y) * 3) / 4;
	Left_Centers.push_back(t_center);

	//right
	p1 = RightBox.GetLeftTop();
	p2 = RightBox.GetRightButt();
	t_center.x = p1.x + (p2.x - p1.x) / 2;
	t_center.y = p1.y + (p2.y - p1.y) / 4;
	Right_Centers.push_back(t_center);
	t_center.x = p1.x + (p2.x - p1.x) / 2;
	t_center.y = p1.y + (p2.y - p1.y) / 2;
	Right_Centers.push_back(t_center);
	t_center.x = p1.x + (p2.x - p1.x) / 2;
	t_center.y = p1.y + ((p2.y - p1.y) * 3) / 4;
	Right_Centers.push_back(t_center);
}
