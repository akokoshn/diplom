#include <opencv/cv.h>

class Rays
{
public:
        Rays(CvPoint2D32f point, int no_name, int criteria, int thickness) {};
        void SingleRay(cv::Mat *img, CvPoint2D32f center, int, int, int, int, int, int) {};
        std::list<CvPoint> GetBorderPoints() { return std::list<CvPoint>(); };
        void SetWindow(float _val1, float _val2) {};
        void Detect(cv::Mat *img, CvPoint2D32f center, int, int, int, int, int, int) {};
};