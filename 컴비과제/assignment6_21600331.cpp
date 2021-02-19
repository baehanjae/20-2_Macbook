#include "opencv2/opencv.hpp"
#include "iostream"
#include "cmath"

using namespace cv;
using namespace std;


int main(){
    
    Mat frame;
    VideoCapture cap;

    if(cap.open("Road-1.mp4") == 0) {
        cout << "no such file" << endl;
        waitKey(0);
    }

    while (1) {
        cap >> frame;
        if (frame.empty()) {
            cout<< "end of video" << endl;
            break;
        }

        Mat leftROI(frame, Rect(200, 400, 600-200, 600-400));
        Mat rightROI(frame, Rect(600, 400, 1000-600, 600-400));
        Mat ROI(frame, Rect(200, 400, 1000-200, 600-400));
        cvtColor(leftROI, leftROI, CV_BGR2GRAY);
        cvtColor(rightROI, rightROI, CV_BGR2GRAY);

        blur(leftROI,leftROI,Size(5,5));
        blur(rightROI,rightROI,Size(5,5));

        Canny(leftROI, leftROI, 10, 60);
        Canny(rightROI, rightROI, 10, 60);

        namedWindow("Left Canny");
        moveWindow("Left Canny",200,0);

        namedWindow("Right Canny");
        moveWindow("Right Canny",600,0);

        imshow("Left Canny", leftROI);
        imshow("Right Canny", rightROI);
        waitKey(33);
    }


    return 0;
}