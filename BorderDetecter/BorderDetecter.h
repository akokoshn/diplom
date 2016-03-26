#include "stdio.h"
#include <list>

//opencv
#include <cv.h>
#include <highgui.h>
#include <ml.h>
#include <cxcore.h>
#include <types_c.h>
#include <opencv2/legacy/legacy.hpp>

#include "MainBox.h"
using namespace cv;

class BorderDetecter
{
private:
    float val;
    int *Gx;
    int *Gy;
    
    void prepare(Mat* src, Mat* dst);
    CvPoint2D32f CalcNormal(CvPoint p, Mat* img);
public:
    BorderDetecter();
    ~BorderDetecter();
    void Detect(std::list<Mat> *buff, CvPoint centr, int num, int insert, float treshold, int ignore, float _val1, float _val2, int x1, int y1, int x2, int y2);
};