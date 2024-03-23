#define MaxSize 50  //定义栈中元素的最大个数

typedef struct {
    int data[MaxSize]; //存放栈中元素
    int top; //栈顶指针
} SqStack;

typedef struct Linknode {
    int data; //数据域
    struct Linknode* next; //指针域
}* LiStack; //栈类型定义

void InitStack(SqStack& S) {
    S.top = -1;
}

bool StackEmpty(SqStack S) {
    if (S.top == -1) return true;
    else
        return false;
}

bool Push(SqStack& S, int& x) {
    if (S.top == MaxSize) return false;
    S.data[++S.top] = x;
    return true;
}

bool Pop(SqStack& S, int& x) {
    if (S.top == -1) return false;
    x = S.data[S.top--]; //先出栈，指针再减1
    return true;
}

bool GetTop(SqStack S, int& x) {
    if (S.top == -1)
        return false;
    x = S.data[S.top];
    return true;
}

