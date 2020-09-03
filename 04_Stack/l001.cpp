#include <iostream>

using namespace std;

class MyStack {
   private:
    int n = 10000;
    int* arr = nullptr;
    int sz = 0;
    int tos = -1;

   public:
    MyStack() {
        this->arr = new int[this->n];
    }

    MyStack(int n) {
        this->n = n;
        this->arr = new int[this->n];
    }

    void push(int val) {
        if (this->sz == this->n) return;
        this->tos++;
        this->arr[tos] = val;
        this->sz++;
    }

    void pop() {
        if (this->sz == 0) return;
        this->tos--;
        this->sz--;
    }

    int top() {
        return this->sz == 0 ? -1 : this->arr[tos];
    }

    int size() {
        return this->sz;
    }

    bool isEmpty() {
        return this->sz == 0;
    }
};

void solve() {
    MyStack st;

    for (int i = 1; i <= 10; i++) {
        st.push(10 + i);
    }

    while (st.size() > 0) {
        cout << st.top() << " ";
        st.pop();
    }
    // cout << st.top();
}

int main(int argc, char** argv) {
    solve();
}