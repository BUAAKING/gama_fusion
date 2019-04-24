#include "HDR.h"

Mat exposure_fusion(Mat &hsv)
{
////correction
//Mat hsv;
//double time0  = static_cast<double>(getTickCount());
//cvtColor(src,hsv,COLOR_BGR2HSV);
//time0 = ((double)getTickCount()-time0)/getTickFrequency();
//cout<<"the split_channel time is:"<<time0<<"秒"<<endl;
vector<Mat> hsv_vec;
split(hsv,hsv_vec);

Mat v;
v = hsv_vec[2];
int flag =0;
Mat dst_v1, dst_v2;

if(flag == 1)
{
	MyGammaCorrection(v, dst_v1, 0.5, dst_v2, 2);
}
if(flag ==0)
{
double time0  = static_cast<double>(getTickCount());
v.convertTo(v, CV_32FC1,1/255.0);
pow(v,0.5,dst_v1);
pow(v,2,dst_v2);
dst_v1.convertTo(dst_v1,CV_8UC1,255.0);
dst_v2.convertTo(dst_v2,CV_8UC1,255.0);
v.convertTo(v, CV_8UC1,255.0);
time0 = ((double)getTickCount()-time0)/getTickFrequency();
cout<<"the gamma time is:"<<time0<<"秒"<<endl;
}
double time0  = static_cast<double>(getTickCount());
//合并通道
vector<Mat> low_images;
for(int i =0;i<2;i++)
	low_images.push_back(hsv_vec[i]);
low_images.push_back(dst_v2);

vector<Mat> high_images;
for(int i =0;i<2;i++)
	high_images.push_back(hsv_vec[i]);
high_images.push_back(dst_v1);
Mat low,middle,high;
merge(low_images,low);
merge(hsv_vec,middle);
merge(high_images,high);
time0 = ((double)getTickCount()-time0)/getTickFrequency();
cout<<"the merge_channel time is:"<<time0<<"秒"<<endl;
//HSV2BGR
time0  = static_cast<double>(getTickCount());
cvtColor(low,low,COLOR_HSV2BGR);
cvtColor(middle,middle,COLOR_HSV2BGR);
cvtColor(high,high,COLOR_HSV2BGR);

vector<Mat> images;
images.push_back(low);
images.push_back(middle);
images.push_back(high);
time0 = ((double)getTickCount()-time0)/getTickFrequency();
cout<<"the convet time is:"<<time0<<"秒"<<endl;
//fusion
Mat fusion;
time0  = static_cast<double>(getTickCount());
Ptr<MergeMertens> merge_mertens = createMergeMertens();
merge_mertens->process(images, fusion);
time0 = ((double)getTickCount()-time0)/getTickFrequency();
cout<<"the merge time is:"<<time0<<"秒"<<endl;
return fusion;
}

void MyGammaCorrection(Mat& src, Mat& dst_low, float fGamma_low, Mat& dst_high, float fGamma_high)  
{  
    unsigned char lut_low[256];  
	unsigned char lut_high[256];
	double time0  = static_cast<double>(getTickCount());
    for( int i = 0; i < 256; i++ )  
    {  
        lut_low[i] = saturate_cast<uchar>(pow((float)(i/255.0), fGamma_low) * 255.0f);  
		lut_high[i] = saturate_cast<uchar>(pow((float)(i/255.0), fGamma_high) * 255.0f);  
    }

    dst_low = src.clone();  
	dst_high = src.clone(); 
    const int channels_low = dst_low.channels();  
	const int channels_high = dst_high.channels(); 
    MatIterator_<uchar> it_low, end_low;  
	MatIterator_<uchar> it_high, end_high;
    for( it_low = dst_low.begin<uchar>(), end_low = dst_low.end<uchar>(),it_high = dst_high.begin<uchar>(),
		end_high = dst_high.end<uchar>(); it_low != end_low, it_high != end_high; it_low++,it_high++ )  
	{
		*it_low = lut_low[(*it_low)];
		*it_high = lut_low[(*it_high)];
	}  
	time0 = ((double)getTickCount()-time0)/getTickFrequency();
    cout<<"the processing time is:"<<time0<<"秒"<<endl;
}

