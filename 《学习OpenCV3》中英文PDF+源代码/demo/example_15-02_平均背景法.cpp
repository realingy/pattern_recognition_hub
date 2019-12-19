// 学习一个背景模型来识别前景像素
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

// Float, 3-channel
cv::Mat frame;
cv::Mat IavgF, IdiffF, IprevF, IhiF, IlowF;
cv::Mat tmp, tmp2, mask;

// Float, 1-channel
vector<cv::Mat> Igray(3);
vector<cv::Mat> Ilow(3);
vector<cv::Mat> Ihi(3);

// Byte, 1-channel
cv::Mat Imaskt;

// Thresholds
float high_thresh = 20.0;
float low_thresh = 28.0;

// Counts number of images learned for averaging later
float Icount;

// 为所有必要中间临时图片申请内存的函数
// 为方便起见，传入一个图片参数(从视频中取得)，这个图片参数只用于指定临时图片的大小
void AllocateImages( const cv::Mat& I ) {
	cv::Size sz = I.size();
	IavgF = cv::Mat::zeros(sz, CV_32FC3 );
	IdiffF = cv::Mat::zeros(sz, CV_32FC3 );
	IprevF = cv::Mat::zeros(sz, CV_32FC3 );
	IhiF = cv::Mat::zeros(sz, CV_32FC3 );
	IlowF = cv::Mat::zeros(sz, CV_32FC3 );
	Icount = 0.00001; // Protect against divide by zero
	tmp = cv::Mat::zeros( sz, CV_32FC3 );
	tmp2 = cv::Mat::zeros( sz, CV_32FC3 );
	Imaskt = cv::Mat( sz, CV_32FC1 );
}

// 累计背景图片和累计绝对值帧间差分
// I: CV_8UC3类型的彩色图
void accumulateBackground( cv::Mat& I )
{
	static int first = 1; // nb. Not thread safe
	I.convertTo( tmp, CV_32F ); // convert to float
	if( !first ){
		IavgF += tmp; //背景帧累加
		Icount += 1.0; //帧数加一（计算均值时用到）
		cv::absdiff( tmp, IprevF, tmp2 ); //计算帧间差分
		IdiffF += tmp2; //累加帧间差分
	}
	first = 0;
	IprevF = tmp;
}

// 用来根据帧间平均绝对差来设置阈值
// 对差分图按因子进行缩放，然后将它从平均图上加上或者减去。接下来通过cv::sp1it()把IhiF或者IlowF应用于图像的每个通道
// IdiffF可以视为用来判断两个数据是否差异明显的距离度量，

// 表示在高于平均值scale倍IdiffF的像素被认为是前景
void setHighThreshold( float scale ) {
	IhiF = IavgF + (IdiffF * scale);
	cv::split( IhiF, Ihi );
}

// 表示在低于平均值scale倍IdiffF的像素被认为是前景
void setLowThreshold( float scale ) {
	IlowF = IavgF - (IdiffF * scale);
	cv::split( IlowF, Ilow );
}

// 累加了足够多的帧，我们就可以将其转化为背景的一个统计模型，即计算每个像素的均值和偏移值(平均绝对差)
void createModelsfromStats() {
	IavgF *= (1.0/Icount); //帧的均值
	IdiffF *= (1.0/Icount); //帧间平均差分
	
	// 我们限制平均差图像中的值至少为1，以免出现上下两个阈值正好相等的情况
	IdiffF += cv::Scalar( 1.0, 1.0, 1.0 );
	setHighThreshold( high_thresh);
	setLowThreshold( low_thresh);
}

// Create a binary: 0,255 mask where 255 (red) means foreground pixel
// I      Input image, 3-channel, 8u
// Imask  Mask image to be created, 1-channel 8u
// 先通过Mat::convertTo()将输入图片I(待分割图片)转化为一个浮点型图片。然后使用cv::split()将三通道图片分为三个单通道图片。
// 接下来，我们对每个通道分别进行处理，使用cv::inRange()以判断每个像素是够位于背景的高低阙值之间，
// 将背景对应的8位灰度图Imask中的位置置为255，前景部分置为0
// 
void backgroundDiff(
		cv::Mat& I,
		cv::Mat& Imask)
{
	I.convertTo( tmp, CV_32F ); // To float
	cv::split( tmp, Igray );
	
	// Channel 1
	cv::inRange( Igray[0], Ilow[0], Ihi[0], Imask );

	// Channel 2
	cv::inRange( Igray[1], Ilow[1], Ihi[1], Imaskt );
	Imask = cv::min( Imask, Imaskt );

	// Channel 3
	cv::inRange( Igray[2], Ilow[2], Ihi[2], Imaskt );
	Imask = cv::min( Imask, Imaskt );

	// Finally, invert the results
	Imask = 255 - Imask;
}

///////////////////
void help(char** argv ) {
	cout << "\n"
	<< "Train a background model on  the first <#frames to train on> frames of an incoming video, then run the model\n"
	<< argv[0] <<" <#frames to train on> <avi_path/filename>\n"
	<< "For example:\n"
	<< argv[0] << " 50 ../tree.avi\n"
	<< "'A' or 'a' to adjust thresholds, esc, 'q' or 'Q' to quit"
	<< endl;
}

void showForgroundInRed( char** argv, const cv::Mat &img) {
		cv::Mat rawImage;
		cv::split( img, Igray );
		Igray[2] = cv::max( mask, Igray[2] );
		cv::merge( Igray, rawImage );
		cv::imshow( argv[0], rawImage );
		cv::imshow("Segmentation", mask);
}

void adjustThresholds(char** argv, cv::Mat &img) {
	int key = 1;
	while((key = cv::waitKey()) != 27 && key != 'Q' && key != 'q')  // Esc or Q or q to exit
	{
		if(key == 'L') { low_thresh += 0.2;}
		if(key == 'l') { low_thresh -= 0.2;}	
		if(key == 'H') { high_thresh += 0.2;}
		if(key == 'h') { high_thresh -= 0.2;}
		cout << "H or h, L or l, esq or q to quit;  high_thresh = " << high_thresh << ", " << "low_thresh = " << low_thresh << endl;
		setHighThreshold(high_thresh);
		setLowThreshold(low_thresh);
		backgroundDiff(img, mask);
		showForgroundInRed(argv, img);
	}
}

int main( int argc, char** argv)
{
	// cv::namedWindow( "E15_2", cv::WINDOW_AUTOSIZE );

	cv::VideoCapture cap;
	if( !cap.open("test.avi") )
	{
		cerr << "Couldn't run the program" << endl;
		cap.open(0);
		return -1;
	}

	// 训练帧数
	int number_to_train_on = 20;

	// FIRST PROCESSING LOOP (TRAINING):
	//
	int frame_count = 0;
	int key;
	bool first_frame = true;
	cout << "Total frames to train on = " << number_to_train_on << endl; //db

	while(1) {
		cout << "frame#: " << frame_count << endl;
		cap >> frame;
		if( !frame.data ) exit(1); // Something went wrong, abort
		if(frame_count == 0) { AllocateImages(frame);}
		accumulateBackground( frame );
		// cv::imshow( "E15_2", frame );
		frame_count++;
		if( (key = cv::waitKey(7)) == 27 || key == 'q' || key == 'Q' || frame_count >= number_to_train_on) break; //Allow early exit on space, esc, q
	}

	// We have accumulated our training, now create the models
	//
	cout << "Creating the background model" << endl;
	createModelsfromStats();
	cout << "Done!  Hit any key to continue into single step. Hit 'a' or 'A' to adjust thresholds, esq, 'q' or 'Q' to quit\n" << endl;
	
	// SECOND PROCESSING LOOP (TESTING):
	// 一旦得到背景模型，完成高低阈值的设定，我们就可以使用它对图像进行前景(不是背景的部分)和背景(像素值位于背景模型的高低阈值之间的部分)的分割。
	cv::namedWindow("Segmentation", cv::WINDOW_AUTOSIZE ); //For the mask image
	while((key = cv::waitKey()) != 27 || key == 'q' || key == 'Q'  ) { // esc, 'q' or 'Q' to exit
		cap >> frame;
		if( !frame.data ) exit(0);
		cout <<  frame_count++ << endl;
		backgroundDiff( frame, mask );
		cv::imshow("Segmentation", mask);

		// A simple visualization is to write to the red channel
		//
		showForgroundInRed( argv, frame);
		if(key == 'a') {
			cout << "In adjust thresholds, 'H' or 'h' == high thresh up or down; 'L' or 'l' for low thresh up or down." << endl;
			cout << " esq, 'q' or 'Q' to quit " << endl;
			adjustThresholds(argv, frame);
			cout << "Done with adjustThreshold, back to frame stepping, esq, q or Q to quit." << endl;
		}
	}
	exit(0);
}
