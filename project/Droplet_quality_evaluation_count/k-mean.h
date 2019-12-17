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
	void generatCentImage();			// 随机生成k个中心点
	void print();						// 打印结果
	void kmeans();						// kmeans的核心函数，计算k个中心点以及每个点的归类
};

class KMeansImage
{
private:
	vector<vector<float>> data_;	// 训练数据（二维矩阵或者图像）
	vector<float> mmin, mmax;		// 
	int col_, row_;					// colLen:向量的维数; rowLen:向量数量
	int K_;							// K值
	vector<float> centroids;		// K个聚类的中心

	// 存有最大最小值的结构体
	typedef struct MinMax
	{
		float Min;
		float Max;
		MinMax(float min, float max) :Min(min), Max(max) {}
	}tMinMax;

	// 每个点所属的聚类以及距离值
	typedef struct Node
	{
		int minIndex; //聚类的index，the index of each node
		double minDist; //距离值（最小距离）
		Node(int idx, double dist) :minIndex(idx), minDist(dist) {}
	}tNode;

	// 每一个向量所属的类别（聚类）
	vector<vector<tNode>>  clusterAssment;

	/*split line into numbers*/
	// void split(char* buffer, vector<float>& vec); // 将一行切分成多个数值放入容器中
	// tMinMax getMinMax(int idx);
	// void setCentroids(tMinMax& tminmax, int idx);
	// void updateCentroids();
	void initClusterAssment() {
		tNode node(-1, -1);
		vector<tNode> temp;
		for (int i = 0; i < row_; i++)
		{
			temp.clear();
			for (int j = 0; j < row_; j++)
			{
				temp.push_back(node);
			}
			clusterAssment.push_back(temp);
		}

	}

	// 计算距离
	float distEclud(float v1, float v2) {
		return abs(v1 - v2);
	}

public:
	KMeansImage(int k) {
		K_ = k;
	}
	void loadImage(cv::Mat& src) {
		// 读入图像信息并初始化dataSet以及colLen、rowLen
		col_ = src.cols;
		row_ = src.rows;
		//img_ = src;
		vector<float> temp;
		for (size_t i = 0; i < row_; i++)
		{
			temp.clear();
			for (size_t j = 0; j < row_; j++)
			{
				temp.push_back((float)src.at<uchar>(i,j));
			}
			data_.push_back(temp);
		}
	}
	void generatCentroids() {
		// 生成K个中心点
		float step = 255 / (K_ - 1);
		for (int i = 0; i < K_; i++)
		{
			centroids.push_back(step*i);
		}
	}
		
	// 计算结果
	cv::Mat update_result()
	{
		cv::Mat result = cv::Mat(cv::Size(row_, col_), CV_32FC1);

		for (int i = 0; i < row_; i++)
		{
			for (int j = 0; j < row_; j++)
			{
				int idx = clusterAssment[i][j].minIndex; // 类别
				result.at<float>(i, j) = centroids[idx];
			}
		}

		return result;
	}

	void kmeans() {
		// kmeans的核心函数，计算k个中心点以及每个点的归类
	
		// 初始化clusterAssment的值，每个元素为一个结构体，一个域值为聚类的索引值；一个域值为存储误差
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
			for (int i = 0; i < row_; i++)
			{
				for (int j = 0; j < col_; j++)
				{
					int minIndex = -1;
					double minDist = INT_MAX;

					// 计算第向量距离所有聚类中心centroids的距离
					for (int cent = 0; cent < K_; cent++)
					{
						//float dist = distEclud(centroids[cent], src.at<float>(i, j));
						float dist = distEclud(centroids[cent], data_[i][j]);
						if (dist < minDist)
						{
							minDist = dist;
							minIndex = cent;
						}
					}
				
					// 如果聚类中心有所变化
					if (clusterAssment[i][j].minIndex != minIndex)
					{
						clusterChanged = true;
						clusterAssment[i][j].minIndex = minIndex;
						clusterAssment[i][j].minDist = minDist;
					}
				}
			}

			// step two : update the centroids
			// 第二步、将同一类的像素灰度值相加并且求平均然后更新聚类中心点centroids的值
			cout << "update the centroids:" << endl;
			vector<float> total;
			for (int cent = 0; cent < K_; cent++)
			{
				int cnt = 0;
				for (int i = 0; i < row_; i++)
				{
					for (int j = 0; j < col_; j++)
					{
						// 对于(i,j)位置为像素，找到其所属类别
						if (clusterAssment[i][j].minIndex == cent)
						{
							++cnt;
							//total[cent] += src.at<float>(i, j);// 0/*灰度值*/;
							total[cent] += data_[i][j];// 0/*灰度值*/;
						}
					}
				}
		
				// mean of the vector and update the centroids[cent]
				if (cnt != 0)
					total[cent] /= cnt;
				centroids[cent] = total[cent];
			}
		
			// update_result();
		}

#if 0
	typename vector<tNode> ::iterator it = clusterAssment.begin();
	while (it != clusterAssment.end())
	{
		cout << (*it).minIndex << "\t" << (*it).minDist << endl;
		it++;
	}
#endif
	}

};

#endif