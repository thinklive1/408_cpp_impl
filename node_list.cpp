#include <iostream>
using namespace std;
struct LNode
{                              // 定义单链表结点类型
    int data = 0;              // 数据域
    struct LNode* next = NULL; // 指针域
};

struct DoubleLNode
{                                     // 定义双链表结点类型
    int data = 0;                     // 数据域
    struct DoubleLNode* prior = NULL; // 指针域
    struct DoubleLNode* next = NULL;  // 指针域
};

typedef LNode* LinkList;
typedef DoubleLNode* DLinkList;

// 遍历且打印链表,略过头结点
void print_linklist(LinkList L)
{
    L = L->next;
    int i = 1;
    while (L != NULL)
    {
        cout << i++ << ":" << L->data << endl;
        L = L->next;
    }
}

//根据数组以尾插法生成链表
LinkList build_nodelist(LinkList& L, int lst[], int length)
{
    LNode* r = L;
    for (int i = 0; i < length; i++)
    {
        LNode* s = new LNode; // 创建新结点
        s->data = lst[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return L;
}

//头插法生成链表，即遍历顺序和输入顺序相反
LinkList List_HeadInsert(LinkList& L)
{
    LNode* s;
    int x;
    cout << "输入结点的值:" << endl;
    cin >> x; // 输入结点的值
    while (x != 9999)
    {                  // 输入9999表示结束
        s = new LNode; // 创建新结点
        s->data = x;
        s->next = L->next;
        L->next = s; // 将新结点插入表中,L为头指针
        cout << "输入结点的值:" << endl;
        cin >> x; // 输入结点的值
    }
    return L;
}

//尾插法生成链表，即遍历顺序和输入顺序一致
LinkList List_TailInsert(LinkList& L)
{
    int x;
    LNode* r = L;
    cout << "输入结点的值:" << endl;
    cin >> x; // 输入结点的值
    while (x != 9999)
    {
        LNode* s = new LNode;
        s->data = x;
        r->next = s;
        r = s; // r指向新的表尾结点
        cout << "输入结点的值:" << endl;
        cin >> x; // 输入结点的值
    }
    r->next = NULL; // 尾结点指针置空
    return L;
}

//按值查找节点，不存在返回NULL
LNode* LocateElem_byval(LinkList L, int e)
{
    LNode* p = L->next;
    while (p != NULL && p->data != e) // 从第1个结点开始查找data域为e的结点
        p = p->next;
    return p; // 找到后返回该结点指针，否则返回NULL
}

//按序号定位结点，如果越界返回NULL
LNode* LocateElem_byno(LinkList L, int i)
{
    if (i < 1)
        return NULL;
    int j = 1;
    LNode* p = L->next;
    while (p != NULL && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}

//插入删除略,删除时要用delete回收内存！！！

LinkList merge_list(LinkList head, LinkList tail) {
    LinkList temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = tail->next;
    return head;
}
