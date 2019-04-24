//#include<iostream>
//#include"opencv2/core/core.hpp"
//#include"opencv2/highgui/highgui.hpp"
//#include"opencv2/imgproc/imgproc.hpp"
//#include <opencv2/photo.hpp>
//#include "opencv2/imgcodecs.hpp"
//#include <vector>
//#include <fstream>
//
//using namespace cv;
//using namespace std;
//void MyGammaCorrection(Mat& src, Mat& dst, float fGamma);
//int main()
//{
////std::cout<<"hello"<<std::endl;
//Mat src = imread("D:\\visual studio 2012_Projects\\Projects\\ConsoleApplication2\\ConsoleApplication2\\2.jpg");
////namedWindow("src_img");
////imshow("src_img",src);
////waitKey(1000);
//Mat hsv;
//cvtColor(src,hsv,COLOR_BGR2HSV);
//
//vector<Mat> hsv_vec;
//split(hsv,hsv_vec);
//Mat v;
//v = hsv_vec[2];
//Mat dst_v1, dst_v2;
//double time0  = static_cast<double>(getTickCount());
//MyGammaCorrection(v, dst_v1, 0.5);
//MyGammaCorrection(v, dst_v2, 2);
//time0 = ((double)getTickCount()-time0)/getTickFrequency();
//cout<<"the processing time is:"<<time0<<"秒"<<endl;
////namedWindow("vvv",1);
////imshow("vvv",dst_v1);
////waitKey(3000);
////namedWindow("vv",1);
////imshow("vv",dst_v2);
////waitKey(3000);
//time0  = static_cast<double>(getTickCount());
//vector<Mat> images;
////合并通道
//vector<Mat> low_images;
//for(int i =0;i<2;i++)
//	low_images.push_back(hsv_vec[i]);
//low_images.push_back(dst_v2);
//
//vector<Mat> high_images;
//for(int i =0;i<2;i++)
//	high_images.push_back(hsv_vec[i]);
//high_images.push_back(dst_v1);
//
//Mat low,middle,high;
//merge(low_images,low);
//merge(hsv_vec,middle);
//merge(high_images,high);
//cvtColor(low,low,COLOR_HSV2BGR);
//cvtColor(middle,middle,COLOR_HSV2BGR);
//cvtColor(high,high,COLOR_HSV2BGR);
//
//images.push_back(low);
//images.push_back(middle);
//images.push_back(high);
//time0 = ((double)getTickCount()-time0)/getTickFrequency();
//cout<<"the processing time is:"<<time0<<"秒"<<endl;
//time0  = static_cast<double>(getTickCount());
//Mat fusion;
//Ptr<MergeMertens> merge_mertens = createMergeMertens();
//merge_mertens->process(images, fusion);
//time0 = ((double)getTickCount()-time0)/getTickFrequency();
//cout<<"the processing time is:"<<time0<<"秒"<<endl;
//namedWindow("v",1);
//imshow("v",fusion);
//waitKey(3000);
//
//system("pause");
//return 0;
//}
//
//
//void MyGammaCorrection(Mat& src, Mat& dst, float fGamma)  
//{  
//    unsigned char lut[256];  
//    for( int i = 0; i < 256; i++ )  
//    {  
//        lut[i] = saturate_cast<uchar>(pow((float)(i/255.0), fGamma) * 255.0f);  
//    }  
//    dst = src.clone();  
//    const int channels = dst.channels();  
//    MatIterator_<uchar> it, end;  
//    for( it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++ )  
//        *it = lut[(*it)];  
//
//}

#include"HDR.h"

int main()
{
Mat src = imread("2.jpg");
Mat hsv;
double time0  = static_cast<double>(getTickCount());
cvtColor(src,hsv,COLOR_BGR2HSV);
time0 = ((double)getTickCount()-time0)/getTickFrequency();
cout<<"the processing time is:"<<time0<<"秒"<<endl;
time0  = static_cast<double>(getTickCount());
Mat dst = exposure_fusion(hsv);
time0 = ((double)getTickCount()-time0)/getTickFrequency();
cout<<"the processing time is:"<<time0<<"秒"<<endl;
namedWindow("res");
imshow("res",dst);
waitKey(3000);
system("pause");
return 0;
}