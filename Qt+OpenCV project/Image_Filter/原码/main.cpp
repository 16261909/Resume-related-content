#include "mainwindow.h"
#include "QVBoxLayout"
#include "QLabel"
#include "QWidget"
#include "QPushButton"
#include "QApplication"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

