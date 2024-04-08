#include <iostream>
#include <queue>
#include <stack>
using namespace std;
#define MaxSize 64

struct TreeNode {
    int data; //数据域
    struct TreeNode* left, * right; //左、右孩子指针
    TreeNode() : data(0), left(nullptr), right(nullptr) {}
};
using LinkTree = TreeNode*;

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

void visit(TreeNode* node) {
    cout << node->data << '\n';
}

//层次遍历
void levelOrder(TreeNode* root) {
    // 初始化队列，加入根节点
    queue<TreeNode*> queue;
    queue.push(root);
    // 初始化一个列表，用于保存遍历序列
    while (!queue.empty()) {
        TreeNode* node = queue.front();
        queue.pop();              // 队列出队
        visit(node);
        if (node->left != nullptr)
            queue.push(node->left); // 左子节点入队
        if (node->right != nullptr)
            queue.push(node->right); // 右子节点入队
    }
}

/* 前序遍历 */
void preOrder(TreeNode* root) {
    if (root == nullptr)
        return;
    // 访问优先级：根节点 -> 左子树 -> 右子树
    visit(root);
    preOrder(root->left);
    preOrder(root->right);
}

/* 中序遍历 */
void inOrder(TreeNode* root) {
    if (root == nullptr)
        return;
    // 访问优先级：左子树 -> 根节点 -> 右子树
    inOrder(root->left);
    visit(root);
    inOrder(root->right);
}

/* 后序遍历 */
void postOrder(TreeNode* root) {
    if (root == nullptr)
        return;
    // 访问优先级：左子树 -> 右子树 -> 根节点
    postOrder(root->left);
    postOrder(root->right);
    visit(root);
}

/*非递归实现
思路是通过堆栈不断将优先级高的节点入栈
入栈到尽头时出栈
*/

//中序遍历的非递归算法
void InOrder2(TreeNode* T) {
    stack<TreeNode*> S;
    TreeNode* p = T;
    while (p || !S.empty()) {
        if (p) {
            S.push(p);
            p = p->left;
        }
        else {
            p = S.top(); S.pop();
            visit(p);
            p = p->right;
        }

    }
}

//先序遍历的非递归算法
void PreOrder2(TreeNode* T) {
    stack<TreeNode*> S;
    TreeNode* p = T;
    while (p || !S.empty()) {
        if (p) {
            visit(p);
            S.push(p);
            p = p->left;
        }
        else {
            p = S.top(); S.pop();
            p = p->right;
        }
    }
}

//后序遍历的非递归算法
/*
难点在于，首先要把所有左孩子入栈
直到第一个没有左孩子的结点入栈，但此时不能访问
必须确保先把该节点的右孩子(如果存在，且没有访问过)也访问了，再访问该节点
那么，visit有几种情况呢？
1. 叶节点，此时可以放心访问
2. 有右孩子，但右孩子访问过，此时也可以访问
只要确保只在这两种情况下visit，就是安全的后序遍历
*/
void postOrder2(LinkTree T) {
    LinkTree pre = nullptr;
    stack<TreeNode*> st;
    while (T || !st.empty()) {
        if (T) {
            st.push(T);
            T = T->left;
        }//一路遍历到没有左孩子，此时可能有右孩子
        else {
            T = st.top();//读节点但不弹出
            if (T->right && T->right != pre) T = T->right;//如果有右孩子，且没有访问过，右孩子入栈
            else {
                T = st.top();
                st.pop();
                visit(T);
                pre = T;
                T = nullptr;
            }
        }
    }
}

//从数组构建链式树，如果值是INT_MIN则视为nullptr
LinkTree build_tree_from_array(LinkTree T, int values[], int size, int start = 1) {
    T->data = values[start];
    T->left = (left(start) < size) ? build_tree_from_array(new TreeNode, values, size, left((start))) : nullptr;
    T->right = (right(start) < size) ? build_tree_from_array(new TreeNode, values, size, right((start))) : nullptr;
    return T;
}

//将值是int_min的节点设为空，并回收内存
void build_tree_helper(LinkTree& T) {
    if (T == nullptr) return;
    if (T->data == INT16_MIN) {
        LinkTree temp = T;
        T = nullptr;
        return;
        delete temp;
    }
    build_tree_helper(T->left);
    build_tree_helper(T->right);
}

//交换给定节点的左右子树
LinkTree& exchange_lr(LinkTree& T) {
    LinkTree temp = T->left;
    T->left = T->right;
    T->right = temp;
    return T;
}