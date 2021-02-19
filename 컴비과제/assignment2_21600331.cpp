#include "opencv2/opencv.hpp"
#include "iostream"
#include "cmath"

using namespace cv;
using namespace std;


int main(){
    Mat gray_image(512,512,CV_8U);
    Mat negative_img(512,512,0);
    Mat log_img;
    Mat gamma_img;
    
    gray_image = imread("lena.png",0);  
    
    imshow("gray image",gray_image);

    negative_img = 255 - gray_image;

    imshow("negative_img",negative_img);
    
    log_img = gray_image.clone();
    gray_image.convertTo(log_img,CV_32F);
    log_img = log_img+1;
    log(log_img,log_img);
    normalize(log_img,log_img,0,255,NORM_MINMAX);
    convertScaleAbs(log_img, log_img); 
    imshow("log_img",log_img);

    MatIterator_<uchar> it, end;
    float gamma = 0.5;
    unsigned char pix[256];
    for (int i = 0; i < 256; i++) {
    
    pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
    }
    gamma_img = gray_image.clone();
    for (it = gamma_img.begin<uchar>(), end = gamma_img.end<uchar>(); it != end; it++) {
    *it = pix[(*it)];
    }
    imshow("gamma_img", gamma_img);
    
    waitKey(0);
        

    return 0;
}