#include "opencv2/opencv.hpp"
#include "iostream"
#include "cmath"

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap;
    Mat img,gray;
    double fps;
    vector<Rect> faces; 
    int index = 0; // 입력값 버퍼
    int buf = 0;

    CascadeClassifier face_classifier;
    face_classifier.load("haarcascades/haarcascade_frontalface_alt.xml");

    if(cap.open("Faces.mp4") == 0) {
        cout << "no such file" << endl;
        waitKey(0);
    }
    
    fps = cap.get(CAP_PROP_POS_FRAMES);
    
    while(1){
        cap >> img;
        //if(cap.get(CAP_PROP_POS_MSEC)<14000) continue;
        cout<<"index : "<<index<<endl;
        cvtColor(img,gray,COLOR_BGR2GRAY);
        
        
        if (img.empty()) {
            cout<< "end of video" << endl;
            break;
        }
        resize(gray,gray,Size(gray.cols/2,gray.rows/2));
        resize(img,img,Size(img.cols/2,img.rows/2));

        // n 110, m 109, f 102;
        if(index == 110){
            face_classifier.detectMultiScale(
                gray,
                faces,
                2.0, // increasesearchscaleby10% each pass
                3, // mergegroupsof threedetections
                0,   // notusedforanewcascade
                Size(30, 30),
                Size(40, 40)
            );
        }
        if(index == 109){
            face_classifier.detectMultiScale(
                gray,
                faces,
                1.1, // increasesearchscaleby10% each pass
                3, // mergegroupsof threedetections
                0,   // notusedforanewcascade
                Size(25, 25), //minsize
                Size(30, 30)
            );
        }
        if(index == 102){
            face_classifier.detectMultiScale(
                gray,
                faces,
                2.0, // increasesearchscaleby10% each pass
                3, // mergegroupsof threedetections
                0,   // notusedforanewcascade
                Size(19, 19), //minsize
                Size(25, 25)
                
            );
        }




        // drawtheresults
        for(int i= 0; i< faces.size(); i++) {
            Point lb(faces[i].x + faces[i].width, faces[i].y+ faces[i].height);
            Point tr(faces[i].x, faces[i].y);
            rectangle(img, lb, tr, Scalar(0, 255, 0), 3, 4, 0);}// p

        imshow("Faces",img);
        buf = waitKey(33);
        cout<<"buf : "<<buf<<endl;
        if(buf == -1) index = index;
        else if(buf == 110){
            index = 110;
        }
        else if(buf == 109){
            index = 109;
        }
        else if(buf == 102){
            index = 102;
        }
        else index = 1000;
    }


    return 0;
}