#include <iostream>
#include <queue>
using namespace std;
#define MaxSize 64

//线索二叉树
struct ThreadNode {
    int data; //数据元素
    struct ThreadNode* lchild, * rchild; //左、右孩子指针
    bool ltag, rtag; //左、右线索标志
    ThreadNode() { lchild = rchild = NULL; ltag = rtag = 0; }
};
using ThreadTree = ThreadNode*;

void visit(ThreadNode* node) {
    cout << node->data << endl;
}

//使用中序遍历线索化二叉树
//先序线索化中当ltag==0时才能对左子树先序列线索化,否则可能形成环
void InThread(ThreadTree& p, ThreadTree& pre) {
    if (p != NULL) {
        InThread(p->lchild, pre); //递归，线索化左子树
        if (p->lchild == NULL) {//左子树为空，建立前驱线索
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = p; //建立前驱结点的后继线索
            pre->rtag = 1;
        }
        pre = p; //标记当前结点成为刚刚访问过的结点
        InThread(p->rchild, pre); //递归，线索化右子树
    }//if(p!=NULL)
}

//使用中序遍历建立线索二叉树
void CreatelnThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {
        InThread(T, pre);
        pre->rchild = NULL;//中序遍历的最后一个结点右孩子指针必为空,不需要判空
        pre->rtag = 1;
    }
}

//求中序线索二叉树中中序序列下的第一个结点
ThreadNode* Firstnode(ThreadNode* p) {
    while (p->ltag == 0) p = p->lchild; //最左下结点(不一定是叶结点)
    return p;
}

//求中序线索二叉树中结点p在中序序列下的后继
ThreadNode* Nextnode(ThreadNode* p) {
    if (p->rtag == 0) return Firstnode(p->rchild);
    else return p->rchild; //rtag==1 直接返回后继线索
}

//不含头结点的中序线索二叉树的中序遍历
void Inorder(ThreadNode* T) {
    for (ThreadNode* p = Firstnode(T);p != NULL; p = Nextnode(p))
        visit(p);
}


//先序线索化
void PreThread(ThreadTree p, ThreadTree& pre) {
    if (p != NULL) {
        if (p->lchild == NULL) {//左子树
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = p;        //建立前
            pre->rtag = 1;
        }
        pre = p;               //标记当
        if (p->ltag == 0)
            PreThread(p->lchild, pre);
        PreThread(p->rchild, pre);
    }//if（p!=NULL）
}

//先序线索化二叉树T
void CreatePreThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {//非空二叉树，线索化
        PreThread(T, pre);//线索化二叉树
        if (pre->rchild == NULL)//处理遍历的最后一个结点
            pre->rtag = 1;
    }
}

//后序线索化
void PostThread(ThreadTree p, ThreadTree& pre) {
    if (p != NULL) {
        PostThread(p->lchild, pre);
        PostThread(p->rchild, pre);
        if (p->lchild == NULL) {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
    }//if(p!=NULL)
}

//后序线索化二叉树T
void CreatePostThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {//非空二叉树，线索化
        PostThread(T, pre);//线索化二叉树
        if (pre->rchild == NULL)//处理遍历的最后一个结点
            pre->rtag = 1;
    }
}
