#include "../Tree.cpp"
#include <stack>
//0.找到顺序存储二叉树的公共父节点
int find_public_parent(Arraytree T, int i, int j) {
    if (i < 1 || j < 1) return -1;
    while (i != j) {
        if (i > j) i = parent(i);
        else j = parent(j);
    }
    if (i == j && i > 0) return T.data[i];
    return -1;
}

//1.二叉树的自下而上、从右到左的层次遍历算法
void rev_levelOrder(LinkTree T) {//相当于层次遍历的相反顺序，即用栈来存储队列遍历产生的结果
    stack<TreeNode*> stack;
    queue<LinkTree> qe;
    qe.push(T);
    while (!qe.empty()) {
        TreeNode* node = qe.front();
        qe.pop();
        stack.push(node);
        if (node->left != nullptr)
            qe.push(node->left); // 左子节点入队
        if (node->right != nullptr)
            qe.push(node->right); // 右子节点入队
    }
    while (!stack.empty()) {
        visit(stack.top());
        stack.pop();
    }
}

//2.递归求二叉树高度
int height(LinkTree T) {
    if (T == nullptr) return 0;
    return max(height(T->left), height(T->right)) + 1;//优雅的两行实现，但不是尾递归？
}

//3.非递归算法求二叉树的高度
int height2(LinkTree T) {//层序遍历中存储每层最右侧指针，每次出队元素和最右侧指针相同时，高度++
    if (T == nullptr) return 0;
    int height = 0;
    TreeNode* last = T;
    queue<LinkTree> qe;
    qe.push(T);
    while (!qe.empty()) {
        LinkTree node = qe.front();
        qe.pop();
        if (node->left != nullptr) qe.push(node->left);
        if (node->right != nullptr) qe.push(node->right);
        if (node == last) {
            height++;
            last = qe.back();
        }
    }
    return height;
}

//4.先序遍历序列和中序遍历序列分别存于两个一维数组,构建二叉树
LinkTree build_tree_from_pre_and_in(int pre[], int in[], int pre1, int pre2, int in1, int in2) {
    //pre1,pre2分别是先序的第一和最后一个节点下标
    LinkTree root = new TreeNode;
    root->data = pre[pre1];
    int i;
    for (i = in1;in[i] != root->data;i++);//找到根节点来划分左右子树
    int left_len = i - in1;
    int right_len = in2 - i;
    if (left_len != 0) root->left = build_tree_from_pre_and_in(pre, in, pre1 + 1, pre1 + left_len, in1, in1 + left_len - 1);
    else root->left = nullptr;
    if (right_len != 0) root->right = build_tree_from_pre_and_in(pre, in, pre2 - right_len + 1, pre2, in2 - right_len + 1, in2);
    else root->right = nullptr;
    return root;
}

//5.判别给定二叉树是否是完全二叉树
bool if_complete(LinkTree T) {
    queue<LinkTree> qe;
    qe.push(T);
    while (!qe.empty()) {
        LinkTree node = qe.front();
        qe.pop();
        if (node) {
            qe.push(node->left);
            qe.push(node->right);
        }
        else {
            while (!qe.empty()) {
                if (qe.front()) return false;
                qe.pop();
            }
        }
    }
    return true;
}


//6.求给定二叉树的所有双分支结点个数

//7.交换所有结点的左右子树

//8.计算二叉树的所有双分支结点个数

//9.交换树所有结点的左、右子树

//10.求先序遍历序列中第k个节点的值

int main() {
    int temp[8] = { 0, 12, 23, 33,54, 72, 88, INT16_MIN };
    int temp2[3] = { 3,17, 23 };
    LinkTree t = new TreeNode;
    t = build_tree_from_array(t, temp, 8, 1);
    build_tree_helper(t);

    //cout << if_complete(t) << '\n';
    //cout << height2(t) << '\n';
    //cout << height(t) << '\n';
    //rev_levelOrder(t);
    //postOrder2(t);
    levelOrder(t);
}