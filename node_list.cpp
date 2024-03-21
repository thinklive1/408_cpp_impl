#include <iostream>
using namespace std;
struct LNode { //定义单链表结点类型
	int data=0; //数据域
	struct LNode *next=NULL; //指针域
};
typedef LNode* LinkList;

void print_linklist(LinkList& L) {
    int i=1;
    while (L!=NULL)
    {
        cout << i++ <<":" << L->data << endl;
        L=L->next;
    }
    
}

LinkList List_HeadInsert(LinkList& L){
	LNode* s;
	int x;
    cout << "输入结点的值:" << endl;
	cin >> x;//输入结点的值
	while(x != 9999){//输入9999表示结束
	    s = new LNode;//创建新结点
	    s->data = x;
	    s->next = L->next;
        L->next = s; // 将新结点插入表中,L为头指针
        cout << "输入结点的值:" << endl;
        cin >> x; // 输入结点的值
    }
    return L;
}

LinkList ListTailInsert(LinkList &L)
{
    int x;
    LNode *s, *r = L;
    cout << "输入结点的值:" << endl;
    cin >> x; // 输入结点的值
    while (x != 9999)
    {
        s = new LNode;
        s->data = x;
        r->next = s;
        r = s; // r指向新的表尾结点
        cout << "输入结点的值:" << endl;
        cin >> x; // 输入结点的值
    }
    r->next = NULL; // 尾结点指针置空
    return L;
}

int main() {
    LinkList nodes= new LNode;
    //List_HeadInsert(nodes);
    print_linklist(nodes);
}





