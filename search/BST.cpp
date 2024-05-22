#include <iostream>
#include <string>
//#include "./graph/Tree.cpp"
using namespace std;
/* AVL 树节点类 */
struct TreeNode {
    int data{};          // 节点值
    int height = 0;     // 节点高度
    TreeNode* left{};   // 左子节点
    TreeNode* right{};  // 右子节点
    TreeNode() = default;
    TreeNode(int x) : data(x) {}
};

/* 查找节点 */
TreeNode* search(TreeNode* root, int num) {
    TreeNode* cur = root;
    // 循环查找，越过叶节点后跳出
    while (cur != nullptr) {
        // 目标节点在 cur 的右子树中
        if (cur->data < num)
            cur = cur->right;
        // 目标节点在 cur 的左子树中
        else if (cur->data > num)
            cur = cur->left;
        // 找到目标节点，跳出循环
        else
            break;
    }
    // 返回目标节点
    return cur;
}

/* 插入节点 */
void insert(TreeNode* root, int num) {
    // 若树为空，则初始化根节点
    if (root == nullptr) {
        root = new TreeNode(num);
        return;
    }
    TreeNode* cur = root, * pre = nullptr;
    // 循环查找，越过叶节点后跳出
    while (cur != nullptr) {
        // 找到重复节点，直接返回
        if (cur->data == num)
            return;
        pre = cur;
        // 插入位置在 cur 的右子树中
        if (cur->data < num)
            cur = cur->right;
        // 插入位置在 cur 的左子树中
        else
            cur = cur->left;
    }
    // 插入节点
    TreeNode* node = new TreeNode(num);
    if (pre->data < num)
        pre->right = node;
    else
        pre->left = node;
}

/* 删除节点 */
void remove(TreeNode* root, int num) {
    // 若树为空，直接提前返回
    if (root == nullptr)
        return;
    TreeNode* cur = root, * pre = nullptr;
    // 循环查找，越过叶节点后跳出
    while (cur != nullptr) {
        // 找到待删除节点，跳出循环
        if (cur->data == num)
            break;
        pre = cur;
        // 待删除节点在 cur 的右子树中
        if (cur->data < num)
            cur = cur->right;
        // 待删除节点在 cur 的左子树中
        else
            cur = cur->left;
    }
    // 若无待删除节点，则直接返回
    if (cur == nullptr)
        return;
    // 子节点数量 = 0 or 1
    if (cur->left == nullptr || cur->right == nullptr) {
        // 当子节点数量 = 0 / 1 时， child = nullptr / 该子节点
        TreeNode* child = cur->left != nullptr ? cur->left : cur->right;
        // 删除节点 cur
        if (cur != root) {
            if (pre->left == cur)
                pre->left = child;
            else
                pre->right = child;
        }
        else {
            // 若删除节点为根节点，则重新指定根节点
            root = child;
        }
        // 释放内存
        delete cur;
    }
    // 子节点数量 = 2
    else {
        // 获取中序遍历中 cur 的下一个节点
        TreeNode* tmp = cur->right;
        while (tmp->left != nullptr) {
            tmp = tmp->left;
        }
        int tmpVal = tmp->data;
        // 递归删除节点 tmp
        remove(root, tmp->data);
        // 用 tmp 覆盖 cur
        cur->data = tmpVal;
    }
}

