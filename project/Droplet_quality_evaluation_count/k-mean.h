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
	vector<vector<T>> dataSet;		// ѵ�����ݣ���ά�������ͼ��
	vector<T> mmin, mmax;			// 
	int colLen, rowLen;				// colLen:������ά��; rowLen:��������
	int k;							// Kֵ
	vector<vector<T>> centroids;	// K�����������

	// ���������Сֵ�Ľṹ��
	typedef struct MinMax
	{
		T Min;
		T Max;
		MinMax(T min, T max) :Min(min), Max(max) {}
	}tMinMax;

	// ÿ���������ľ����Լ�����ֵ
	typedef struct Node
	{
		int minIndex; //�����index��the index of each node
		double minDist; //����ֵ����С���룩
		Node(int idx, double dist) :minIndex(idx), minDist(dist) {}
	}tNode;

	// ÿһ��������������𣨾��ࣩ
	vector<tNode>  clusterAssment;

	/*split line into numbers*/
	void split(char* buffer, vector<T>& vec); // ��һ���зֳɶ����ֵ����������
	tMinMax getMinMax(int idx);
	void setCentroids(tMinMax& tminmax, int idx);
	// void updateCentroids();
	void initClusterAssment();
	double distEclud(vector<T>& v1, vector<T>& v2); // ��������������ŷʽ����

public:
	KMEANS(int k);
	void loadDataSet(char* filename);	// ����������Ϣ����ʼ��dataSet�Լ�colLen��rowLen
	void loadImage(cv::Mat & src);		// ����ͼ����Ϣ����ʼ��dataSet�Լ�colLen��rowLen
	void randCent();					// �������k�����ĵ�
	void print();						// ��ӡ���
	void kmeans();						// kmeans�ĺ��ĺ���������k�����ĵ��Լ�ÿ����Ĺ���
};

#endif