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
    graph[v].push_back(Edge(u, wt));
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

// remove edge
int findEdge(int u, int v) {
    for (int i = 0; i < graph[u].size(); i++) {
        if (graph[u][i].nbr == v)
            return i;
    }
    return -1;
}

void removeEdge(int u, int v) {
    int idx1 = findEdge(u, v);
    graph[u].erase(graph[u].begin() + idx1);

    int idx2 = findEdge(v, u);
    graph[v].erase(graph[v].begin() + idx2);
}

// remove Vertex
void removeVtx(int v) {
    while (graph[v].size() != 0) {
        int u = graph[v][graph[v].size() - 1].nbr;
        removeEdge(u, v);
    }
}

// haspath
bool hashpath(int src, int dst, vector<bool>& vis) {
    if (src == dst)
        return true;

    bool res = false;
    vis[src] = true;
    for (Edge e : graph[src]) {
        int nbr = e.nbr;
        if (vis[nbr] == false) {
            res = res || hashpath(nbr, dst, vis);
        }
    }

    vis[src] = false;

    return res;
}

// all paths
int AllPath(int src, int dst, vector<bool>& vis, int cost, string str) {
    if (src == dst) {
        str += to_string(src);
        cout << str << " @ " << cost << endl;
        return 1;
    }

    int count = 0;
    vis[src] = true;
    for (Edge e : graph[src]) {
        int nbr = e.nbr;
        int wt = e.wt;
        if (vis[nbr] == false) {
            count += AllPath(nbr, dst, vis, cost + wt, str + to_string(src) + " ");
        }
    }

    vis[src] = false;
    return count;
}

// Max path, min path
// make a pair of <int = cost, string = path> for min/max
pair<int, string> maxPath(int src, int dst, vector<bool>& vis) {
    if (src == dst) {
        return {0, to_string(src)};
    }

    vis[src] = true;
    pair<int, string> mpair = {-1e8, to_string(src)};

    for (Edge e : graph[src]) {
        int nbr = e.nbr;
        int wt = e.wt;

        if (vis[nbr] == false) {
            pair<int, string> rpair = maxPath(nbr, dst, vis);
            if (rpair.first + wt > mpair.first) {
                mpair.first = rpair.first + wt;
                mpair.second = rpair.second;
            }
        }
    }

    mpair.second = to_string(src) + " " + mpair.second;
    vis[src] = false;
    return mpair;
}

pair<int, string> minPath(int src, int dst, vector<bool>& vis) {
    if (src == dst) {
        return {0, to_string(src)};
    }

    vis[src] = true;
    pair<int, string> mpair = {1e8, to_string(src)};

    for (Edge e : graph[src]) {
        int nbr = e.nbr;
        int wt = e.wt;

        if (vis[nbr] == false) {
            pair<int, string> rpair = minPath(nbr, dst, vis);
            if (rpair.first + wt < mpair.first) {
                mpair.first = rpair.first + wt;
                mpair.second = rpair.second;
            }
        }
    }

    mpair.second = to_string(src) + " " + mpair.second;
    vis[src] = false;
    return mpair;
}

// hamiltonian path and cycle
int hamiltonian(int src, int vc, int osrc, vector<bool>& vis, string psf) {
    if (vc == graph.size() - 1) {
        psf += to_string(src);
        cout << psf;

        if (findEdge(src, osrc) == -1)
            cout << " : path" << endl;
        else
            cout << " : cycle" << endl;
        return 1;
    }

    vis[src] = true;

    int count = 0;
    for (Edge e : graph[src]) {
        int nbr = e.nbr;
        if (vis[nbr] == false) {
            count += hamiltonian(nbr, vc + 1, osrc, vis, psf + to_string(src) + " ");
        }
    }

    vis[src] = false;
    return count;
}

// get connected components
void gcc_dfs(int src, vector<bool>& vis) {
    vis[src] = true;
    for (Edge e : graph[src])
        if (!vis[e.nbr])
            gcc_dfs(e.nbr, vis);
}

int gcc() {
    vector<bool> vis(graph.size(), false);
    int count = 0;

    for (int i = 0; i < graph.size(); i++) {
        if (vis[i] == false) {
            gcc_dfs(i, vis);
            count++;
        }
    }

    return count;
}

void solve() {
    // removeVtx(3);
    // display();
    vector<bool> vis(graph.size(), false);
    // cout << hashpath(0, 6, vis) << endl;
    // AllPath(0, 6, vis, 0, "");
    // pair<int, string> res = maxPath(0, 6, vis);
    // pair<int, string> res = minPath(0, 6, vis);
    // cout << res.second << " @ " << res.first << endl;
    // cout << hamiltonian(0, 0, 0, vis, "");
    cout << gcc() << endl;
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
    // addEdge(2, 5, 10); // extra  edge for hamiltonian cycle

    // display();
}

int main(int argc, char** argv) {
    constructGraph();
    solve();
}