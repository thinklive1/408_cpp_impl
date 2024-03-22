#include <node_list.cpp>

int main()
{
    int temp[8] = {2, 3, 17, 22, 23, 25, 42, 67};
    LinkList nodes = new LNode;
    build_nodelist(nodes, temp, sizeof(temp) / sizeof(temp[0]));
    // List_HeadInsert(nodes);
    // List_TailInsert(nodes);
    print_linklist(nodes);
}

