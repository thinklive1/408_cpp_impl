#include "../tree.cpp"
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



int main() {
    int temp[8] = { 2, 12, 23, 33,54, 72, INT16_MIN, 99 };
    int temp2[3] = { 3,17, 23 };
    LinkTree t = new TreeNode;
    t = build_tree_from_array(t, temp, 8, 1);
    build_tree_helper(t);
    postOrder2(t);
    //levelOrder(t);
}