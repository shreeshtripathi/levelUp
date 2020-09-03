#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Leetcode 200. Number of Islands
void island_dfs(int x, int y, vector<vector<char>>& grid, int dir[4][2]) {
    grid[x][y] = '2';
    for (int d = 0; d < 4; d++) {
        int r = x + dir[d][0];
        int c = y + dir[d][1];

        if (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size() && grid[r][c] == '1') {
            island_dfs(r, c, grid, dir);
        }
    }
}

int numIslands(vector<vector<char>>& grid) {
    // 1 = land
    // 0 = water
    // 2 = marked / visited

    int dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    int count = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '1') {
                island_dfs(i, j, grid, dir);
                count++;
            }
        }
    }
    return count;
}

// Leetcode 695. Max Area of Island
int islandMax_dfs(int x, int y, vector<vector<int>>& grid, int dir[4][2]) {
    grid[x][y] = 2;
    int count = 0;
    for (int d = 0; d < 4; d++) {
        int r = x + dir[d][0];
        int c = y + dir[d][1];

        if (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size() && grid[r][c] == 1) {
            count += islandMax_dfs(r, c, grid, dir);
        }
    }
    return count + 1;
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
    // 1 = land
    // 0 = water
    // 2 = marked / visited

    int dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    int count = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 1) {
                count = max(count, islandMax_dfs(i, j, grid, dir));
            }
        }
    }
    return count;
}

// Leetcode 463. Island Perimeter
int islandPerimeter(vector<vector<int>>& grid) {
    int dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    int count = 0;
    int nbr = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 1) {
                count++;
                for (int d = 0; d < 4; d++) {
                    int r = i + dir[d][0];
                    int c = j + dir[d][1];

                    if (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size() && grid[r][c] == 1) {
                        nbr++;
                    }
                }
            }
        }
    }
    return count * 4 - nbr;
}

// Leetcode 130. Surrounded Regions
void surrounded_dfs(int x, int y, vector<vector<char>>& board, int dir[4][2]) {
    board[x][y] = '#';

    for (int d = 0; d < 4; d++) {
        int r = x + dir[d][0];
        int c = y + dir[d][1];

        if (r >= 0 && r < board.size() && c >= 0 && c < board[0].size() && board[r][c] == 'O') {
            surrounded_dfs(r, c, board, dir);
        }
    }
}

void solve(vector<vector<char>>& board) {
    int dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    // convert all boaundary 'O' into '#'
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (i == 0 || j == 0 || i == board.size() - 1 || j == board[0].size() - 1) {
                if (board[i][j] == 'O') {
                    surrounded_dfs(i, j, board, dir);
                }
            }
        }
    }
    // convert rest of innner 'O' into 'X'
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] == 'O')
                board[i][j] = 'X';
        }
    }
    // convert all '#' nto 'O' again
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] == '#')
                board[i][j] = 'O';
        }
    }
}

// Hackerrank : Journey to the moon
// Link : https://www.hackerrank.com/challenges/journey-to-the-moon/problem
// Solution is present in the same folder of this code "astro.cpp"

//==============================================================
// 28th Jully Code
//==============================================================

// Leetcode 994. Rotting Oranges
int orangesRotting(vector<vector<int>>& grid) {
    if (grid.size() == 0 || grid[0].size() == 0) return 0;

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int n = grid.size();
    int m = grid[0].size();

    list<pair<int, int>> queue;

    int freshOranges = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1)
                freshOranges++;
            else if (grid[i][j] == 2)
                queue.push_back({i, j});
        }
    }

    int time = 0;
    if (freshOranges == 0 && queue.size() >= 0) return time;
    while (queue.size() != 0) {
        int size = queue.size();
        while (size--) {
            pair<int, int> rem = queue.front();
            queue.pop_front();

            int x = rem.first;
            int y = rem.second;

            for (int d = 0; d < 4; d++) {
                int r = x + dir[d][0];
                int c = y + dir[d][1];

                if (r >= 0 && r < n && c >= 0 && c < m && grid[r][c] == 1) {
                    grid[r][c] = 2;
                    queue.push_back({r, c});
                    freshOranges--;
                }
            }
        }
        time++;
        if (freshOranges == 0) return time;
    }
    return -1;
}

// Leetcode 1091. Shortest Path in Binary Matrix
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    if (grid.size() == 0 || grid[0].size() == 0) return 0;

    int dir[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

    int n = grid.size();
    int m = grid[0].size();

    if (grid[0][0] == 1 || grid[n - 1][m - 1] == 1) return -1;

    list<pair<int, int>> queue;

    int level = 0;

    queue.push_back({0, 0});
    grid[0][0] = 1;

    while (queue.size() != 0) {
        int size = queue.size();
        while (size--) {
            pair<int, int> rem = queue.front();
            queue.pop_front();

            int x = rem.first;
            int y = rem.second;

            if (x == n - 1 && y == m - 1) return level + 1;

            for (int d = 0; d < 8; d++) {
                int r = x + dir[d][0];
                int c = y + dir[d][1];

                if (r >= 0 && r < n && c >= 0 && c < m && grid[r][c] == 0) {
                    grid[r][c] = 1;
                    queue.push_back({r, c});
                }
            }
        }
        level++;
    }
    return -1;
}

// Leetcode 542. 01 Matrix
vector<vector<int>> updateMatrix(vector<vector<int>>& grid) {
    if (grid.size() == 0 || grid[0].size() == 0) return {};

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> res(n, vector<int>(m, -1));

    list<pair<int, int>> queue;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) {
                queue.push_back({i, j});
                res[i][j] = 0;
            }
        }
    }

    int ones = n * m - queue.size();

    while (queue.size() != 0) {
        int size = queue.size();
        while (size--) {
            pair<int, int> rem = queue.front();
            queue.pop_front();

            int x = rem.first;
            int y = rem.second;

            for (int d = 0; d < 4; d++) {
                int r = x + dir[d][0];
                int c = y + dir[d][1];

                if (r >= 0 && r < n && c >= 0 && c < m && res[r][c] == -1) {
                    res[r][c] = res[x][y] + 1;
                    ones--;
                    queue.push_back({r, c});
                }
            }
            if (ones == 0) break;
        }
    }
    return res;
}

// Leetcode 815. Bus Routes
int numBusesToDestination(vector<vector<int>>& routes, int src, int dst) {
    unordered_map<int, vector<int>> standToBus;

    for (int i = 0; i < routes.size(); i++)
        for (int busStand : routes[i])
            standToBus[busStand].push_back(i);

    queue<int> que;
    // visited for stand
    unordered_set<int> visStand;
    // visited for bus
    vector<bool> visBus(routes.size(), false);

    que.push(src);
    visStand.insert(src);
    int level = 0;

    while (que.size() != 0) {
        int size = que.size();
        while (size--) {
            int busStand = que.front();
            que.pop();

            if (busStand == dst)
                return level;

            for (int bus : standToBus[busStand]) {
                if (visBus[bus] == true)
                    continue;

                for (int busSt : routes[bus]) {
                    if (visStand.find(busSt) == visStand.end()) {
                        que.push(busSt);
                        visStand.insert(busSt);
                    }
                }
                visBus[bus] = true;
            }
        }
        level++;
    }
    return -1;
}

// Leetcode 207. Course Schedule
bool canFinish_(int n, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(n);

    queue<int> que;
    vector<int> indegree(n, 0);

    for (vector<int>& edge : prerequisites) {
        int u = edge[0];
        int v = edge[1];

        graph[u].push_back(v);
        indegree[v]++;
    }

    for (int i = 0; i < indegree.size(); i++) {
        if (indegree[i] == 0) que.push(i);
    }

    vector<int> ans;
    while (que.size() != 0) {
        int rem = que.front();
        que.pop();

        ans.push_back(rem);

        for (int nbr : graph[rem]) {
            if (--indegree[nbr] == 0) que.push(nbr);
        }
    }

    if (ans.size() != n) ans.clear();

    return ans.size() != 0;
}

// Leetcode 207. Course Schedule using DFS(cycle detection in topological sort)
bool isCycleInTopo(vector<vector<int>>& graph, int src, vector<bool>& vis, vector<bool>& myPath) {
    vis[src] = myPath[src] = true;

    bool res = false;
    for (int nbr : graph[src]) {
        if (!vis[nbr])
            res = res || isCycleInTopo(graph, nbr, vis, myPath);
        else if (myPath[nbr])
            return true;
    }
    myPath[src] = false;
    return res;
}

bool canFinish(int n, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(n);

    for (vector<int>& edge : prerequisites) {
        int u = edge[0];
        int v = edge[1];

        graph[u].push_back(v);
    }

    vector<bool> vis(n, false);
    vector<bool> myPath(n, false);

    for (int i = 0; i < n; i++) {
        if (!vis[i] && isCycleInTopo(graph, i, vis, myPath))
            return false;
    }
    return true;
}

// Leetcode 210. Course Schedule II
vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(n);

    queue<int> que;
    vector<int> indegree(n, 0);

    for (vector<int>& edge : prerequisites) {
        int v = edge[0];
        int u = edge[1];

        graph[u].push_back(v);
        indegree[v]++;
    }

    for (int i = 0; i < indegree.size(); i++) {
        if (indegree[i] == 0) que.push(i);
    }

    vector<int> ans;
    while (que.size() != 0) {
        int rem = que.front();
        que.pop();

        ans.push_back(rem);

        for (int nbr : graph[rem]) {
            if (--indegree[nbr] == 0) que.push(nbr);
        }
    }

    if (ans.size() != n) ans.clear();

    return ans;
}

// Leetcode 329. Longest Increasing Path in a Matrix
int longestIncreasingPath(vector<vector<int>>& matrix) {
}

int main(int argc, char** argv) {
}