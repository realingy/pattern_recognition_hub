#include "connect_region.h"
#include <fstream>

int ConnectRegion(cv::Mat src, int ConnectBodyNumber, int x, int y)
{
	int rows = src.rows;
	int cols = src.cols;

	int count = 0;
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			count++;
		}

	}

	return 0;
}

void Seed_Filling(const cv::Mat& binImg, cv::Mat& labelImg)   //种子填充法
{
	// 4邻接方法
	if (binImg.empty() ||
		binImg.type() != CV_8UC1)
	{
		return;
	}

	int rows = binImg.rows - 1;
	int cols = binImg.cols - 1;

	labelImg.release();
	//binImg.convertTo(labelImg, CV_32SC1);
	binImg.convertTo(labelImg, CV_8UC1);

	std::ofstream file3("bin.txt");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			file3 << (int)labelImg.at<uchar>(i, j) << "\t";
		}
		file3 << std::endl;
	}

	#if 1
	int label = 0;

	for (int i = 1; i < rows - 1; i++)
	{
		// uchar* data = labelImg.ptr<uchar>(i);
		for (int j = 1; j < cols - 1; j++)
		{
					
			if((int)labelImg.at<uchar>(i, j) == 0)
			// data[j]
			// if ((int)data[j] == 0)
			{
				std::stack<std::pair<int, int>> neighborPixels;
				neighborPixels.push(std::pair<int, int>(i, j)); //像素位置: <i,j>
				++label;  // 开始新的标签
				std::cout << label << std::endl;

				while (!neighborPixels.empty())
				{
					//如果与上一行中一个团有重合区域，则将上一行的那个团的标号赋给它
					std::pair<int, int> curPixel = neighborPixels.top();
					int curX = curPixel.first;
					int curY = curPixel.second;
					labelImg.at<uchar>(curX, curY) = (uchar)label;

					neighborPixels.pop();

					if ((int)labelImg.at<uchar>(curX, curY - 1) == 0)
					{ //左
						neighborPixels.push(std::pair<int, int>(curX, curY - 1));
					}
					if ((int)labelImg.at<uchar>(curX, curY + 1) == 0)
					{ // 右
						neighborPixels.push(std::pair<int, int>(curX, curY + 1));
					}
					if ((int)labelImg.at<uchar>(curX - 1, curY) == 0)
					{ // 上
						neighborPixels.push(std::pair<int, int>(curX - 1, curY));
					}
					if ((int)labelImg.at<uchar>(curX + 1, curY) == 0)
					{ // 下
						neighborPixels.push(std::pair<int, int>(curX + 1, curY));
					}

					/*
					if (labelImg.at<int>(curX, curY - 1) == 1)
					{//左
						neighborPixels.push(std::pair<int, int>(curX, curY - 1));
					}
					if (labelImg.at<int>(curX, curY + 1) == 1)
					{// 右
						neighborPixels.push(std::pair<int, int>(curX, curY + 1));
					}
					if (labelImg.at<int>(curX - 1, curY) == 1)
					{// 上
						neighborPixels.push(std::pair<int, int>(curX - 1, curY));
					}
					if (labelImg.at<int>(curX + 1, curY) == 1)
					{// 下
						neighborPixels.push(std::pair<int, int>(curX + 1, curY));
					}
					*/
				}
			}
		}
	}
	#endif
}

void Two_Pass(const cv::Mat& binImg, cv::Mat& labelImg)    //两遍扫描法
{
	if (binImg.empty() ||
		binImg.type() != CV_8UC1)
	{
		return;
	}

	// 第一个通路
	labelImg.release();
	binImg.convertTo(labelImg, CV_32SC1);

	int label = 1;
	std::vector<int> labelSet;
	labelSet.push_back(0);
	labelSet.push_back(1);

	int rows = binImg.rows - 1;
	int cols = binImg.cols - 1;
	for (int i = 1; i < rows; i++)
	{
		int* data_preRow = labelImg.ptr<int>(i - 1);
		int* data_curRow = labelImg.ptr<int>(i);
		for (int j = 1; j < cols; j++)
		{
			if (data_curRow[j] == 0)
			{
				std::vector<int> neighborLabels;
				neighborLabels.reserve(2);
				int leftPixel = data_curRow[j - 1];
				int upPixel = data_preRow[j];
				if (leftPixel > 0)
				{
					neighborLabels.push_back(leftPixel);
				}
				if (upPixel > 0)
				{
					neighborLabels.push_back(upPixel);
				}

				if (neighborLabels.empty())
				{
					labelSet.push_back(++label);  // 不连通，标签+1
					data_curRow[j] = label;
					labelSet[label] = label;
				}
				else
				{
					std::sort(neighborLabels.begin(), neighborLabels.end());
					int smallestLabel = neighborLabels[0];
					data_curRow[j] = smallestLabel;

					// 保存最小等价表
					for (size_t k = 1; k < neighborLabels.size(); k++)
					{
						int tempLabel = neighborLabels[k];
						int& oldSmallestLabel = labelSet[tempLabel];
						if (oldSmallestLabel > smallestLabel)
						{
							labelSet[oldSmallestLabel] = smallestLabel;
							oldSmallestLabel = smallestLabel;
						}
						else if (oldSmallestLabel < smallestLabel)
						{
							labelSet[smallestLabel] = oldSmallestLabel;
						}
					}
				}
			}
		}
	}

	// 更新等价对列表
	// 将最小标号给重复区域
	for (size_t i = 2; i < labelSet.size(); i++)
	{
		int curLabel = labelSet[i];
		int preLabel = labelSet[curLabel];
		while (preLabel != curLabel)
		{
			curLabel = preLabel;
			preLabel = labelSet[preLabel];
		}
		labelSet[i] = curLabel;
	}

	for (int i = 0; i < rows; i++)
	{
		int* data = labelImg.ptr<int>(i);
		for (int j = 0; j < cols; j++)
		{
			int& pixelLabel = data[j];
			pixelLabel = labelSet[pixelLabel];
		}
	}
}

//彩色显示
cv::Scalar GetRandomColor()
{
	uchar r = 255 * (rand() / (1.0 + RAND_MAX));
	uchar g = 255 * (rand() / (1.0 + RAND_MAX));
	uchar b = 255 * (rand() / (1.0 + RAND_MAX));
	return cv::Scalar(b, g, r);
}

void LabelColor(const cv::Mat& labelImg, cv::Mat& colorLabelImg)
{
	if (labelImg.empty() ||
		labelImg.type() != CV_32SC1)
	{
		std::cout << "check the image or the type\n";
		return;
	}

	std::map<int, cv::Scalar> colors;

	int rows = labelImg.rows;
	int cols = labelImg.cols;

	colorLabelImg.release();
	colorLabelImg.create(rows, cols, CV_8UC3);
	colorLabelImg = cv::Scalar::all(0);

	for (int i = 0; i < rows; i++)
	{
		const int* data_src = (int*)labelImg.ptr<int>(i);
		uchar* data_dst = colorLabelImg.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			int pixelValue = data_src[j];
			if (pixelValue > 1)
			{
				if (colors.count(pixelValue) <= 0)
				{
					colors[pixelValue] = GetRandomColor();
				}

				cv::Scalar color = colors[pixelValue];
				*data_dst++ = color[0];
				*data_dst++ = color[1];
				*data_dst++ = color[2];
			}
			else
			{
				data_dst++;
				data_dst++;
				data_dst++;
			}
		}
	}
}


/*
int main()
{

	cv::Mat binImage = cv::imread("test.jpg", 0);
	cv::threshold(binImage, binImage, 50, 1, CV_THRESH_BINARY_INV);
	cv::Mat labelImg;
	Two_Pass(binImage, labelImg, num);
	//Seed_Filling(binImage, labelImg);
	//彩色显示
	cv::Mat colorLabelImg;
	LabelColor(labelImg, colorLabelImg);
	cv::imshow("colorImg", colorLabelImg);

	#if 0
	//灰度显示
	cv::Mat grayImg;
	labelImg *= 10;
	labelImg.convertTo(grayImg, CV_8UC1);
	cv::imshow("labelImg", grayImg);
	#endif

	cv::waitKey(0);
	return 0;
}
*/

