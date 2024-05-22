#include "./BST.cpp"

/* 获取节点高度 */
int height(TreeNode* node) {
    // 空节点高度为 -1 ，叶节点高度为 0
    return node == nullptr ? -1 : node->height;
}

/* 更新节点高度 */
void updateHeight(TreeNode* node) {
    // 节点高度等于最高子树高度 + 1
    node->height = max(height(node->left), height(node->right)) + 1;
}

/* 获取平衡因子 */
int balanceFactor(TreeNode* node) {
    // 空节点平衡因子为 0
    if (node == nullptr)
        return 0;
    // 节点平衡因子 = 左子树高度 - 右子树高度
    return height(node->left) - height(node->right);
}

/* 右旋操作 */
TreeNode* rightRotate(TreeNode* node) {
    TreeNode* child = node->left;
    TreeNode* grandChild = child->right;
    // 以 child 为原点，将 node 向右旋转
    child->right = node;
    node->left = grandChild;
    // 更新节点高度
    updateHeight(node);
    updateHeight(child);
    // 返回旋转后子树的根节点
    return child;
}

/* 左旋操作 */
TreeNode* leftRotate(TreeNode* node) {
    TreeNode* child = node->right;
    TreeNode* grandChild = child->left;
    // 以 child 为原点，将 node 向左旋转
    child->left = node;
    node->right = grandChild;
    // 更新节点高度
    updateHeight(node);
    updateHeight(child);
    // 返回旋转后子树的根节点
    return child;
}

/* 执行旋转操作，使该子树重新恢复平衡 */
TreeNode* rotate(TreeNode* node) {
    // 获取节点 node 的平衡因子
    int _balanceFactor = balanceFactor(node);
    // 左偏树
    if (_balanceFactor > 1) {
        if (balanceFactor(node->left) >= 0) {
            // 右旋
            return rightRotate(node);
        }
        else {
            // 先左旋后右旋
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    // 右偏树
    if (_balanceFactor < -1) {
        if (balanceFactor(node->right) <= 0) {
            // 左旋
            return leftRotate(node);
        }
        else {
            // 先右旋后左旋
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    // 平衡树，无须旋转，直接返回
    return node;
}

/* 插入节点 */
void insert(TreeNode* root, int val) {
    root = insertHelper(root, val);
}

/* 递归插入节点（辅助方法） */
TreeNode* insertHelper(TreeNode* node, int val) {
    if (node == nullptr)
        return new TreeNode(val);
    /* 1. 查找插入位置并插入节点 */
    if (val < node->data)
        node->left = insertHelper(node->left, val);
    else if (val > node->data)
        node->right = insertHelper(node->right, val);
    else
        return node;    // 重复节点不插入，直接返回
    updateHeight(node); // 更新节点高度
    /* 2. 执行旋转操作，使该子树重新恢复平衡 */
    node = rotate(node);
    // 返回子树的根节点
    return node;
}

/* 删除节点 */
void remove(TreeNode* root, int val) {
    root = removeHelper(root, val);
}

/* 递归删除节点（辅助方法） */
TreeNode* removeHelper(TreeNode* node, int val) {
    if (node == nullptr)
        return nullptr;
    /* 1. 查找节点并删除 */
    if (val < node->data)
        node->left = removeHelper(node->left, val);
    else if (val > node->data)
        node->right = removeHelper(node->right, val);
    else {
        if (node->left == nullptr || node->right == nullptr) {
            TreeNode* child = node->left != nullptr ? node->left : node->right;
            // 子节点数量 = 0 ，直接删除 node 并返回
            if (child == nullptr) {
                delete node;
                return nullptr;
            }
            // 子节点数量 = 1 ，直接删除 node
            else {
                delete node;
                node = child;
            }
        }
        else {
            // 子节点数量 = 2 ，则将中序遍历的下个节点删除，并用该节点替换当前节点
            TreeNode* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            int tempVal = temp->data;
            node->right = removeHelper(node->right, temp->data);
            node->data = tempVal;
        }
    }
    updateHeight(node); // 更新节点高度
    /* 2. 执行旋转操作，使该子树重新恢复平衡 */
    node = rotate(node);
    // 返回子树的根节点
    return node;
}