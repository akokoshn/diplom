#include <list>
#include <cv.h>

using namespace cv;
class Detail
{
private:
    std::list<CvPoint> Points;

public:
    Detail ();
    Detail (CvPoint p);
    Detail (int x, int y);
    ~Detail ();
    CvPoint GetPoint ();
    int AddPoint (CvPoint p);
    int GetSize ();

};