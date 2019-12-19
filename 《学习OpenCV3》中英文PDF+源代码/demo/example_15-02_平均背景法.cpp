// ѧϰһ������ģ����ʶ��ǰ������
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

// Ϊ���б�Ҫ�м���ʱͼƬ�����ڴ�ĺ���
// Ϊ�������������һ��ͼƬ����(����Ƶ��ȡ��)�����ͼƬ����ֻ����ָ����ʱͼƬ�Ĵ�С
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

// �ۼƱ���ͼƬ���ۼƾ���ֵ֡����
// I: CV_8UC3���͵Ĳ�ɫͼ
void accumulateBackground( cv::Mat& I )
{
	static int first = 1; // nb. Not thread safe
	I.convertTo( tmp, CV_32F ); // convert to float
	if( !first ){
		IavgF += tmp; //����֡�ۼ�
		Icount += 1.0; //֡����һ�������ֵʱ�õ���
		cv::absdiff( tmp, IprevF, tmp2 ); //����֡����
		IdiffF += tmp2; //�ۼ�֡����
	}
	first = 0;
	IprevF = tmp;
}

// ��������֡��ƽ�����Բ���������ֵ
// �Բ��ͼ�����ӽ������ţ�Ȼ������ƽ��ͼ�ϼ��ϻ��߼�ȥ��������ͨ��cv::sp1it()��IhiF����IlowFӦ����ͼ���ÿ��ͨ��
// IdiffF������Ϊ�����ж����������Ƿ�������Եľ��������

// ��ʾ�ڸ���ƽ��ֵscale��IdiffF�����ر���Ϊ��ǰ��
void setHighThreshold( float scale ) {
	IhiF = IavgF + (IdiffF * scale);
	cv::split( IhiF, Ihi );
}

// ��ʾ�ڵ���ƽ��ֵscale��IdiffF�����ر���Ϊ��ǰ��
void setLowThreshold( float scale ) {
	IlowF = IavgF - (IdiffF * scale);
	cv::split( IlowF, Ilow );
}

// �ۼ����㹻���֡�����ǾͿ��Խ���ת��Ϊ������һ��ͳ��ģ�ͣ�������ÿ�����صľ�ֵ��ƫ��ֵ(ƽ�����Բ�)
void createModelsfromStats() {
	IavgF *= (1.0/Icount); //֡�ľ�ֵ
	IdiffF *= (1.0/Icount); //֡��ƽ�����
	
	// ��������ƽ����ͼ���е�ֵ����Ϊ1�������������������ֵ������ȵ����
	IdiffF += cv::Scalar( 1.0, 1.0, 1.0 );
	setHighThreshold( high_thresh);
	setLowThreshold( low_thresh);
}

// Create a binary: 0,255 mask where 255 (red) means foreground pixel
// I      Input image, 3-channel, 8u
// Imask  Mask image to be created, 1-channel 8u
// ��ͨ��Mat::convertTo()������ͼƬI(���ָ�ͼƬ)ת��Ϊһ��������ͼƬ��Ȼ��ʹ��cv::split()����ͨ��ͼƬ��Ϊ������ͨ��ͼƬ��
// �����������Ƕ�ÿ��ͨ���ֱ���д���ʹ��cv::inRange()���ж�ÿ�������ǹ�λ�ڱ����ĸߵ���ֵ֮�䣬
// ��������Ӧ��8λ�Ҷ�ͼImask�е�λ����Ϊ255��ǰ��������Ϊ0
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

	// ѵ��֡��
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
	// һ���õ�����ģ�ͣ���ɸߵ���ֵ���趨�����ǾͿ���ʹ������ͼ�����ǰ��(���Ǳ����Ĳ���)�ͱ���(����ֵλ�ڱ���ģ�͵ĸߵ���ֵ֮��Ĳ���)�ķָ
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
