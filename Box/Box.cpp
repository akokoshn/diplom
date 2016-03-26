#include "Box.h"

Box::Box()
{
	p1.x = 0;
	p1.y = 0;
	p2.x = 0;
	p2.y = 0;
	y1_lim = 150;
	y2_lim = 450;
	x1_lim = 50;
	x2_lim = 450;
}
Box::~Box()
{

}
CvPoint Box::GetLeftTop()
{
	return p1;
}
CvPoint Box::GetRightButt()
{
	return p2;
}
void Box::AddKeyPoint(CvPoint p)
{
	KeyPoints.push_back(p);
}
void Box::SetKeyPoints(std::list<CvPoint> p)
{
	KeyPoints = std::list<CvPoint>(p);
}
std::list<CvPoint> Box::GetKeyPoints()
{
	return KeyPoints;
}
void Box::Create()
{
	p1.x = KeyPoints.front().x;
	p1.y = KeyPoints.front().y;
	p2.x = KeyPoints.front().x;
	p2.y = KeyPoints.front().y;
	
	for (std::list<CvPoint>::iterator it = KeyPoints.begin(); it != KeyPoints.end(); it++)
	{
		if (((it->x >= x1_lim) && (it->x <= x2_lim)) &&
			((it->y >= y1_lim) && (it->y <= y2_lim)))
		{

			if (p1.x > it->x)
				p1.x = it->x;
			if (p1.y > it->y)
				p1.y = it->y;
			if (p2.x < it->x)
				p2.x = it->x;
			if (p2.y < it->y)
				p2.y = it->y;
		}
	}
}

