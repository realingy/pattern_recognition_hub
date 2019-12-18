#include "k-mean.h"
#include "connect_region.h"

#if 1
int main(int argc, char *argv[])
{
#if 0
	QApplication app(argc, argv);
	QLabel* label = new QLabel("Hello Qt");
	label->show();
	return app.exec();
#endif

	//cv::Mat src = cv::imread("bean.JPG");
	cv::Mat src = cv::imread("DSC00128.JPG");
	//cv::Mat src = cv::imread("test.PNG");
	if (!src.data)
		return -1;

	cv::namedWindow("Source Image", CV_WINDOW_NORMAL);
	cv::imshow("Source Image", src);

	cv::Mat dst_kmean;

	KMean(src, dst_kmean);

	cv::namedWindow("K-Means�ָ�Ч��", CV_WINDOW_NORMAL);
	cv::imshow("K-Means�ָ�Ч��", dst_kmean);

	// cv::Mat label;
	// Seed_Filling(dst_kmean, label); //������䷨
	// Two_Pass(dst_kmean, label);

	/*
	//��ɫ��ʾ
	cv::Mat colorLabelImg;
	LabelColor(label, colorLabelImg);
	cv::namedWindow("label", CV_WINDOW_NORMAL);
	cv::imshow("label", colorLabelImg);
	*/

	cv::waitKey(0);

	return 0;
}
#endif


