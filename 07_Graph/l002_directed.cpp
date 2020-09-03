#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Edge {
   public:
    int wt;
    int nbr;

    Edge(int nbr, int wt) {
        this->nbr = nbr;
        this->wt = wt;
    }
};

vector<vector<Edge>> graph;

void addEdge(int u, int v, int wt) {
    graph[u].push_back(Edge(v, wt));
}

void display() {
    for (int i = 0; i < graph.size(); i++) {
        cout << "[" << i << "]-> ";
        for (Edge e : graph[i]) {
            cout << "[" << e.nbr << "_" << e.wt << "], ";
        }
        cout << endl;
    }
}

void topoogicalSort(int src, vector<bool>& vis, stack<int>& st) {
    vis[src] = true;
    for (Edge e : graph[src])
        if (vis[e.nbr] == false)
            topoogicalSort(e.nbr, vis, st);

    st.push(src);
}

void topologicalOrder() {
    vector<bool> vis(graph.size(), false);

    stack<int> st;
    for (int i = 0; i < graph.size(); i++)
        if (vis[i] == false)
            topoogicalSort(i, vis, st);

    while (st.size() > 0) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

// Kahns Algorithm - Helpful for Topological Sort type problem
void kahnsAlgo() {
    vector<int> indegree(graph.size(), 0);

    // 1. Fill indegree Array
    for (int i = 0; i < graph.size(); i++) {
        for (Edge e : graph[i])
            indegree[e.nbr]++;
    }

    // 2. Add 0 indegree in queue
    queue<int> que;
    for (int i = 0; i < indegree.size(); i++)
        if (indegree[i] == 0) que.push(i);

    // 3. Make a while loop and add answer in it
    vector<int> ans;
    while (que.size() != 0) {
        int rem = que.front();
        que.pop();
        ans.push_back(rem);

        for (Edge e : graph[rem]) {
            if (--indegree[e.nbr] == 0) que.push(e.nbr);
        }
    }

    if (ans.size() != graph.size()) ans.clear();

    for (int ele : ans) {
        cout << ele << " ";
    }
    cout << endl;
}

void constructGraph() {
    int n = 7;
    graph.resize(7);

    addEdge(0, 1, 10);
    addEdge(1, 2, 10);
    addEdge(2, 3, 10);
    addEdge(0, 3, 40);
    addEdge(3, 4, 2);
    addEdge(4, 5, 3);
    addEdge(5, 6, 3);
    addEdge(4, 6, 8);
}

void solve() {
    constructGraph();
}

int main(int argc, char** argv) {
    constructGraph();
    solve();
}