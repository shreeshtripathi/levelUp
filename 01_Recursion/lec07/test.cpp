#include<iostream>
#include<vector>

using namespace std;

// int* fun1() {
//     int arr[4] =  {1, 2, 3, 4};
//     return arr;
// }

void fun2(int& a) {
    cout << &a << endl;
}

int main(int argc, char** argv) {
    // int* arr = fun1();
    int a = 10;
    int* b = new int(10);

    fun2(a);
    cout << &a<< endl;
}