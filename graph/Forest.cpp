#include <iostream>
using namespace std;
#define MaxSize 64
#define ElemType int

struct PTNode {
    ElemType data;
    int parent;
};
struct PTree {
    PTNode nodes[MaxSize];
    int n;
};
struct CSNode {
    ElemType data; //数据域
    struct CSNode* firstchild, * nextsibling; //第一个孩子和右兄弟指针
};
using CSTree = CSNode*;

int UFSets[MaxSize]; //集合元素数组(双亲指针数组)
void Initial(int S[]) {
    for (int i = 0; i < MaxSize; i++) //每个自成单元素集合
        S[i] = -1;
}
int Find(int S[], int x) {
    while (S[x] >= 0) //循环寻找x的根
        x = S[x];
    return x; //根的 S[]小于 0
}
void Union(int S[], int Root1, int Root2) {
    if (Root1 == Root2) return; //要求 Root1 与 Root2 是不同的集合
    S[Root2] = Root1; //将根 Root2 连接到另一根 Root1 下面
}