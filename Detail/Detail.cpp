#include "Detail.h"

Detail::Detail()
{

}

Detail::Detail (CvPoint p)
{
    Points.push_back(p);
}

Detail::Detail(int x, int y)
{
    CvPoint p;
    p.x = x;
    p.y = y;
    Points.push_back(p);
}

Detail::~Detail ()
{
    Points.clear();
}

CvPoint Detail::GetPoint()
{
    CvPoint p = Points.back();
    Points.pop_back();
    return p;
}

int Detail::AddPoint(CvPoint p)
{
    Points.push_back(p);
    return 0;
}

int Detail::GetSize()
{
    return Points.size();
}
