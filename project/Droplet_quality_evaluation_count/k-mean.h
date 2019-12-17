#ifndef __K_MEAN_H__
#define __K_MEAN_H__

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

//void kmean();
void KMean(cv::Mat& src, cv::Mat& dst);

template<typename T>
class KMEANS
{
private:
	vector<vector<T>> dataSet;		// 训练数据（二维矩阵或者图像）
	vector<T> mmin, mmax;			// 
	int colLen, rowLen;				// colLen:向量的维数; rowLen:向量数量
	int k;							// K值
	vector<vector<T>> centroids;	// K个聚类的中心

	// 存有最大最小值的结构体
	typedef struct MinMax
	{
		T Min;
		T Max;
		MinMax(T min, T max) :Min(min), Max(max) {}
	}tMinMax;

	// 每个点所属的聚类以及距离值
	typedef struct Node
	{
		int minIndex; //聚类的index，the index of each node
		double minDist; //距离值（最小距离）
		Node(int idx, double dist) :minIndex(idx), minDist(dist) {}
	}tNode;

	// 每一个向量所属的类别（聚类）
	vector<tNode>  clusterAssment;

	/*split line into numbers*/
	void split(char* buffer, vector<T>& vec); // 将一行切分成多个数值放入容器中
	tMinMax getMinMax(int idx);
	void setCentroids(tMinMax& tminmax, int idx);
	// void updateCentroids();
	void initClusterAssment();
	double distEclud(vector<T>& v1, vector<T>& v2); // 计算两个向量的欧式距离

public:
	KMEANS(int k);
	void loadDataSet(char* filename);	// 读入数据信息并初始化dataSet以及colLen、rowLen
	void loadImage(cv::Mat & src);		// 读入图像信息并初始化dataSet以及colLen、rowLen
	void randCent();					// 随机生成k个中心点
	void print();						// 打印结果
	void kmeans();						// kmeans的核心函数，计算k个中心点以及每个点的归类
};

#endif