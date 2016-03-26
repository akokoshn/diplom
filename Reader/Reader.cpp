#include "Reader.h"

using namespace cv;

#if defined(_WIN32) || defined(_WIN64)
    int Reader::Read(LPCWSTR path, std::list<Mat> *buff)
    {
        RW reader;
        reader = RW();
        int height;
        int with;
        char str[MAX_PATH];
        char curr_path[MAX_PATH];
        int len = 0;
        size_t converted = 0;
        signed short* img_buff;
        WIN32_FIND_DATAW f_data;
        HANDLE const h_find = FindFirstFile(path, &f_data);
        Mat img;


        if (h_find != INVALID_HANDLE_VALUE)
        {
            do
            {
                len = (wcslen(f_data.cFileName) + 1);
                wcstombs_s(&converted, str, MAX_PATH, f_data.cFileName, len);
                len = (wcslen(path) - 1);
                wcstombs_s(&converted, curr_path, MAX_PATH, path, len);
                strcat(curr_path, str);
                reader.set_in(curr_path, 0);
                if (!reader.init())
                {
                    height = reader.get_height();
                    with = reader.get_with();
                    img_buff = new signed short[with*height];
                    reader.get_img(img_buff);
                    img = Mat(with, height, CV_32SC1);
                    for (int h = 0; h < height; h++)
                    for (int w =0; w < with; w++)
                    {
                            img.at<signed int>(h,w) = img_buff[h*with + w];
                    }
                    buff->push_back(img);
                }
            }
            while (FindNextFile(h_find, &f_data) != NULL);
            FindClose(h_find);
        }
        return 1;
    }
#else
    int Reader::Read(char *path, std::list<Mat> *buff)
    {
    }
#endif