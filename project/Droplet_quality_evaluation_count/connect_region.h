#ifndef __CONNECT_REGION__
#define __CONNECT_REGION__

#include <iostream>
#include <stack>
#include <opencv2/opencv.hpp>

// ����4�������8����ķ�ʽ������Һ������ı��
int ConnectRegion(cv::Mat src, int ConnectBodyNumber, int x, int y);
void Seed_Filling(const cv::Mat& binImg, cv::Mat& labelImg); //������䷨
void Two_Pass(const cv::Mat& binImg, cv::Mat& labelImg); //����ɨ�跨
void LabelColor(const cv::Mat& label, cv::Mat& colorLabel);

#endif
