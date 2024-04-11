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

