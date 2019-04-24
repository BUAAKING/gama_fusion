#ifndef __HDR__
#define __HDR__

#include<iostream>
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include <opencv2/photo.hpp>
#include "opencv2/imgcodecs.hpp"
#include <vector>
#include <fstream>
using namespace cv;
using namespace std;

Mat exposure_fusion(Mat &src);
void MyGammaCorrection(Mat& src, Mat& dst, float fGamma,Mat& dst1, float fGamma1);

#endif