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
        
        // if(cap.get(CAP_PROP_POS_MSEC)<31000) continue;
        if(cap.get(CAP_PROP_POS_MSEC)>35000) break;

        Mat leftROI(frame, Rect(200, 400, 600-200, 600-400));
        Mat rightROI(frame, Rect(600, 400, 1000-600, 600-400));
        Mat centerROI(frame, Rect(550,400,700-550,600-400));
        Mat centerROI2(frame, Rect(600,400,900-600,600-400));
        Mat ROI(frame, Rect(200, 400, 1000-200, 600-400));

        cvtColor(leftROI, leftROI, CV_BGR2GRAY);
        cvtColor(rightROI, rightROI, CV_BGR2GRAY);
        cvtColor(centerROI, centerROI, CV_BGR2GRAY);
        cvtColor(centerROI2, centerROI2, CV_BGR2GRAY);


        blur(leftROI,leftROI,Size(5,5));
        blur(rightROI,rightROI,Size(5,5));
        blur(centerROI,centerROI,Size(5,5));
        blur(centerROI2,centerROI2,Size(5,5));


        Canny(leftROI, leftROI, 10, 60);
        Canny(rightROI, rightROI, 10, 45);
        Canny(centerROI, centerROI, 10, 75);
        Canny(centerROI2, centerROI2, 10, 70);

        Mat poly_roi;
        Mat poly_mask= Mat::zeros(leftROI.size(), leftROI.type());
        Point poly[1][4];
        poly[0][0] = Point(380, 0);
        poly[0][1] = Point(400, 0);
        poly[0][2] = Point(400, 200);
        poly[0][3] = Point(80, 200);
        const Point* ppt[1] = { poly[0] };
        int npt[] = { 4 };
        fillPoly(poly_mask, ppt, npt, 1, Scalar(255), 8);
        leftROI.copyTo(poly_roi, poly_mask);
        //imshow("polyROI", poly_roi);

        Mat poly_roi2;
        Mat poly_mask2= Mat::zeros(rightROI.size(), rightROI.type());
        Point poly2[1][4];
        poly2[0][0] = Point(0, 0);
        poly2[0][1] = Point(110, 0);
        poly2[0][2] = Point(400, 200);
        poly2[0][3] = Point(0, 200);
        const Point* ppt2[1] = { poly2[0] };
        int npt2[] = { 4 };
        fillPoly(poly_mask2, ppt2, npt2, 1, Scalar(255), 8);
        rightROI.copyTo(poly_roi2, poly_mask2);
        //imshow("polyROI", poly_roi2);


        vector<Vec2f> l_lines,r_lines,c_lines,c_lines2;
        float l_rho,l_theta, l_a, l_b, l_x0, l_y0;
        float r_rho,r_theta, r_a, r_b, r_x0, r_y0;
        float c_rho,c_theta, c_a, c_b, c_x0, c_y0;
        float c_rho2,c_theta2, c_a2, c_b2, c_x02, c_y02;

        Point l_p1,l_p2;
        Point r_p1,r_p2;
        Point c_p1,c_p2;
        Point c_p12,c_p22;

        HoughLines(poly_roi,l_lines,1,CV_PI / 180, 55);
        HoughLines(poly_roi2,r_lines,1,CV_PI / 180, 60);
        HoughLines(centerROI,c_lines,1,CV_PI / 180, 50);
        HoughLines(centerROI2,c_lines2,1,CV_PI / 180, 50);

        cvtColor(leftROI,leftROI,CV_GRAY2BGR);
        cvtColor(rightROI,rightROI,CV_GRAY2BGR);
        cvtColor(centerROI,centerROI,CV_GRAY2BGR);
        cvtColor(centerROI2,centerROI2,CV_GRAY2BGR);
        

        float l_tot_rho=0,l_tot_theta=0,l_avg_rho=0,l_avg_theta=0;
        int l_tot_cnt = 0;
        float r_tot_rho=0,r_tot_theta=0,r_avg_rho=0,r_avg_theta=0;
        int r_tot_cnt = 0;
        float c_tot_rho=0,c_tot_theta=0,c_avg_rho=0,c_avg_theta=0;
        int c_tot_cnt = 0;
        float c_tot_rho2=0,c_tot_theta2=0,c_avg_rho2=0,c_avg_theta2=0;
        int c_tot_cnt2 = 0;

        for(int i=0;i<l_lines.size();i++){
            l_rho = l_lines[i][0];
            l_theta = l_lines[i][1];
            
            if(l_theta<40* CV_PI / 180 || 60*CV_PI / 180<l_theta){
                continue;
            }

            l_tot_rho += l_rho;
            l_tot_theta += l_theta;
            l_tot_cnt += 1;
            
        }

        for(int i=0;i<c_lines.size();i++){
            c_rho = c_lines[i][0];
            c_theta = c_lines[i][1];

            if( c_theta < 0*CV_PI/180 || 30*CV_PI / 180<c_theta){
                continue;
            }

            c_tot_rho += c_rho;
            c_tot_theta += c_theta;
            c_tot_cnt += 1;
        }

        for(int i=0;i<c_lines2.size();i++){
            c_rho2 = c_lines2[i][0];
            c_theta2 = c_lines2[i][1];

            if( c_theta2 < 150*CV_PI/180 || 180*CV_PI / 180<c_theta2){
                continue;
            }

            c_tot_rho2 += c_rho2;
            c_tot_theta2 += c_theta2;
            c_tot_cnt2 += 1;
        }

        for(int i=0;i<r_lines.size();i++){
            r_rho = r_lines[i][0];
            r_theta = r_lines[i][1];
            
            if(r_theta<120* CV_PI / 180 || 150*CV_PI / 180<r_theta){
                continue;
            }

            r_tot_rho += r_rho;
            r_tot_theta += r_theta;
            r_tot_cnt += 1;
            
        }

        l_avg_rho = l_tot_rho / l_tot_cnt;
        l_avg_theta = l_tot_theta / l_tot_cnt;

        r_avg_rho = r_tot_rho / r_tot_cnt;
        r_avg_theta = r_tot_theta / r_tot_cnt;

        c_avg_rho = c_tot_rho / c_tot_cnt;
        c_avg_theta = c_tot_theta / c_tot_cnt;

        c_avg_rho2 = c_tot_rho2 / c_tot_cnt2;
        c_avg_theta2 = c_tot_theta2 / c_tot_cnt2;

        //cout << "c tot : "<< c_tot_cnt2 << "  c theta : " << c_avg_theta2*180/CV_PI << endl;

        l_a = cos(l_avg_theta);
        l_b = sin(l_avg_theta);
        r_a = cos(r_avg_theta);
        r_b = sin(r_avg_theta);
        c_a = cos(c_avg_theta);
        c_b = sin(c_avg_theta);
        c_a2 = cos(c_avg_theta2);
        c_b2 = sin(c_avg_theta2);

        l_x0 = l_a * l_avg_rho;
        l_y0 = l_b * l_avg_rho;

        l_p1 = Point(cvRound(l_x0 + 1500 * (-l_b)+200),cvRound(l_y0 + 1500 * l_a)+400);
        l_p2 = Point(cvRound(l_x0 - 1500 * (-l_b)+200),cvRound(l_y0 - 1500 * l_a)+400);
        
        r_x0 = r_a * r_avg_rho;
        r_y0 = r_b * r_avg_rho;

        r_p1 = Point(cvRound(r_x0 + 1500 * (-r_b))+600,cvRound(r_y0 + 1500 * r_a)+400);
        r_p2 = Point(cvRound(r_x0 - 1500 * (-r_b))+600,cvRound(r_y0 - 1500 * r_a)+400);

        c_x0 = c_a * c_avg_rho;
        c_y0 = c_b * c_avg_rho;

        c_p1 = Point(cvRound(c_x0 + 1500 * (-c_b))+500,cvRound(c_y0 + 1500 * c_a)+420);
        c_p2 = Point(cvRound(c_x0 - 1500 * (-c_b))+500,cvRound(c_y0 - 1500 * c_a)+420);

        c_x02 = c_a2 * c_avg_rho2;
        c_y02 = c_b2 * c_avg_rho2;

        c_p12 = Point(cvRound(c_x02 + 1500 * (-c_b2))+600,cvRound(c_y02 + 1500 * c_a2)+420);
        c_p22 = Point(cvRound(c_x02 - 1500 * (-c_b2))+600,cvRound(c_y02 - 1500 * c_a2)+420);

        // line(frame,l_p1,l_p2,Scalar(0,0,255),3,8);
        // line(frame,r_p1,r_p2,Scalar(0,0,255),3,8);
        // line(frame,c_p1,c_p2,Scalar(255,0,0),3,8);
        // line(frame,c_p12,c_p22,Scalar(255,0,255),3,8);
        // line(centerROI,c_p1,c_p2,Scalar(0,0,255),3,8);

        
        // putText(frame,format("%lf",cap.get(CAP_PROP_POS_MSEC)),Point(400,300), FONT_HERSHEY_SIMPLEX,3,Scalar(0,0,255));

        

        if((c_tot_cnt2 != 0 || c_tot_cnt != 0) && (r_tot_cnt == 0 || l_tot_cnt == 0)){
            putText(frame,format("warning!:"),Point(400,100), FONT_HERSHEY_SIMPLEX,3,Scalar(0,0,255));
            putText(frame,format("lane departure"),Point(300,200), FONT_HERSHEY_SIMPLEX,3,Scalar(0,0,255));
        }
        else if((c_tot_cnt2 != 0 || c_tot_cnt != 0)||(r_tot_cnt != 0 && l_tot_cnt != 0)){
        }
        

        namedWindow("Frame");
        // namedWindow("right");
        // namedWindow("left");
        // namedWindow("center");
        // namedWindow("center2");
        
        // moveWindow("center",500,0);
        // moveWindow("center2",700,0);
        moveWindow("Frame",0,0);
        // moveWindow("left",200,0);
        // moveWindow("right",600,0);
        
        // imshow("left",centerROI);
        // imshow("right",poly_roi2);
        // imshow("center",centerROI);
        // imshow("center2",centerROI2);
        imshow("Frame",frame);
        waitKey(1000/cap.get(CAP_PROP_FPS));
        //waitKey(1000);
    }

    return 0;
}