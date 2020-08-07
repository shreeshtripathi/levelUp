#include <iostream>
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

void topoogicalSort() {
    vector<int> stack;
    vector<bool> vis(graph.size(), false);

    for(int v = 0; v < graph.size(); v++) {
        if(graph.size())
    }

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

int main(int argc, char** argv) {
    constructGraph();
    solve();
}