#include <iostream>
#include <queue>
using namespace std;
#define MaxSize 64

//线索二叉树
struct ThreadNode {
    int data; //数据元素
    struct ThreadNode* lchild, * rchild; //左、右孩子指针
    int Itag, rtag; //左、右线索标志
};

