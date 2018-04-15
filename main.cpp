//#include "DICOM_RW.h"
#include "Reader.h"
#include "stdio.h"
#include <list>
#include <windows.h>
//opencv
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/ml.h>
#include <opencv/cxcore.h>
#include <opencv2/core/types_c.h>
//#include <opencv2/legacy/legacy.hpp>

#  pragma comment(lib, "opencv_core340d.lib")
#  pragma comment(lib, "opencv_highgui340d.lib")
#  pragma comment(lib, "opencv_imgproc340d.lib")
#  pragma comment(lib, "opencv_video340d.lib")
#  pragma comment(lib, "opencv_ml340d.lib")

#  pragma comment(lib, "opencv_calib3d340d.lib")
#  pragma comment(lib, "opencv_objdetect340d.lib")
#  pragma comment(lib, "opencv_features2d340d.lib")
//#  pragma comment(lib, "opencv_contrib340d.lib")
#  pragma comment(lib, "opencv_ts340d.lib")
//#  pragma comment(lib, "opencv_legacy340d.lib")
#  pragma comment(lib, "opencv_flann340d.lib")
//#  pragma comment(lib, "opencv_gpu340d.lib")

using namespace cv; 

#include "BorderDetecter.h"



int main(int argc, char** argv)
{
    std::list<Mat> buff;
    CvPoint c;
	c.x = 0;
	c.y = 0;
    int num = 256;
    int insert = 0;
// read DICOM files
    if (argc == 2)
    {
        wchar_t wpath[MAX_PATH];
        mbstowcs(wpath, argv[1], strlen(argv[1])+1);
        Reader::Read(wpath, &buff);
    }
    else
    {
        Reader::Read(L"C:\\DIPLOM\\IMAGES\\*", &buff);
    }
	/*
    printf("Input center point:\nx = ");
    scanf_s("%d", &c.x);
    printf("y = ");
    scanf_s("%d", &c.y);
    printf ("Input number of main points:\nnumber = ");
    scanf_s("%d", &num);
    printf("Input number of inserted points:\nnumber = ");
    scanf_s("%d", &insert);
	*/
// detect border 
    BorderDetecter detecter;
    detecter.Detect(&buff, c, num, insert, 100, 20, -400, 200, 0, 512, 250, 0);
    
    
	return 0;
}