#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //0-9,小数点和变号按键的链接函数
    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_dot,SIGNAL(released()),this,SLOT(digit_pressed()));
    //功能键链接函数
    connect(ui->pushButton_AC,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_backspace,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_leftbra,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_rightbra,SIGNAL(released()),this,SLOT(digit_pressed()));
    //运算键的链接函数
    connect(ui->pushButton_div,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_mul,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_add,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_sub,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_pow,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_sqrt,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_equ,SIGNAL(released()),this,SLOT(digit_pressed()));
    //输入框检测回车的链接函数
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(lineEdit_return_pressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lineEdit_return_pressed()  //按回车的情况
{
    QString nowlineEdit;  //当前输入框的字符串
     nowlineEdit=ui->lineEdit->text();  //初始化输入框,防止异常情况的发生
    if(nowlineEdit=="")  //处理当输入框没有字符,按下等号的情况
    {
        nowlineEdit="0";
    }
    inputMidfix(nowlineEdit);  //输入表达式
    printMidfix();  //打印表达式,debug用
    convertMidfix();  //转换表达式为后缀表达式
    calculatePostfix();  //计算后缀表达式
    ui->label->setText(QString::number(getResult()));  //将计算的结果显示在label结果框上
    operators.setTopLocation(-1);  //初始化栈,防止异常
    numbers.setTopLocation(-1);
}

void MainWindow::digit_pressed()  //按下界面按键的情况
{
//    qDebug()<<operators.getTopLocation();
//    qDebug()<<numbers.getTopLocation();

    QPushButton* button = (QPushButton*)sender();
    QString nowlineEdit,newlineEdit;  //当前输入框的字符串和按键更新后输入框的字符串
    nowlineEdit=ui->lineEdit->text();  //初始化输入框,防止异常情况的发生
    ui->label->setText("");
    //清除键
    if(button->text()=="AC")
    {
        newlineEdit='0';
        ui->lineEdit->setText(newlineEdit);
        ui->label->setText("清除");
    }
    //退格键
    else if(button->text()=="<-x")
    {
        newlineEdit=nowlineEdit;
        newlineEdit.chop(1);  //丢弃表达式的最后一个字符
        ui->lineEdit->setText(newlineEdit);  //更新输入框
        ui->label->setText("退格");  //提示
    }
    //等于
    else if(button->text()=='=')
    {
        if(nowlineEdit=="")  //处理输入框中没有字符的情况
        {
            nowlineEdit="0";
        }
        inputMidfix(nowlineEdit);  //将用户输入的表达式传给表达式转换函数
        printMidfix();  //debug用
        convertMidfix();  //表达式转换函数
        calculatePostfix();  //后缀表达式计算函数
        ui->label->setText(QString::number(getResult()));  //更新结果框
        operators.setTopLocation(-1);  //栈初始化
        numbers.setTopLocation(-1);

    }
    //根号
    else if(button->text()=="根号")
    {
        if(nowlineEdit=='0')  //处理输入根号时,输入框时0的情况
        {
            ui->lineEdit->setText("S");  //由于根号导致乱码,采用大写S代替根号符号
        }
        else
        {
            newlineEdit=nowlineEdit+"S";
            ui->lineEdit->setText(newlineEdit);
        }

    }
    //数字键
    else
    {
        if(nowlineEdit=='0')  //输入框为0时,输入的第一个数字要替换0
        {
            newlineEdit =button->text();
            ui->lineEdit->setText(newlineEdit);
        }
        else  //其他情况直接追加字符到字符串尾
        {
            newlineEdit = nowlineEdit+button->text();
            ui->lineEdit->setText(newlineEdit);
        }
    }
}

double MainWindow::getResult()
{
    return result_;
}

void MainWindow::inputMidfix(QString line_edit)
{
    //将qtring转换,并赋值给midfix_字符数组
//    midfix=line_edit.toLatin1().data();
    strcpy(midfix_,line_edit.toLocal8Bit().data());
}

void MainWindow::printMidfix()
{
    qDebug() << midfix;
}

/* 以下为转换和计算表达式的函数  */


int MainWindow::judgeOperatorPriority(char ope)
{
    switch (ope)  //数字越大,优先级越高
    {
    case '(':return 0;
    case ')':return 0;
    case 'S':return 5;
    case '+':return 2;
    case '-':return 2;
    case '*':return 3;
    case '/':return 3;
    case '^':return 4;
    default:return -1;
    }
}

bool MainWindow::isNumber(char character)
{
    if (character >= '0' && character <= '9' || character == '.')
        {
            return true;
        }
        else
        {
            return false;
        }
}

void MainWindow::addBlank()
{
        *postfix = ' ';
        postfix++;
}

void MainWindow::outputToPostfix(char outputChar)
{
    *postfix = outputChar;
    postfix++;
}

void MainWindow::convertMidfix()
{
    postfix=postfix_;
    bool isfirstrun = true;  //用于解决表达式第一个数字是负数的情况
    //从头到尾扫描用户输入的表达式的midfix_数组
    while (*midfix!='\0')
    {
        //遇到数字和小数点直接输出到postfix_数组
        if (isNumber(*midfix))
        {
            outputToPostfix(*midfix);
            if (!(*(midfix + 1) >= '0' && *(midfix + 1) <= '9') && *(midfix + 1) != '.')
            {
                addBlank();
            }
        }//除数字外其他符号
        else
        {
            if (isfirstrun&&*midfix=='-')  //检测表达式第一个数字是否为负数
            {
                outputToPostfix(*midfix);
            }
            else if (*midfix == '(')//遇到左括号入栈operators符号栈作为结束标志
            {
                operators.pushStack(*midfix);
            }
            else if (*midfix == ')')//当遇到右括号
            {
                //将直到栈底左括号以上的符号弹出
                while (operators.getStackTop() != '(')
                {
                    outputToPostfix(operators.popStack());
                    addBlank();
                }
                operators.popStack();  //弹出'('
            }//若符号栈为空,符号直接入符号栈
            else if (operators.getTopLocation() == -1)
            {
                operators.pushStack(*midfix);
            }//若扫描到的运算符比符号栈栈顶的运算符优先级要大,则该运算符入符号栈
            else if(judgeOperatorPriority(*midfix)>judgeOperatorPriority(operators.getStackTop()))
            {
                operators.pushStack(*midfix);
            }
            else
            {
                while (judgeOperatorPriority(*midfix) <= judgeOperatorPriority(operators.getStackTop()))
                {
                    outputToPostfix(operators.getStackTop());
                    addBlank();
                    operators.popStack();
                    if (operators.isEmpty())
                    {
                        break;
                    }
                }
                operators.pushStack(*midfix);
            }
            if (*(midfix + 1) == '-'&&*midfix!=')')
            {
                outputToPostfix(*(++midfix));
            }
        }
        isfirstrun = false;
        midfix++;
    }
    //读取完成用户输入的数组后将符号栈里剩余的符号依次出栈
    while (!operators.isEmpty())
    {
        outputToPostfix(operators.popStack());
        addBlank();
    }
    *postfix = '\0';
    postfix = postfix_;
    midfix = midfix_;
    qDebug()<<postfix;
}

void MainWindow::calculatePostfix()
{
    postfix = postfix_;
    const char* atof_postfix;  //指向数字段的开头,用于转换字符串中的数字
    while (*postfix != '\0')
    {
        if (isNumber(*postfix)||(*postfix=='-'&&isNumber(*(postfix+1)))) //是数字,直接入数字栈
        {
            atof_postfix = postfix;
            if (*postfix == '-')
            {
                postfix++;
            }
            while (isNumber(*postfix))
            {
                postfix++;
            }
            postfix++; //跳过空格
            numbers.pushStack(atof(atof_postfix));  //atof():将字符串中的数字转换为双精度浮点数
        }
        else  //是数字符
        {
            switch (*postfix)
            {
            case '+':
                numbers.pushStack(Add(numbers.popStack() , numbers.popStack())); break;
            case '-':
                numbers.pushStack(Sub(numbers.popStack() , numbers.popStack()));break;
            case '*':
                numbers.pushStack(Mul(numbers.popStack() , numbers.popStack()));break;
            case '/':
                numbers.pushStack(Div(numbers.popStack() , numbers.popStack()));break;
            case '^':
                numbers.pushStack(Pow(numbers.popStack(), numbers.popStack()));break;
            case 'S':
                numbers.pushStack(Sqrt(numbers.popStack()));break;
            default:
                break;
            }
            postfix++;
        }
    }
    result_ = numbers.popStack();
}


/* 以下为计算函数模块  */

double MainWindow::Add(double opd1, double opd2)
{
    return opd1+opd2;
}


double MainWindow::Sub(double opd1, double opd2)
{
    return opd1 - opd2;
}


double MainWindow::Mul(double opd1, double opd2)
{
    return opd1 * opd2;
}


double MainWindow::Div(double opd1, double opd2)
{
    if (opd2 == 0)
    {
//        ui->label->setText( "错误! 分母不能为0!" );
        return -2345783;
    }
    else
    {
        return opd1 / opd2;
    }
}


double MainWindow::Pow(double opd1, double opd2)
{
    //opd1^opd2 opd1的opd2次方
    double opd = 1;
    int i;
    if (opd2 < 0)
    {
        opd2 = -opd2;
        for ( i = 0; i < opd2; i++)
        {
            opd *= opd1;
        }
        opd = 1.0 / opd;
        return opd;
    }
    else
    {
        for ( i = 0; i < opd2; i++)
        {
            opd *= opd1;
        }
        return opd;
    }
}


double MainWindow::Sqrt(double opd1)
{
    //根号opd1
    if (opd1 < 0)
    {
//        ui->label->setText("错误! 被开方数不能小于0!");
        return -1927348;
    }
    else if(opd1 == 0)
    {
        return opd1;
    }
    else
    {
        int i;
        double opd = opd1 / 2;
        for (i = 0; i < 100; i++)
        {
            opd = 0.5 * (opd + opd1 / opd);
        }
        return opd;
    }
}
