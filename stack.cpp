#include"stack.h"
#include <QDebug>
#include <cstdlib>
void Stack::pushStack(double data)
{
    if (!isFull())
    {
        stack_[++top_] = data;  //先上升栈顶位置一个单位
    }
    else
    {
        qDebug() << "Stack fulled!";
    }
}

double Stack::popStack()
{
    if (!isEmpty())
    {
        return stack_[top_--];  //返回栈顶值,并下降栈顶的位置一个单位
    }
    else
    {
        qDebug() << "Error! Stack is already empty!" << endl;
        exit(-1);
    }
}


double Stack::getStackTop()
{
    if (!isEmpty())
    {
        return stack_[top_];  //返回栈顶值,不下降栈顶位置
    }
    else
    {
        qDebug() << "Error! Stack is already empty!";
        exit(-2);
    }

}


int Stack::getTopLocation()
{
    return top_;
}


bool Stack::isEmpty()
{
    if (top_ == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Stack::isFull()
{
    if (top_ == kmax_length - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Stack::setTopLocation(int top)
{
    top_=top;
}

//void Stack::setDefault()
//{
//    top_=-1;
//    stack_[kmax_length]={0};
//}



