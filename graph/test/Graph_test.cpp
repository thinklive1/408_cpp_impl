#include "../Graph.cpp"

const int MAXV = 50;

struct MGraph {
    int numVertices, numEdges;
    char VerticesList[MAXV];
    int Edge[MAXV][MAXV];
};

int IsExistEL(MGraph G) {
    return 0;
}

int* Convert(ALGraph& G, int V, int arcs[]) {
    //将邻接表方式表示的图G转换为邻接矩阵arcs,V是图的顶点数
    //为了方便，二维矩阵在存储上视为一维，结点位置实际是i*V+j
    for (int i = 0;i < V;i++) for (int j = 0;j < V;j++) arcs[i * V + j] = 0;
    for (int i = 0; i < V; i++) { //依次遍历各顶点表结点为头的边链表
        ArcNode* p = G.vertices[i].first;
        while (p != nullptr) { //遍历边链表
            if (p->adjvex >= V) { //需要注意ArcNode储存的顶点数不可以超过V，否则会数组越界
                cout << "数组越界\n";
                return nullptr;
            }
            arcs[i * V + p->adjvex] = 1;
            p = p->next;
        } //while
    }
    for (int i = 0;i < 25;i++) {
        cout << "i is " << i / 5 << ' ' << "j is " << i % 5 << ' ' << "val is " << arcs[i] << '\n';
    }
    return arcs;
}


int main() {
    int V[5] = { 0,1,2,3,4 };
    pair<int, int> edges[6] = { {1,2},{1,3},{2,4},{4,3},{3,2},{4,2} };
    ALGraph g = build_graph(V, edges, 5, 6);
    print_graph(g);
    int matrix[25];
    Convert(g, 5, matrix);
}