#include <iostream>
using namespace std;
#define MaxSize 64
#define ElemType int

//树的双亲节点表示法
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

//求孩子兄弟表示法的树的叶节点数量
int leaves_of_cs(CSTree t) {
    if (!t) return 0;//空节点返回0
    if (!t->firstchild) return 1 + leaves_of_cs(t->nextsibling);//如果孩子节点为空，返回1+兄弟节点的叶节点树
    else return leaves_of_cs(t->nextsibling) + leaves_of_cs(t->firstchild);//孩子节点不空，返回孩子节点和兄弟节点的叶节点数
}

//求孩子兄弟表示法的树的深度
void depth_helper(CSTree t, int depth, int& max_depth) {//记忆递归
    if (!t) {
        max_depth = max(depth, max_depth);
        return;
    }
    depth_helper(t->firstchild, depth + 1, max_depth);
    depth_helper(t->nextsibling, depth, max_depth);
}
int depth_of_cs(CSTree t) {//直接递归
    int hc, hs;
    if (t == NULL)
        return 0;
    else {//否则，高度取子女高度+1和兄弟子树高度的大者
        hc = depth_of_cs(t->firstchild); //第一子女树高
        hs = depth_of_cs(t->nextsibling); //兄弟树高
        if (hc + 1 > hs)
            return hc + 1;
        else
            return hs;
    }
}

//已知一棵树的层次序列及每个结点的度，编写算法构造此树的孩子-兄弟链表
CSTree build_cs_from_levelorder(int degrees[], int len, int levelorder[]) {

}

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

