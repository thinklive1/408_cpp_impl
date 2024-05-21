#include "../Tree.cpp"
#include <stack>
#include "../../container/Linked_list.cpp"

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
int num_of_twinnode(LinkTree& T) {//优雅的递归
    if (T == nullptr) return 0;
    if (T->left && T->right) return 1 + num_of_twinnode(T->left) + num_of_twinnode(T->right);
    else return num_of_twinnode(T->left) + num_of_twinnode(T->right);
}

//7.交换所有结点的左右子树
void swap_lr(LinkTree& T) {
    if (T) {
        swap_lr(T->left);
        swap_lr(T->right);
        LinkTree L = T->left;
        T->left = T->right;
        T->right = L;
    }
}

//8.求先序遍历序列中第k个节点的值
int preOrder_kth_node(LinkTree T, int& i, int& k) {
    if (k <= 0) return INT32_MIN;//输入不合理，直接退出
    if (k == i) return T->data;//由于每次递归i只+1,因此达到k时必然立刻返回
    int val;
    if (T->left) val = preOrder_kth_node(T->left, ++i, k);//存储对左子树遍历后的值
    if (i == k) return val;//如果遍历完左子树，且i==k,那么返回值必然是ith节点的data
    else if (T->right) return preOrder_kth_node(T->right, ++i, k);//如果右孩子不空，才可以++i
    else return INT16_MIN;
}

//9.对于树中每个元素值为x的结点，删除以x为根的子树，并释放相应的空间
void del_val_x_node_helper(LinkTree& T, int& x, LinkTree& pre, bool is_lft) {
    if (!T) return;
    del_val_x_node_helper(T->left, x, T, 1);
    del_val_x_node_helper(T->right, x, T, 0);
    if (T->data == x) {
        del_node(T);//递归删除T的所有子节点
        if (is_lft) pre->left = nullptr;
        else pre->right = nullptr;
    }
}

void del_val_x_node(LinkTree& T, int x) {
    if (T->data == x) del_node(T);
    else {
        del_val_x_node_helper(T->left, x, T, 1);
        del_val_x_node_helper(T->right, x, T, 0);
    }
}

//10.打印值为x的结点的所有祖先，假设值为x的结点不多于一个
bool print_ancestor_helper(LinkTree& T, int& x);
void print_ancestor_of_xval(LinkTree& T, int x) {
    print_ancestor_helper(T, x);
}

bool print_ancestor_helper(LinkTree& T, int& x) {
    //递归返回true表示该节点的子节点中有x节点，因此可以打印，否则不能打印
    if (!T) return false;
    if (T->data == x) return true;
    bool val1 = print_ancestor_helper(T->left, x);
    if (val1 == 1) cout << T->data << '\n';
    bool val2 = print_ancestor_helper(T->right, x);
    if (val2 == 1) cout << T->data << '\n';
    return val1 || val2;
}
//非递归实现用到栈，访问到值为x的结点时，栈中所有元素均为该结点的祖先，依次出栈打印


//11.p和q分别为指向该二叉树中任意两个结点的指针,寻找其最近公共祖先
//祖先有两种可能：1.该节点左右子树各自存在pq 2.节点本身是p或q且其左子树或右子树有另一个孩子节点
bool ancestor_helper(LinkTree tree, LinkTree& p, LinkTree& q, LinkTree& res) {
    if (!tree) return false;
    bool is_lft_son = ancestor_helper(tree->left, p, q, res);
    bool is_rht_son = ancestor_helper(tree->right, p, q, res);
    if ((is_lft_son && is_rht_son) || ((tree->data == p->data || tree->data == q->data) && (is_lft_son || is_rht_son))) {
        res = tree;
    }
    return is_lft_son || is_rht_son || (tree->data == p->data || tree->data == q->data);
}

LinkTree find_ancestor_root(LinkTree root, LinkTree p, LinkTree q) {
    LinkTree res = nullptr;
    ancestor_helper(root, p, q, res);
    return res;
}

//12.求非空二叉树的宽度（结点数最多的一层的结点个数）
int width_of_tree(LinkTree& T) {
    if (!T) return 0;
    int max_layer = 1;
    queue<LinkTree> qe;
    queue<LinkTree> next_qe;
    qe.push(T);
    while (true) {
        while (!qe.empty()) {
            LinkTree t = qe.front();
            qe.pop();
            if (t->left) next_qe.push(t->left);
            if (t->right) next_qe.push(t->right);
        }
        if (next_qe.empty()) break;
        max_layer = max(int(next_qe.size()), max_layer);
        qe = next_qe;
        while (!next_qe.empty()) next_qe.pop();
    }
    return max_layer;
}

//13.一棵满二叉树(所有结点值均不同),已知其先序序列为pre,求其后序序列post。
void find_post_from_pre(int pre[], int l1, int h1, int post[], int l2, int h2) {
    int half;
    if (h1 >= l1) {
        post[h2] = pre[11];
        half = (h1 - l1) / 2;
        find_post_from_pre(pre, 11 + 1, 11 + half, post, 12, 12 + half - 1); //转换左子树
        find_post_from_pre(pre, 11 + half + 1, h1, post, 12 + half, h2 - 1); //转换右子树
    }
}

//14.将二叉树的叶结点按从左到右的顺序连成一个带头结点单链表，表头指针为head，叶结点的右指针域来存放单链表指针
void tree_to_link_helper(LinkTree t, LinkTree& tail) {
    if (!t->left && !t->right) {
        tail->right = t;
        tail = t;
    }
    else {
        tree_to_link_helper(t->left, tail);
        tree_to_link_helper(t->right, tail);
    }
}

LinkTree tree_to_link(LinkTree& T) {
    LinkTree head = new TreeNode;
    LinkTree tail = head;
    head->data = INT16_MIN;
    head->left = nullptr;
    head->right = tail;
    tree_to_link_helper(T, tail);
    return head;
}

/*15.判断二叉树是否相似，相似的定义：
T1和T2都是空的二叉树或都只有一个根结点；
或者T1的左子树和T2的左子树相似，且T1的右子树和T2的右子树相似
*/
bool if_tree_similar(LinkTree& T1, LinkTree& T2) {
    if (!T1 && !T2) return true;
    if (!T1 || !T2) return false;
    return if_tree_similar(T1->left, T2->left) && if_tree_similar(T1->right, T2->right);
}


//真题1.求出二叉树中所有叶结点的带权路径长度之和,需要权值乘层高
//视data为weight
void sum_weight_helper(LinkTree t, int& sum, int path_weight, int depth) {
    if (!t) return;
    if (!t->left && !t->right) {
        sum += path_weight + t->data * depth;
    }
    path_weight += t->data * depth;
    sum_weight_helper(t->left, sum, path_weight, depth + 1);
    sum_weight_helper(t->right, sum, path_weight, depth + 1);
}
int sum_weight(LinkTree& t) {
    int w = 0;
    sum_weight_helper(t, w, 0, 0);
    return w;
}

//2.真题2: 将给定的表达式树（二叉树）转换为等价的中缀表达式
void expression_helper(LinkTree t, int h) {
    if (!t) return;
    if (!t->left && !t->right) cout << t->data;
    else {
        if (h > 1) cout << '(';
        expression_helper(t->left, h + 1);
        cout << t->data;
        expression_helper(t->right, h + 1);
        if (h > 1) cout << ')';
    }
}
void expression(LinkTree t) {
    expression_helper(t, 1);
}

//3.真题3： 判定一棵采用顺序表存储的二叉树是否为二叉搜索树
bool is_bst_helper(Arraytree t, int index) {
    if (t.size < index * 2) return true;
    else if (t.size == index * 2) return t.data[index] >= t.data[index * 2] && is_bst_helper(t, index * 2);
    else return t.data[index] >= t.data[index * 2 + 1]
        && t.data[index] <= t.data[index * 2 + 1]
        && is_bst_helper(t, index * 2)
        && is_bst_helper(t, index * 2 + 1);
}
bool is_bst(Arraytree t) {
    return is_bst_helper(t, 1);
}

int main() {
    int temp[8] = { 0, 8,14, 25,54, 72, 88, 99 };
    int temp2[3] = { 3,17, 23 };
    LinkTree t = new TreeNode;
    t = build_tree_from_array(t, temp, 8, 1);
    build_tree_helper(t);

    /*     auto leaves = tree_to_link(t)->right;
        while (leaves) {
            cout << leaves->data << '\n';
            leaves = leaves->right;
        } */
        //cout << width_of_tree(t);
        //cout << "ancestor is:" << find_ancestor_root(t, t->left->left, t->left->right)->data;
        //print_ancestor_of_xval(t, 54);
        //del_val_x_node(t, 88);
        /* for (int i = 1;i < 8;i++) {
            int j = 1;
            cout << i << "th node: " << preOrder_kth_node(t, j, i) << '\n';
        } */
        //cout << num_of_twinnode(t);
    //cout << if_complete(t) << '\n';
    //cout << height2(t) << '\n';
    //cout << height(t) << '\n';
    //rev_levelOrder(t);
    //postOrder2(t);
    //levelOrder(t);
}