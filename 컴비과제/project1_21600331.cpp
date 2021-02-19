#include "opencv2/opencv.hpp"
#include "iostream"
#include "ctime"

using namespace cv;
using namespace std;

int main(){
    Mat lena;
    lena = imread("lena.png", 1);
    if(lena.empty()){
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    namedWindow("lena", WINDOW_AUTOSIZE);
    imshow("lena", lena);
    Mat lenaChannels[3];

    Mat colorful(200,200,CV_8UC3);
    colorful = imread("colorful.jpg", 1);
    if(colorful.empty()){
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    namedWindow("colorful", WINDOW_NORMAL);
    resizeWindow("colorful",200,200);
    imshow("colorful", colorful);
    Mat colorfulChannels[3];

    Mat balancing;
    balancing = imread("balancing.jpg", 1);
    if(balancing.empty()){
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    resize(balancing, balancing, Size(balancing.cols/2, balancing.rows/2));
    namedWindow("balancing", WINDOW_NORMAL);
    imshow("balancing", balancing);
    Mat balancingChannels[3];
    float channelAverages[3];
    int channelValues[3];

    while(1){
        //0의미는 영원히 기다린다.
        int a = waitKey();
        //cout << a << endl;
        if (a == 114){
            lena = imread("lena.png",1);
            imshow("lena", lena);
            balancing = imread("balancing.jpg", 1);
            resize(balancing, balancing, Size(balancing.cols/2, balancing.rows/2));
            imshow("balancing", balancing);
            colorful = imread("colorful.jpg", 1);
            imshow("colorful", colorful);
        }
        else if(a == 110){
            cvtColor(lena,lena,CV_BGR2HSV,0);
            split(lena,lenaChannels);

            for(int i=0;i<lenaChannels[2].cols;i++){
                for(int j=0;j<lenaChannels[2].rows;j++){
                    lenaChannels[2].at<uchar>(i,j) = 255 - lenaChannels[2].at<uchar>(i,j);
                }   
            }  

            merge(lenaChannels,3,lena);

            cvtColor(lena,lena,CV_HSV2BGR,0);

            imshow("lena",lena);     
        }

        else if(a == 103){
            cvtColor(lena,lena,CV_BGR2HSV,0);
            split(lena,lenaChannels);

            MatIterator_<uchar> it, end;
            float gamma = 2.5;
            unsigned char pix[256];
            for (int i = 0; i < 256; i++) {
            
            pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
            }
            for (it = lenaChannels[2].begin<uchar>(), end = lenaChannels[2].end<uchar>(); it != end; it++) {
            *it = pix[(*it)];
            }

            merge(lenaChannels,3,lena);

            cvtColor(lena,lena,CV_HSV2BGR,0);

            imshow("lena",lena);     
        }

        else if(a == 104){
            cvtColor(lena,lena,CV_BGR2HSV,0);
            split(lena,lenaChannels);

            equalizeHist(lenaChannels[2],lenaChannels[2]);

            merge(lenaChannels,3,lena);

            cvtColor(lena,lena,CV_HSV2BGR,0);

            imshow("lena",lena);     
        }

        else if(a == 97){
            cvtColor(balancing,balancing,CV_BGR2HSV,0);
            split(balancing,balancingChannels);

            blur(balancingChannels[2],balancingChannels[2],Size(9,9)); 
            for(int i=lena.cols/2;i<512;i++){
                for(int j=0;j<512;j++){
                    balancingChannels[2].at<uchar>(j,i) = balancingChannels[2].at<uchar>(j,i);
                }
            }

            merge(balancingChannels,3,balancing);

            cvtColor(balancing,balancing,CV_HSV2BGR,0);

            imshow("balancing",balancing);     
        }

        else if(a == 119){
            for(int i=0;i<3;i++){
                channelAverages[i] = 0;
                channelValues[i] = 0;
            }

            balancing.convertTo(balancing,CV_32FC3);
            
            split(balancing,balancingChannels);

            for(int k=0;k<3;k++){
                for(int i=0;i<balancingChannels[k].rows;i++){
                    for(int j=0;j<balancingChannels[k].cols;j++){
                        channelValues[k]+=balancingChannels[k].at<float>(i,j);
                    }
                }
            }

            for(int k=0;k<3;k++){
                channelAverages[k]= (double)channelValues[k] / (balancingChannels[k].cols * balancingChannels[k].rows) ;
            }
            for(int k=0;k<3;k++){
                for(int i=0;i<balancingChannels[k].rows;i++){
                    for(int j=0;j<balancingChannels[k].cols;j++){
                        balancingChannels[k].at<float>(i,j) = 128/channelAverages[k] * balancingChannels[k].at<float>(i,j);
                    }
                }
            }

            merge(balancingChannels,3,balancing);

            convertScaleAbs(balancing, balancing);

            imshow("balancing",balancing);     
        }

        else if(a == 115){
            cvtColor(colorful,colorful,CV_BGR2HSV,0);
            split(colorful,colorfulChannels);

            for(int i=0;i<colorfulChannels[0].rows;i++){
                for(int j=0;j<colorfulChannels[0].cols;j++){
                    if(9<colorfulChannels[0].at<uchar>(i,j) && colorfulChannels[0].at<uchar>(i,j)<23){
                    }  
                    else{
                        colorfulChannels[1].at<uchar>(i,j)=0;
                    }
                }
            }


            merge(colorfulChannels,3,colorful);

            cvtColor(colorful,colorful,CV_HSV2BGR,0);

            imshow("colorful",colorful);     
        }

        else if(a == 99){
            cvtColor(colorful,colorful,CV_BGR2HSV,0);
            split(colorful,colorfulChannels);

            for(int i=0;i<colorfulChannels[0].rows;i++){
                for(int j=0;j<colorfulChannels[0].cols;j++){
                    
                    if(129<colorfulChannels[0].at<uchar>(i,j)){
                        colorfulChannels[0].at<uchar>(i,j) -= 129;
                    }  
                    else{
                        colorfulChannels[0].at<uchar>(i,j) += 50;
                    }
                }
            }


            merge(colorfulChannels,3,colorful);

            cvtColor(colorful,colorful,CV_HSV2BGR,0);

            imshow("colorful",colorful);     
        }

    }

}