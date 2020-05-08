#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Optimisation in nqueen combination
int n = 4;
int m = 4;

vector<bool> ROW(n, false);
vector<bool> COL(m, false);
vector<bool> Dia(n + m - 1, false);
vector<bool> AntiDia(n + m - 1, false);

int nQueen_Optimise1(int n, int m, int lb, int qsf, string ans)
{
    if (qsf == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int b = lb; b < n * m; b++)
    {
        int x = b / m;
        int y = b % m;

        if (!ROW[x] && !COL[y] && !Dia[x + y] && !AntiDia[x - y + m - 1])
        {
            ROW[x] = true;
            COL[y] = true;
            Dia[x + y] = true;
            AntiDia[x - y + m - 1] = true;
            count += nQueen_Optimise1(n, m, b + 1, qsf - 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
            ROW[x] = false;
            COL[y] = false;
            Dia[x + y] = false;
            AntiDia[x - y + m - 1] = false;
        }
    }
    return count;
}

// optimisation using bits;
int row = 0;
int col = 0;
int dia = 0;
int antiDia = 0;

int nQueen_Optimise2(int n, int m, int lb, int qsf, string ans)
{
    if (qsf == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int b = lb; b < n * m; b++)
    {
        int x = b / m;
        int y = b % m;

        // check in bit number using bit manupulation concept
        if ((row & (1 << x)) == 0 && (col & (1 << y)) == 0 && (dia & (1 << (x + y))) == 0 && (antiDia & 1 << (x - y + m - 1)) == 0)
        {
            row ^= (1 << x);
            col ^= (1 << y);
            dia ^= (1 << (x + y));
            antiDia ^= (1 << (x - y + m - 1));
            count += nQueen_Optimise2(n, m, b + 1, qsf - 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
            row ^= (1 << x);
            col ^= (1 << y);
            dia ^= (1 << (x + y));
            antiDia ^= (1 << (x - y + m - 1));
        }
    }
    return count;
}

void nQueen()
{
    // cout << nQueen_Optimise1(n, m, 0, n, "");
    cout << nQueen_Optimise2(n, m, 0, n, "");
}

void solve()
{
    nQueen();
}

int main(int argc, char **argv)
{
    solve();
}