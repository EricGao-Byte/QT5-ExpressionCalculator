#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  //应用类对象
    MainWindow w;  //窗口类对象
    w.show();  //显示窗口

    return a.exec();  //应用循环执行
}
