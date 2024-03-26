#define MaxSize 50

typedef struct {
    int data[MaxSize];
    int front, rear;
} SqQueue;

void InitQueue(SqQueue& Q) {
    Q.rear = Q.front = 0; //初始化队首、队尾指针
}