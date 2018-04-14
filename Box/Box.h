#include <list>
#include <opencv/cv.h>

using namespace cv;
class Box
{
private:
	std::list<CvPoint> KeyPoints;
	CvPoint p1;
	CvPoint p2;
	int y1_lim;
	int y2_lim;
	int x1_lim;
	int x2_lim;
public:
	Box();
	~Box();
	CvPoint GetLeftTop();
	CvPoint GetRightButt();
	void Create();
	void AddKeyPoint(CvPoint p);
	void SetKeyPoints(std::list<CvPoint> p);
	std::list<CvPoint> GetKeyPoints();
};