#include <iostream>
using namespace std;
#define MaxSize 64

struct LinkTreeNode {
    int data; //数据域
    struct LinkTreeNode* lchild, * rchild; //左、右孩子指针
    LinkTreeNode() { lchild = NULL; rchild = NULL; }
};
using LinkTree = LinkTreeNode*;

struct Arraytree {
    int data[MaxSize];
    int size = 0;
};


/* 获取索引为 i 节点的左子节点的索引 */
int left(int i) {
    return 2 * i;
}

/* 获取索引为 i 节点的右子节点的索引 */
int right(int i) {
    return 2 * i + 1;
}

/* 获取索引为 i 节点的父节点的索引 */
int parent(int i) {
    return i / 2;
}

int find_public_parent(Arraytree T, int i, int j) {
    if (i < 1 || j < 1) return -1;
    while (i != j) {
        if (i > j) i = parent(i);
        else j = parent(j);
    }
    if (i == j && i > 0) return T.data[i];
    return -1;


}

int main() {

}