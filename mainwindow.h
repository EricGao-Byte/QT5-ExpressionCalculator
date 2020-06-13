#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stack.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT  //qt的object宏

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //转换部分
    void inputMidfix(QString);  //用户输入表达式
    void printMidfix();  //打印用户输入的表达式
    int judgeOperatorPriority(char ope);  //判断符号优先级
    bool isNumber(char);  //判断指针指向的字符是否是数字或者小数点
    void addBlank();  //添加数字与数字之间的空格分隔符,方便从数组中提取数字
    void outputToPostfix(char);  //将单个字符输出到后缀表达式数组
    void convertMidfix();  //用户输入表达式转换为后缀表达式
    void printPostfix();  //打印后缀表达式

    //计算部分
    void calculatePostfix();  //计算后缀表达式的值
    double getResult();  //获取表达式的计算结果
    void printResult();  //打印表达式的计算结果

    //计算函数模组
    double Add(double, double);  //加法
    double Sub(double, double);  //减法
    double Mul(double, double);  //乘法
    double Div(double, double);  //除法
    double Pow(double, double);  //幂方
    double Sqrt(double);  //开方


private:
    Ui::MainWindow *ui;
    double result_=0;  //表达式结果
    char midfix_[kmax_length]={0};  //存放用户输入表达式
    char postfix_[kmax_length]={0};  //存放后缀表达式
    char* midfix=midfix_, * postfix=postfix_;  //分别指向用户输入表达式和后缀表达式数组的指针
    Stack operators;  //符号栈
    Stack numbers;  //数字栈

private slots:
    void digit_pressed();  //接受按键信号的槽函数
    void lineEdit_return_pressed();  //接受输入框回车信号的槽函数
};

#endif // MAINWINDOW_H
