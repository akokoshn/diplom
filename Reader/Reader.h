#include "DICOM_RW.h"
#include <list>
#include <windows.h>
//opencv
#include <cv.h>
#include <highgui.h>
#include <ml.h>
#include <cxcore.h>
#include <types_c.h>
#include <opencv2/legacy/legacy.hpp>

using namespace cv;

static class Reader
{
public:
#if defined (_WIN32) || defined(_WIN64)
    static int Read(LPCWSTR path, std::list<Mat> *buff);
#else
    static int Read(char *path, std::list<Mat> *buff);
#endif
};