#include <iostream>
#include <string>
#include <vector>

using namespace std;

// EquiSet Problem
int equiSet(vector<int> &arr, int idx, int s1, int s2, string set1, string set2) {
    if (idx == arr.size()) {
        if (s1 == s2) {
            cout << set1 << " - " << set2 << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    count += equiSet(arr, idx + 1, s1 + arr[idx], s2, set1 + to_string(arr[idx]) + " ", set2);
    count += equiSet(arr, idx + 1, s1, s2 + arr[idx], set1, set2 + to_string(arr[idx]) + " ");
    return count;
}

int equiSet_2(vector<int> &arr, int idx, int s1, int s2, string set1, string set2) {
    if (idx == arr.size()) {
        if (s1 == s2 && s1 != 0) {
            cout << set1 << "- " << set2 << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    // yes call
    count += equiSet_2(arr, idx + 1, s1 + arr[idx], s2, set1 + to_string(arr[idx]) + " ", set2);
    count += equiSet_2(arr, idx + 1, s1, s2 + arr[idx], set1, set2 + to_string(arr[idx]) + " ");

    // no call
    count += equiSet_2(arr, idx + 1, s1, s2, set1, set2);
    return count;
}

void equiSet() {
    vector<int> arr{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    // cout << equiSet(arr, 0, 0, 0, "", ""); // this will give answer but reition occur
    // cout << equiSet(arr, 1, 10, 0, "10 ", ""); // add from first call

    cout << equiSet_2(arr, 0, 0, 0, "", "");
}

// crossword
vector<vector<char>> board{
    {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
    {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
    {'+', '-', '-', '-', '-', '-', '-', '-', '+', '+'},
    {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
    {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
    {'+', '-', '-', '-', '-', '-', '-', '+', '+', '-'},
    {'+', '-', '+', '+', '+', '-', '+', '+', '+', '-'},
    {'+', '+', '+', '+', '+', '-', '+', '+', '+', '-'},
    {'+', '+', '+', '+', '+', '-', '+', '+', '+', '-'},
    {'+', '+', '+', '+', '+', '+', '+', '+', '+', '+'}};

vector<string> words{"ENGLAND", "GWALIOR", "NORWAY", "AGRA", "ASAM"};

void printBoard() {
    cout << "~~~~~~~~~~~~~~~~~~~~" << endl;
    for (vector<char> &arr : board) {
        for (char &ch : arr)
            cout << ch << " ";

        cout << endl;
    }
    cout << "~~~~~~~~~~~~~~~~~~~" << endl;
}

// horizontal check
bool canPlaceHorizontal(string &word, int x, int y) {
    if (y == 0 && y + word.size() < board[0].size()) {
        if (board[x][y + word.size()] != '+')
            return false;
    } else if (y + word.size() == board[0].size() && (y + word.size() != board[0].size())) {
        if (board[x][y - 1] != '+')
            return false;
    } else {
        if (((y - 1) >= 0 && board[x][y - 1] != '+') || ((y + word.size()) < board[0].size() && board[x][y + word.size()] != '+'))
            return false;
    }

    for (int i = 0; i < word.size(); i++) {
        if (y + i == board[0].size())
            return false;

        if (board[x][y + i] != '-' && board[x][y + i] != word[i])
            return false;
    }
    return true;
}

vector<bool> placeHorizontal(string &word, int x, int y) {
    vector<bool> loc(word.size(), false);
    for (int i = 0; i < word.size(); i++) {
        if (board[x][y + i] == '-') {
            loc[i] = true;
            board[x][y + i] = word[i];
        }
    }
    return loc;
}

void unplaceHorizontal(string &word, int x, int y, vector<bool> &loc) {
    for (int i = 0; i < word.size(); i++) {
        if (loc[i] == true)
            board[x][y + i] = '-';
    }
}

// vertical check
bool canPlaceVertical(string &word, int x, int y) {
    if (x == 0 && word.length() < board.size()) {
        if (board[x + word.length()][y] != '+')
            return false;
    } else if ((x + word.length()) == board.size() && (word.length() != board.size())) {
        if (board[x - 1][y] != '+')
            return false;
    } else {
        if (((x - 1) >= 0 && board[x - 1][y] != '+') || ((x + word.length()) < board.size() && board[x + word.length()][y] != '+'))
            return false;
    }

    for (int i = 0; i < word.length(); i++) {
        if ((x + i) == board.size())
            return false;
        if (board[x + i][y] != '-' && board[x + i][y] != word[i])
            return false;
    }

    return true;
}

vector<bool> placeVertical(string &word, int x, int y) {
    vector<bool> loc(word.size(), false);
    for (int i = 0; i < word.size(); i++) {
        if (board[x + i][y] == '-') {
            loc[i] = true;
            board[x + i][y] = word[i];
        }
    }
    return loc;
}

void unplaceVertical(string &word, int x, int y, vector<bool> &loc) {
    for (int i = 0; i < word.size(); i++) {
        if (loc[i] == true)
            board[x + i][y] = '-';
    }
}

int crossWord_1(int idx) {
    if (idx == words.size()) {
        printBoard();
        return 1;
    }

    string word = words[idx];
    int count = 0;
    for (int x = 0; x < board.size(); x++) {
        for (int y = 0; y < board[0].size(); y++) {
            if (board[x][y] == '-' || board[x][y] == word[0]) {
                // place word horizontally - if possible
                if (canPlaceHorizontal(word, x, y)) {
                    // cout << word << " " << x << ", " << y << "-H" << endl;
                    vector<bool> loc = placeHorizontal(word, x, y);
                    count += crossWord_1(idx + 1);
                    unplaceHorizontal(word, x, y, loc);
                }

                // place word vertically - if possible
                if (canPlaceVertical(word, x, y)) {
                    vector<bool> loc = placeVertical(word, x, y);
                    // cout << word << " " << x << ", " << y << "-V" << endl;
                    count += crossWord_1(idx + 1);
                    unplaceVertical(word, x, y, loc);
                }
            }
        }
    }
    return count;
}

void crossWord() {
    cout << crossWord_1(0);
}

// Leetcode 39 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<vector<int>> res;

void combSum(vector<int> &coins, int idx, int tar, vector<int> &ans) {
    if (tar == 0) {
        vector<int> base;
        for (int val : ans)
            base.push_back(val);

        res.push_back(base);
        return;
    }

    for (int i = idx; i < coins.size(); i++) {
        if (tar - coins[i] >= 0) {
            ans.push_back(coins[i]);
            combSum(coins, i, tar - coins[i], ans);
            ans.pop_back();
        }
    }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<int> ans;
    combSum(candidates, 0, target, ans);
    return res;
}

// leetcode 77
vector<vector<int>> res;

void combSum_(int num, int idx, int k, vector<int> &ans) {
    if (ans.size() == k) {
        vector<int> base;
        for (int val : ans)
            base.push_back(val);

        res.push_back(base);
    }

    if (idx > num) {
        return;
    }

    for (int i = idx; i <= num; i++) {
        ans.push_back(i);
        combSum_(num, i + 1, k, ans);
        ans.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<int> ans;
    combSum_(n, 1, k, ans);
    return res;
}

// lintCode 2
vector<vector<int>> res;

void combSum_2(vector<int> &coins, int idx, int k, int tar, vector<int> &ans) {
    if (tar == 0) {
        if (ans.size() == k) {
            vector<int> base;
            for (int val : ans)
                base.push_back(val);

            res.push_back(base);
        }
        return;
    }

    for (int i = idx; i < coins.size(); i++) {
        if (tar - coins[i] >= 0) {
            ans.push_back(coins[i]);
            combSum_2(coins, i + 1, k, tar - coins[i], ans);
            ans.pop_back();
        }
    }
}

vector<vector<int>> kSumII(vector<int> &A, int k, int target) {
    vector<int> ans;
    combSum_2(A, 0, k, target, ans);
    return res;
}

void solve() {
    // equiSet();
    crossWord();
}

int main(int argc, char **argv) {
    solve();
}