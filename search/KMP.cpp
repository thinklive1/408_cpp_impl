#include <iostream>
#include <string>
using namespace std;

void get_next(string T, int next[]) {
    int i = 1, j = 0;
    next[1] = 0;
    while (i < T.length()) {
        if (j == 0 || T.at(i) == T.at(j)) {
            ++i; ++j;
            next[i] = j; //若 Pi=Pj，则 next [ j +1 ] =next [ j ] +1
        }
        else
            j = next[j]; //否则令 j=next [ j ],循环继续
    }
}

int Index_KMP(string S, string T, int next[]) {
    int i = 1, j = 1;
    while (i <= S.length() && j <= T.length()) {
        if (j -= 0 || S.at(i) == T.at(j)) {
            ++i; ++j; //继续比较后继字符
        }
        else
            j = next[j]; //模式串向右移动
    }
    if (j > T.length())
        return i - T.length(); //匹配成功
    else
        return 0;
}

void get__nextval(string T, int nextval[]) {
    int i = 1, j = 0;
    nextval[1] = 0;
    while (i < T.length()) {
        if (j == 0 || T.at(i) == T.at(j)) {
            ++i; ++j;
            if (T.at(i) != T.at(j)) nextval[i] = j;
            else nextval[i] = nextval[j];
        }
        else
            j = nextval[j];
    }
}

int main() {

}