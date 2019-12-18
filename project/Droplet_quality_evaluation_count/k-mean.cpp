#include "k-mean.h"
#include <vector>
#include <iostream>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <time.h>
#include <limits.h> //for INT_MIN INT_MAX

void GaussianBlur(cv::Mat& src, cv::Mat& dst);
void do_kmean(cv::Mat src);

//void kmean(cv::Mat &src, cv::Mat & dst)
void KMean(cv::Mat &src, cv::Mat & dst)
{
	using namespace cv;

	// 生成一维采样点,包括所有图像像素点,注意采样点格式为32bit浮点数。(cv::kmeans只接受32bit浮点型Mat数据) 
	Mat samples(src.cols * src.rows, 1, CV_32FC3);

	// 标记矩阵，32位整形 
	Mat labels(src.cols * src.rows, 1, CV_32SC1);

	uchar* p;
	int k = 0;
	for (int i = 0; i < src.rows; i++)
	{
		p = src.ptr<uchar>(i);
		for (int j = 0; j < src.cols; j++)
		{
			samples.at<Vec3f>(k, 0)[0] = float(p[j * 3]);
			samples.at<Vec3f>(k, 0)[1] = float(p[j * 3 + 1]);
			samples.at<Vec3f>(k, 0)[2] = float(p[j * 3 + 2]);
			k++;
		}
	}

	int clusterCount = 2; //聚类中心数（类别数量）
	Mat centers(clusterCount, 1, samples.type());
	kmeans(samples, clusterCount, labels,
			TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0),
			3, KMEANS_PP_CENTERS, centers);

	// 我们已知有2个聚类(前景和背景)，用不同的灰度层表示。 
	Mat img1(src.rows, src.cols, CV_8UC1);
	float step = 255 / (clusterCount - 1);
	k = 0;
	for (int i = 0; i < img1.rows; i++)
	{
		p = img1.ptr<uchar>(i);
		for (int j = 0; j < img1.cols; j++)
		{
			int cent = labels.at<int>(k, 0);
			k++;
			p[j] = 255 - cent * step;
			if (p[j] != 0)
			{
				p[j] = 255;
			}
		}
	}

	dst = img1;
	//namedWindow("K-Means分割效果", CV_WINDOW_NORMAL);
	//imshow("K-Means分割效果", dst);
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

template<typename T>
KMEANS<T>::KMEANS(int k)
{
	this->k = k;
}

template<typename T>
void KMEANS<T>::initClusterAssment()
{
	tNode node(-1, -1);
	for (int i = 0; i < rowLen; i++)
	{
		clusterAssment.push_back(node);
	}
}

template<typename T>
void KMEANS<T>::kmeans()
{
	// 初始化clusterAssment的值，每个元素为一个结构体，一个域值为聚类的索引值；一个域值为存储误差。
	initClusterAssment(); 

	// 创建一个标志变量clusterChanged，如果该值为true，说明有点改变了类的归属，那么继续迭代，
	// 直到没有任何一个点改变了簇的归属为止。
	// 还有一种方法来作为循环的结束条件：循环的次数，例如循环在1000次以内计算。
	bool clusterChanged = true; 

	while (clusterChanged)
	{
		clusterChanged = false;

		//step one : find the nearest centroid of each point
		// 第一步、找到每个点距离最近的中心点
		cout << "find the nearest centroid of each point : " << endl;
		for (int i = 0; i < rowLen; i++)
		{
			int minIndex = -1;
			double minDist = INT_MAX;
			// 计算dataSet的第i个向量距离所有簇中心centroids的距离
			for (int j = 0; j < k; j++)
			{
				double distJI = distEclud(centroids[j], dataSet[i]);
				if (distJI < minDist)
				{
					minDist = distJI;
					minIndex = j;
				}
			}
			// 如果簇中心有所变化然后更新
			if (clusterAssment[i].minIndex != minIndex)
			{
				clusterChanged = true;
				clusterAssment[i].minIndex = minIndex;
				clusterAssment[i].minDist = minDist;
			}
		}

		// step two : update the centroids
		// 第二步、将同一类的向量相加并且求平均然后更新聚类中心点centroids的值
		cout << "update the centroids:" << endl;
		for (int cent = 0; cent < k; cent++)
		{
			vector<T> vec(colLen, 0);
			int cnt = 0;
			for (int i = 0; i < rowLen; i++)
			{
				if (clusterAssment[i].minIndex == cent)
				{
					++cnt;
					//sum of two vectors
					for (int j = 0; j < colLen; j++)
					{
						vec[j] += dataSet[i].at(j);
					}
				}
			}

			//mean of the vector and update the centroids[cent]
			for (int i = 0; i < colLen; i++)
			{
				if (cnt != 0)	vec[i] /= cnt;
				centroids[cent].at(i) = vec[i];
			}
		}//for

		print();//update the centroids
	}//while

#if 0
	typename vector<tNode> ::iterator it = clusterAssment.begin();
	while (it != clusterAssment.end())
	{
		cout << (*it).minIndex << "\t" << (*it).minDist << endl;
		it++;
	}
#endif
}

template<typename T>
void KMEANS<T>::setCentroids(tMinMax& tminmax, int idx)
{
	T rangeIdx = tminmax.Max - tminmax.Min;
	for (int i = 0; i < k; i++)
	{
		/* generate float data between 0 and 1 */
		centroids[i].at(idx) = tminmax.Min + rangeIdx * (rand() / (double)RAND_MAX);
	}
}

//get the min and max value of the idx column
template<typename T>
typename KMEANS<T>::tMinMax KMEANS<T>::getMinMax(int idx)
{
	T min, max;
	dataSet[0].at(idx) > dataSet[1].at(idx) ? (max = dataSet[0].at(idx), min = dataSet[1].at(idx)) : (max = dataSet[1].at(idx), min = dataSet[0].at(idx));

	for (int i = 2; i < rowLen; i++)
	{
		if (dataSet[i].at(idx) < min)	min = dataSet[i].at(idx);
		else if (dataSet[i].at(idx) > max) max = dataSet[i].at(idx);
		else continue;
	}

	tMinMax tminmax(min, max);
	return tminmax;
}

template<typename T>
void KMEANS<T>::randCent()
{
	//init centroids
	vector<T> vec(colLen, 0);
	for (int i = 0; i < k; i++)
	{
		centroids.push_back(vec);
	}

	//set values by column
	srand(time(NULL));
	for (int j = 0; j < colLen; j++)
	{
		tMinMax tminmax = getMinMax(j);
		setCentroids(tminmax, j);
	}
}

template<typename T>
double KMEANS<T>::distEclud(vector<T>& v1, vector<T>& v2)
{
	T sum = 0;
	int size = v1.size();
	for (int i = 0; i < size; i++)
	{
		sum += (v1[i] - v2[i]) * (v1[i] - v2[i]);
	}
	return sum;
}

template<typename T>
void KMEANS<T>::split(char* buffer, vector<T>& vec)
{
	char* p = strtok(buffer, " \t");
	while (p != NULL)
	{
		vec.push_back(atof(p));
		p = strtok(NULL, " ");
	}
}

template<typename T>
void KMEANS<T>::print()
{
	ofstream fout;
	fout.open("res.txt");
	if (!fout)
	{
		cout << "file res.txt open failed" << endl;
		exit(0);
	}

#if 0
	typename vector< vector<T> > ::iterator it = centroids.begin();
	while (it != centroids.end())
	{
		typename vector<T> ::iterator it2 = (*it).begin();
		while (it2 != (*it).end())
		{
			//fout<<*it2<<"\t";
			cout << *it2 << "\t";
			it2++;
		}
		//fout<<endl;
		cout << endl;
		it++;
	}
#endif

	typename vector< vector<T> > ::iterator it = dataSet.begin();
	typename vector< tNode > ::iterator itt = clusterAssment.begin();
	for (int i = 0; i < rowLen; i++)
	{
		typename vector<T> ::iterator it2 = (*it).begin();
		while (it2 != (*it).end())
		{
			fout << *it2 << "\t";
			it2++;
		}
		fout << (*itt).minIndex << endl;
		itt++;
		it++;
	}
}

template<typename T>
void KMEANS<T>::loadDataSet(char* filename)
{
	FILE* pFile;
	pFile = fopen(filename, "r");
	if (!pFile)
	{
		printf("open file %s failed...\n", filename);
		exit(0);
	}

	//init dataSet
	char* buffer = new char[100];
	vector<T> temp;
	while (fgets(buffer, 100, pFile))
	{
		temp.clear();
		split(buffer, temp);
		dataSet.push_back(temp);
	}

	//init colLen,rowLen 
	colLen = dataSet[0].size();
	rowLen = dataSet.size();
}

/*
#if 0
int main()
{
	char *filename = "data.txt";

	int k = 2;
	KMEANS<double> kms(k);
	kms.loadDataSet(filename);
	kms.randCent();
	kms.kmeans();

	return 0;
}
#else
int main()
{
	cv::Mat src = cv::imread("DSC00128.JPG");
	if (!src.data)
		return -1;

	cv::Mat gray;
	cv::cvtColor(src, gray, CV_RGB2GRAY);

	cv::namedWindow("Source Image", CV_WINDOW_NORMAL);
	cv::imshow("Source Image", gray);

	// kmean聚类图像分割
	int k = 2;
	KMeansImage kms(k);
	kms.loadImage(gray);
	kms.generatCentroids(); // 生成K个中心点
	kms.kmeans(gray);
	cv::Mat res = kms.update_result();
	// kms.update_result();

	cv::namedWindow("Result Image", CV_WINDOW_NORMAL);
	cv::imshow("Result Image", res);

	cv::waitKey(0);

	return 0;
}
#endif
*/
