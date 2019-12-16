#include "k-mean.h"
#include <vector>
#include <iostream>

void GaussianBlur(cv::Mat& src, cv::Mat& dst);
void do_kmean(cv::Mat src);

void kmean()
{
	using namespace cv;
	Mat img = imread("bean.JPG");
	namedWindow("Source Image", CV_WINDOW_NORMAL);
	imshow("Source Image", img);

	//����һά������,��������ͼ�����ص�,ע��������ʽΪ32bit�������� 
	Mat samples(img.cols * img.rows, 1, CV_32FC3);

	//��Ǿ���32λ���� 
	Mat labels(img.cols * img.rows, 1, CV_32SC1);

	uchar* p;
	int k = 0;
	for (int i = 0; i < img.rows; i++)
	{
		p = img.ptr<uchar>(i);
		for (int j = 0; j < img.cols; j++)
		{
			samples.at<Vec3f>(k, 0)[0] = float(p[j * 3]);
			samples.at<Vec3f>(k, 0)[1] = float(p[j * 3 + 1]);
			samples.at<Vec3f>(k, 0)[2] = float(p[j * 3 + 2]);
			k++;
		}
	}

	// int clusterCount = 4; //�������ĸ���
	int clusterCount = 2; //�������ĸ���
	Mat centers(clusterCount, 1, samples.type());
	kmeans(samples, clusterCount, labels,
		TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0),
		3, KMEANS_PP_CENTERS, centers);

	// ������֪��2������(ǰ���ͱ���)���ò�ͬ�ĻҶȲ��ʾ�� 
	Mat img1(img.rows, img.cols, CV_8UC1);
	float step = 255 / (clusterCount - 1);
	k = 0;
	for (int i = 0; i < img1.rows; i++)
	{
		p = img1.ptr<uchar>(i);
		for (int j = 0; j < img1.cols; j++)
		{
			int tt = labels.at<int>(k, 0);
			k++;
			p[j] = 255 - tt * step;
		}
	}

	namedWindow("K-Means�ָ�Ч��", CV_WINDOW_NORMAL);
	imshow("K-Means�ָ�Ч��", img1);
}

/*
void kmean()
{
	using namespace cv;
	Mat src_rgb = imread("bean.JPG");
	if (!src_rgb.data) {
		std::cout << "open image error!" << std::endl;
		return;
	}

	//namedWindow("src", CV_WINDOW_AUTOSIZE);
	namedWindow("src_rgb", CV_WINDOW_NORMAL);
	imshow("src_rgb", src_rgb);

	// ƽ��ȥ��
	GaussianBlur(src_rgb, src_rgb);

	// ����ɫͼ���RGBת����lab��ɫ�ռ�
	Mat src_lab;
	cv::cvtColor(src_rgb, src_lab, CV_BGR2Lab);

	// ����K-mean���ཫͼ��ָ��2������
	do_kmean(src_lab);
}
*/

void do_kmean(cv::Mat src)
{
	std::vector<cv::Mat> channels;

	// ȡ��lab�ռ��a������b����
	cv::split(src, channels);

	/*
	cv::Mat a = channels[1];
	cv::Mat b = channels[2];
	*/
	cv::Mat ab;
	channels[0] = 0;
	merge(channels, ab);

	int rows = ab.rows;
	int cols = ab.cols;

	cv::resize(ab, ab, cv::Size(2, 2));

//ab = reshape(ab, nrows * ncols, 2)

	int colors = 4; // �ָ���������Ϊ4

	/*
	[cluster_idx, cluster_center] = kmeans(ab, nColors, 'distance', 'sqEuclidean', 'Replicates', 2) # �ظ�����2��
	pixel_labels = reshape(cluster_idx, nrows, ncols)
	*/


}

// ��˹ƽ��ȥ��
void GaussianBlur(cv::Mat& src, cv::Mat& dst)
{
	// ƽ��ȥ��
	std::vector<cv::Mat> channels;

	split(src, channels);

	/*
	cv::imshow("b", channels[0]);
	cv::imshow("g", channels[1]);
	cv::imshow("r", channels[2]);
	*/

	/*
	channel_m[0] = channels[0];
	channel_m[1] = channels[1];
	channel_m[2] = channels[2];
	*/

	/*
	cv::GaussianBlur(channels[0], channels[0], cv::Size(3, 3), 2.0);
	cv::GaussianBlur(channels[1], channels[1], cv::Size(3, 3), 2.0);
	cv::GaussianBlur(channels[2], channels[2], cv::Size(3, 3), 2.0);
	*/

	cv::GaussianBlur(channels[0], channels[0], cv::Size(13, 13), 2.0);
	cv::GaussianBlur(channels[1], channels[1], cv::Size(13, 13), 2.0);
	cv::GaussianBlur(channels[2], channels[2], cv::Size(13, 13), 2.0);

	merge(channels, dst);
	cv::namedWindow("dst", CV_WINDOW_NORMAL);
	cv::imshow("dst", dst);
}

/*
void Rgb2Lab(cv::Mat rgb, cv::Mat lab)
{
	int rows = rgb.rows;
	int cols = rgb.cols;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

		}
	}
}
*/



