#include "opencv2/opencv.hpp"
#include "iostream"
#include "cmath"

using namespace cv;
using namespace std;


int main(){

    CascadeClassifier face_classifier;
    face_classifier.load("haarcascades/haarcascade_frontalface_alt.xml");
    vector<Rect> faces; 
    Mat flag = imread("flag.jpg",1);
    resize(flag,flag,Size(640,360));
    Mat frame, m_backproj, hsv;
    Mat m_model3d;
    Rect m_rc;
    float hrange[] = { 0,180 };
    float vrange[] = { 0,255 };
    float srange[] = { 0,255 };
    const float* ranges[] = { hrange, srange, vrange }; // hue, saturation, brightness
    int channels[] = { 0, 1, 2 };
    int hist_sizes[] = { 16, 16, 16 };
    Mat img(10,10,CV_8UC1);
    int update = 0;
    int tracking = 0;
    Mat bgModel,fgModel,foreground,result,b_result,background;
    Mat imgRoi,mask,b_flag;

    VideoCapture cap(0);

    if(!cap.isOpened()){
        cout << ("Can't open Webcam") << endl;
        return -1;
    }


    while(1){
        

        cap >> frame;
        resize(frame,frame,Size(frame.cols/2,frame.rows/2));
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        face_classifier.detectMultiScale(
            frame,
            faces,
            1.1, // increasesearchscaleby10% each pass
            3
        );

        if(faces.size()>0) {
            update = 1;
        }    
        

        if(update == 1){
        Point lb(faces[1].x + faces[1].width, faces[1].y+ faces[1].height);
        Point tr(faces[1].x, faces[1].y);
        //rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
        Rect rc =  Rect(faces[0].x,faces[0].y,faces[0].width,faces[0].height);
        Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
        ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255, CV_FILLED);
        Mat roi(hsv, rc);
        calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges);
        m_rc = rc;
        update = 0;
        tracking = 1;
        }

        if(tracking) {
            //histogram backprojection
            calcBackProject(&hsv, 1, channels, m_model3d, m_backproj, ranges);
            //tracking;
            CamShift(m_backproj, m_rc, TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
            rectangle(frame, m_rc, Scalar(0, 0, 255), 3);

            grabCut(frame, result, m_rc, bgModel, fgModel, 3, GC_INIT_WITH_RECT);
            compare(result, GC_PR_FGD, result, CMP_EQ);
            foreground = Mat(frame.size(), CV_8UC3, Scalar(255, 255, 255));
            frame.copyTo(foreground, result);
            threshold(result,b_result,127,255,THRESH_BINARY_INV);
            b_flag = imread("flag.jpg",1);
            resize(b_flag,b_flag,Size(640,360));
            
            foreground.copyTo(b_flag,result);

            imshow("project3",b_flag);
        }
        

        if(waitKey(33) == 27) break;

    }
    

    return 0;
}