#include "node_list.cpp"

//1.递归删除不带头结点链表值为x的节点
void del_by_val(LinkList& L,const int& x) {
    if (L==NULL) return;
    if (L->data==x) {
        LinkList l = L;
        L=L->next;//这里L为调用该函数的外层L->next，故这里实现了L->next=L-next->next
        delete l;
        del_by_val(L,x);
    } 
    else del_by_val(L->next,x);
}

//2.在带头结点的单链表L中，删除所有值为x的结点
void del_by_val_withhead(LinkList p, int x) {//p是先驱节点，最初是头结点
    LinkList q=p->next;
    while (q != NULL) {  //循环检查后继结点的值是否是x
        if (q->data == x) {
            p->next = q->next;
            LinkList temp = q;
            q=p->next;
            delete temp;
        }
        else {
            p = p->next;
            q = p->next;
        }
    }
}

//3.带头结点的单链表从尾到头反向输出每个结点的值
void print_linklist_rev(LinkList L) {
    if (L==NULL) return;
    else print_linklist_rev(L->next);
    cout << L->data << endl;
}

LinkList remove_head(LinkList head) {
    if (head->next==NULL) return NULL;
    return head->next;
}

//4.在带头结点的单链表L中删除一个最小值结点(假设唯一)
void del_min_withhead(LinkList L) {
    if (L->next==NULL) return;
    LinkList prev=L;
    L=L->next;
    LinkList min_node,min_prev;
    int min_val=INT16_MAX;
    while(L!=NULL) {
        if (L->data<min_val) min_node=L,min_prev=prev,min_val=L->data;
        prev=L;
        L=L->next;
    }
    min_prev->next=min_node->next;
    delete min_node;
    cout << "删除的节点值为:" << min_val << endl;

}


int main() {
    int temp[8] = {2, 3, 17, 22, 22, 1, 22, 67};
    LinkList nodes = new LNode;
    build_nodelist(nodes, temp, sizeof(temp) / sizeof(temp[0]));//生成带头结点的测试链表
    //del_by_val(nodes->next,22);//传入头结点的next就可以视为无头结点链表
    //del_by_val_withhead(nodes,22);
    //print_linklist_rev(remove_head(nodes));
    //del_min_withhead(nodes);
    print_linklist(nodes);
}
