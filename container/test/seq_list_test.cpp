#include "../Sequence_list.cpp"
#include <vector>

void deletemin(sqList& L) {//1.从顺序表中删除具有最小值的元素(假设唯一)并由函数打印被删元素的值。空出的位置由最后一个元素填上
    int min = L.data[0];
    int min_index = 0;
    for (int i = 1;i < L.length;i++) {
        if (min > L.data[i]) {
            min = L.data[i];
            min_index = i;
        }
    }
    cout << "min is " << min << endl;
    L.data[min_index] = L.data[L.length - 1];
    L.length--;
}

void reverseql(sqList& L) {//2.逆转线性表
    for (int i = 0;i < L.length / 2;i++) {
        int temp = L.data[i];
        L.data[i] = L.data[L.length - i - 1];
        L.data[L.length - 1 - i] = temp;
    }
    cout << "after rev" << endl;
    printql(L);
}

void deletex(sqList L, const int& x) {//3.删除所有值为x的元素
    int xtimes = 0;
    for (int i = 0;i < L.length;i++) {
        if (x == L.data[i]) {
            xtimes++;
        }
    }
    int values_except_x = L.length - xtimes;
    int new_index = 0;
    for (int i = 0;i < L.length;i++) {
        if (L.data[i] != x) {
            L.data[new_index] = L.data[i];
            new_index++;
            values_except_x--;
        }
        if (values_except_x == 0) {
            break;
        }
    }
    L.length = L.length - xtimes;
    cout << "after del" << endl;
    printql(L);
}

void delete_orderedql_by_range(sqList L, int i, int j) {//4.删除有序线性表一定范围的元素
    if (i > j) return;
    int lft = 0;
    while (lft < L.length) {//找到首个≥i的元素
        if (L.data[lft] >= i) {
            break;
        }
        lft++;
    }
    if (lft >= L.length - 1) return;
    int rht = lft + 1;
    while (rht < L.length) {
        if (L.data[rht] > j) {
            break;
        }
        rht++;
    }
    for (int index = rht;index < L.length;index++) {
        L.data[lft++] = L.data[index];
    }
    L.length = lft;
}

void delete_ql_by_range(sqList L, int s, int t) {//5.删除无序线性表一定范围的元素
    int value_in_range = 0;
    for (int i = 0;i < L.length;i++) {
        if (s <= L.data[i] && L.data[i] <= t) {
            value_in_range++;
            continue;
        }
        L.data[i - value_in_range] = L.data[i];
    }
    L.length -= value_in_range;
}

void make_unique(sqList L) {//6.删除有序线性表相同值的元素
    int before = L.data[0];
    int same_values = 0;
    for (int i = 1;i < L.length;i++) {
        if (L.data[i] == before) {
            same_values++;
        }
        else {
            L.data[i - same_values] = L.data[i];
            before = L.data[i];
        }
    }
    L.length -= same_values;
}

sqList mergesq(sqList L1, sqList L2) {//7.融合两个有序表(归并排序青春版)
    sqList result;
    int i = 0, j = 0, k = 0;
    while (i < L1.length && j < L2.length) {
        if (L1.data[i] < L2.data[j]) result.data[k++] = L1.data[i++];
        else result.data[k++] = L2.data[j++];
    }
    while (i < L1.length) result.data[k++] = L1.data[i++];
    while (j < L2.length) result.data[k++] = L2.data[j++];
    result.length = L1.length + L2.length;
    return result;
}

void swap(sqList& L, int i, int j) {
    int temp = L.data[i];
    L.data[i] = L.data[j];
    L.data[j] = temp;
}

void reverse(sqList& L, int lft, int rht) {
    for (int i = 0;i < (rht - lft) / 2;i++) { //c++的int除法向下取整
        swap(L, i + lft, rht - i - 1); //从0索引所以右侧减一
    }
}

sqList exchange(sqList L, int m, int n) {//8.位置互换
    reverse(L, 0, L.length);
    reverse(L, 0, n);
    reverse(L, n, L.length);
    return L;
}

int middle_find_x(const sqList& L, int x) {//二分查找有序表内的x
    int index;int lft = 0;int rht = L.length - 1;
    while (lft <= rht) {
        index = (rht + lft) / 2;
        if (L.data[index] == x) return index;
        else if (L.data[index] < x) lft = index + 1;
        else rht = index - 1;
    }
    return lft;//lft必然指向首个大于等于x的元素，rht则指向首个小于等于x的元素
}

void find_x(sqList L, int x) { //9.最少时间在表中查找数值为x的元素，若找到，则将其与后继元素位置相交换，若找不到，则将其插入表中并使表中元素仍递增有序
    int i = middle_find_x(L, x);
    if (i == L.length - 1) return;
    else if (L.data[i] == x) {
        swap(L, i, i + 1);
    }
    else {
        L.data[L.length] = x;
        L.length++;
        swap(L, i++, L.length - 1);
        for (;i < L.length;i++) {
            swap(L, i, L.length - 1);
        }
    }
}

void left_move(sqList L, int p) {//整体左移p位，前面的8.就相当于左移m位或者右移n位
    reverse(L, 0, p);
    reverse(L, p, L.length);
    reverse(L, 0, L.length);
}

int find_middle_2(sqList L1, sqList L2) { //二分查找的非递归实现
    int index = 0;
    int middle = 0;
    int lft = 0;int rht = 0;
    while (index < (L1.length + L2.length + 1) / 2) {
        if (L1.data[lft] <= L2.data[rht]) {
            middle = L1.data[lft];
            lft++;
        }
        else {
            middle = L2.data[rht];
            rht++;
        }
        index++;
    }
    return middle;
}

int find_middle_best(sqList L1, sqList L2) {//寻找两个等长有序表的公共中位数
    //两组中位数之间的子数组的中位数与两整个数组的公共中位数，可以不断扔掉两侧的一半，直到只剩一个
    int m1 = L1.data[(L1.length + 1) / 2];
    int m2 = L2.data[(L2.length + 1) / 2];
    int lft1, lft2, rht1, rht2;
    lft1 = lft2 = 0;
    rht1 = rht2 = L1.length;
    while (rht1 - lft1 > 1 || rht2 - lft2 > 1) {//如果L1中位数小于L2，就舍弃L1较小边，L2较大边
        if (m1 == m2) return m1;
        else if (m1 < m2) {
            lft1 = (lft1 + rht1) / 2;
            rht2 = (rht2 + lft2) / 2;
        }
        else {
            rht1 = (lft1 + rht1) / 2;
            lft2 = (rht2 + lft2) / 2;
        }
        m1 = L1.data[(lft1 + rht1) / 2];
        m2 = L2.data[(lft2 + rht2) / 2];
    }
    if (L1.length % 2 == 0) return min(m1, m2);
    else return max(m1, m2);
    //两个等长序列，最后总长度必然是偶数位，m1,m2一个是中点位，一个是中点位+1,奇数情况下要取较大的，偶数取较小的
}

int find_key_of_sqL(sqList L) {//查找主元(出现次数大于长度的一半)
    int l = L.length;
    int vals[l];
    for (int i = 0;i < l;i++) {
        vals[i] = 0;
    }
    for (int i = 0;i < l;i++) {
        vals[L.data[i]]++;
    }
    for (int i = 0;i < l;i++) {
        if (vals[i] > l / 2) return i;
    }
    return -1;
}

int find_key_of_sqL_best(sqList L) {
    /*选取候选的主元素。依次扫描所给数组中的每个整数，将第一个遇到的整数Num保存到
    c中，记录Num的出现次数为1；若遇到的下一个整数仍等于Num,则计数加1,否则计
        数减1;当计数减到0时，将遇到的下一个整数保存到c中，计数重新记为1,开始新一
        轮计数，即从当前位置开始重复上述过程，直到扫描完全部数组元素。*/
    int i, c, count = 1;//c用来保存候选主元素，count用来计数
    c = L.data[0];
    int n = L.length;
    for (i = 1; i < n; i++) {
        if (L.data[i] == c) {
            count++;
        }
        else {
            if (count > 0) {
                count--;
            }
            else {
                c = L.data[i];
                count = 1;
            }
        }
    }
    if (count > 0)  for (i = count = 0; i < n; i++) {//判断c中元素是否是真正的主元素
        if (L.data[i] == c) {
            count++;
        }
    }

    if (count > n / 2) {
        return c;
    }
    else return -1;
}

int find_min_Z(sqList L) {//查找最小的未出现正整数，可能的返回值只有[1,n+1]，超出这个范围不用考虑
    int n = L.length;
    int vals[n];
    for (int i = 0; i < n;i++) vals[i] = 0;
    for (int i = 0;i < n;i++) if (L.data[i] > 0 && L.data[i] <= n) vals[L.data[i] - 1]++;//由于数组从0开始索引，需要进行转化
    for (int i = 0;i < n;i++) if (vals[i] == 0) return i + 1;
    return -1;
}

bool xls_min(int a, int b, int c) {//a是否是三个数中的最小值
    if (a <= b && a <= c) return true;
    return false;
}

int findMinofTrip(int A[], int n, int B[], int m, int C[], int p) {//查找距离最小的三元组
    //D_min用于记录三元组的最小距离，初值赋为INT_MAX
    int i = 0, j = 0, k = 0, D_min = INT8_MAX, D;
    while (i < n && j < m && k < p && D_min>0) {
        D = abs(A[i] - B[j]) + abs(B[j] - C[k]) + abs(C[k] - A[i]); //计算 D
        if (D < D_min) D_min = D; //更新 D
        if (xls_min(A[i], B[j], C[k])) i++; //更新 a
        else if (xls_min(B[j], C[k], A[i])) j++;
        else k++;
    }
    return D_min;
}


int main() {
    sqList* L_ptr = new sqList();
    sqList L = *L_ptr;
    sqList L2 = *new sqList();
    //int temp[8]={23,13,2,42,12,23,13,23};
    int temp[8] = { 2,3,17,22,23,25,42,67 };
    int temp2[5] = { 1,2,5,12,22 };
    int temp3[6] = { -21,-3,14,33,35,40 };

    vector<int> text = { 3,2,4 };
    twoSum(text, 6);

    // 使用索引遍历
    // 求数组长度：sizeof(array)/sizeof(array[0])
    for (int i = 0;i < sizeof(temp) / sizeof(temp[0]);i++) {
        ListInsert(L, i + 1, temp[i]);
        cout << L.data[i] << endl;
    }
    for (int i = 0;i < sizeof(temp2) / sizeof(temp2[0]);i++) {
        ListInsert(L2, i + 1, temp2[i]);
    }
    //findMinofTrip(temp,8,temp2,5,temp3,6);
    //find_min_Z(L);
    //find_key_of_sqL_best(L2);
    //find_middle(L,L2);
    //left_move(L,2);
    //find_x(L,44);
    //exchange(L,8,3);
    //mergesq(L,L2);
    //make_unique(L);
    //delete_ql_by_range(L,6,43);
    //delete_orderedql_by_range(L,6,45);
    //deletex(L,23);
    //deletemin(L);
    //reverseql(L);
}

