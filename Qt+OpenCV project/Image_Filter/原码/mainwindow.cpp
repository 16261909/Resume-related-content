#include "mainwindow.h"
#include <QVBoxLayout>
#include "QPushButton"
#include "ui_mainwindow.h"
#include "sonwidget.h"
const int LEN=500;
using namespace std;
using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    init();
    connect(&P5, &QPushButton::clicked,
            [=]()
            {
                QString filename = QFileDialog::getOpenFileName(this,tr("open image"),".",tr("Image file(*.png *.jpg *.bmp)"));
                img = imread(filename.toLocal8Bit().data());
                deal();
            }
            );
    connect(&P1, &QPushButton::clicked,
            [=]()
            {
                if(img.empty())return;
                MedianFlitering(Salt_Image, img3);
                displayResult(ui->label_3,img3);
                Q3.setText("Custom Median Filtered Picture");
                Q3.move(1360,25);
            }
            );
    connect(&P2, &QPushButton::clicked,
            [=]()
            {
                if(img.empty())return;
                medianBlur(Salt_Image, img4, 3);
                displayResult(ui->label_3,img4);
                Q3.setText("Opencv Median Filtered Picture");
                Q3.move(1360,25);
            }
            );
    connect(&P3, &QPushButton::clicked,
            [=]()
            {
                if(img.empty())return;
                Mat imgtmp(img.size(), img.type());
                AverFiltering(Salt_Image, imgtmp);
                img5=imgtmp;
                displayResult(ui->label_3,img5);
                Q3.setText("Custom Mean Filtered Picture");
                Q3.move(1370,25);
            }
            );
    connect(&P4, &QPushButton::clicked,
            [=]()
            {
                if(img.empty())return;
                blur(Salt_Image, img6, Size(3, 3));
                displayResult(ui->label_3,img6);
                Q3.setText("Opencv Mean Filtered Picture");
                Q3.move(1370,25);
            }
            );
    connect(sld, &QSlider::sliderReleased,
            [=]()
            {
                if(img.empty())return;
                img.copyTo(Salt_Image);
                salt(Salt_Image, sld->value());
                displayResult(ui->label_2, Salt_Image);
            }
            );
}
void MainWindow::init()
{
    ui->setupUi(this);
    this->setMinimumSize(1800, 700);
    this->setMaximumSize(1800, 700);
    this->setWindowTitle("Image Filter");
    font.setPointSize(12);
    ui->label->resize(LEN, LEN);
    ui->label_2->resize(LEN, LEN);
    ui->label_3->resize(LEN, LEN);
    ui->label->move(75, 100);
    ui->label_2->move(650, 100);
    ui->label_3->move(1225, 100);
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    P1.setFont(font);
    P2.setFont(font);
    P3.setFont(font);
    P4.setFont(font);
    P5.setFont(font);
    Q1.setFont(font);
    Q2.setFont(font);
    Q3.setFont(font);
    Q4.setFont(font);
    P1.setParent(this);
    P2.setParent(this);
    P3.setParent(this);
    P4.setParent(this);
    P5.setParent(this);
    Q1.setParent(this);
    Q2.setParent(this);
    Q3.setParent(this);
    Q4.setParent(this);
    P1.setText("custom median filtering");
    P2.setText("opencv median filtering");
    P3.setText("custom mean filtering");
    P4.setText("opencv mean filtering");
    P5.setText("choose a picture");
    Q1.setText("Original Picture");
    Q2.setText("Noise Picture");
    Q3.setText("NULL");
    Q4.setText("Noise Level");
    P1.resize(210,50);
    P2.resize(210,50);
    P3.resize(210,50);
    P4.resize(210,50);
    P5.resize(210,50);
    Q1.resize(200,50);
    Q2.resize(200,50);
    Q3.resize(300,50);
    Q4.resize(200,50);
    P1.move(125,630);
    P2.move(450,630);
    P3.move(775,630);
    P4.move(1100,630);
    P5.move(1425,630);
    Q1.move(270,25);
    Q2.move(860,25);
    Q3.move(1480,25);
    Q4.move(1145,60);
    sld = new QSlider(Qt::Vertical);
    sld->setParent(this);
    sld->resize(20,450);
    sld->move(1178,125);
    sld->setMaximum(50000);
    sld->setMinimum(1000);
}
void MainWindow::deal()
{
    if(img.empty())return;
    img.copyTo(Salt_Image);
    salt(Salt_Image, sld->value());
    displayResult(ui->label, img);
    displayResult(ui->label_2, Salt_Image);
    Q3.setText("NULL");
    ui->label_3->hide();
}
void MainWindow::MedianFlitering(const Mat& src, Mat& dst)
{
    if (!src.data)return;
    Mat _dst(src.size(), src.type());
    for (int i = 0; i < src.rows; ++i)
        for (int j = 0; j < src.cols; ++j) {
            if ((i - 1) > 0 && (i + 1) < src.rows && (j - 1) > 0 && (j + 1) < src.cols) {
                _dst.at<Vec3b>(i, j)[0] = Median(src.at<Vec3b>(i, j)[0], src.at<Vec3b>(i + 1, j + 1)[0],
                    src.at<Vec3b>(i + 1, j)[0], src.at<Vec3b>(i, j + 1)[0], src.at<Vec3b>(i + 1, j - 1)[0],
                    src.at<Vec3b>(i - 1, j + 1)[0], src.at<Vec3b>(i - 1, j)[0], src.at<Vec3b>(i, j - 1)[0],
                    src.at<Vec3b>(i - 1, j - 1)[0]);
                _dst.at<Vec3b>(i, j)[1] = Median(src.at<Vec3b>(i, j)[1], src.at<Vec3b>(i + 1, j + 1)[1],
                    src.at<Vec3b>(i + 1, j)[1], src.at<Vec3b>(i, j + 1)[1], src.at<Vec3b>(i + 1, j - 1)[1],
                    src.at<Vec3b>(i - 1, j + 1)[1], src.at<Vec3b>(i - 1, j)[1], src.at<Vec3b>(i, j - 1)[1],
                    src.at<Vec3b>(i - 1, j - 1)[1]);
                _dst.at<Vec3b>(i, j)[2] = Median(src.at<Vec3b>(i, j)[2], src.at<Vec3b>(i + 1, j + 1)[2],
                    src.at<Vec3b>(i + 1, j)[2], src.at<Vec3b>(i, j + 1)[2], src.at<Vec3b>(i + 1, j - 1)[2],
                    src.at<Vec3b>(i - 1, j + 1)[2], src.at<Vec3b>(i - 1, j)[2], src.at<Vec3b>(i, j - 1)[2],
                    src.at<Vec3b>(i - 1, j - 1)[2]);
            }
            else
                _dst.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
        }
    _dst.copyTo(dst);//拷贝
}
void MainWindow::salt(Mat& image, int num)
{
    if (!image.data) return;
    int i, j;
    srand(time(NULL));
    for (int x = 0; x < num; ++x) {
        i = rand() % image.rows;
        j = rand() % image.cols;
        int flag=rand()%2;
        image.at<Vec3b>(i, j)[0] = 255 * flag;
        image.at<Vec3b>(i, j)[1] = 255 * flag;
        image.at<Vec3b>(i, j)[2] = 255 * flag;
    }
}
void MainWindow::AverFiltering(const Mat& src, Mat& dst)
{
    if (!src.data) return;
    for(int i = 0; i < src.rows; i++)
        for(int j = 0; j < src.cols; j++) {
            if((i - 1 >= 0) && (j - 1) >= 0 && (i + 1) < src.rows && (j + 1) < src.cols) {//边缘不进行处理
                dst.at<Vec3b>(i, j)[0] = (src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i - 1, j - 1)[0] + src.at<Vec3b>(i - 1, j)[0] + src.at<Vec3b>(i, j - 1)[0] +
                    src.at<Vec3b>(i - 1, j + 1)[0] + src.at<Vec3b>(i + 1, j - 1)[0] + src.at<Vec3b>(i + 1, j + 1)[0] + src.at<Vec3b>(i, j + 1)[0] +
                    src.at<Vec3b>(i + 1, j)[0]) / 9;
                dst.at<Vec3b>(i, j)[1] = (src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i - 1, j - 1)[1] + src.at<Vec3b>(i - 1, j)[1] + src.at<Vec3b>(i, j - 1)[1] +
                    src.at<Vec3b>(i - 1, j + 1)[1] + src.at<Vec3b>(i + 1, j - 1)[1] + src.at<Vec3b>(i + 1, j + 1)[1] + src.at<Vec3b>(i, j + 1)[1] +
                    src.at<Vec3b>(i + 1, j)[1]) / 9;
                dst.at<Vec3b>(i, j)[2] = (src.at<Vec3b>(i, j)[2] + src.at<Vec3b>(i - 1, j - 1)[2] + src.at<Vec3b>(i - 1, j)[2] + src.at<Vec3b>(i, j - 1)[2] +
                    src.at<Vec3b>(i - 1, j + 1)[2] + src.at<Vec3b>(i + 1, j - 1)[2] + src.at<Vec3b>(i + 1, j + 1)[2] + src.at<Vec3b>(i, j + 1)[2] +
                    src.at<Vec3b>(i + 1, j)[2]) / 9;
            }
            else {//边缘赋值
                dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0];
                dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1];
                dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2];
            }
        }
}
uchar MainWindow::Median(uchar n1, uchar n2, uchar n3, uchar n4, uchar n5,
                         uchar n6, uchar n7, uchar n8, uchar n9)
{
    uchar arr[9];
    arr[0] = n1;
    arr[1] = n2;
    arr[2] = n3;
    arr[3] = n4;
    arr[4] = n5;
    arr[5] = n6;
    arr[6] = n7;
    arr[7] = n8;
    arr[8] = n9;
    for(int gap = 9 / 2; gap > 0; gap /= 2)
        for(int i = gap; i < 9; ++i)
            for (int j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap)
                swap(arr[j], arr[j + gap]);
    return arr[4];
}
void MainWindow::displayResult(QLabel *des,Mat mat)
{   //show the resultImage in result area;
    cv::resize(mat, mat, Size(LEN, LEN), 0, 0);
    Mat rgb;
    QImage img;
    if(mat.channels() == 3)    // RGB image
    {
        cvtColor(mat,rgb,CV_BGR2RGB);
        img = QImage((const uchar*)(rgb.data),  //(const unsigned char*)
                     rgb.cols,rgb.rows,
                     rgb.cols*rgb.channels(),   //new add
                     QImage::Format_RGB888);
    }else                     // gray image
    {
        img = QImage((const uchar*)(mat.data),
                     mat.cols,mat.rows,
                     mat.cols*mat.channels(),    //new add
                     QImage::Format_Indexed8);
    }

    des->setPixmap(QPixmap::fromImage(img));
    des->resize(des->pixmap()->size());
    des->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}

