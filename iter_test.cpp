#include <iostream>
using namespace std;

void change_iter(int*& x) {
    x = new int;
}

void change_arr(int x[]) {
    x[1] = 10;
}

/* int main() {
    int x = 3;
    int* x_iter = &x;
    cout << x_iter << endl;
    change_iter(x_iter);
    cout << "after change:" << x_iter << endl;
int arr[3] = { 1,2,3 };
cout << "arr[1] is " << arr[110] << endl;
change_arr(arr);
cout << "after change is " << arr[1] << endl;
} */


