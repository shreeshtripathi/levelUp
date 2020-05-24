#include <iostream>
#include <vector>

using namespace std;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Coin Change Perm & Comb in comb formula~~~~~~~~~~~~~~~~~~~~~~~~~*/

int coinChangePermutation_INF(vector<int> &coins, int tar, string str)
{
    if (tar == 0)
    {
        cout << str << endl;
        return 1;
    }

    int count = 0;

    for (int coin : coins)
    {
        if (tar - coin >= 0)
        {
            count += coinChangePermutation_INF(coins, tar - coin, str + to_string(coin) + " ");
        }
    }
    return count;
}

int coinChangeCombination_INF(vector<int> &coins, int pi, int tar, string str)
{
    if (tar == 0)
    {
        cout << str << endl;
        return 1;
    }

    int count = 0;

    for (int i = pi; i < coins.size(); i++)
    {
        if (tar - coins[i] >= 0)
        {
            count += coinChangeCombination_INF(coins, i, tar - coins[i], str + to_string(coins[i]) + " ");
        }
    }
    return count;
}

int coinChangeCombination(vector<int> &coins, int pi, int tar, string str)
{
    if (tar == 0)
    {
        cout << str << endl;
        return 1;
    }

    int count = 0;

    for (int i = pi; i < coins.size(); i++)
    {
        if (tar - coins[i] >= 0)
        {
            count += coinChangeCombination(coins, i + 1, tar - coins[i], str + to_string(coins[i]) + " ");
        }
    }
    return count;
}

int coinChangePermutation(vector<int> &coins, int tar, string str)
{
    if (tar == 0)
    {
        cout << str << endl;
        return 1;
    }

    int count = 0;

    for (int i = 0; i < coins.size(); i++)
    {
        int coin = coins[i];
        if (coin > 0 && tar - coin >= 0)
        {
            coins[i] = -coins[i];
            count += coinChangePermutation(coins, tar - coin, str + to_string(coin) + " ");
            coins[i] = -coins[i];
        }
    }
    return count;
}

void subSeq_Comb_style(string &str, string ans, int pi)
{
    if (pi == str.size() + 1)
    {
        return;
    }
    cout << ans << endl;
    // here subseq is for string that why we just add i string
    // if ques is about subset then we add and remove from array(vector)
    for (int i = pi; i < str.size(); i++)
    {
        subSeq_Comb_style(str, ans + str[i] + " ", i + 1);
    }
}

void coinChange()
{
    // cout << coinChangePermutation_INF(coins, 10, "") << " - Count" << endl;
    // cout << coinChangeCombination_INF(coins,0, 10, "") << " - Count" << endl;
    // cout << coinChangeCombination(coins, 0, 10, "") << " - Count" << endl;
    // cout << coinChangePermutation(coins, 10, "") << " - Count" << endl;
    string str = "abc";
    subSeq_Comb_style(str, "", 0);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~Coin Change perm & comb in subseq formula~~~~~~~~~~~~~~~~~~~~~~*/
int coinChangeCombination_subseq(vector<int> &coins, int pi, int tar, string ans)
{
    if (pi >= coins.size() || tar == 0)
    {
        if (tar == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    // yes call
    if (tar - coins[pi] >= 0)
    {
        count += coinChangeCombination_subseq(coins, pi + 1, tar - coins[pi], ans + to_string(coins[pi]) + " ");
    }
    //No call
    count += coinChangeCombination_subseq(coins, pi + 1, tar, ans);
    return count;
}

int coinChangeComb_INF_subseq(vector<int> &coins, int pi, int tar, string ans)
{
    if (pi >= coins.size() || tar == 0)
    {
        if (tar == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    // yes call
    if (tar - coins[pi] >= 0)
    {
        count += coinChangeComb_INF_subseq(coins, pi, tar - coins[pi], ans + to_string(coins[pi]) + " ");
    }
    //No call
    count += coinChangeComb_INF_subseq(coins, pi + 1, tar, ans);
    return count;
}

int coinChangePerm_INF_subseq(vector<int> &coins, int pi, int tar, string ans)
{
    if (pi >= coins.size() || tar == 0)
    {
        if (tar == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    // yes call
    if (tar - coins[pi] >= 0)
    {
        count += coinChangePerm_INF_subseq(coins, 0, tar - coins[pi], ans + to_string(coins[pi]) + " ");
    }
    //No call
    count += coinChangePerm_INF_subseq(coins, pi + 1, tar, ans);
    return count;
}

int coinChangePerm_subseq(vector<int> &coins, int pi, int tar, string ans)
{
    if (pi >= coins.size() || tar == 0)
    {
        if (tar == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    // yes call
    if (coins[pi] > 0 && tar - coins[pi] >= 0)
    {
        int temp = coins[pi]; // hold the +ve value of coin
        coins[pi] = -coins[pi];
        count += coinChangePerm_subseq(coins, 0, tar - temp, ans + to_string(temp) + " ");
        coins[pi] = -coins[pi];
    }
    //No call
    count += coinChangePerm_subseq(coins, pi + 1, tar, ans);
    return count;
}

void coinChangeInSubseqStyle()
{
    vector<int> coins{2, 3, 5, 7};
    // cout << coinChangeCombination_subseq(coins, 0, 10, "");
    // cout << coinChangeComb_INF_subseq(coins, 0, 10, "");
    // cout << coinChangePerm_INF_subseq(coins, 0, 10, "");
    cout << coinChangePerm_subseq(coins, 0, 10, "");
}

/*~~~~~~~~~~~~~~~R rooms & Q queens perm & comb~~~~~~~~~~~~~~~~~~~~~~~*/

int queensPerm(vector<bool> &rooms, int qpsf, int tq, string ans)
{

    if (qpsf == tq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int r = 0; r < rooms.size(); r++)
    {
        if (!rooms[r])
        {
            rooms[r] = true;
            count += queensPerm(rooms, qpsf + 1, tq, ans + "Q" + to_string(qpsf) + "R" + to_string(r) + " ");
            rooms[r] = false;
        }
    }
    return count;
}

int queensComb(vector<bool> &rooms, int room, int qpsf, int tq, string ans)
{
    if (qpsf == tq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int r = room; r < rooms.size(); r++)
    {
        count += queensComb(rooms, r + 1, qpsf + 1, tq, ans + "Q" + to_string(qpsf) + "R" + to_string(r) + " ");
    }
    return count;
}

void queens()
{
    vector<bool> rooms(16, false);
    int tq = 4;
    cout << queensPerm(rooms, 0, tq, "");
    // cout << queensComb(rooms, 0, 0, tq, "");
}

/*~~~~~~~~~~~~~~~R rooms (2D) & Q quuens perm & comb~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int queensPerm2D(vector<vector<bool>> &rooms, int tq, string ans)
{

    if (tq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int r = 0; r < rooms.size() * rooms[0].size(); r++)
    {
        int x = r / rooms[0].size();
        int y = r % rooms[0].size();
        if (!rooms[x][y])
        {
            rooms[x][y] = true;
            count += queensPerm2D(rooms, tq - 1, ans + "(" + to_string(x) + to_string(y) + ") ");
            rooms[x][y] = false;
        }
    }
    return count;
}

int queensComb2D(vector<vector<bool>> &rooms, int room, int tq, string ans)
{

    if (tq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int r = room; r < rooms.size() * rooms[0].size(); r++)
    {
        int x = r / rooms[0].size();
        int y = r % rooms[0].size();
        count += queensComb2D(rooms, r + 1, tq - 1, ans + "(" + to_string(x) + to_string(y) + ") ");
    }
    return count;
}

void queens2D()
{
    vector<vector<bool>> rooms(4, vector<bool>(4, false));
    int tq = 4;
    // cout << queensPerm2D(rooms, tq, "");
    cout << queensComb2D(rooms, 0, tq, "");
}

int main(int argc, char **argv)
{
    // coinChange();
    // coinChangeInSubseqStyle();
    // queens();
    queens2D();
}