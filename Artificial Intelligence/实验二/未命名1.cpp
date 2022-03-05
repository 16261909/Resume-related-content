#include<opencv.hpp>
#include<ml.hpp>
#include<iostream>
using namespace std;
using namespace cv;
using namespace ml;
void svm1() {
	const int Kwidth = 512;
	const int Kheight = 512;

	//用于显示分类结果的图像
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
	//参数设置
	model->setC(1);	
	model->setKernel(SVM::LINEAR);
	model->setType(SVM::C_SVC);
	model->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
	//数据准备
	Ptr<TrainData> data = TrainData::create(trainMat, ROW_SAMPLE, labelsMat);

	model->train(data);

	//对图像内所有512*512个背景点进行预测，不同的预测结果，图像背景区域显示不同的颜色
	Vec3b red(0, 0, 255), green(0, 255, 0), blue(255, 0, 0);
	Mat sampleMat;
	for (int i = 0; i < image.rows; ++i) {
		for (int j = 0; j < image.cols; ++j)
		{
			sampleMat = (Mat_<float>(1, 2) << j, i);  //生成测试数据
			int response = model->predict(sampleMat);  //进行预测，返回1或-1
			if (response == 1)
				image.at<Vec3b>(i, j) = red;
			else
				image.at<Vec3b>(i, j) = green;

		}
	}

	
	//把训练样本点，显示在图相框内
	for (int i = 0; i < trainMat.rows; i++)
	{
		const float * v = trainMat.ptr<float>(i);
		Point pt = Point((int)v[0], (int)v[1]);
		if (labels[i] == 1) //不同的圆点，标记不同的颜色
			circle(image, pt, 5, Scalar::all(255), -1, 8);
		else if (labels[i] == 2)
			circle(image, pt, 5, Scalar::all(128), -1, 8);
		else
			circle(image, pt, 5, Scalar::all(255), -1, 8);
	}
	//显示分类结果图像
	imshow("SVM", image);
	waitKey(0);


}
int main() {
	svm1();
	system("pause");
}
————————————————
版权声明：本文为CSDN博主「邓文尧」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/AlonewaitingNew/article/details/100764610
