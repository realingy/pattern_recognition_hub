// 帧间差分法
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;

int N = 4; //N帧的帧间差分

int main()
{
	using namespace cv;

	cv::VideoCapture cap;
	if (!cap.open("test.avi"))
	{
		cerr << "Couldn't open video file" << endl;
		return -1;
	}

	vector<Mat> frames;
	for (int i = 1; ; i++)
	{
		Mat frame, frame_gray;
		cap >> frame;
		if( !frame.data ) break;
		if (i > 10 && i <= 10 + N)
		{
			cvtColor(frame, frame_gray, CV_RGB2GRAY); // 将彩色图像转换为灰度图像;
			frames.push_back(frame_gray);
		}
	}

	int row = frames[0].rows;
	int col = frames[0].cols;

	vector<Mat> alldiff(N-1, Mat(row, col, CV_8UC1)); // 生成一个Mat容器alldiff用于存储最终的各个帧的差分结果        

	for (int i = 0; i < N - 1; i++)
	{
		Mat diff = Mat(row, col, CV_8UC1);
		absdiff(frames[i], frames[i+1], diff); //帧间差分
		threshold(diff, diff, 20, 255, CV_8UC1); //二值化
		alldiff.push_back(~diff);
		string n = to_string(i);
		string name = "diff_" + n + ".jpg";
		imwrite(name, ~diff);
	}

	waitKey(0);

	return 0;
}
