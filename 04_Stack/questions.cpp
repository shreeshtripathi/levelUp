#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void display(vector<int>& arr) {
    for (int val : arr)
        cout << val << " ";

    cout << endl;
}

// next greater left to right
void ngL2R(vector<int>& arr) {
    if (arr.size() == 0) return;
    stack<int> st;
    st.push(0);
    vector<int> res(arr.size(), arr.size());

    for (int i = 1; i < arr.size(); i++) {
        while (st.size() > 0 && arr[st.top()] < arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    display(res);
}

// next greater right to left
void ngR2L(vector<int>& arr) {
    if (arr.size() == 0) return;
    stack<int> st;
    st.push(arr.size() - 1);
    vector<int> res(arr.size(), -1);

    for (int i = arr.size() - 2; i >= 0; i--) {
        while (st.size() > 0 && arr[st.top()] < arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    display(res);
}

// next smaller left to right
void nsL2R(vector<int>& arr) {
    if (arr.size() == 0) return;
    stack<int> st;
    st.push(0);
    vector<int> res(arr.size(), arr.size());

    for (int i = 1; i < arr.size(); i++) {
        while (st.size() > 0 && arr[st.top()] > arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    display(res);
}

// next smaller right to left
void nsR2L(vector<int>& arr) {
    if (arr.size() == 0) return;
    stack<int> st;
    st.push(arr.size() - 1);
    vector<int> res(arr.size(), -1);

    for (int i = arr.size() - 2; i >= 0; i--) {
        while (st.size() > 0 && arr[st.top()] > arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    display(res);
}

// Next Greater from left to right
// Link : https://practice.geeksforgeeks.org/problems/next-larger-element/0
void nge(vector<long>& arr) {
    vector<int> res(arr.size(), -1);
    stack<int> st;
    st.push(0);

    for (int i = 1; i < arr.size(); i++) {
        while (st.size() > 0 && arr[st.top()] < arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    for (int i = 0; i < res.size(); i++) {
        if (res[i] >= 0 && res[i] < arr.size())
            cout << arr[res[i]] << " ";
        else
            cout << res[i] << " ";
    }

    cout << endl;
}

// Leetcode 20. Valid Parentheses
bool isValid(string s) {
    stack<char> st;
    for (int i = 0; i < s.size(); i++) {
        char ch = s[i];
        if (ch == '[' || ch == '{' || ch == '(') {
            st.push(ch);
        } else if (st.size() > 0 && ch == '}' && st.top() == '{') {
            st.pop();
        } else if (st.size() > 0 && ch == ']' && st.top() == '[') {
            st.pop();
        } else if (st.size() > 0 && ch == ')' && st.top() == '(') {
            st.pop();
        } else {
            return false;
        }
    }
    return st.size() == 0 ? true : false;
}

// Leetcode 1021. Remove Outermost Parentheses
string removeOuterParentheses(string S) {
    string str = "";
    int count = 0;
    for (int i = 0; i < S.size(); i++) {
        char ch = S[i];
        if (ch == '(' && count++ > 0) str += ch;
        if (ch == ')' && count-- > 1) str += ch;
    }
    return str;
}

// Leetcode 503. Next Greater Element II
vector<int> nextGreaterElements(vector<int>& arr) {
    int n = arr.size();
    vector<int> res(n, -1);
    stack<int> st;
    st.push(0);

    for (int i = 1; i < 2 * n; i++) {
        while (st.size() > 0 && arr[st.top()] < arr[i % n]) {
            res[st.top()] = arr[i % n];
            st.pop();
        }
        if (i < n)
            st.push(i);
    }
    return res;
}



void solve() {
    vector<int> arr = {2, -1, 8, 6, 9, 4, 3, 5};
    // ngL2R(arr);
    // ngR2L(arr);
    // nsL2R(arr);
    // nsR2L(arr);
}

int main(int argc, char** argv) {
    solve();
}