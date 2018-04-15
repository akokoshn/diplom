#include <opencv/cv.h>
#include <list>

#include "Detail.h"

class Rays
{
public:
    Rays(CvPoint2D32f point, int no_name, int _criteria, int _thickness) { criteria = _criteria; thickness = _thickness; };
        void SingleRay(cv::Mat *img, CvPoint2D32f center, float, float, int, int, int, int);
        std::list<CvPoint> GetBorderPoints() { return BorderPoints; };
        void SetWindow(float _val1, float _val2) {};
        void Detect(cv::Mat *img, CvPoint2D32f center, int, int, int, int, int, int) {};
private:
    std::list<CvPoint> BorderPoints;
    std::list<Detail> Details;
    int criteria;
    int thickness;
};