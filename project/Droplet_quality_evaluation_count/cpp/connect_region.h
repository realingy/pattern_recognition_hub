#ifndef __CONNECT_REGION__
#define __CONNECT_REGION__

#include <iostream>
#include <opencv2/opencv.hpp>

// 基于4邻域或者8领域的方式，进行液滴区域的标记
int ConnectRegion(cv::Mat src, int ConnectBodyNumber, int x, int y);

#endif
