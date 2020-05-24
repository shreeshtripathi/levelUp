#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isQueenSafe(vector<vector<bool>> &board, int i, int j)
{
    // direction for permutation
    // vector<vector<int>> dir = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

    // direction for combination
    vector<vector<int>> dir = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};
    for (int d = 0; d < dir.size(); d++)
    {
        for (int r = 1; r < board.size(); r++)
        {
            int x = i + (r * dir[d][0]);
            int y = j + (r * dir[d][1]);

            if (x >= 0 && y >= 0 && x < board.size() && y < board[0].size())
            {
                if (board[x][y] == true)
                    return false;
            }
            else
            {
                break;
            }
        }
    }
    return true;
}

int nQueens_01(vector<vector<bool>> &board, int lb, int qsf, string ans)
{
    if (qsf == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int b = lb; b < board.size() * board[0].size(); b++)
    {
        int x = b / board[0].size();
        int y = b % board[0].size();

        if (isQueenSafe(board, x, y))
        {
            board[x][y] = true;
            count += nQueens_01(board, b + 1, qsf - 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
            board[x][y] = false;
        }
    }
    return count;
}

int nQueen_Perm(vector<vector<bool>> &board, int lb, int qsf, string ans)
{
    if (qsf == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int b = 0; b < board.size() * board[0].size(); b++)
    {
        int x = b / board[0].size();
        int y = b % board[0].size();

        if (board[x][y] == false && isQueenSafe(board, x, y))
        {
            board[x][y] = true;
            count += nQueen_Perm(board, b + 1, qsf - 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
            board[x][y] = false;
        }
    }
    return count;
}

int nQueen_Subseq(vector<vector<bool>> &board, int lb, int qsf, string ans)
{

    if (lb == board.size() * board[0].size() || qsf == 0)
    {
        if (qsf == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int x = lb / board[0].size();
    int y = lb % board[0].size();

    int count = 0;
    if (isQueenSafe(board, x, y) == true)
    {
        board[x][y] = true;
        count += nQueen_Subseq(board, lb + 1, qsf - 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
        board[x][y] = false;
    }

    count += nQueen_Subseq(board, lb + 1, qsf, ans);
    return count;
}

int nQueenPerm_Subseq(vector<vector<bool>> &board, int lb, int qsf, string ans)
{
    if (lb == board.size() * board[0].size() || qsf == 0)
    {
        if (qsf == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int x = lb / board[0].size();
    int y = lb % board[0].size();

    int count = 0;
    if (board[x][y] == false && isQueenSafe(board, x, y) == true)
    {
        board[x][y] = true;
        count += nQueenPerm_Subseq(board, 0, qsf - 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
        board[x][y] = false;
    }

    count += nQueenPerm_Subseq(board, lb + 1, qsf, ans);
    return count;
}

void nQueens()
{
    vector<vector<bool>> board(4, vector<bool>(4, false));
    // cout << nQueens_01(board, 0, 4, "");
    // cout << nQueen_Subseq(board, 0, 4, "");
    // cout << nQueen_Perm(board, 0, 4, "");
    cout << nQueenPerm_Subseq(board, 0, 4, "");
}

// bool isKnightSafe(vector<vector<int>>& board, int i, int j) {

// }

void printBoard(vector<vector<int>> &board)
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
    for (vector<int> row : board)
    {
        for (int val : row)
        {
            cout << val << "\t"
                 << " ";
        }
        cout << endl;
    }
}

bool knightsTour(vector<vector<int>> &board, int kpsf, int r, int c)
{
    board[r][c] = kpsf;
    if (kpsf == board.size() * board[0].size() - 1)
    {
        printBoard(board);
        return true;
    }

    // we can declare stati so that it will not made in each level of recursion
    static int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    static int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    bool res = false;
    for (int d = 0; d < 8; d++)
    {
        int x = r + xMove[d];
        int y = c + yMove[d];

        if (x >= 0 && y >= 0 && x < board.size() && y < board[0].size() && board[x][y] == -1)
        {
            res = res || knightsTour(board, kpsf + 1, x, y);
        }
    }

    board[r][c] = -1;

    return res;
}

void knights()
{
    vector<vector<int>> board(8, vector<int>(8, -1));
    knightsTour(board, 0, 0, 0);
}

void solve()
{
    // nQueens();
    knights();
}

int main(int argc, char **argv)
{
    solve();
}