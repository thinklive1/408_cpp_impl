#include <iostream>
typedef struct LinkNode {
    int data;
    struct LinkNode* next;
}LinkNode;

typedef struct {
    LinkNode* front, * rear;
}LinkQueue;

void InitQueue(LinkQueue& Q) {
    Q.front = Q.rear = new LinkNode; //建立头结点
    Q.front->next = NULL; //初始为空
}

bool IsEmpty(LinkQueue Q) {
    if (Q.front == Q.rear) return true;
    else return false;
}

void EnQueue(LinkQueue& Q, int x) {
    LinkNode* s = new LinkNode;
    s->data = x; s->next = NULL; //创建新结点，插入到链尾
    Q.rear->next = s;
    Q.rear = s;
}

bool DeQueue(LinkQueue& Q, int& x) {
    if (Q.front == Q.rear) return false;//空队
    LinkNode* p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front; //若原队列中只有一个结点，删除后变空
    delete p;
    return true;
}
