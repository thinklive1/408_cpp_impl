#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
using namespace std;

struct ArcNode { //边表结点
    int adjvex; //该弧所指向的顶点的位置
    struct ArcNode* next; //指向下一条弧的指针
    //InfoType info; //网的边权值
};

struct Vertex { //顶点表结点
    int data; //顶点信息
    ArcNode* first; //指向第一条依附该项点的弧的指针
};

void printVector(vector <Vertex*> vec) {
    int k = 0;
    for (auto i : vec) cout << k++ << ':' << i->data << '\n';
}

/* 基于邻接表实现的无向图类 */
class GraphAdjList {
public:
    // 邻接表，key：顶点，value：该顶点的所有邻接顶点
    map<Vertex*, vector<Vertex*>> adjList;

    /* 在 vector 中删除指定节点 */
    void remove(vector<Vertex*>& vec, Vertex* vet) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] == vet) {
                vec.erase(vec.begin() + i);
                break;
            }
        }
    }

    /* 构造方法 */
    GraphAdjList(const vector<vector<Vertex*>>& edges) {
        // 添加所有顶点和边
        for (const vector<Vertex*>& edge : edges) {
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0], edge[1]);
        }
    }

    /* 获取顶点数量 */
    int size() {
        return adjList.size();
    }

    /* 添加边 */
    void addEdge(Vertex* vet1, Vertex* vet2) {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
            throw invalid_argument("不存在顶点");
        // 添加边 vet1 - vet2
        adjList[vet1].push_back(vet2);
        adjList[vet2].push_back(vet1);
    }

    /* 删除边 */
    void removeEdge(Vertex* vet1, Vertex* vet2) {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
            throw invalid_argument("不存在顶点");
        // 删除边 vet1 - vet2
        remove(adjList[vet1], vet2);
        remove(adjList[vet2], vet1);
    }

    /* 添加顶点 */
    void addVertex(Vertex* vet) {
        if (adjList.count(vet))
            return;
        // 在邻接表中添加一个新链表
        adjList[vet] = vector<Vertex*>();
    }

    /* 删除顶点 */
    void removeVertex(Vertex* vet) {
        if (!adjList.count(vet))
            throw invalid_argument("不存在顶点");
        // 在邻接表中删除顶点 vet 对应的链表
        adjList.erase(vet);
        // 遍历其他顶点的链表，删除所有包含 vet 的边
        for (auto& adj : adjList) {
            remove(adj.second, vet);
        }
    }

    /* 打印邻接表 */
    void print() {
        cout << "邻接表 =" << endl;
        for (auto& adj : adjList) {
            const auto& key = adj.first;
            const auto& vec = adj.second;
            cout << key->data << ": ";
            printVector(vec);
        }
    }
};

/* 广度优先遍历 */
// 使用邻接表来表示图，以便获取指定顶点的所有邻接顶点
vector<Vertex*> graphBFS(GraphAdjList& graph, Vertex* startVet) {
    // 顶点遍历序列
    vector<Vertex*> res;
    // 哈希表，用于记录已被访问过的顶点
    set<Vertex*> visited = { startVet };
    // 队列用于实现 BFS
    queue<Vertex*> que;
    que.push(startVet);
    // 以顶点 vet 为起点，循环直至访问完所有顶点
    while (!que.empty()) {
        Vertex* vet = que.front();
        que.pop();          // 队首顶点出队
        res.push_back(vet); // 记录访问顶点
        // 遍历该顶点的所有邻接顶点
        for (auto adjVet : graph.adjList[vet]) {
            if (visited.count(adjVet))
                continue;            // 跳过已被访问的顶点
            que.push(adjVet);        // 只入队未访问的顶点
            visited.emplace(adjVet); // 标记该顶点已被访问
        }
    }
    // 返回顶点遍历序列
    return res;
}

/* 深度优先遍历辅助函数 */
void dfs(GraphAdjList& graph, set<Vertex*>& visited, vector<Vertex*>& res, Vertex* vet) {
    res.push_back(vet);   // 记录访问顶点
    visited.emplace(vet); // 标记该顶点已被访问
    // 遍历该顶点的所有邻接顶点
    for (Vertex* adjVet : graph.adjList[vet]) {
        if (visited.count(adjVet))
            continue; // 跳过已被访问的顶点
        // 递归访问邻接顶点
        dfs(graph, visited, res, adjVet);
    }
}

/* 深度优先遍历 */
// 使用邻接表来表示图，以便获取指定顶点的所有邻接顶点
vector<Vertex*> graphDFS(GraphAdjList& graph, Vertex* startVet) {
    // 顶点遍历序列
    vector<Vertex*> res;
    // 哈希表，用于记录已被访问过的顶点
    set<Vertex*> visited;
    dfs(graph, visited, res, startVet);
    return res;
}