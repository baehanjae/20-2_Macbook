#include "opencv2/opencv.hpp"
#include "iostream"
#include "cmath"

using namespace cv;
using namespace std;


int main(){
    
    Mat finger;
    Mat fingerb;
    Mat ad1;
    Mat ad1b;
    Mat ad;
    Mat adb;

    finger = imread("Finger.png",0);
    ad1 = imread("adaptive_1.jpg",0);
    ad = imread("adaptive.png",0);
    

    // GaussianBlur(ad1, ad1, Size(5, 5), 5, 5, BORDER_DEFAULT);
    // GaussianBlur(ad, ad, Size(5, 5), 5, 5, BORDER_DEFAULT);

    imshow("a",ad1);
    imshow("b",ad);

    threshold(finger,finger,100, 255,THRESH_BINARY | THRESH_OTSU);

    adaptiveThreshold(ad1, ad1b, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 12);

    adaptiveThreshold(ad, adb, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 15);

    namedWindow("ad1");
    moveWindow("ad1",200,0);
    namedWindow("ad");
    moveWindow("ad",0,250);
    namedWindow("finger");
    moveWindow("finger",0,0);

    imshow("finger",finger);
    imshow("ad1",ad1b);
    imshow("ad",adb);

    waitKey(0);

    return 0;
}