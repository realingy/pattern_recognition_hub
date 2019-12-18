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
	void randCent();					// �������k�����ĵ�
	void print();						// ��ӡ���
	void kmeans();						// kmeans�ĺ��ĺ���������k�����ĵ��Լ�ÿ����Ĺ���
};

class KMeansImage
{
private:
	vector<float> mmin, mmax;		// 
	int col_, row_;					// colLen:������ά��; rowLen:��������
	int K_;							// Kֵ
	vector<float> centroids;		// K�����������
	cv::Mat img_;
	float cent_max_;

	// ���������Сֵ�Ľṹ��
	typedef struct MinMax
	{
		float Min;
		float Max;
		MinMax(float min, float max) :Min(min), Max(max) {}
	}tMinMax;

	// ÿ���������ľ����Լ�����ֵ
	typedef struct Node
	{
		uint minIndex; //�����index��the index of each node
		double minDist; //����ֵ����С���룩
		Node(int idx, double dist) :minIndex(idx), minDist(dist) {}
	}tNode;

	// ÿһ��������������𣨾��ࣩ
	vector<vector<tNode>>  clusterAssment;

	/*split line into numbers*/
	// void split(char* buffer, vector<float>& vec); // ��һ���зֳɶ����ֵ����������
	// tMinMax getMinMax(int idx);
	// void setCentroids(tMinMax& tminmax, int idx);
	// void updateCentroids();
	void initClusterAssment() {
		tNode node(-1, -1);
		vector<tNode> temp;
		for (int i = 0; i < row_; i++)
		{
			temp.clear();
			for (int j = 0; j < col_; j++)
			{
				temp.push_back(node);
			}
			clusterAssment.push_back(temp);
		}

	}

	// �������
	float distEclud(float v1, float v2) {
		float dist = v1 - v2;
		return abs(v1 - v2);
	}

public:
	KMeansImage(int k) {
		K_ = k;
		cent_max_ = 0;
	}
	void loadImage(cv::Mat& src)
	{
		col_ = src.cols;
		row_ = src.rows;

		img_.create(cv::Size(col_, row_), CV_32FC1);

		for (size_t i = 0; i < row_; i++)
		{
			for (size_t j = 0; j < row_; j++)
			{
				img_.at<float>(i, j) = (float)src.at<uchar>(i, j);
				if((float)src.at<uchar>(i,j) > cent_max_)
					cent_max_ = (float)src.at<uchar>(i, j);
			}
		}

		/*
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
		*/
	}

	void generatCentroids() {
		// ����K�����ĵ�
		//float step = 255 / (K_ - 1);
		float step = cent_max_ / (K_ - 1);
		for (int i = 0; i < K_; i++)
		{
			centroids.push_back(step * i);
		}
	}
		
	// ������
	cv::Mat update_result()
	{
		cv::Mat result = cv::Mat(cv::Size(col_, row_), CV_32FC1);

		for (int i = 0; i < row_; i++)
		{
			for (int j = 0; j < col_; j++)
			{
				int idx = clusterAssment[i][j].minIndex; // ���
				result.at<float>(i, j) = (float)centroids[idx];
				//if(idx > 0)
				//	cout << idx << " ";
				if (centroids[idx] > 0)
					cout << centroids[idx] << "\t";
			}
		}

		return result;
	}

	void kmeans(cv::Mat & src) {
		// kmeans�ĺ��ĺ���������k�����ĵ��Լ�ÿ����Ĺ���
	
		// ��ʼ��clusterAssment��ֵ��ÿ��Ԫ��Ϊһ���ṹ�壬һ����ֵΪ���������ֵ��һ����ֵΪ�洢���
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
			for (int i = 0; i < row_; i++)
			{
				for (int j = 0; j < col_; j++)
				{
					int minIndex = -1;
					double minDist = INT_MAX;

					// ����������������о�������centroids�ľ���
					for (int cent = 0; cent < K_; cent++)
					{
						float ccc = centroids[cent];
						float dist = distEclud(centroids[cent], (float)src.at<uchar>(i, j));
						if (dist < minDist)
						{
							minDist = dist;
							minIndex = cent;
						}
					}
				
					//if(minIndex > 0)
					//	cout << " " << minIndex;

					// ����������������仯
					if (clusterAssment[i][j].minIndex != minIndex)
					{
						clusterChanged = true;
						clusterAssment[i][j].minIndex = minIndex;
						clusterAssment[i][j].minDist = minDist;
					}
				}
			}

			// ����
			std::ofstream file3("clusterAssment.txt");
			for (int i = 0; i < row_; i++)
			{
				for (int j = 0; j < col_; j++)
				{
					file3 << clusterAssment[i][j].minIndex << "\t";
				}
				file3 << std::endl;
			}

			// step two : update the centroids
			// �ڶ�������ͬһ������ػҶ�ֵ��Ӳ�����ƽ��Ȼ����¾������ĵ�centroids��ֵ
			cout << "update the centroids:" << endl;
			//vector<float> total(K_, 0.0);
			float * total = new float[K_];
			for (int cent = 0; cent < K_; cent++)
			{
				int cnt = 0;
				for (int i = 0; i < row_; i++)
				{
					for (int j = 0; j < col_; j++)
					{
						// ����(i,j)λ��Ϊ���أ��ҵ����������
						if (clusterAssment[i][j].minIndex == cent)
						{
							++cnt;
							total[cent] += (float)src.at<uchar>(i, j);// 0/*�Ҷ�ֵ*/;
						}
					}
				}
		
				// mean of the vector and update the centroids[cent]
				if (cnt != 0)
					total[cent] /= cnt;
				centroids[cent] = total[cent];
			}

			delete [] total;
		
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