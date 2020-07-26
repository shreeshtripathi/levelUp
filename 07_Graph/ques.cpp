#include <iostream>
#include <string>
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

    for(int d = 0; d < 4; d++) {
        int r = x + dir[d][0];
        int c = y + dir[d][1];

        if(r >= 0 && r < board.size() && c >= 0 && c < board[0].size() && board[r][c] == 'O') {
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

int main(int argc, char** argv) {
}