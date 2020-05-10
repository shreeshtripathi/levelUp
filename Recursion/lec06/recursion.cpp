#include <iostream>
#include <vector>
#include <string>

using namespace std;

//~~~~~~~~~~~~~1_Sudoku~~~~~~~~~~~~~~

bool isSafeToPlace(vector<vector<char>> &board, int x, int y, int num)
{
    // row
    for (int i = 0; i < board.size(); i++)
        if (board[x][i] - '0' == num)
            return false;
    // col
    for (int j = 0; j < board.size(); j++)
        if (board[j][y] - '0' == num)
            return false;
    // check in sub matrix

    x = (x / 3) * 3;
    y = (y / 3) * 3;
    for (int i = x; i < x + 3; i++)
        for (int j = y; j < y + 3; j++)
            if (board[i][j] - '0' == num)
                return false;

    return true;
}

bool solveSudoku_1(vector<vector<char>> &board, vector<int> calls, int indx)
{
    if (indx == calls.size())
    {
        return true;
    }

    int x = calls[indx] / 9;
    int y = calls[indx] % 9;

    bool res = false;

    for (int n = 1; n <= 9; n++)
    {
        if (isSafeToPlace(board, x, y, n))
        {
            board[x][y] = (char)(n + '0');
            res = solveSudoku_1(board, calls, indx + 1);
            if (res)
                return true;
            board[x][y] = '.';
        }
    }
    return res;
}

//~~~~~~~~~~~~~Sudoku(Optimise)~~~~~~~~~~~~~~
vector<int> srow;
vector<int> scol;
vector<vector<int>> smat;

bool solveSudoku_2(vector<vector<char>> &board, vector<int> &calls, int indx)
{
    if (indx == calls.size())
    {
        return true;
    }

    int x = calls[indx] / 9;
    int y = calls[indx] % 9;

    for (int n = 1; n <= 9; n++)
    {
        int mask = 1 << n;
        if ((srow[x] & mask) == 0 && (scol[y] & mask) == 0 && (smat[x / 3][y / 3] & mask) == 0)
        {
            board[x][y] = (char)(n + '0');

            srow[x] ^= mask;
            scol[y] ^= mask;
            smat[x / 3][y / 3] ^= mask;

            if (solveSudoku_2(board, calls, indx + 1))
                return true;

            board[x][y] = '.';
            srow[x] ^= mask;
            scol[y] ^= mask;
            smat[x / 3][y / 3] ^= mask;
        }
    }
    return false;
}

//~~~~~~~~~~~~~3_IsValidSudoku~~~~~~~~~~~~~~
bool isValidSudoku(vector<vector<char>> &board)
{
    vector<int> row(9, 0);
    vector<int> col(9, 0);
    vector<vector<int>> mat(3, vector<int>(3, 0));

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '.')
            {
                int num = board[i][j] - '0';
                int mask = (1 << num);
                if ((row[i] & mask) != 0 || (col[j] & mask) != 0 || (mat[i / 3][j / 3] & mask) != 0)
                    return false;

                row[i] ^= mask;
                col[j] ^= mask;
                mat[i / 3][j / 3] ^= mask;
            }
        }
    }

    return true;
}

void sudoku(vector<vector<char>> &board)
{
    vector<int> calls;
    srow.assign(9, 0);
    scol.assign(9, 0);
    smat.assign(3, vector<int>(3, 0));

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == '.')
            {
                calls.push_back(i * 9 + j);
            }
            else
            {
                int num = board[i][j] - '0';
                int mask = (1 << num);
                srow[i] ^= mask;
                scol[j] ^= mask;
                smat[i / 3][j / 3] ^= mask;
            }
        }
    }
    solveSudoku_2(board, calls, 0);
}

//~~~~~~~~~~~~~~~~~WORD BREAK~~~~~~~~~~~~~~~~~~~~~~~~~
vector<string> dictionary{"mobile", "samsung", "sam", "sung",
                          "man", "mango", "icecream", "and",
                          "go", "i", "like", "ice", "cream"};

bool isContain(string &smallStr)
{
    for (string& s : dictionary)
        if (smallStr == s)
            return true;

    return false;
}

int wordBreak(string &str, int idx, string ans)
{
    if(idx == str.size()) {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = idx; i < str.size(); i++)
    {
        string smallStr = str.substr(idx, i - idx + 1);
        // cout << idx << "->" << smallStr << endl;
        if (isContain(smallStr))
        {
            count += wordBreak(str, i + 1, ans + smallStr + " ");
        }
    }
    return count;
}

void solve()
{
    string str = "ilikesamsungmangoicecream";
    cout << wordBreak(str, 0, "");
}

int main(int argc, char **argv)
{
    solve();
}