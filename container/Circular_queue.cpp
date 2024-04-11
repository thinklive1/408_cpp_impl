#define MaxSize 50

typedef struct {
    int data[MaxSize];
    int front, rear;
} SqQueue;

void InitQueue(SqQueue& Q) {
    Q.rear = Q.front = 0; //初始化队首、队尾指针
}

bool isEmpty(SqQueue Q) {
    if (Q.rear == Q.front) return true; //队空条件
    else return false;
}

bool EnQueue(SqQueue& Q, int x) {
    if ((Q.rear + 1) % MaxSize == Q.front) return false; //队满贝!I报错
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize; //队尾指针加 1 取模
    return true;
}

bool DeQueue(SqQueue& Q, int& x) {
    if (Q.rear == Q.front) return false; //队空则报错
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize; //队头指针加 1 取模
    return true;
}