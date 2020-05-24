#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*~~~~~~~~~~~ 1219 leetcode~~~~~~~~~~~*/
int getMaximumGold(int sr, int sc, vector<vector<int>> &grid, int dir[][2])
{
    grid[sr][sc] = -grid[sr][sc];
    int res = 0;

    for (int d = 0; d < 4; d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];

        if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] > 0)
            res = max(res, getMaximumGold(x, y, grid, dir));
    }

    grid[sr][sc] = -grid[sr][sc];
    return res + grid[sr][sc];
}

int getMaximumGold(vector<vector<int>> &grid)
{
    int dir[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int res = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            res = max(res, getMaximumGold(i, j, grid, dir));
        }
    }
    return res;
}

/*~~~~~~~~~~~ 980 leetcode~~~~~~~~~~~*/
int solveUnique(int sr, int sc, int dr, int dc, vector<vector<int>> &grid, int dir[][2], int fc)
{
    // destination
    if (sr == dr && sc == dc)
    {
        if (fc == 1)
            return 1;
        else
            return 0;
    }
    grid[sr][sc] = -2;
    // recursion
    int paths = 0;
    for (int d = 0; d < 4; d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];

        if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] >= 0)
            paths += solveUnique(x, y, dr, dc, grid, dir, fc - 1);
    }
    grid[sr][sc] = 0;
    return paths;
}

int uniquePathsIII(vector<vector<int>> &grid)
{
    int fc = 0;
    int sr = 0, sc = 0, dr = 0, dc = 0;
    int dir[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1)
            {
                sr = i, sc = j;
            }
            if (grid[i][j] == 2)
            {
                dr = i, dc = j;
            }
            if (grid[i][j] != -1)
            {
                fc++;
            }
        }
    }
    return solveUnique(sr, sc, dr, dc, grid, dir, fc);
}

void solve()
{
}

int main(int argc, char **argv)
{
    solve();
}
