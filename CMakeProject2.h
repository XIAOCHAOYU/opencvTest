// CMakeProject2.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>

// TODO: 在此处引用程序需要的其他标头。

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>

#include <io.h>

#include <fcntl.h>

using namespace std;
using namespace cv;


Mat getGray(const Mat& mat);
int get_Value(int value);

//浮雕的函数
cv::Mat Relief(cv::Mat src);
cv::Mat Sculpture(cv::Mat src);
cv::Mat Relief_Gray_one(cv::Mat src);
cv::Mat Relief_Gray(cv::Mat src);


//扩散的函数  遵循从左到右，从上到下
cv::Mat Diffuser(cv::Mat src, vector<int> &value_List,int value);

cv::Mat Diffuser_Halftone(cv::Mat src);
cv::Mat Diffuser(cv::Mat src);


cv::Mat Diffuser_FloydSteinberg(cv::Mat src);



cv::Mat Diffuser_Burkes(cv::Mat src);

cv::Mat Diffuser_Jarris(cv::Mat src);

cv::Mat Diffuser_Sierra(cv::Mat src);

cv::Mat Diffuser_Two_row_Sierra(cv::Mat src);

cv::Mat Diffuser_Sierra_Lite(cv::Mat src);

cv::Mat Diffuser_Atkinson(cv::Mat src);


Mat setDither_Threshold(const Mat& mat);

Mat setDither_Screw(const Mat& mat);


Mat setDither_CoarseFatting(const Mat& mat);


Mat setDither_Screening_Zero(const Mat& mat);


Mat setDither_Screening_Fifteen(const Mat& mat);

Mat setDither_Screening_forty_five(const Mat& mat);



Mat setDither_Seventy_five(const Mat& mat);





//图像操作
bool SetResolution(const char* path, int iResolution);




//局部二值化算法
Mat Threshold_AdaptiveThreshold(Mat& mat);



//边缘提边

Mat GetOutlineCanny(Mat& mat,int value_low,int value_hight);

