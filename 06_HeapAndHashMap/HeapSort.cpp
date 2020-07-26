#include <iostream>
#include <vector>

using namespace std;

void downHeapify(vector<int> &arr, int pi, int n) {
    int lci = 2 * pi + 1;
    int rci = 2 * pi + 2;

    int maxIndx = pi;

    if (lci <= n && arr[lci] > arr[maxIndx])
        maxIndx = lci;

    if (rci <= n && arr[rci] > arr[maxIndx])
        maxIndx = rci;

    if (maxIndx != pi) {
        swap(arr[maxIndx], arr[pi]);
        downHeapify(arr, maxIndx, n);
    }
}

void HeapSort(vector<int> &arr) {
    int n = arr.size() - 1;
    for (int i = n; i >= 0; i--)
        downHeapify(arr, i, n);

    while (n != 0) {
        swap(arr[0], arr[n--]);
        downHeapify(arr, 0, n);
    }
}

int main(int argc, char **argv) {
    vector<int> arr{10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13, 50};
    HeapSort(arr);

    for (int val : arr)
        cout << val << " ";
    cout << endl;
}