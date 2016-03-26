#include "Box.h"
#include "Rays.h"

class MainBox
{
private:
	int MainLineX;
	int MainLineY;
	Box LeftBox;
	Box RightBox;
	int criteria;
	int thickness;
	int greed_size;
	std::list<CvPoint> Left_Centers;
	std::list<CvPoint> Right_Centers;
	void set_centers();
public:
	MainBox(float _criteria, int _thickness);
	~MainBox();
	void Create(Mat *img);
	void Create(Mat *img, MainBox *_box);
	Box GetLeft();
	Box GetRight();
	CvPoint GetMain();
	std::list<CvPoint> GetLeftCenters();
	std::list<CvPoint> GetRightCenters();
};
