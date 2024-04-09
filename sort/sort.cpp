#include <iostream>
using namespace std;
#define ElemType int

/* 插入排序 */
void Insertsort(ElemType A[], int n) {
    int i, j;
    for (i = 2; i <= n; i++) //依次将A[2] ~A[n]插入前面己排序序列
        if (A[i] < A[i - 1]) { //若A[i]关键码小于其前驱，将A[i]插入有序表
            A[0] = A[i]; //复制为哨兵，A【0]不存放元素
            for (j = i - 1;A[0] < A[j];--j)//从后往前查找待插入位置
                A[j + 1] = A[j]; //向后挪位
            A[j + 1] = A[0]; //复制到插入位置
        }
}

void InsertSort_byhalf(ElemType A[], int n) {
    int i, j, low, high, mid; //依次将A[2]~A[n]插入前面的巳排序序列
    for (i = 2; i <= n; i++) { //将A[i]暂存到A[0]
        A[0] = A[i];
        low = 1;high = i - 1; //设置折半查找的范围
        while (low <= high) {
            mid = (low + high) / 2;
            if (A[mid] > A[0]) high = mid - 1;
            else low = mid + 1;
            for (j = i - 1;j >= high + 1;--j)
                A[j + 1] = A[j]; //统一后移元素，空出插入位置
            A[high + 1] = A[0]; //插入操作
        }
    }
}

void ShellSort(ElemType A[], int n) {
    //A[0]]是暂存单元，不是哨兵，当j<=0时，插入位置已到
    int dk, i, j;
    for (dk = n / 2; dk >= 1; dk = dk / 2) //增量变化(无统一规定)
        for (i = dk + 1;i <= n;++i)
            if (A[i] < A[i - dk]) { //需将A [i ]插入有序增量子表
                A[0] = A[i]; //暂存在 A[0]
                for (j = i - dk;j > 0 && A[0] < A[j];j -= dk)
                    A[j + dk] = A[j]; //记录后移，查找插入的位置
                A[j + dk] = A[0]; //插入
            }
}

void BubbleSort(ElemType A[], int n) {
    for (int i = 0;i < n - 1;i++) {
        bool flag = false; //表示本趟冒泡是否发生交换的标志
        for (int j = n - 1; j > i; j--) //一趟冒泡过程
            if (A[j - 1] > A[j]) { //若为逆序
                swap(A[j - 1], A[j]); //交换
                flag = true;
            }
        if (flag == false)
            return; //本趟遍历后没有发生交换，说明表已经有序
    }
}

void Quicksort(ElemType A[], int low, int high) {
    if (low < high) { //递归跳出的条件
        //Partition ()就是划分操作，将表A [low…high]划分为满足上述条件的两个子表
        int pivotpos = Partition(A, low, high); //划分
        Quicksort(A, low, pivotpos - 1); //依次对两个子表进行递归排序
        Quicksort(A, pivotpos + 1, high);
    }
}

int Partition(ElemType A[], int low, int high) { //一趟划分
    ElemType pivot = A[low]; //将当前表中第一个元素设为枢轴，对表进行划分
    while (low < high) { //循环跳出条件
        while (low < high && A[high] >= pivot) --high;
        A[low] = A[high]; //将比枢轴小的元素移动到左端
        while (low < high && A[low] <= pivot) ++low;
        A[high] = A[low]; //将比枢轴大的元素移动到右端
    }
    A[low] = pivot; //枢轴元素存放到最终位置
    return low; //返回存放枢轴的最终位置
}

void SelectSort(ElemType A[], int n) {
    for (int i = 0; i < n - 1; i++) { //一共进行 n-1 趟
        int min = i; //记录最小元素位置
        for (int j = i + 1; j < n; j++) //在A[i~n-1]中选择最小的元素
            if (A[j] < A[min]) min = j; //更新最小元素位置
        if (min != i) swap(A[i], A[min]); //swap()函数共移动元素 3 次
    }
}