#include <iostream>
using namespace std;
struct LNode { //定义单链表结点类型
	int data=0; //数据域
	struct LNode *next=NULL; //指针域
};
typedef LNode* LinkList;

LinkList List_HeadInsert(LinkList& L){
	LNode* s;
	int x;
	scanf("%d", &x);//输入结点的值
	while(x != 9999){//输入9999表示结束
	    s = new LNode;//创建新结点
	    s->data = x;
	    s->next = L->next;
	    L->next = s;//将新结点插入表中,L为头指针
	    scanf("%d", &x);
	}
	return L;
}


int main() {
    LinkList nodes= new LNode;
    List_HeadInsert(nodes);
}





