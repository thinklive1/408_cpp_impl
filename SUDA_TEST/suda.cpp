#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <set>
#include <queue>
#define null INT16_MIN
using namespace std;

//c++输入输出,当cin>>从缓冲区中读取数据时，若缓冲区中第一个字符是空格、tab或换行这些分隔符时，cin>>会将其忽略并清除，继续读取下一个字符，若缓冲区为空，则继续等待。但是如果读取成功，字符后面的分隔符是残留在缓冲区的，cin>>不做
//1. 计算a+b
void a_plus_b() {
    cout << "please input two numbers : " << '\n';
    int a, b;
    while (cin >> a >> b) cout << "a+b is " << a + b << '\n';
}

//读取字符串并排序输出
void read_from_line() {
    string l;
    while (getline(cin, l)) {
        stringstream ss(l);
        int sum = 0, num;
        while (ss >> num) sum += num;
        cout << sum << '\n';
    }
}

void sort_strings() {
    string s;
    vector<string> vec;
    while (getline(cin, s)) {
        stringstream ss(s);//初始化语法
        s.clear();
        while (ss >> s) vec.push_back(s);
        sort(vec.begin(), vec.end());
        for (auto i = vec.begin();i != vec.end();i++) cout << *i << ' ';
        cout << '\n';
        vec.clear();
    }
}

void strings_withdot() {
    string s;
    while (getline(cin, s)) {
        stringstream ss(s);
        vector<string> vec;
        while (getline(ss, s, ',')) vec.push_back(s);//getline属于string头文件，可以指定分隔符 
        sort(vec.begin(), vec.end());
        for (int i = 0;i < vec.size() - 1;i++) cout << vec[i] << ',';
        cout << vec.back() << '\n';
    }
}

vector<int> twoSum(vector<int>& nums, int target) {// 暴力解法，O(N^2)
    vector<int> temp, result;
    for (auto i = nums.begin(); i != nums.end();i++) {
        temp.push_back(target - *i);
    }
    int index1 = 0;
    for (auto i = nums.begin(); i != nums.end();i++) {
        int index2 = index1 + 1;
        auto it = temp.begin();
        for (int t = 0;t < index2;t++) it++;
        while (it != temp.end()) {
            if (*i == *it) {
                result.push_back(index1);
                result.push_back(index2);
                return result;
            }
            it++;
            index2++;
        }
        index1++;
    }
    return result;
};

vector<int> twoSum2(vector<int>& nums, int target) {
    /*
    对数组的每个元素：
        1. 查找哈希表是否有其元素值对应的<k,v>,如果有，该<k,v>的v值就是其匹配的数组索引号
        2. 将target与该元素值的差作为k，其索引作为v写入哈希表
    */
    unordered_map<int, int> hash;
    for (int i = 0; i < nums.size();i++) {
        if (hash.find(nums[i]) != hash.end()) return { i,hash[nums[i]] };
        hash[target - nums[i]] = i;
    }
    return {};
}

//给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。必须在不复制数组的情况下原地对数组进行操作。
void moveZeroes(vector<int>& nums) {
    int n = nums.size(), slow = 0, fast = 0;
    if (n <= 1) return;
    while (fast < n) {
        if (nums[slow] == 0) {
            while (fast < n && nums[fast] == 0) ++fast;
            if (fast >= n) return;
            nums[slow] = nums[fast];
            nums[fast] = 0;
            ++slow;
        }
        else { ++slow;++fast; }
    }
}

//一个非空整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素
int singleNumber(vector<int>& nums) {
    int temp = 0;
    for (int i : nums) temp ^= i;
    return temp;
}

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//寻找链表公共节点
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    int m = 0, n = 0;
    ListNode* t = headA->next;
    while (t != NULL) {
        ++m;
        t = t->next;
    }
    t = headB->next;
    while (t != NULL) {
        ++n;
        t = t->next;
    }
    if (m > n) for (int i = 0;i < m - n;i++) headA = headA->next;
    else for (int i = 0;i < n - m;i++) headB = headB->next;
    while (headA && headA != headB) { headA = headA->next;headB = headB->next; }
    return headA;
}

ListNode* getIntersectionNode_better(ListNode* headA, ListNode* headB) {//相当于同时遍历A+B和B+A
    if (headA == NULL || headB == NULL) {
        return NULL;
    }
    ListNode* pA = headA;
    ListNode* pB = headB;
    while (pA != pB) {
        pA = (pA == NULL ? headB : pA->next);
        pB = (pB == NULL ? headA : pB->next);
    }
    return pA;
}


ListNode* build_nodelist_withhead(ListNode* L, vector<int> lst) {
    ListNode* r = L;
    for (int i = 0; i < lst.size(); i++) {
        ListNode* s = new ListNode(lst[i]); // 创建新结点
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return L;
}

ListNode* build_nodelist_withouthead(ListNode* L, vector<int> lst) {
    ListNode* r = L;
    r->val = lst[0];
    for (int i = 1; i < lst.size(); i++) {
        ListNode* s = new ListNode(lst[i]); // 创建新结点
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return L;
}

ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* p = head, * q = head->next;
    p->next = nullptr;
    while (q) {
        auto t = q->next;
        q->next = p;
        p = q;
        q = t;
    }
    return p;
}

//判断该链表是否为回文链表
bool isPalindrome(ListNode* head) {
    ListNode* slow = head, * fast = head;
    while (fast) {
        slow = slow->next;
        fast = fast->next;
        if (!fast) break;
        fast = fast->next;
    }
    slow = reverseList(slow);
    while (head && slow) {
        if (head->val != slow->val) return 0;
        head = head->next;
        slow = slow->next;
    }
    return 1;
}

bool hasCycle(ListNode* head) {
    ListNode* slow = head, * fast = head;
    while (fast) {
        if (slow == fast) return 1;
        slow = slow->next;
        fast = fast->next;
        if (!fast) return 0;
    }
    return 0;
}

//合并两个有序链表
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* head = new ListNode{}; //声明一个新指针不会调用默认构造函数
    ListNode* tail = head, * t;
    while (list1 && list2) {
        t = list1->val < list2->val ? list1 : list2;
        if (t == list1) list1 = list1->next;
        else list2 = list2->next;
        tail->next = t;
        tail = tail->next;
    }
    tail->next = (!list1) ? list2 : list1;
    return head->next;
}

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

using LinkTree = TreeNode*;

/* 获取索引为 i 节点的左子节点的索引 */
int left(int i) {
    return 2 * i + 1;
}

/* 获取索引为 i 节点的右子节点的索引 */
int right(int i) {
    return 2 * i + 2;
}

//从数组构建链式树，如果值是INT_MIN则视为nullptr
LinkTree build_tree_from_array(LinkTree T, vector<int> values, int start = 0) {
    int size = values.size();
    if (values[start] == INT16_MIN) return nullptr;
    T->val = values[start];
    T->left = (left(start) < size) ? build_tree_from_array(new TreeNode, values, left((start))) : nullptr;
    T->right = (right(start) < size) ? build_tree_from_array(new TreeNode, values, right((start))) : nullptr;
    return T;
}

vector<int> inorderTraversal(TreeNode* root) {
    if (!root) return {};
    vector<int> res;
    stack<TreeNode*> st;
    while (root || !st.empty()) {
        if (root) {
            st.emplace(root);
            root = root->left;
        }
        else {
            root = st.top();st.pop();
            res.push_back(root->val);
            root = root->right;
        }
    }
    return res;
}

//假设当前遍历到的节点为 x，将 x 的左子树中最右边的节点的右孩子指向 x，这样在左子树遍历完成后我们通过这个指向走回了 x，且能通过这个指向知晓我们已经遍历完成了左子树，而不用再通过栈来维护
vector<int> inorderTraversal_best(TreeNode* root) {
    vector<int> res;
    TreeNode* predecessor = nullptr;

    while (root != nullptr) {
        if (root->left != nullptr) {
            // predecessor 节点就是当前 root 节点向左走一步，然后一直向右走至无法走为止
            predecessor = root->left;
            while (predecessor->right != nullptr && predecessor->right != root) {
                predecessor = predecessor->right;
            }

            // 让 predecessor 的右指针指向 root，继续遍历左子树
            if (predecessor->right == nullptr) {
                predecessor->right = root;
                root = root->left;
            }
            // 说明左子树已经访问完了，我们需要断开链接
            else {
                res.push_back(root->val);
                predecessor->right = nullptr;
                root = root->right;
            }
        }
        // 如果没有左孩子，则直接访问右孩子
        else {
            res.push_back(root->val);
            root = root->right;
        }
    }
    return res;
}

int maxDepth(TreeNode* root) {
    queue<TreeNode*> qe1, qe2;
    qe1.emplace(root);
    int dep = 0, signal = 0;
    while (1) {
        if (qe1.empty()) return dep;
        while (!qe1.empty()) {
            if (qe1.front()->left) qe2.push(qe1.front()->left);
            if (qe1.front()->right) qe2.push(qe1.front()->right);
            qe1.pop();
        }
        ++dep;
        swap(qe1, qe2);
    }
}

//交换给定节点的左右子树
LinkTree& exchange_lr(LinkTree& root) {
    if (!root) return root;
    queue<TreeNode*> qe;
    qe.push(root);
    while (!qe.empty()) {
        TreeNode* t = qe.front();qe.pop();
        if (t->left) qe.push(t->left);
        if (t->right) qe.push(t->right);
        swap(t->left, t->right);
    }
    return root;
}

TreeNode* invertTree(TreeNode* root) {
    if (!root) return root;
    queue<TreeNode*> qe;
    qe.push(root);
    while (!qe.empty()) {
        TreeNode* t = qe.front();qe.pop();
        if (t->left) qe.push(t->left);
        if (t->right) qe.push(t->right);
        swap(t->left, t->right);
    }
    return root;
}

TreeNode* invertTree2(TreeNode* root) {
    if (!root) {
        return nullptr;
    }
    TreeNode* left = invertTree2(root->left);
    TreeNode* right = invertTree2(root->right);
    root->left = right;
    root->right = left;
    return root;
}

void invert_helper(TreeNode* node) {
    if (!node) return;
    swap(node->left, node->right);
    invert_helper(node->left);
    invert_helper(node->right);
}

TreeNode* invertTree3(TreeNode* root) {
    invert_helper(root);
    return root;
}

bool isCenterSymmetric(TreeNode* root) {
    if (!root) return 1;
    if (root->left && root->right && root->left->val == root->right->val) return isCenterSymmetric(root->left) && isCenterSymmetric(root->right);
    else if (!root->left && !root->right) return 1;
    return 0;
}

bool isSymmetric(TreeNode* root) {
    if (!root) return 1;
    stack<TreeNode*> st1, st2;
    TreeNode* p1 = root;
    TreeNode* p2 = p1;
    st1.emplace(p1);
    st2.emplace(p2);
    while (!st1.empty()) {
        p1 = st1.top();st1.pop();
        p2 = st2.top();st2.pop();
        if ((p1 && !p2) || (p2 && !p1)) return 0;
        else if (!p1) continue;
        else if (p1->val != p2->val) return 0;
        else {
            st1.push(p1->left);
            st1.push(p1->right);
            st2.push(p2->right);
            st2.push(p2->left);
        }
    }
    return 1;
}

bool check(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
}

bool isSymmetric2(TreeNode* root) {
    if (!root) return 1;
    return check(root->left, root->right);
}

int node_height(TreeNode* t) {
    if (!t)
        return 0;
    else {
        int temp = 1 + max(node_height(t->left), node_height(t->right));
        return temp;
    }
}

void diameterOfBinaryTree_helper(TreeNode* root, int& m) {
    if (!root) return;
    diameterOfBinaryTree_helper(root->left, m);
    diameterOfBinaryTree_helper(root->right, m);
    m = max(m, node_height(root->right) + node_height(root->left));
}

//二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点
int diameterOfBinaryTree(TreeNode* root) {
    int dia = 0;
    diameterOfBinaryTree_helper(root, dia);
    return dia;
}

TreeNode* sortedArrayToBST_helper(vector<int>& nums, int head, int tail, TreeNode* parent, bool lft) {
    if (head > tail) return nullptr;
    if (head == tail) return new TreeNode(nums[head]);
    TreeNode* node = new TreeNode;
    int mid = (tail + head) / 2;
    node->val = nums[mid];
    node->left = sortedArrayToBST_helper(nums, head, mid - 1, parent, 1);
    node->right = sortedArrayToBST_helper(nums, mid + 1, tail, parent, 0);
    return node;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    if (nums.empty()) return nullptr;
    int mid = nums.size() / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = sortedArrayToBST_helper(nums, 0, mid - 1, root, 1);
    root->right = sortedArrayToBST_helper(nums, mid + 1, nums.size() - 1, root, 0);
    return root;
}

//给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置
int searchInsert(vector<int>& nums, int target) {
    int head = 0, tail = nums.size() - 1;
    while (head <= tail) {
        int mid = (head + tail) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) head = mid + 1;
        else tail = mid - 1;
    }
    return head;
}

//判断括号字符串是否有效
bool isValid(string s) {
    stack<char> st;
    set<char> se = { '(','{','[' };
    if (se.find(s[0]) == se.end()) return 0;
    unordered_map<char, char> ma = { {')','('},{']','['},{'}','{'} };
    for (char c : s) {
        if (se.find(c) != se.end()) st.push(c);//左括号直接入栈
        else {//c是右括号
            if (st.empty() || ma[c] != st.top()) return 0;
            else st.pop();
        }
    }
    return st.empty();
}

int majorityElement(vector<int>& nums) {
    vector<int> times;
    return 0;
}



int maxProfit(vector<int>& prices) {
    int prev_min = INT16_MAX, pro = 0;;
    for (int i : prices) {
        prev_min = min(i, prev_min);
        pro = max(pro, i - prev_min);
    }
    return pro;
}

int climbStairs(int n) {
    if (n <= 2) return n;
    int steps = 2;
    vector<int> memory = { 0,1,2 };
    while (steps < n) {
        memory[0] = memory[1] + memory[2];
        memory[1] = memory[0];
        swap(memory[1], memory[2]);
        steps++;
    }
    return memory[0];
}

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> um;
    vector<vector<string>> res;
    for (auto s : strs) {
        string t = s;
        sort(t.begin(), t.end());
        um[t].emplace_back(s);
    }
    for (auto i : um) res.push_back(i.second);
    return res;
}

int longestConsecutive(vector<int>& nums) {
    if (nums.empty()) return 0;
    unordered_set<int> us;
    int max_len = 0;
    for (auto i : nums) us.emplace(i);
    while (!us.empty()) {
        int i = *us.begin();
        int len = 0;
        while (us.count(i + 1)) ++i;
        while (us.count(i)) {
            ++len;
            us.erase(i);
            --i;
        }
        max_len = max(max_len, len);
    }
    return max_len;
}

int maxArea(vector<int>& height) {
    int i = 0, j = height.size() - 1, max_ar = (j - i) * min(height[i], height[j]);
    while (i < j) {
        if (height[i] < height[j]) ++i;
        else --j;
        max_ar = max(max_ar, (j - i) * min(height[i], height[j]));
    }
    return max_ar;
}

int main() {
    //a_plus_b();
    vector <int> test = { 0,3,7,2,5,8,4,6,0,1,2,1 };
    vector <int> test2 = { 1,3,4 };
    vector<string> strs = { "eat","tea","tan","ate","nat","bat" };
    ListNode temp(65535);
    ListNode temp2(65535);
    TreeNode* tree1 = new TreeNode;
    tree1 = build_tree_from_array(tree1, test, 0);
    //reverseList(build_nodelist_withouthead(&temp, test));
    //isPalindrome(build_nodelist_withouthead(&temp, test));
    //mergeTwoLists(build_nodelist_withouthead(&temp, test), build_nodelist_withouthead(&temp2, test2));
    //inorderTraversal(build_tree_from_array(tree1, test, 1));
    //cout << maxDepth(build_tree_from_array(tree1, test));
    //invertTree2(tree1);
    //cout << isSymmetric(tree1);
    //cout << diameterOfBinaryTree(tree1);
    //auto bst1 = sortedArrayToBST(test);
    //cout << isValid("(){}}{");
    //cout << maxProfit(test);
    //cout << climbStairs(5);
    //groupAnagrams(strs);
    //cout << longestConsecutive(test);

    //strings_withdot();
    //auto si = twoSum2(test, 6);
    //moveZeroes(test);
}