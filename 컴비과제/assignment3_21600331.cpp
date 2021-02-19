#include "opencv2/opencv.hpp"
#include "iostream"
#include "cmath"

using namespace cv;
using namespace std;


int main(){
    Mat lena(512,512,CV_8U);
    lena = imread("lena.png",0);

    Mat lena_filtered = lena.clone();
    blur(lena_filtered,lena_filtered,Size(7,7)); 
    for(int i=lena.cols/2;i<512;i++){
        for(int j=0;j<512;j++){
            lena_filtered.at<uchar>(j,i) = lena.at<uchar>(j,i);
        }
    }

    Mat saltnpepper = imread("saltnpepper.png",0);
    Mat saltnpepper_filtered = saltnpepper.clone();
    


    Mat moon = imread("moon.png",0);
    Mat moon_filtered = moon.clone();
    Laplacian(moon,moon_filtered,CV_16S);
    convertScaleAbs(moon_filtered, moon_filtered);
    moon_filtered = moon + moon_filtered;
    for(int i=0;i<moon.cols/2;i++){
        for(int j=0;j<512;j++){
            moon_filtered.at<uchar>(j,i) = moon.at<uchar>(j,i);
        }
    }

    imshow("lena",lena);
    imshow("lena_filtered",lena_filtered);
    imshow("moon",moon);
    imshow("moon_filtered",moon_filtered);
    imshow("saltnpepper",saltnpepper);
    imshow("saltnpepper_filtered",saltnpepper_filtered);
    waitKey(0);

    


    return 0;
}