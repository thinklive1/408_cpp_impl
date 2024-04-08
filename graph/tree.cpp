#include <iostream>
#include <queue>
#include <stack>
using namespace std;
#define MaxSize 64

struct TreeNode {
    int data; //数据域
    struct TreeNode* left, * right; //左、右孩子指针
    TreeNode() { left = nullptr; right = nullptr; }
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
    cout << node->data << endl;
}

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
void postOrder2(LinkTree T) {
    LinkTree pre = nullptr;
    stack<TreeNode*> st;
    while (T || !st.empty()) {
        if (T) {
            st.push(T);
            T = T->left;
        }
        else {
            T = st.top();//读节点但不弹出
            if (T->right && T->right != pre) T = T->right;
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