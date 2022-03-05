#include<opencv.hpp>
#include<ml.hpp>
#include<iostream>
using namespace std;
using namespace cv;
using namespace ml;
void svm1() {
	const int Kwidth = 512;
	const int Kheight = 512;

	//������ʾ��������ͼ��
	Mat image = Mat::zeros(Kheight, Kwidth, CV_8UC3);
	int labels[20];
	for (int i = 0; i < 10; i++)
		labels[i] = 1;
	for (int i = 10; i < 20; i++)
		labels[i] = 2;

	Mat labelsMat(20, 1, CV_32SC1, labels);

	float trainDataArray[20][2];
	RNG rng;
	for (int i = 0; i < 10; i++)
	{
		trainDataArray[i][0] = 400 + static_cast<float>(rng.gaussian(30));
		trainDataArray[i][1] = 400 + static_cast<float>(rng.gaussian(30));
	}
	for (int i = 10; i < 20; i++)
	{
		trainDataArray[i][0] = 30 + static_cast<float>(rng.gaussian(30));
		trainDataArray[i][1] = 30 + static_cast<float>(rng.gaussian(30));
	}
	
	Mat trainMat(20, 2, CV_32FC1, trainDataArray);


	Ptr<SVM> model = SVM::create();
	//��������
	model->setC(1);	
	model->setKernel(SVM::LINEAR);
	model->setType(SVM::C_SVC);
	model->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
	//����׼��
	Ptr<TrainData> data = TrainData::create(trainMat, ROW_SAMPLE, labelsMat);

	model->train(data);

	//��ͼ��������512*512�����������Ԥ�⣬��ͬ��Ԥ������ͼ�񱳾�������ʾ��ͬ����ɫ
	Vec3b red(0, 0, 255), green(0, 255, 0), blue(255, 0, 0);
	Mat sampleMat;
	for (int i = 0; i < image.rows; ++i) {
		for (int j = 0; j < image.cols; ++j)
		{
			sampleMat = (Mat_<float>(1, 2) << j, i);  //���ɲ�������
			int response = model->predict(sampleMat);  //����Ԥ�⣬����1��-1
			if (response == 1)
				image.at<Vec3b>(i, j) = red;
			else
				image.at<Vec3b>(i, j) = green;

		}
	}

	
	//��ѵ�������㣬��ʾ��ͼ�����
	for (int i = 0; i < trainMat.rows; i++)
	{
		const float * v = trainMat.ptr<float>(i);
		Point pt = Point((int)v[0], (int)v[1]);
		if (labels[i] == 1) //��ͬ��Բ�㣬��ǲ�ͬ����ɫ
			circle(image, pt, 5, Scalar::all(255), -1, 8);
		else if (labels[i] == 2)
			circle(image, pt, 5, Scalar::all(128), -1, 8);
		else
			circle(image, pt, 5, Scalar::all(255), -1, 8);
	}
	//��ʾ������ͼ��
	imshow("SVM", image);
	waitKey(0);


}
int main() {
	svm1();
	system("pause");
}
��������������������������������
��Ȩ����������ΪCSDN����������Ң����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/AlonewaitingNew/article/details/100764610
