#include "node_list.cpp"

//使用栈来判断链表中的数据是否中心对称,前一半元素依次进栈,和后一半元素一一比较
int if_symmetric(LinkList L, int n) {
    int i;
    char s[n / 2];
    LNode* p = L->next;
    for (i = 0;i < n / 2;i++) {
        s[i] = p->data;
        p = p->next;
    }
    if (n % 2 == 1) p = p->next;
    while (p != NULL && s[i] == p->data) {
        i--; //.i充当栈顶指针
        p = p->next;
    }
    if (i == -1)
        return 1;
    else
        return 0; //链表不中心对称
}


//栈顶相向、迎面增长的共享栈
#define maxsize 100 //两个栈共享顺序存储空间所能达到的最多元素数，
#define elemtp int
struct stk {
    elemtp stack[maxsize]; //栈空间
    int top[2]; //top为两个栈顶指针
    stk() {
        top[0] = -1;
        top[1] = maxsize;
    }
};

int push(int i, elemtp x, stk& s) {
    //入栈操作。i为栈号，i=0表示左边的si栈，i=l表示右边的s2栈，x是入栈元素
    //入栈成功返回1,否则返回0
    if (i < 0 || i>1) {
        cout << "栈号输入不对";
        return 0;
    }
    if (s.top[1] - s.top[0] == 1) {
        cout << "栈己满\n";
        return 0;
    }
    switch (i) {
    case 0: s.stack[++s.top[0]] = x; return 1; break;
    case 1: s.stack[--s.top[1]] = x; return 1;
    }
}


elemtp pop(int i, stk& s) {
    //退栈算法。i代表栈号，i=0时为si栈，时为s2栈
    //退栈成功返回退栈元素，否则返回-1
    if (i < 0 || i>1) {
        cout << ("栈号输入错误\n");
        return -1;
    }
    switch (i) {
    case 0:
    if (s.top[0] == -1) {
        cout << "栈空\n";
        return -1;
    }
    else
        return s.stack[s.top[0]--];
    break;
    case 1:
    if (s.top[1] == maxsize) {
        cout << "栈空\n";
        return -1;
    }
    else
        return s.stack[s.top[1]++];
    break;
    }//switch
}

int main() {
    stk s;
    push(1, 1, s);
    pop(1, s);
}

