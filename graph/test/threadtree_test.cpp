#include"../ThreadTree.cpp"


//16.在中序线索二叉树里查找指定结点在后序的前驱结点
ThreadTree find_pre_node(ThreadTree& t, ThreadTree& p) {
    //在中序线索二叉树t中，求指定结点p在后序下的前驱结点q
    ThreadTree q;
    if (p->rtag == 0) //若p有右子女，则右子女是其后序前驱
        q = p->rchild;
    else if (p->ltag == 0) //若p只有左子女，则左子女是其后序前驱
        q = p->lchild;
    else if (p->lchild == NULL)
        q = NULL; //p是中序序列第一结点，无后序前驱
    else { //顺左线索向上找p的祖先，若存在，再找祖先的左子女
        while (p->ltag == 1 && p->lchild != NULL)
            p = p->lchild;
        if (p->ltag == 0)
            q = p->lchild; //p结点的祖先的左子女是其后序前驱
        else
            q = NULL; //仅有单支树(p是叶子)，己到根结点，p无后序前驱
    }
    return q;
}