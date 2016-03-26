
#ifdef DICOMApp_EXPORTS
#define DICOMApp_API __declspec(dllexport) 
#else
#define DICOMApp_API __declspec(dllimport) 
#endif


#define FUNCTION_H

#include <list>

class RW
{
private:
    signed short* img;
    unsigned int height;
    unsigned int with;
    bool is_dir;
    char* in_name;
    char* out_name;
    char* filter;
    int init_from_file();
    int init_from_dir();
public:
    DICOMApp_API RW();
    DICOMApp_API  void set_in(char* name, bool is_dir);
    DICOMApp_API  void set_out(char* name, bool is_dir);
    DICOMApp_API  void set_filter(char* filter);
    DICOMApp_API  int init();
    

    DICOMApp_API  void get_img(signed short* out);
    DICOMApp_API  unsigned int get_height();
    DICOMApp_API  unsigned int get_with();
};
