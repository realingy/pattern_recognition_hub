#ifndef __CONNECT_REGION__
#define __CONNECT_REGION__

#include <iostream>
#include <stack>
#include <opencv2/opencv.hpp>

// 基于4邻域或者8领域的方式，进行液滴区域的标记
int ConnectRegion(cv::Mat src, int ConnectBodyNumber, int x, int y);
void Seed_Filling(const cv::Mat& binImg, cv::Mat& labelImg); //种子填充法
void Two_Pass(const cv::Mat& binImg, cv::Mat& labelImg); //两遍扫描法
void LabelColor(const cv::Mat& label, cv::Mat& colorLabel);

#endif
