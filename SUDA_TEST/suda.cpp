#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <sstream>
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

vector<int> twoSum(vector<int>& nums, int target) {
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

int main() {
    //a_plus_b();
    strings_withdot();
}

