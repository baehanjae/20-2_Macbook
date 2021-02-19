#include "opencv2/opencv.hpp"
#include "iostream"
#include "ctime"

using namespace cv;
using namespace std;

int main(){

    Mat frame; 
    VideoCapture cap;

    if(cap.open("background.mp4") == 0) {
        cout << "no such file" << endl;
        waitKey(0);
    }

    double fps = cap.get(CAP_PROP_FPS);
    double time_in_msec= cap.get(CAP_PROP_POS_MSEC); 
    int total_frames= cap.get(CAP_PROP_FRAME_COUNT);

    while (time_in_msec < 3000) {
        cap >> frame;
        if (frame.empty()) {
            cout<< "end of video" << endl;
            break;
        }
        imshow("video", frame);
        waitKey(33);
        time_in_msec= cap.get(CAP_PROP_POS_MSEC); 
        fps = cap.get(CAP_PROP_POS_FRAMES);
        total_frames= cap.get(CAP_PROP_FRAME_COUNT);
        cout << fps << "/" << total_frames << endl;
    }

    return 0;

}
