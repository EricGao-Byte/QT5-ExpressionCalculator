#ifndef STACK_H
#define STACK_H

const int kmax_length = 100;
class Stack
{
public:
    void pushStack(double);  //入栈
    double popStack();  //出栈
    double getStackTop(); //获取栈顶元素
    int getTopLocation();  //获取栈顶的位置
    void setTopLocation(int);  //设置栈顶的位置
    bool isEmpty();  //判断栈是否为空
    bool isFull();  //判断栈是否满了
private:
    int top_=-1;  //栈顶的位置
    double stack_[kmax_length]={0};  //栈数组
};

#endif // STACK_H

