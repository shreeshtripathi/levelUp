#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//~~~~~~~~~~~~~~~~1_Crypto Arithmatic~~~~~~~~~~~~~
string str1 = "YOUR";
string str2 = "YOU";
string str3 = "HEART";
vector<int> assignNum(26, 0);
int numUse = 0;

string createUniqueString()
{
    vector<int> freq(26, 0);
    string str = str1 + str2 + str3;
    for (int i = 0; i < str.size(); i++)
        freq[str[i] - 'A']++;

    str = "";
    for (int i = 0; i < 26; i++)
        if (freq[i] > 0)
            str += (char)(i + 'A');

    return str;
}

int stringToInt(string &s)
{
    int num = 0;
    for (int i = 0; i < s.size(); i++)
    {
        num = num * 10 + assignNum[s[i] - 'A'];
    }
    return num;
}

int cryptoArithmatic(string &str, int idx)
{
    if (idx == str.size())
    {
        int val1 = stringToInt(str1);
        int val2 = stringToInt(str2);
        int val3 = stringToInt(str3);

        if (assignNum[str1[0] - 'A'] != 0 &&
            assignNum[str2[0] - 'A'] != 0 &&
            assignNum[str3[0] - 'A'] != 0 &&
            val1 + val2 == val3)
        {
            cout << "\t" << val1 << endl;
            cout << "+\t" << val2 << endl;
            cout << "~~~~~~~~~~~~~" << endl;
            cout << "\t" << val3 << endl;
            cout << "~~~~~~~~~~~~~" << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;

    for (int num = 0; num < 10; num++)
    {
        int mask = 1 << num;
        if ((numUse & mask) == 0)
        {
            numUse ^= mask;
            assignNum[str[idx] - 'A'] = num;
            count += cryptoArithmatic(str, idx + 1);
            assignNum[str[idx] - 'A'] = 0;
            numUse ^= mask;
        }
    }

    return count;
}

void crypto()
{
    string str = createUniqueString();
    cout << cryptoArithmatic(str, 0);
}

// leetcode : Combination Sum - II ~~~~~~~~~~~~~~~~~~~~
vector<vector<int>> res;
vector<int> ans;

void combination(vector<int> &arr, int idx, int tar)
{
    if (tar == 0)
    {
        vector<int> base;

        for (int ele : ans)
            base.push_back(ele);

        res.push_back(base);
        return;
    }

    // prevent from revise call of same elment
    int prev = -1;
    for (int i = idx; i < arr.size(); i++)
    {
        if (prev == arr[i])
            continue;

        prev = arr[i];
        if (tar - arr[i] >= 0)
        {
            ans.push_back(arr[i]);
            combination(arr, i + 1, tar - arr[i]);
            ans.pop_back();
        }
    }
}

vector<vector<int>> combinationSum2(vector<int> &arr, int tar)
{
    sort(arr.begin(), arr.end());
    combination(arr, 0, tar);
    return res;
}

void solve()
{
    crypto();
}

int main(int argc, char **argv)
{
    solve();
}