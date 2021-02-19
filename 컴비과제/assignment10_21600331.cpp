#include "opencv2/opencv.hpp"
#include "iostream"
#include "cmath"

using namespace cv;
using namespace std;


int main() {
    VideoCapture capture2("background.mp4");
    Mat img, sum, avg;
    int cnt = 2;
    
    capture2 >> avg;
    cvtColor(avg,avg,CV_BGR2GRAY);

    while(cnt < 11){
        if (!capture2.read(img)) break;
        cvtColor(img,img,CV_BGR2GRAY);
        add(img / cnt, avg*(cnt-1) / cnt, avg);
        
        
        cnt++;
        waitKey(33);
    }

    //imshow("avg", avg);
    //waitKey(0);

    VideoCapture capture("background.mp4");
    Mat image, gray, result, foregroundMask, foregroundImg;
    //set the first frame as background
    

    
    while (true) {
        if (capture.grab() == 0) break;
        capture.retrieve(image);
        cvtColor(image, gray, CV_BGR2GRAY);
        absdiff(avg, gray, foregroundMask);
        threshold(foregroundMask, foregroundMask, 50, 255, CV_THRESH_BINARY);
        foregroundMask.copyTo(foregroundImg);
        gray.copyTo(foregroundImg, foregroundMask);
        vector<vector<Point> > contours;
        vector<Vec4i>hierarchy;
        findContours(foregroundMask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        
        vector<Rect> boundRect(contours.size());
        for (int i= 0; i< contours.size(); i++) {
            boundRect[i] = boundingRect(Mat(contours[i]));
        }
        //draw rectangles on the contours
        int size = 0;
        for (int i= 0; i< contours.size(); i++) {
            if(boundRect[i].area()>400) {
                rectangle(gray, boundRect[i].tl(), boundRect[i].br(), Scalar(255), 2, 8, 0);
                size++;
            }
        }

        putText(gray, format("# Rect : %d", size), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 4);

        //imshow("foregroundImg", foregroundImg);
        //imshow("foregroundMask", foregroundMask);
        imshow("background", gray);
        waitKey(33);
    }
}