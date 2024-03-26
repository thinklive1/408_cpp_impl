#include "node_list.cpp"

// 1.递归删除不带头结点链表值为x的节点
void del_by_val(LinkList& L, const int& x) {
    if (L == NULL) return;
    if (L->data == x) {
        LinkList l = L;
        L = L->next;  // 这里L为调用该函数的外层L->next，故这里实现了L->next=L-next->next
        delete l;
        del_by_val(L, x);
    }
    else
        del_by_val(L->next, x);
}

// 2.在带头结点的单链表L中，删除所有值为x的结点
void del_by_val_withhead(LinkList p, int x) {  // p是先驱节点，最初是头结点
    LinkList q = p->next;
    while (q != NULL) {  // 循环检查后继结点的值是否是x
        if (q->data == x) {
            p->next = q->next;
            LinkList temp = q;
            q = p->next;
            delete temp;
        }
        else {
            p = p->next;
            q = p->next;
        }
    }
}

// 3.带头结点的单链表从尾到头反向输出每个结点的值
void print_linklist_rev(LinkList L) {
    if (L == NULL)
        return;
    else
        print_linklist_rev(L->next);
    cout << L->data << endl;
}

LinkList remove_head(LinkList head) {
    if (head->next == NULL) return NULL;
    return head->next;
}

// 4.在带头结点的单链表L中删除一个最小值结点(假设唯一)
void del_min_withhead(LinkList L) {
    if (L->next == NULL) return;
    LinkList prev = L;
    L = L->next;
    LinkList min_node, min_prev;
    int min_val = INT16_MAX;
    while (L != NULL) {
        if (L->data < min_val) min_node = L, min_prev = prev, min_val = L->data;
        prev = L;
        L = L->next;
    }
    min_prev->next = min_node->next;
    delete min_node;
    cout << "删除的节点值为:" << min_val << endl;
}

//5.将带头结点的单链表就地逆置
LinkList rev_insite_withhead(LinkList L) {
    LinkList head = L, temp; //暂存头结点
    L = L->next;
    LinkList p = L->next;  //L和p分别是先驱后继节点
    L->next = NULL;
    while (p != NULL) {
        temp = p->next; //暂存p之后的链表
        p->next = L;  //反转L和p
        L = p;
        p = temp;
    }
    head->next = L;
    return head;

    /*另一种解法
    LNode* p, * r;
    p = L->next;
    L->next = NULL;
    while (p != NULL) {
        r = p->next;
        p->next = L->next;
        L->next = p;//将P结点插入到头结点之后
        p = r;
    }
    return L;*/
}

/*6.插入排序带头结点的单链表L
    1. 排序部分初始为头结点及其后续一个节点,未排序部分是head->next->next为首的链表
    2. 取一个未排序节点，遍历找到插入位置
    3. 插入节点，将leaft指向之前暂存的未排序部分首个结点
*/
void insertsort_list(LinkList L) {
    LinkList leaft = L->next;//leaft是未排序部分的首个节点
    LinkList remains = leaft->next;
    leaft->next = NULL;
    leaft = remains;
    while (leaft != NULL) {
        remains = leaft->next;
        LinkList prev = L;
        while (prev->next != NULL && leaft->data > prev->next->data) prev = prev->next;
        //注意要先判断next是否为空，否则会访问空指针出现异常！！！
        leaft->next = prev->next;
        prev->next = leaft;
        leaft = remains;
    }
}

//7. 删除无序带头结点单链表介于[x,y]内的值
void del_val_inrange(LinkList L, int x, int y) {
    LinkList p = L, q = L->next;
    while (q != NULL) {
        if (q->data < y && q->data >x) {
            LinkList temp = q;
            p->next = q->next;
            delete temp;
            q = p->next;
            continue;
        }
        p = p->next;
        q = q->next;
    }
}


/*8.找出两个链表的公共结点
若有公共结点，则从其开始，两链表完全一致，因此必出现在距离尾部距离一致的地方
因此可以将较长的链表截断到较短链表长度，随后遍历寻找公共结点
*/
int len_of_list(LinkList L);
LinkList find_public_node(LinkList L1, LinkList L2) {
    int len1 = len_of_list(L1->next);
    int len2 = len_of_list(L2->next);
    LinkList longer, shorter;
    longer = (len1 > len2) ? L1->next : L2->next;
    shorter = (len1 > len2) ? L2->next : L1->next;
    longer = (len1 == len2) ? longer : LocateElem_byno(longer, abs(len1 - len2));
    while (longer != NULL) {
        if (longer == shorter) return longer;
        longer = longer->next;
        shorter = shorter->next;
    }
    return NULL;
}

int len_of_list(LinkList L) {
    int len = 0;
    while (L != NULL) {
        len++;
        L = L->next;
    }
    return len;
}

//9.按递增次序输出单链表中各结点的数据元素，并释放结点,就地算法
void print_and_del_sorted_list(LinkList& L) {
    if (L->next == NULL) return;
    LinkList iter = L->next->next, min = L->next, prev = min, prev_min = L;
    while (iter != NULL) {
        if (min->data > iter->data) min = iter, prev_min = prev;
        prev = iter;
        iter = iter->next;
    }
    prev_min->next = min->next;
    cout << min->data << endl;
    delete min;
    print_and_del_sorted_list(L);
}

//10.将一个带头结点的单链表按奇偶分解成两个链表
pair<LinkList, LinkList> tear_list(LinkList L) {
    int signal = 1;
    LinkList L1head = new LNode, L2head = L;
    LinkList q = L->next;
    L->next = NULL;
    while (q != NULL) {
        LinkList temp = q->next;
        if (signal == 1) {
            signal = 0;
            q->next = L1head->next;
            L1head->next = q;
        }
        else {
            signal = 1;
            q->next = L2head->next;
            L2head->next = q;
        }
        q=temp;
    }
    return make_pair(L1head, L2head);
}

//11.C= {a1, b1,...,an,bn}线性表，采用带头结点的单链表存放，设计一个就地算法，将其拆分为两个线性表，使得A = (a1 a2,,,an}, B= bn,,,b2,b1}
//即一个头插法，一个尾插法
pair<LinkList,LinkList> tear_list_rev(LinkList L) {
    LinkList L1head = new LNode,L1tail=L1head, L2head =L;
    LinkList node = L->next;
    L2head->next=NULL;
    int signal=0;
    while (node !=NULL) {
        LinkList temp = node->next;
        if (signal==0) {
            signal=1;
            L1tail->next=node;
            L1tail=node;
            L1tail->next=NULL;
        }
        else {
            signal=0;
            node->next=L2head->next;
            L2head->next=node;
        }
        node =temp;
    }
    return make_pair(L1head,L2head);
}

//12.递增有序的线性表去除重复元素
void remove_samepart_list(LinkList L) {
    LinkList prev = L->next, q = prev->next;
    while (prev->next!=NULL) {
        q=prev->next;
        if (prev->data==q->data) {
            prev->next=q->next;
            delete q;
            continue;
        }
        prev=prev->next;
    }
}

/*13.两个按元素值递增次序排列的单链表,归并为一个按元素值递增次序排列的单链表，不创造新节点
如果是递减版本，则需要使用头插法
*/
LinkList merge_and_sort(LinkList L1, LinkList L2) {
    LinkList l1node = L1->next,l2node = L2->next,l1tail=L1;
    L1->next=NULL;
    while (l1node!=NULL && l2node!=NULL) {
        LinkList temp;
        if (l1node->data<l2node->data) {
            l1tail->next=l1node;
            l1tail=l1node;
            l1node=l1node->next;
            l1tail->next=NULL;
        }
        else {
            l1tail->next=l2node;
            l1tail=l2node;
            l2node = l2node->next;
            l1tail->next=NULL;
        }
    }
    l1tail->next=(l1node==NULL)?l2node:l1node;
    delete L2;
    return L1;
}

//14.4和B是两个递增有序单链表，用其公共元素产生一个新链表
LinkList build_list_from_public(LinkList L1,LinkList L2) {
    return L1;
}


int main() {
    int temp[8] = { 2, 3, 17, 23, 26, 33, 37, 67 };
    int temp2[3] = { 6,26, 28 };
    LinkList nodes = new LNode;
    LinkList nodes2 = new LNode;
    build_nodelist(nodes, temp,
        sizeof(temp) / sizeof(temp[0]));  // 生成带头结点的测试链表
    build_nodelist(nodes2, temp2,
        sizeof(temp2) / sizeof(temp2[0]));  // 生成带头结点的测试链表
    //nodes2 = merge_list(nodes2, nodes);
    // del_by_val(nodes->next,22);//传入头结点的next就可以视为无头结点链表
    // del_by_val_withhead(nodes,22);
    // print_linklist_rev(remove_head(nodes));
    // del_min_withhead(nodes);
    //nodes = rev_insite_withhead(nodes);
    //insertsort_list(nodes);
    //del_val_inrange(nodes,10,30);
    //find_public_node(nodes,nodes2);
    //print_and_del_sorted_list(nodes2);
/*     auto listpair = tear_list(nodes);
    print_linklist(listpair.first);
    print_linklist(listpair.second); */
/*     auto nodespair = tear_list_rev(nodes);
    print_linklist(nodespair.first);
    print_linklist(nodespair.second); */
    //remove_samepart_list(nodes);
    nodes = merge_and_sort(nodes2,nodes);
    print_linklist(nodes);
}
