#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<ctime>
#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QFont>
#include <QSlider>
#include <algorithm>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

QT_BEGIN_NAMESPACE
using namespace cv;
using namespace std;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton P1,P2,P3,P4,P5;
    QLabel Q1,Q2,Q3,Q4;
    QFont font;
    QSlider *sld;
    Mat img,img3,img4,img5,img6,Salt_Image;
    void init();
    void displayResult(QLabel *des, Mat mat);
    uchar Median(uchar n1, uchar n2, uchar n3, uchar n4, uchar n5,
                 uchar n6, uchar n7, uchar n8, uchar n9);
    void salt(Mat& image, int num);
    void AverFiltering(const Mat& src, Mat& dst);
    void MedianFlitering(const Mat& src, Mat& dst);
    void deal();
};

#endif // MAINWINDOW_H

