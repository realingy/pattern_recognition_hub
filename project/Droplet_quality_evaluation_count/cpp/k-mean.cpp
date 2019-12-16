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

	//生成一维采样点,包括所有图像像素点,注意采样点格式为32bit浮点数。 
	Mat samples(img.cols * img.rows, 1, CV_32FC3);

	//标记矩阵，32位整形 
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

	// int clusterCount = 4; //区域中心个数
	int clusterCount = 2; //区域中心个数
	Mat centers(clusterCount, 1, samples.type());
	kmeans(samples, clusterCount, labels,
		TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0),
		3, KMEANS_PP_CENTERS, centers);

	// 我们已知有2个聚类(前景和背景)，用不同的灰度层表示。 
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

	namedWindow("K-Means分割效果", CV_WINDOW_NORMAL);
	imshow("K-Means分割效果", img1);
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

	// 平滑去噪
	GaussianBlur(src_rgb, src_rgb);

	// 将彩色图像从RGB转化到lab彩色空间
	Mat src_lab;
	cv::cvtColor(src_rgb, src_lab, CV_BGR2Lab);

	// 进行K-mean聚类将图像分割成2个区域
	do_kmean(src_lab);
}
*/

void do_kmean(cv::Mat src)
{
	std::vector<cv::Mat> channels;

	// 取出lab空间的a分量和b分量
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

	int colors = 4; // 分割的区域个数为4

	/*
	[cluster_idx, cluster_center] = kmeans(ab, nColors, 'distance', 'sqEuclidean', 'Replicates', 2) # 重复聚类2次
	pixel_labels = reshape(cluster_idx, nrows, ncols)
	*/


}

// 高斯平滑去噪
void GaussianBlur(cv::Mat& src, cv::Mat& dst)
{
	// 平滑去噪
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



