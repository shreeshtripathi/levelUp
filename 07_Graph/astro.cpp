#include <iostream>
#include <vector>

using namespace std;

// Link of Problem
// https://www.hackerrank.com/challenges/journey-to-the-moon/problem

vector<vector<int>> graph;

void display() {
    for (int i = 0; i < graph.size(); i++) {
        cout << "[" << i << "] -> ";
        for (int e : graph[i])
            cout << e << ", ";
        cout << endl;
    }
}

int gcc_dfs(int src, vector<bool>& vis) {
    vis[src] = true;
    int count = 0;
    for (int e : graph[src]) {
        if (vis[e] == false) {
            count += gcc_dfs(e, vis);
        }
    }
    return count + 1;
}

// O(n) time and O(n) space
long gcc_01() {
    vector<int> astros;
    vector<bool> vis(graph.size(), false);
    for (int i = 0; i < graph.size(); i++) {
        if (vis[i] == false) {
            int res = gcc_dfs(i, vis);
            astros.push_back(res);
        }
    }

    // find overall sum, lets it is osum
    long osum = 0;
    for (int ele : astros)
        osum += ele;

    long ans = 0;
    for (int ele : astros) {
        osum -= ele;
        ans += (ele * osum);
    }

    return ans;
}

// O(n) time and O(1) space
long gcc_02() {
    vector<bool> vis(graph.size(), false);
    long osum = 0;
    long ans = 0;
    for (int i = 0; i < graph.size(); i++) {
        if (vis[i] == false) {
            int res = gcc_dfs(i, vis);
            ans += (osum * res);
            osum += res;
        }
    }
    return ans;
}

int main(int argc, char** argv) {
    int n, e;
    cin >> n >> e;
    graph.resize(n);

    // add edge
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // display();
    // cout << gcc_01() << endl;
    cout << gcc_02() << endl;
}