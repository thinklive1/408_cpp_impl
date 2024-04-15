#include "../Graph.cpp"

const int MAXV = 50;

struct MGraph {
    int numVertices, numEdges;
    char VerticesList[MAXV];
    int Edge[MAXV][MAXV];
};

//0.当无向图G中度为奇数的顶点个数为不大于2的偶数时，G存在包含所有边且长度为E的路径,称为EL路径，判断是否存在
int IsExistEL(MGraph G) {//因为是无向图，只需要遍历每行的度数，并计算奇数度数节点数量即可
    int degree = 0, count = 0;
    for (int i = 0;i < G.numVertices;i++) {
        degree = 0;
        for (int j = 0;j < G.numVertices;j++) if (G.Edge[i][j] == 1) ++degree;
        if (degree % 2 == 1) ++count;
    }
    return (count == 0 || count == 2) ? 1 : 0;
}

//1.将邻接表方式表示的图G转换为邻接矩阵arcs,V是图的顶点数
int* Convert(ALGraph& G, int V, int arcs[]) {
    //为了方便，二维矩阵在存储上视为一维，结点位置实际是i*V+j
    for (int i = 0;i < V;i++) for (int j = 0;j < V;j++) arcs[i * V + j] = 0;
    for (int i = 0; i < V; i++) { //依次遍历各顶点表结点为头的边链表
        ArcNode* p = G.vertices[i].first;
        while (p != nullptr) { //遍历边链表
            if (p->adjvex->no >= V) { //需要注意ArcNode储存的顶点数不可以超过V，否则会数组越界
                cout << "数组越界\n";
                return nullptr;
            }
            arcs[i * V + p->adjvex->no] = 1;
            p = p->next;
        } //while
    }
    for (int i = 0;i < 25;i++) {
        cout << "i is " << i / 5 << ' ' << "j is " << i % 5 << ' ' << "val is " << arcs[i] << '\n';
    }
    return arcs;
}

//2.判断无向图是否是树,逻辑是深度遍历中有2(v-1)条边的连通图肯定是树
//其实我也不知道严格来说要求是遍历中涉及边数还是图的总边数可满足要求，保险起见使用前者
//因此需要一个统计边数的dfs算法
void dfs2(ALGraph& graph, set<VNode*>& visited, vector<VNode*>& res, VNode* vet, int& e_num);
bool is_tree(ALGraph& G) {
    set<VNode*> visited;
    vector<VNode*> res;
    int e_size = 0;
    dfs2(G, visited, res, &G.vertices[0], e_size);
    //理论上讲无向图判断的边数应该*2，这里涉及图的实现就不乘了，这样不严谨，但实在不想有向无向图各自写一遍了
    if ((G.vexnum - 1) == e_size && visited.size() == G.vexnum) return true;
    return false;
}

void dfs2(ALGraph& graph, set<VNode*>& visited, vector<VNode*>& res, VNode* vet, int& e_num) {
    res.push_back(vet);   // 记录访问顶点
    visited.emplace(vet); // 标记该顶点已被访问
    // 遍历该顶点的所有邻接顶点
    auto adjVet = vet->first;
    vector<VNode*> temp = {};
    while (adjVet) {
        ++e_num;//统计遍历涉及的边数
        temp.push_back(adjVet->adjvex);
        adjVet = adjVet->next;
    }
    for (auto V : temp) {
        if (visited.count(V))
            continue; // 跳过已被访问的顶点
        dfs2(graph, visited, res, V, e_num); // 递归访问邻接顶点
    }
}

void print_bool(bool bit) {
    if (bit == 1) cout << "true\n";
    else cout << "false\n";
}

int main() {
    int V[5] = { 0,1,2,3,4 };
    pair<int, int> edges[6] = { {1,2},{1,3},{2,4},{4,3},{3,2},{4,2} };
    pair<int, int> tree_edges[4] = { {1,2},{1,3},{2,4},{0,1} };
    ALGraph g = build_graph(V, edges, 5, 6);
    ALGraph tree = build_graph(V, tree_edges, 5, 4);
    //print_graph(g);
    print_graph(tree);
    /*     int matrix[25];
        Convert(g, 5, matrix); */
        //for (auto i : graphBFS(g, &g.vertices[1])) cout << i->no;
        //for (auto i : graphDFS(g, &g.vertices[2])) cout << i->no;
    print_bool(is_tree(tree));




}