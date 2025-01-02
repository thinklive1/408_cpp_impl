#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <sstream>
#include <unordered_map>
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
    ListNode(int x) : val(x), next(NULL) {}
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


ListNode* build_nodelist(ListNode* L, vector<int> lst) {
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

int main() {
    //a_plus_b();
    vector <int> test = { 1,2,3,4,5 };
    ListNode temp(65535);
    reverseList(build_nodelist_withouthead(&temp, test));

    //strings_withdot();
    //auto si = twoSum2(test, 6);
    //moveZeroes(test);
}

