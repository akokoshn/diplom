#include "Rays.h"

void Rays::SingleRay(cv::Mat *img, CvPoint2D32f center, float step, float angle, int left, int top, int right, int bottom)
{
    CvPoint2D32f head = center;
    CvPoint p;
    p.x = (int)head.x;
    p.y = (int)head.y;
    float val = img->at<signed int>(p.y, p.x);
    int detail_size = 0;

    while (((p.x > left) && (p.x < right)) &&
           ((p.y > top) && (p.y < bottom)))
    {
        if (abs(val - img->at<signed int>(p.y, p.x)) > criteria)
        {
            detail_size++;
            if (detail_size >= thickness)
                break;
        }
        else
        {
            if (detail_size)
                Details.push_back(Detail(p));
            detail_size = 0;
            val = img->at<signed int>(p.y, p.x);
        }
        head.x = head.x + step * sin(angle);
        head.y = head.y - step * cos(angle);
        p.x = (int)head.x;
        p.y = (int)head.y;
    }
    if (p.x <= left) p.x = left + 1;
    if (p.x >= right) p.x = right - 1;
    if (p.y <= top) p.y = top + 1;
    if (p.y >= bottom) p.y = bottom - 1;

    BorderPoints.push_back(p);
}