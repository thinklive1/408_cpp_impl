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
        q = temp;
    }
    return make_pair(L1head, L2head);
}

//11.C= {a1, b1,...,an,bn}线性表，采用带头结点的单链表存放，设计一个就地算法，将其拆分为两个线性表，使得A = (a1 a2,,,an}, B= bn,,,b2,b1}
//即一个头插法，一个尾插法
pair<LinkList, LinkList> tear_list_rev(LinkList L) {
    LinkList L1head = new LNode, L1tail = L1head, L2head = L;
    LinkList node = L->next;
    L2head->next = NULL;
    int signal = 0;
    while (node != NULL) {
        LinkList temp = node->next;
        if (signal == 0) {
            signal = 1;
            L1tail->next = node;
            L1tail = node;
        }
        else {
            signal = 0;
            node->next = L2head->next;
            L2head->next = node;
        }
        node = temp;
    }
    L1tail->next = NULL;
    return make_pair(L1head, L2head);
}

//12.递增有序的线性表去除重复元素
void remove_samepart_list(LinkList L) {
    LinkList prev = L->next, q = prev->next;
    while (prev->next != NULL) {
        q = prev->next;
        if (prev->data == q->data) {
            prev->next = q->next;
            delete q;
            continue;
        }
        prev = prev->next;
    }
}

/*13.两个按元素值递增次序排列的单链表,归并为一个按元素值递增次序排列的单链表，不创造新节点
如果是递减版本，则需要使用头插法
*/
LinkList merge_and_sort(LinkList L1, LinkList L2) {
    LinkList l1node = L1->next, l2node = L2->next, l1tail = L1;
    L1->next = NULL;
    while (l1node != NULL && l2node != NULL) {
        LinkList temp;
        if (l1node->data < l2node->data) {
            l1tail->next = l1node;
            l1tail = l1node;
            l1node = l1node->next;
        }
        else {
            l1tail->next = l2node;
            l1tail = l2node;
            l2node = l2node->next;
        }
    }
    l1tail->next = (l1node == NULL) ? l2node : l1node;
    delete L2;
    return L1;
}

//14.两个递增有序单链表，用其公共元素产生一个新链表
LinkList build_list_from_public(LinkList L1, LinkList L2) {
    LinkList prev1 = L1, prev2 = L2;
    LinkList L3 = new LNode;
    while (prev1->next != NULL && prev2->next != NULL) {
        if (prev1->next->data == prev2->next->data) {
            LinkList new_node = new LNode;
            new_node->data = prev1->next->data;
            new_node->next = L3->next;
            L3->next = new_node;
            prev1 = prev1->next;
            prev2 = prev2->next;
        }
        else if (prev1->next->data < prev2->next->data) prev1 = prev1->next;
        else prev2 = prev2->next;
    }
    return L3;
}

//15.两个链表分别表示两个集合，其元素递增排列，将其交集存放于A链表
LinkList list_intersection(LinkList L1, LinkList L2) {
    LinkList prev1 = L1, prev2 = L2, l1tail = L1;
    while (prev1->next != NULL && prev2->next != NULL) {
        if (prev1->next->data == prev2->next->data) {
            l1tail->next = prev1->next;
            l1tail = prev1->next;
            prev1 = prev1->next;
            prev2 = prev2->next;
        }
        else if (prev1->next->data < prev2->next->data) prev1 = prev1->next;
        else prev2 = prev2->next;
    }
    l1tail->next = NULL;
    return L1;
}

/*16.两个链表分别是一个整数序列，判断B是否是A的子序列
1. 不断比较两个先驱指针的next
2. 若相等，同时后移
3. 若不等，有两种可能，
    1. 如果该节点是一个子序列的开始，则比较其后续节点与son的后续节点
    2. 否则，比较其后续结点和son的开始节点
*/
bool if_sonlist(LinkList parent, LinkList son) {
    LinkList sonhead = son;
    while (parent->next != NULL) {
        if (son->next == NULL) return true;
        if (parent->next->data == son->next->data) {
            parent = parent->next;
            son = son->next;
        }
        else if (parent->next->data == sonhead->next->data) {
            parent = parent->next;
            son = sonhead->next;
        }
        else {
            parent = parent->next;
            son = sonhead;
        }
    }
    return false;
}

//17. 判断带头结点的循环双链表是否对称
bool if_symmetry(DLinkList L) {
    DLinkList lft = L->next, rht = L->prior;
    while (lft != rht && lft != rht->next) {//边界有两种情况，偶数时，lft会跑到rht右边，奇数时，两者碰到一起
        if (lft->data == rht->data) {
            lft = lft->next;
            rht = rht->prior;
        }
        else return false;
    }
    return true;
}

//18.两个循环单链表,将链表h2链接到链表hl之后，要求链接后的链表仍保持循环链表形式
LinkList merge_loop_list(LinkList L1, LinkList L2) {
    LinkList l1tail = L1, l2tail = L2;
    while (l1tail->next != L1) l1tail = l1tail->next;
    while (l2tail->next != L2) l2tail = l2tail->next;
    l1tail->next = L2->next;
    l2tail->next = L1;
    return L1;
}

//19.反复找出循环单链表中结点值最小的结点并输出，然后将该结点从中删除，直到单链表空为止，再删除表头结点
void find_and_del_minnode_loop(LinkList L) {
    LinkList node = L->next;
    if (node == L) return;
    LinkList min_node_prev = L, work_node = node;
    while (work_node->next != L) {
        if (work_node->next->data < min_node_prev->next->data) min_node_prev = work_node;
        work_node = work_node->next;
    }
    cout << "del min_node:" << min_node_prev->next->data << endl;
    LinkList temp = min_node_prev->next;
    min_node_prev->next = min_node_prev->next->next;
    delete temp;
    find_and_del_minnode_loop(L);
}

//20.判断单链表是否有环
bool if_has_cycle(LinkList L) {
    LinkList slow = L, fast = L;
    while (1) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
        if (fast == NULL || fast->next == NULL) return false;
    }
    return false;
}

LNode* FindLoopStart(LNode* head) {
    LNode* fast = head, * slow = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next; //每次走一步
        fast = fast->next->next; //每次走两步
        if (slow == fast) break; //相遇
    }
    if (fast == NULL || fast->next == NULL)
        return NULL; //没有环，返回NULL
    LNode* pl = head, * p2 = slow;
    while (pl != p2) {
        //分别指向开始点、相遇点
        pl = pl->next;
        p2 = p2->next;
    }
    return pl; //返回入口点
}

//真题1.查找带头结点的链表中倒数第k个位置上的结点
int find_k_rev_node(LinkList L, int k) {
    LinkList prev = L, after = L;
    for (int i = 0;i < k;i++) {
        if (after == NULL) return 0;
        after = after->next;
    }
    while (after != NULL) {
        after = after->next;
        prev = prev->next;
    }
    cout << "the node is:" << prev->data << endl;
    return 1;
}

//真题2.strl和str2分别指向两个单词所在单链表的头结点，找出由strl和str2所指向两个链表共同后缀的起始位置
LinkList find_public_charnode(LinkList L1, LinkList L2) {
    if (L1->next == NULL || L2->next == NULL) return NULL;
    int len1 = len_of_list(L1->next), len2 = len_of_list(L2->next);
    LinkList longer = (len1 > len2) ? L1->next : L2->next;
    LinkList shorter = (len1 > len2) ? L2->next : L1->next;
    for (int i = 0;i < abs(len1 - len2);i++) longer = longer->next;
    while (longer != NULL) {
        if (longer == shorter) return longer;
        longer = longer->next;
        shorter = shorter->next;
    }
    return longer;
}

//真题3.用单链表保存m个整数,其绝对值均小于n,对于链表中data的绝对值相等的结点，仅保留第一次出现的结点而删除其余绝对值相等的结点
LinkList remove_sameabs(LinkList& L, int n) {
    bool bucket[n];
    for (int i = 0;i < n;i++) bucket[i] = 0;
    LinkList prev = L;
    while (prev->next != NULL) {
        if (bucket[abs(prev->next->data)] == true) {
            LinkList temp = prev->next;
            prev->next = prev->next->next;
            delete temp;
        }
        else {
            bucket[abs(prev->next->data)] = true;
            prev = prev->next;
        }
    }
    print_linklist(L);
    return L;
}

//真题4.线性表L =（a1,a2,,an）采用带头结点的单链表保存,就地将其排序为(a1,an,a2,an-1,,,)
LinkList resort_list(LinkList L) {
    LinkList p = L, q = L, r;
    while (q != NULL && q->next != NULL) {//寻找中点
        q = q->next->next;
        p = p->next;
    }
    q = p->next;//令q为后半段第一个节点
    p->next = NULL;//断开前半段
    while (q != NULL) {//逆置后半段
        r = q->next;
        q->next = p->next;
        p->next = q;
        q = r;
    }
    LinkList prev;
    prev = L->next;//前半段第一个节点
    q = p->next;//后半段第一个节点
    while (q != NULL) {//也可以是prev!=p
        r = q->next;//暂存的r是后半段链表下一个要处理的节点
        q->next = prev->next;
        prev->next = q;//将n-i+1号节点插入到i号节点后
        prev = q->next;
        q = r;
    }
    p->next = NULL;//最后形成的链表到p为止
    return L;
}

int main() {
    int temp[8] = { 2, 12, 23, 33,54, 72, 83, 99 };
    int temp2[3] = { 3,17, 23 };
    LinkList nodes = new LNode;
    LinkList nodes2 = new LNode;
    build_nodelist(nodes, temp,
        sizeof(temp) / sizeof(temp[0]));  // 生成带头结点的测试链表
    build_nodelist(nodes2, temp2,
        sizeof(temp2) / sizeof(temp2[0]));  // 生成带头结点的测试链表 
    /*     DLinkList doublelist = new DoubleLNode;
        build_loop_double_list(doublelist, temp, sizeof(temp) / sizeof(temp[0])); */
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
        //nodes = merge_and_sort(nodes2, nodes);
        //print_linklist(build_list_from_public(nodes,nodes2));
        //print_linklist(list_intersection(nodes,nodes2));
        //cout << "A is B's parent?" << if_sonlist(nodes, nodes2) << endl;
        //cout << "symmetry? " << if_symmetry(doublelist) << endl;
//print_loop_linklist(merge_loop_list(build_loop_list(nodes, temp, sizeof(temp) / sizeof(temp[0])), build_loop_list(nodes2, temp2, sizeof(temp2) / sizeof(temp2[0]))));
//find_and_del_minnode_loop(build_loop_list(nodes, temp, sizeof(temp) / sizeof(temp[0])));
    //cout << "has a cycle?" << if_has_cycle(nodes) << endl;
    //find_k_rev_node(nodes, 8);
    //find_public_charnode(nodes, nodes2);
    //remove_sameabs(nodes, 200);
    print_linklist(resort_list(nodes));




    //print_linklist(doublelist);
    //print_linklist(nodes);
}
