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
int height2(LinkTree T) {
    int height = 0;
    return height;
}

//4.先序遍历序列和中序遍历序列分别存于两个一维数组,构建二叉树

//5.判别给定二叉树是否是完全二叉树

//6.求给定二叉树的所有双分支结点个数

//7.交换所有结点的左右子树

int main() {
    int temp[8] = { 0, 12, 23, 33,54, 72, 88, 99 };
    int temp2[3] = { 3,17, 23 };
    LinkTree t = new TreeNode;
    t = build_tree_from_array(t, temp, 8, 1);
    build_tree_helper(t);

    //cout << height(t) << '\n';
    //rev_levelOrder(t);
    //postOrder2(t);
    levelOrder(t);
}