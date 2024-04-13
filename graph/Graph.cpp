#include <iostream>
#include <queue>
using namespace std;
#define MaxVertexNum 64
#define ElemType int

using VertexType = char;
using EdgeType = int;

struct Matrix_Graph {
    VertexType Vex[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum]; //邻接矩阵，边表
    int vexnum, arcnum; //图的当前顶点数和弧数
};

struct ArcNode { //边表结点
    int adjvex; //该弧所指向的顶点的位置
    struct ArcNode* next; //指向下一条弧的指针
    //InfoType info; //网的边权值
};

struct VNode { //顶点表结点
    VertexType data; //顶点信息
    ArcNode* first; //指向第一条依附该项点的弧的指针
};


struct ALGraph {
    VNode vertices[MaxVertexNum]; //邻接表
    int vexnum, arcnum; //图的顶点数和弧数
};

ALGraph build_graph(int V[], pair<int, int> edges[], int V_size, int e_size) {
    ALGraph G;
    G.vexnum = V_size;G.arcnum = e_size;
    for (int i = 0;i < G.vexnum;i++) {
        VNode v;
        v.data = V[i];
        v.first = nullptr;
        G.vertices[i] = v;
    }
    for (int i = 0;i < G.arcnum;i++) {
        auto e = edges[i];
        ArcNode* arc = new ArcNode;
        arc->adjvex = e.second;
        arc->next = nullptr;
        auto temp = G.vertices[e.first].first;
        G.vertices[e.first].first = arc;
        G.vertices[e.first].first->next = temp;
    }
    return G;
}

void print_graph(ALGraph G) {
    for (int i = 0;i < G.vexnum;i++) {
        auto p = G.vertices[i].first;
        while (p) {
            cout << i << "->" << p->adjvex << '\n';
            p = p->next;
        }
    }
}