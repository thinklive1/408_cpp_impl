#include <iostream>
using namespace std;
const int Maxsize = 50;
struct sqList {
    int data[Maxsize]; //顺序表的元素
    int length = 0;      //顺序表的当前长度
};
//L.data=new ElemType[InitSize]; //动态分配

bool ListInsert(sqList& L, int i, int e) {
    if (i<1 || i>L.length + 1) {//判断i的范围是否有效
        return false;
    }
    if (L.length >= Maxsize) {
        //当前存储空间已满,不能插入
        return false;
    }
    for (int j = L.length; j > i; j--) {
        //将第i个元素及之后的元素后移
        L.data[j] = L.data[j - 1];
    }
    L.data[i - 1] = e; //在位置i处放入e
    L.length++; //线性表长度加1
    return true;
}

int LocateElem(sqList L, int e) {
    int i;
    for (i = 0; i < L.length; i++) {
        if (L.data[i] == e) {
            return i + 1; //下标为i的元素值等于e,返回其位序i+1
        }
    }
    return 0; //退出循环,说明查找失败
}

bool ListDelete(sqList& L, int i, int e) {
    if (i<1 || i>L.length) {//判断i的范围是否有效
        return false;
    }
    e = L.data[i - 1];//将被删除的元素赋值给e
    for (int j = i; j < L.length; j++) {
        //将第i个位置后的元素前移
        L.data[j - 1] = L.data[j];
    }
    cout << "del val:" << e << '\n';
    L.length--;//线性表长度减1
    return true;
}

void deletemin(sqList L) {//从顺序表中删除具有最小值的元素(假设唯一)并由函数返回被删元素的值。空出的位置由最后一个元素填上
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
}

void printql(sqList L) {
    for (int i = 0;i < L.length;i++) {
        cout << L.data[i] << endl;
    }
}
