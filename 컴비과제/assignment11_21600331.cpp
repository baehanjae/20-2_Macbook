#include "opencv2/opencv.hpp"
#include "iostream"
#include "cmath"

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("background.mp4");
    Mat avg,sub, frame, frame_gray,element, elementForErode;
    //set the first frame as background
    vector<vector<Point> > contours;
    vector<Vec4i>hierarchy;

    double fps = cap.get(CV_CAP_PROP_FPS);
    int time = 0;
    int num_frame_avg = 10;
    int cnt = 1;
    int rect_num = 0;

    int num = 0;
    

    cap >> frame;
    cvtColor(frame,frame_gray,CV_BGR2GRAY);
    avg= Mat(frame_gray.rows, frame_gray.cols,CV_8UC1,Scalar(0));
    add(frame_gray/num_frame_avg,avg,avg);

    element = getStructuringElement(MORPH_ELLIPSE, Size(40, 20));
    
    while(1){
        //1초마다 디버깅용 waitKey 3초 (사람수 확인용)
        //if(time%1000 == 0) waitKey(3000);

        cap >> frame;
        if (frame.empty()) {
            cout<< "end of video" << endl;
            break;
        }
        cvtColor(frame,frame_gray,CV_BGR2GRAY);
        time = cap.get(CAP_PROP_POS_MSEC);

        if(cnt < num_frame_avg){
            add(frame_gray/num_frame_avg,avg,avg);
            cnt++;
        }
        else{
            absdiff(avg, frame_gray, sub);
            threshold(sub, sub, 40, 255, CV_THRESH_BINARY);
            
            //morphological operation
            morphologyEx(sub, sub, MORPH_CLOSE, element);
            dilate(sub,sub,element);
            morphologyEx(sub, sub, MORPH_OPEN, element);
            
            findContours(sub, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
            vector<Rect> boundRect(contours.size());
            rect_num = 0;

            for(int i=0; i<contours.size(); i++){
                boundRect[i] = boundingRect(contours[i]);
                if(boundRect[i].area()>6000){
                    rectangle(sub,boundRect[i],Scalar(126),2,8);
                    rect_num++;
                }
            }
            
            putText(frame, format("# Number of People : %d", rect_num), Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 4);
            //putText(sub, format("# time : %d", time/1000), Point(520, 120), FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 4);
            imshow("background subtraction",frame);
        }
        waitKey(1000/fps);
    }
    return 0;
}