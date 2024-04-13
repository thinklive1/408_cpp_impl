#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
const int MaxVNodeNum = 64;;
const int MaxVertexNum = 64;;

using ElemType = int;
using VNodeType = int;
using EdgeType = int;

struct Matrix_Graph {
    VNodeType Vex[MaxVertexNum];
    EdgeType Edge[MaxVNodeNum][MaxVertexNum]; //邻接矩阵，边表
    int vexnum, arcnum; //图的当前顶点数和弧数
};
struct VNode;
struct ArcNode { //边表结点
    VNode* adjvex; //该弧所指向的顶点的指针
    struct ArcNode* next; //指向下一条弧的指针
    //InfoType info; //网的边权值
};

struct VNode { //顶点表结点
    VNodeType no; //顶点编号
    ArcNode* first; //指向第一条依附该项点的弧的指针
};


struct ALGraph {
    VNode vertices[MaxVNodeNum]; //邻接表
    int vexnum, arcnum; //图的顶点数和弧数
};

using GraphAdjList = ALGraph;
using Vertex = VNode;

ALGraph build_graph(int V[], pair<int, int> edges[], int V_size, int e_size) {
    ALGraph G;
    G.vexnum = V_size;G.arcnum = e_size;
    for (int i = 0;i < G.vexnum;i++) {
        VNode v;
        v.no = i;
        v.first = nullptr;
        G.vertices[i] = v;
    }
    for (int i = 0;i < G.arcnum;i++) {
        auto e = edges[i];
        ArcNode* arc = new ArcNode;
        arc->adjvex = &G.vertices[e.second];
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
            cout << i << "->" << p->adjvex->no << '\n';
            p = p->next;
        }
    }
}

/* 广度优先遍历 */
// 使用邻接表来表示图，以便获取指定顶点的所有邻接顶点
vector<Vertex*> graphBFS(GraphAdjList& graph, Vertex* startVet) {
    // 顶点遍历序列
    vector<Vertex*> res;
    // 哈希表，用于记录已被访问过的顶点
    set<Vertex*> visited = { startVet };
    // 队列用于实现 BFS
    queue<VNode*> que;
    que.push(startVet);
    // 以顶点 vet 为起点，循环直至访问完所有顶点
    while (!que.empty()) {
        Vertex* vet = que.front();
        que.pop();          // 队首顶点出队
        res.push_back(vet); // 记录访问顶点
        // 遍历该顶点的所有邻接顶点
        auto adjVet = vet->first;
        while (adjVet) {
            if (visited.count(adjVet->adjvex)) {
                adjVet = adjVet->next;
                continue;            // 跳过已被访问的顶点
            }
            que.push(adjVet->adjvex);        // 只入队未访问的顶点
            visited.emplace(adjVet->adjvex); // 标记该顶点已被访问
            adjVet = adjVet->next;
        }
    }
    // 返回顶点遍历序列
    return res;
}

/* 深度优先遍历辅助函数 */
void dfs(ALGraph& graph, set<VNode*>& visited, vector<VNode*>& res, VNode* vet) {
    res.push_back(vet);   // 记录访问顶点
    visited.emplace(vet); // 标记该顶点已被访问
    // 遍历该顶点的所有邻接顶点
    auto adjVet = vet->first;
    vector<VNode*> temp = {};
    while (adjVet) {
        temp.push_back(adjVet->adjvex);
        adjVet = adjVet->next;
    }
    for (auto V : temp) {
        if (visited.count(V))
            continue; // 跳过已被访问的顶点
        dfs(graph, visited, res, V); // 递归访问邻接顶点
    }
}

/* 深度优先遍历 */
// 使用邻接表来表示图，以便获取指定顶点的所有邻接顶点
vector<VNode*> graphDFS(ALGraph& graph, VNode* startVet) {
    // 顶点遍历序列
    vector<VNode*> res;
    // 哈希表，用于记录已被访问过的顶点
    set<VNode*> visited;
    dfs(graph, visited, res, startVet);
    return res;
}