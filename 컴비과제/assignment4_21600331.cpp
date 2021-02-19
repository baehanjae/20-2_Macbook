#include "opencv2/opencv.hpp"
#include "iostream"
#include "ctime"

using namespace cv;
using namespace std;

Mat drawHistogram(Mat src);
Mat drawHistogram2(Mat src);

int main(){

    Mat before;

    before = imread("moon.png",0);

    //nomallization
    Mat after;
    equalizeHist(before,after);

    //putText()

    int w = before.cols;
    int h = before.rows;
    Mat hist = drawHistogram2(before);
    Mat hist2 = drawHistogram2(after);
    for(int i=0;i<8;i++){
        putText(before, format("bin %d : %.3f", i+1, hist.at<float>(i)/100000),
            Point(10, 30+i*30), 20, 
            1,Scalar(255, 200, 200), 4);
    }
    for(int i=0;i<8;i++){
        putText(after, format("bin %d : %.3f", i+1, hist2.at<float>(i)/100000),
        Point(10, 30+i*30), 100, 
        1,Scalar(255, 200, 200), 4);
    }   
    
    imshow("before",before);
    imshow("after",after);

    //histogram display
    Mat h1(512,512,CV_8U);
    Mat h2(512,512,CV_8U);

    

    h1 = drawHistogram(before);
    h2 = drawHistogram(after);
    
    imshow("h1",h1);
    imshow("h2",h2);
    
    waitKey(0);
    return 0;

}



Mat drawHistogram(Mat src){
    Mat hist, histImage;
    // establish the number of bins
    int i, hist_w, hist_h, bin_w, histSize;
    float range[] = { 0, 255 };
    const float* histRange = { range };
    hist_w = 512;
    hist_h = 512;
    histSize = 16;
    bin_w = cvRound((double)hist_w / histSize);
    //draw the histogram
    histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    // compute the histograms
    // &src: input image, 1: #of src image, 0: #of channels numerated from 0 ~ channels()-1, Mat(): optional mask
    // hist: output histogram, 1: histogram dimension, &histSize: array of histogram size, &histRange: array of histogram’s boundaries
    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);
    // Fit the histogram to [0, histImage.rows]
    // hist: input Mat, hist: output Mat, 0: lower range boundary of range normalization, histImage.rows: upper range boundary
    // NORM_MINMAX: normalization type, -1: when negative, the ouput array has the same type as src, Mat(): optional mask
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    for (i = 0; i < histSize; i++)
    {
        rectangle(histImage, Point(bin_w * i, hist_h), Point(bin_w * i+hist_w/histSize, hist_h - cvRound(hist.at<float>(i))), Scalar(0, 0, 0), -1);
    }
    return histImage;
}

Mat drawHistogram2(Mat src){
    Mat hist, histImage;
    // establish the number of bins
    int i, hist_w, hist_h, bin_w, histSize;
    float range[] = { 0, 255 };
    const float* histRange = { range };
    hist_w = 512;
    hist_h = 512;
    histSize = 8;
    bin_w = cvRound((double)hist_w / histSize);
    //draw the histogram
    histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    // compute the histograms
    // &src: input image, 1: #of src image, 0: #of channels numerated from 0 ~ channels()-1, Mat(): optional mask
    // hist: output histogram, 1: histogram dimension, &histSize: array of histogram size, &histRange: array of histogram’s boundaries
    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);
    // Fit the histogram to [0, histImage.rows]
    // hist: input Mat, hist: output Mat, 0: lower range boundary of range normalization, histImage.rows: upper range boundary
    // NORM_MINMAX: normalization type, -1: when negative, the ouput array has the same type as src, Mat(): optional mask
    //normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    
    return hist;
}