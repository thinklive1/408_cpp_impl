#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ElemType int

/* 插入排序 */
int* Insertsort(ElemType A[], int n) {
    int i, j;
    for (i = 2; i < n; i++) //依次将A[2] ~A[n]插入前面己排序序列
        if (A[i] < A[i - 1]) { //若A[i]关键码小于其前驱，将A[i]插入有序表
            A[0] = A[i]; //复制为哨兵，A[0]不存放元素
            for (j = i - 1;A[0] < A[j];--j)//从后往前查找待插入位置
                A[j + 1] = A[j]; //向后挪位
            A[j + 1] = A[0]; //复制到插入位置
        }
    return A;
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
    //A[0]是暂存单元，不是哨兵，当j<=0时，插入位置已到
    int dk, i, j;
    for (dk = n / 2; dk >= 1; dk = dk / 2) //增量变化(无统一规定)
        for (i = dk + 1;i <= n;++i)
            if (A[i] < A[i - dk]) { //需将A [i]插入有序增量子表
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

void Quicksort(ElemType A[], int low, int high) {
    if (low < high) { //递归跳出的条件
        //Partition ()就是划分操作，将表A [low…high]划分为满足上述条件的两个子表
        int pivotpos = Partition(A, low, high); //划分
        Quicksort(A, low, pivotpos - 1); //依次对两个子表进行递归排序
        Quicksort(A, pivotpos + 1, high);
    }
}

void SelectSort(ElemType A[], int n) {
    for (int i = 0; i < n - 1; i++) { //一共进行 n-1 趟
        int min = i; //记录最小元素位置
        for (int j = i + 1; j < n; j++) //在A[i~n-1]中选择最小的元素
            if (A[j] < A[min]) min = j; //更新最小元素位置
        if (min != i) swap(A[i], A[min]); //swap()函数共移动元素 3 次
    }
}

void Swap(ElemType A[], int i, int j);
void HeadAdjust(ElemType A[], int k, int len) {
    //函数HeadAdjust将元素k为根的子树进行调整
    A[0] = A[k]; //A[0]暂存子树的根结点
    for (int i = 2 * k; i < len; i *= 2) {//沿key较大的子结点向下筛选
        if (i < len&& A[i] < A[i + 1])
            i++; //取key较大的子结点的下标
        if (A[0] >= A[i]) break; //筛选结束
        else {
            A[k] = A[i]; //将A【汀调整到双亲结点上
            k = i; //修改k值，以便继续向下筛选
        }
    }
    A[k] = A[0]; //被筛选结点的值放入最终位置
}

void BuildMaxHeap(ElemType A[], int len) {
    for (int i = len / 2;i > 0;i--) //从 i = [n / 2]〜1, 反复调整堆
        HeadAdjust(A, i, len);
}

void HeapSort(ElemType A[], int len) {
    BuildMaxHeap(A, len); //初始建堆
    for (int i = len; i > 1; i--) { //n-1趟的交换和建堆过程
        Swap(A, i, 1); //输出堆顶元素(和堆底元素交换)
        HeadAdjust(A, 1, i - 1); //调整，把剩余的i-1个元素整理成堆
    }
}

ElemType* B; //辅助数组 B
void Merge(ElemType A[], int low, int mid, int high) {
    //表A的两段A[low...mid]和A [mid+l...high]各自有序，将它们合并成一个有序表
    int i, j, k;
    for (k = low;k <= high;k++)
        B[k] = A[k]; //将A中所有元素复制到B中
    for (i - low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
        if (B[i] <= B[j]) //比较B的左右两段中的元素
            A[k] = B[i++]; //将较小值复制到A中
        else
            A[k] = B[j++];
    }
    while (i <= mid) A[k++] = B[i++]; //若第一个表未检测完，复制
    while (j <= high) A[k++] = B[j++]; //若第二个表未检测完，复制
}

void MergeSort(ElemType A[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2; //从中间划分两个子序列
        MergeSort(A, low, mid); //对左侧子序列进行递归排序
        MergeSort(A, mid + 1, high); //对右侧子序列进行递归排序
        Merge(A, low, mid, high); //归并
    }//if *
}

/* 计数排序 */
// 完整实现，可排序对象，并且是稳定排序
void countingSort(vector<int>& nums) {
    // 1. 统计数组最大元素 m
    int m = 0;
    for (int num : nums) {
        m = max(m, num);
    }
    // 2. 统计各数字的出现次数
    // counter[num] 代表 num 的出现次数
    vector<int> counter(m + 1, 0);
    for (int num : nums) {
        counter[num]++;
    }
    // 3. 求 counter 的前缀和，将“出现次数”转换为“尾索引”
    // 即 counter[num]-1 是 num 在 res 中最后一次出现的索引
    for (int i = 0; i < m; i++) {
        counter[i + 1] += counter[i];
    }
    // 4. 倒序遍历 nums ，将各元素填入结果数组 res
    // 初始化数组 res 用于记录结果
    int n = nums.size();
    vector<int> res(n);
    for (int i = n - 1; i >= 0; i--) {
        int num = nums[i];
        res[counter[num] - 1] = num; // 将 num 放置到对应索引处
        counter[num]--;              // 令前缀和自减 1 ，得到下次放置 num 的索引
    }
    // 使用结果数组 res 覆盖原数组 nums
    nums = res;
}

/* 获取元素 num 的第 k 位，其中 exp = 10^(k-1) */
int digit(int num, int exp) {
    // 传入 exp 而非 k 可以避免在此重复执行昂贵的次方计算
    return (num / exp) % 10;
}

/* 计数排序（根据 nums 第 k 位排序） */
void countingSortDigit(vector<int>& nums, int exp) {
    // 十进制的位范围为 0~9 ，因此需要长度为 10 的桶数组
    vector<int> counter(10, 0);
    int n = nums.size();
    // 统计 0~9 各数字的出现次数
    for (int i = 0; i < n; i++) {
        int d = digit(nums[i], exp); // 获取 nums[i] 第 k 位，记为 d
        counter[d]++;                // 统计数字 d 的出现次数
    }
    // 求前缀和，将“出现个数”转换为“数组索引”
    for (int i = 1; i < 10; i++) {
        counter[i] += counter[i - 1];
    }
    // 倒序遍历，根据桶内统计结果，将各元素填入 res
    vector<int> res(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        int d = digit(nums[i], exp);
        int j = counter[d] - 1; // 获取 d 在数组中的索引 j
        res[j] = nums[i];       // 将当前元素填入索引 j
        counter[d]--;           // 将 d 的数量减 1
    }
    // 使用结果覆盖原数组 nums
    for (int i = 0; i < n; i++)
        nums[i] = res[i];
}

/* 基数排序 */
void radixSort(vector<int>& nums) {
    // 获取数组的最大元素，用于判断最大位数
    int m = *max_element(nums.begin(), nums.end());
    // 按照从低位到高位的顺序遍历
    for (int exp = 1; exp <= m; exp *= 10)
        // 对数组元素的第 k 位执行计数排序
        // k = 1 -> exp = 1
        // k = 2 -> exp = 10
        // 即 exp = 10^(k-1)
        countingSortDigit(nums, exp);
}

void print_arr(int A[], int n) {
    for (int i = 0;i < n;i++)
        cout << i << ":" << A[i] << '\n';
}

int main() {
    int temp[8] = { 1,24,12,35,4,13,72,54 };
    print_arr(temp, 8);
    cout << "after sort:\n";
    print_arr(Insertsort(temp, 8), 8);

}