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

	// ����һά������,��������ͼ�����ص�,ע��������ʽΪ32bit��������(cv::kmeansֻ����32bit������Mat����) 
	Mat samples(src.cols * src.rows, 1, CV_32FC3);

	// ��Ǿ���32λ���� 
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

	int clusterCount = 2; //���������������������
	Mat centers(clusterCount, 1, samples.type());
	kmeans(samples, clusterCount, labels,
			TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0),
			3, KMEANS_PP_CENTERS, centers);

	// ������֪��2������(ǰ���ͱ���)���ò�ͬ�ĻҶȲ��ʾ�� 
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
	//namedWindow("K-Means�ָ�Ч��", CV_WINDOW_NORMAL);
	//imshow("K-Means�ָ�Ч��", dst);
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
	// ��ʼ��clusterAssment��ֵ��ÿ��Ԫ��Ϊһ���ṹ�壬һ����ֵΪ���������ֵ��һ����ֵΪ�洢��
	initClusterAssment(); 

	// ����һ����־����clusterChanged�������ֵΪtrue��˵���е�ı�����Ĺ�������ô����������
	// ֱ��û���κ�һ����ı��˴صĹ���Ϊֹ��
	// ����һ�ַ�������Ϊѭ���Ľ���������ѭ���Ĵ���������ѭ����1000�����ڼ��㡣
	bool clusterChanged = true; 

	while (clusterChanged)
	{
		clusterChanged = false;

		//step one : find the nearest centroid of each point
		// ��һ�����ҵ�ÿ���������������ĵ�
		cout << "find the nearest centroid of each point : " << endl;
		for (int i = 0; i < rowLen; i++)
		{
			int minIndex = -1;
			double minDist = INT_MAX;
			// ����dataSet�ĵ�i�������������д�����centroids�ľ���
			for (int j = 0; j < k; j++)
			{
				double distJI = distEclud(centroids[j], dataSet[i]);
				if (distJI < minDist)
				{
					minDist = distJI;
					minIndex = j;
				}
			}
			// ��������������仯Ȼ�����
			if (clusterAssment[i].minIndex != minIndex)
			{
				clusterChanged = true;
				clusterAssment[i].minIndex = minIndex;
				clusterAssment[i].minDist = minDist;
			}
		}

		// step two : update the centroids
		// �ڶ�������ͬһ���������Ӳ�����ƽ��Ȼ����¾������ĵ�centroids��ֵ
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

	// kmean����ͼ��ָ�
	int k = 2;
	KMeansImage kms(k);
	kms.loadImage(gray);
	kms.generatCentroids(); // ����K�����ĵ�
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
