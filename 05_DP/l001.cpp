#include <iostream>
#include <vector>
#include <list>

using namespace std;

//PRINT==================================================================
// Printing the storage 1D
void display(vector<int> &dp)
{
	for (int i = 0; i < dp.size(); i++)
		cout << dp[i] << " ";
	cout << endl;
}

// Printing the storage 2D
void display2D(vector<vector<int>> &dp)
{
	for (int r = 0; r < dp.size(); r++)
	{
		for (int c = 0; c < dp[0].size(); c++)
			cout << dp[r][c] << " ";
		cout << endl;
	}
}
//Fibonacci=======================================================================
// Memoisation
int fibo(int n, vector<int> &dp)
{
	if (n <= 1)
		return dp[n] = n;

	if (dp[n] != 0)
		return dp[n];

	int ans = fibo(n - 1, dp) + fibo(n - 2, dp);

	return dp[n] = ans;
}

// Tabulation
int fiboDP(int N, vector<int> &dp)
{
	for (int n = 0; n <= N; n++)
	{
		if (n <= 1)
		{
			dp[n] = n;
			continue;
		}
		int ans = dp[n - 1] + dp[n - 2];
		dp[n] = ans;
	}
	return dp[N];
}

// two pointer approach of fibonacci
int fibo_btr(int n)
{
	int a = 0;
	int b = 1;
	int sum = 0;

	for (int i = 0; i < n; i++)
	{
		sum = a + b;
		a = b;
		b = sum;
	}
	return a;
}

void set1()
{
	int n = 5;
	vector<int> dp(n + 1, 0);
	// cout << fibo(n, dp) << endl;
	// cout << fiboDP(n, dp) << endl;
	cout << fibo_btr(n) << endl;
	// display(dp);
}

// Mazepath Series=============================================================
int mazePathHV(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
	if (sr == er && sc == ec)
		return dp[sr][sc] = 1;

	if (dp[sr][sc] != 0)
		return dp[sr][sc];

	int count = 0;
	if (sr + 1 <= er)
		count += mazePathHV(sr + 1, sc, er, ec, dp);

	if (sc + 1 <= ec)
		count += mazePathHV(sr, sc + 1, er, ec, dp);

	if (sr + 1 <= er && sc + 1 <= ec)
		count += mazePathHV(sr + 1, sc + 1, er, ec, dp);

	return dp[sr][sc] = count;
}

int mazePathHV_DP(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
	for (sr = er; sr >= 0; sr--)
	{
		for (sc = ec; sc >= 0; sc--)
		{
			if (sr == er && sc == ec)
			{
				dp[sr][sc] = 1;
				continue;
			}

			int count = 0;
			if (sr + 1 <= er)
				count += dp[sr + 1][sc];

			if (sc + 1 <= ec)
				count += dp[sr][sc + 1];

			if (sr + 1 <= er && sc + 1 <= ec)
				count += dp[sr + 1][sc + 1];
			dp[sr][sc] = count;
		}
	}
	return dp[0][0];
}

// mazepath, moves in loop
int mazePathMulti(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
	if (sr == er && sc == ec)
		return dp[sr][sc] = 1;

	if (dp[sr][sc] != 0)
		return dp[sr][sc];

	int count = 0;
	for (int jump = 1; sr + jump <= er; jump++)
		count += mazePathMulti(sr + jump, sc, er, ec, dp);

	for (int jump = 1; sc + jump <= er; jump++)
		count += mazePathMulti(sr, sc + jump, er, ec, dp);

	for (int jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
		count += mazePathMulti(sr + jump, sc + jump, er, ec, dp);
	return dp[sr][sc] = count;
}

int mazePathMulti_DP(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{

	for (sr = er; sr >= 0; sr--)
	{
		for (sc = ec; sc >= 0; sc--)
		{
			if (sr == er && sc == ec)
			{
				dp[sr][sc] = 1;
				continue;
			}

			int count = 0;
			for (int jump = 1; sr + jump <= er; jump++)
				count += dp[sr + jump][sc];

			for (int jump = 1; sc + jump <= er; jump++)
				count += dp[sr][sc + jump];

			for (int jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
				count += dp[sr + jump][sc + jump];

			dp[sr][sc] = count;
		}
	}

	return dp[0][0];
}

// Board path======================================================================
int boardPath(int sp, int ep, vector<int> &dp)
{
	if (sp == ep)
		return dp[sp] = 1;

	if (dp[sp] != 0)
		return dp[sp];

	int count = 0;
	for (int dice = 1; sp + dice <= ep && dice <= 6; dice++)
		count += boardPath(sp + dice, ep, dp);

	return dp[sp] = count;
}

int boardPath_DP(int sp, int ep, vector<int> &dp)
{
	for (sp = ep; sp >= 0; sp--)
	{
		if (sp == ep)
		{
			dp[sp] = 1;
			continue;
		}

		int count = 0;
		for (int dice = 1; dice + sp <= ep && dice <= 6; dice++)
			count += dp[sp + dice];
		dp[sp] = count;
	}
	return dp[0];
}

int boardPath_btr(int sp, int ep)
{
	list<int> ll;
	for (sp = ep; sp >= 0; sp--)
	{
		if (sp > ep - 2)
		{
			ll.push_front(1);
			continue;
		}

		if (ll.size() <= 6)
			ll.push_front(2 * ll.front());
		else
		{
			ll.push_front(2 * ll.front() - ll.back());
			ll.pop_back();
		}
	}
	return ll.front();
}

int boardPathWithDiceArray(int sp, int ep, vector<int> &dp, vector<int> &darr)
{
	for (sp = ep; sp >= 0; sp--)
	{
		if (sp == ep)
		{
			dp[sp] = 1;
			continue;
		}

		int count = 0;
		for (int dice = 0; darr[dice] + sp <= ep && dice < darr.size(); dice++)
			count += dp[sp + darr[dice]];
		dp[sp] = count;
	}
	return dp[0];
}

void pathSet()
{
	// int n = 3;
	// int m = 3;
	// vector<vector<int>> dp(n, vector<int>(m, 0));
	// cout << mazePathHV(0, 0, n - 1, m - 1, dp) << endl;
	// cout << mazePathHV_DP(0, 0, n - 1, m - 1, dp) << endl;
	// cout << mazePathMulti(0, 0, n - 1, m - 1, dp) << endl;
	// cout << mazePathMulti_DP(0, 0, n - 1, m - 1, dp) << endl;

	int sp = 0, ep = 10;
	vector<int> dp(ep + 1, 0);
	// cout << boardPath(sp, ep, dp) << endl;
	// cout << boardPath_DP(sp, ep, dp) << endl;
	// cout << boardPath_btr(0, 10) << endl;
	vector<int> darr{1, 2, 3, 4, 5, 6};
	cout << boardPathWithDiceArray(0, 10, dp, darr) << endl;

	// display(dp);
	// display2D(dp);
}

// Leetcode 70. Climbing Stairs==================================================
// memoisation
int climbStairs_01(int n, vector<int> &dp)
{
	if (n == 0 || n == 1)
		return dp[n] = 1;

	if (dp[n] != 0)
		return dp[n];

	int ans = climbStairs_01(n - 1, dp) + climbStairs_01(n - 2, dp);
	return dp[n] = ans;
}

int climbStairs_DP(int N, vector<int> &dp)
{
	for (int n = 0; n <= N; n++)
	{
		if (n == 0 || n == 1)
		{
			dp[n] = 1;
			continue;
		}

		int ans = dp[n - 1] + dp[n - 2];
		dp[n] = ans;
	}

	return dp[N];
}

int climbStairs_btr(int N)
{
	int a = 1;
	int b = 1;
	int sum = 1;
	for (int n = 2; n <= N; n++)
	{
		sum = a + b;
		a = b;
		b = sum;
	}
	return sum;
}

int climbStairs(int n)
{
	// vector<int> dp(n + 1, 0);
	// return climbStairs_01(n, dp);
	// return climbStairs_DP(n, dp);
	return climbStairs_btr(n);
}

// Leetcode 746. Min Cost Climbing Stairs=====================================
int minCostClimbingStaris_01(int n, vector<int> &dp, vector<int> &cost)
{
	if (n <= 1)
	{
		return dp[n] = cost[n];
	}

	if (dp[n] != 0)
		return dp[n];

	int ans = min(minCostClimbingStaris_01(n - 1, dp, cost),
				  minCostClimbingStaris_01(n - 2, dp, cost));
	return dp[n] = ans + cost[n];
}

int minCostClimbingStairsDP(int n, vector<int> &dp, vector<int> &cost)
{
	int N = n;
	for (int n = 0; n <= N; n++)
	{
		if (n <= 1)
		{
			dp[n] = cost[n];
			continue;
		}

		int ans = min(dp[n - 1], dp[n - 2]);
		dp[n] = ans + cost[n];
	}
	return dp[N];
}

int minCostClimbingStairs(vector<int> &cost)
{
	int n = cost.size();

	cost.push_back(0);
	vector<int> dp(n + 1, 0);

	// return minCostClimbingStairs(n, dp, cost);
	return minCostClimbingStairsDP(n, dp, cost);
}

// friends Pairing problem==================================================
// Link : https://practice.geeksforgeeks.org/problems/friends-pairing-problem/0
int friendsPairProblem_01(int n, vector<int> &dp)
{
	if (n <= 1)
		return dp[n] = 1;

	if (dp[n] != 0)
		return dp[n];

	int single = friendsPairProblem_01(n - 1, dp);
	int pair = friendsPairProblem_01(n - 2, dp) * (n - 1);

	return dp[n] = single + pair;
}

int friendsPairProblem_DP(int N, vector<int> &dp)
{
	for (int n = 0; n <= N; n++)
	{
		if (n <= 1)
		{
			dp[n] = 1;
			continue;
		}

		int single = dp[n - 1];
		int pair = dp[n - 2] * (n - 1);

		dp[n] = single + pair;
	}
	return dp[N];
}

void friendsPairProblem()
{
	int n = 10;
	vector<int> dp(n + 1, 0);
	cout << friendsPairProblem_01(n, dp) << endl;

	display(dp);
}

// Leetcode 64. Minimum Path Sum==================================================
int minPathSum_01(int sr, int sc, int er, int ec,
				  vector<vector<int>> &dp, vector<vector<int>> &grid)
{
	if (sr == er && sc == ec)
		return dp[sr][sc] = grid[sr][sc];

	if (dp[sr][sc] != 0)
		return dp[sr][sc];
	int right = 1e8, down = 1e8;
	if (sc + 1 <= ec)
		right = minPathSum_01(sr, sc + 1, er, ec, dp, grid);

	if (sr + 1 <= er)
		down = minPathSum_01(sr + 1, sc, er, ec, dp, grid);

	return dp[sr][sc] = min(right, down) + grid[sr][sc];
}

int minPathSum_DP(int sr, int sc, int er, int ec,
				  vector<vector<int>> &dp, vector<vector<int>> &grid)
{
	for (sr = er; sr >= 0; sr--)
	{
		for (sc = ec; sc >= 0; sc--)
		{
			if (sr == er && sc == ec)
			{
				dp[sr][sc] = grid[sr][sc];
				continue;
			}

			int right = 1e8, down = 1e8;

			if (sc + 1 <= ec)
				right = dp[sr][sc + 1];

			if (sr + 1 <= er)
				down = dp[sr + 1][sc];

			dp[sr][sc] = min(right, down) + grid[sr][sc];
		}
	}
	return dp[0][0];
}

int minPathSum(vector<vector<int>> &grid)
{
	int n = grid.size();
	int m = grid[0].size();
	vector<vector<int>> dp(n, vector<int>(m, 0));
	// return minPathSum_01(0, 0, n - 1, m - 1, dp, grid);
	return minPathSum_DP(0, 0, n - 1, m - 1, dp, grid);
}

//==========================================================================================
// Goldmine link: https://practice.geeksforgeeks.org/problems/gold-mine-problem/0
int goldmine_01(int sr, int sc, vector<vector<int>> &mine, vector<vector<int>> &dp)
{
	if (sc == mine[0].size() - 1)
		return dp[sr][sc] = mine[sr][sc];

	if (dp[sr][sc] != 0)
		return dp[sr][sc];

	int dir[3][2] = {{-1, 1}, {0, 1}, {1, 1}};

	int maxGold = 0;
	for (int i = 0; i < 3; i++)
	{
		int x = dir[i][0] + sr;
		int y = dir[i][1] + sc;

		if (x >= 0 && y >= 0 && x < mine.size() && y < mine[0].size())
			maxGold = max(maxGold, goldmine_01(x, y, mine, dp));
	}

	return dp[sr][sc] = maxGold + mine[sr][sc];
}

int goldmine_DP(int sr, int sc, vector<vector<int>> &mine, vector<vector<int>> &dp)
{
	// DP
	for (sc = mine[0].size() - 1; sc >= 0; sc--)
	{
		for (sr = 0; sr < mine.size(); sr++)
		{
			if (sc == mine[0].size() - 1)
			{
				dp[sr][sc] = mine[sr][sc];
				continue;
			}

			int dir[3][2] = {{-1, 1}, {0, 1}, {1, 1}};

			int maxGold = 0;
			for (int i = 0; i < 3; i++)
			{
				int x = dir[i][0] + sr;
				int y = dir[i][1] + sc;

				if (x >= 0 && y >= 0 && x < mine.size() && y < mine[0].size())
					maxGold = max(maxGold, dp[x][y]);
			}

			dp[sr][sc] = maxGold + mine[sr][sc];
		}
	}

	int res = 0;
	for (int r = 0; r < mine.size(); r++)
		res = max(res, dp[r][0]);

	return res;
}

void goldmine()
{
	vector<vector<int>> mine = {{1, 3, 1, 5},
								{2, 2, 4, 1},
								{5, 0, 2, 3},
								{0, 6, 1, 2}};

	vector<vector<int>> dp(mine.size(), vector<int>(mine[0].size(), 0));

	// for (int r = 0; r < mine.size(); r++)
	// 	goldmine_01(r, 0, mine, dp);

	// int res = 0;
	// for (int r = 0; r < mine.size(); r++)
	// 	res = max(res, dp[r][0]);

	// cout << res << endl;
	cout << goldmine_DP(0, 0, mine, dp) << endl;
	display2D(dp);
}

//=================================================================================================
// GFG link : https://www.geeksforgeeks.org/count-number-of-ways-to-partition-a-set-into-k-subsets/
int countWays_01(int n, int k, vector<vector<int>> &dp)
{
	if (n < k)
		return 0;
	if (n == k || k == 1)
		return dp[k][n] = 1;

	if (dp[k][n] != 0)
		return dp[k][n];

	int newGroup = countWays_01(n - 1, k - 1, dp);
	int existingGroup = countWays_01(n - 1, k, dp) * k;

	return dp[k][n] = newGroup + existingGroup;
}

int countWays_DP(int n, int k, vector<vector<int>> &dp)
{
	int N = n, K = k;
	for (k = 1; k <= K; k++)
	{
		for (n = k; n <= N; n++)
		{
			if (n == k || k == 1)
			{
				dp[k][n] = 1;
				continue;
			}

			int newGroup = dp[n - 1][k - 1];
			int existingGroup = dp[n - 1][k] * k;

			dp[k][n] = newGroup + existingGroup;
		}
	}
	return dp[K][N];
}

void countWays()
{
	int n = 3;
	int k = 1;

	vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

	cout << countWays_01(n, k, dp) << endl;
	// cout << countWays_DP(n, k, dp) << endl;

	display2D(dp);
}

void set2()
{
	// friendsPairProblem();
	// goldmine();
	countWays();
}

//===================================================================================
// Practice Link: https://practice.geeksforgeeks.org/problems/mobile-numeric-keypad/0

//Substring and Subsequence Series.==================================================

vector<vector<bool>> isPlaindromeSubstring(string &str)
{
	int n = str.length();
	vector<vector<bool>> dp(n, vector<bool>(n, 0));
	for (int gap = 0; gap < n; gap++)
	{
		for (int i = 0, j = gap; j < n; i++, j++)
		{
			if (gap == 0)
				dp[i][j] = true;
			else if (gap == 1 && str[i] == str[j])
				dp[i][j] = true;
			else
				dp[i][j] = str[i] == str[j] && dp[i + 1][j - 1];
		}
	}

	return dp;
}

//Leetcode 5. Longest Palindromic Substring==========================================
string longestPlaindromeSubstring(string str)
{
	int n = str.length();
	vector<vector<int>> dp(n, vector<int>(n, 0));

	int maxLen = 0;
	int si = 0, ei = 0;
	for (int gap = 0; gap < n; gap++)
	{
		for (int i = 0, j = gap; j < n; i++, j++)
		{
			if (gap == 0)
				dp[i][j] = 1;
			else if (gap == 1 && str[i] == str[j])
				dp[i][j] = 2;
			else if (str[i] == str[j] && dp[i + 1][j - 1] != 0)
				dp[i][j] = gap + 1;

			if (dp[i][j] > maxLen)
			{
				maxLen = dp[i][j];
				si = i;
				ei = j;
			}
		}
	}

	return str.substr(si, (ei - si + 1));
}

//===================================================================================
//Leetcode 647.Palindromic Substrings================================================
int countAllPlaindromicSubstring(string str)
{
	int n = str.length();
	vector<vector<int>> dp(n, vector<int>(n, 0));

	int count = 0;
	for (int gap = 0; gap < n; gap++)
	{
		for (int i = 0, j = gap; j < n; i++, j++)
		{
			if (gap == 0)
				dp[i][j] = 1;
			else if (gap == 1 && str[i] == str[j])
				dp[i][j] = 2;
			else if (str[i] == str[j] && dp[i + 1][j - 1] != 0)
				dp[i][j] = gap + 1;

			count += dp[i][j] != 0 ? 1 : 0;
		}
	}
	return count;
}

//======================================================================================
//Leetcode 516. Longest Palindromic Subsequence=========================================
int longestPlaindromeSubseq_Rec(string &str, int si, int ei, vector<vector<int>> &dp)
{
	if (si > ei)
		return 0;
	if (si == ei)
		return dp[si][ei] = 1;
	if (dp[si][ei] != 0)
		return dp[si][ei];

	int len = 0;
	if (str[si] == str[ei])
		len = longestPlaindromeSubseq_Rec(str, si + 1, ei - 1, dp) + 2;
	else
		len = max(longestPlaindromeSubseq_Rec(str, si + 1, ei, dp), longestPlaindromeSubseq_Rec(str, si, ei - 1, dp));

	return dp[si][ei] = len;
}

int longestPlaindromeSubseq_DP(string &str, int si, int ei, vector<vector<int>> &dp, vector<vector<bool>> &isPalindrome)
{
	for (int gap = 0; gap < str.size(); gap++)
	{
		for (si = 0, ei = gap; ei < str.size(); si++, ei++)
		{
			if (isPalindrome[si][ei])
			{
				dp[si][ei] = ei - si + 1;
				continue;
			}

			int len = 0;
			if (str[si] == str[ei])
				len = dp[si + 1][ei - 1];
			else
				len = max(dp[si + 1][ei], dp[si][ei - 1]);

			dp[si][ei] = len;
		}
	}
	return dp[0][str.size() - 1];
}

int longestPalindromeSubseq(string &s)
{
	int n = s.size();

	vector<vector<int>> dp(n, vector<int>(n, 0));
	vector<vector<bool>> isPalindrome = isPlaindromeSubstring(s);
	// return longestPlaindromeSubseq_Rec(s, 0, n - 1, dp);
	return longestPlaindromeSubseq_DP(s, 0, n - 1, dp, isPalindrome);
}

//======================================================================================
//Leetcode 115 : distinct-subsequences.=================================================
int distinct_subsequences(string S, string T, int n, int m, vector<vector<int>> &dp)
{
	if (m == 0)
		return dp[n][m] = 1;
	if (m > n)
		return dp[n][m] = 0;

	if (dp[n][m] != -1)
		return dp[n][m];

	if (S[n - 1] == T[m - 1])
		return dp[n][m] = distinct_subsequences(S, T, n - 1, m - 1, dp) + distinct_subsequences(S, T, n - 1, m, dp);

	return dp[n][m] = distinct_subsequences(S, T, n - 1, m, dp);
}

int distinct_subsequences_02(string S, string T, int i, int j, vector<vector<int>> &dp)
{
	if (T.length() - j == 0)
		return dp[i][j] = 1;
	if (S.length() - i > T.length() - j)
		return dp[i][j] = 0;

	if (dp[i][j] != -1)
		return dp[i][j];

	if (S[i] == T[j])
		return dp[i][j] = distinct_subsequences_02(S, T, i + 1, j + 1, dp) + distinct_subsequences_02(S, T, i + 1, j, dp);

	return dp[i][j] = distinct_subsequences_02(S, T, i + 1, j, dp);
}

int distinct_subsequences_DP(string S, string T, int n, int m, vector<vector<int>> &dp)
{
	int N = n, M = m;
	for (n = 0; n <= N; n++)
	{
		for (m = 0; m <= M; m++)
		{
			if (m == 0)
			{
				dp[n][m] = 1;
				continue;
			}
			if (m > n)
			{
				dp[n][m] = 0;
				continue;
			}
			if (S[n - 1] == T[m - 1])
				dp[n][m] = dp[n - 1][m - 1] + dp[n - 1][m];
			else
				dp[n][m] = dp[n - 1][m];
		}
	}

	return dp[N][M];
}

int numDistinct(string s, string t)
{
	int n = s.length();
	int m = t.length();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
	// cout << distinct_subsequences(s, t, n, m, dp) << endl;
	cout << distinct_subsequences_DP(s, t, n, m, dp) << endl;

	display2D(dp);
}

//===================================================================================
//Geeks: https://practice.geeksforgeeks.org/problems/count-palindromic-subsequences/1
int countPS(string &s, int i, int j, vector<vector<int>> &dp)
{
	if (i > j)
		return 0;
	if (i == j)
		return dp[i][j] = 1;
	if (dp[i][j] != 0)
		return dp[i][j];

	int middleString = countPS(s, i + 1, j - 1, dp);
	int excludingLast = countPS(s, i, j - 1, dp);
	int excludingFirst = countPS(s, i + 1, j, dp);

	int ans = excludingFirst + excludingLast;
	return dp[i][j] = (s[i] == s[j]) ? ans + 1 : ans - middleString;
}

int countPS_DP(string &s, int i, int j, vector<vector<int>> &dp)
{

	int n = s.length();
	for (int gap = 0; gap < n; gap++)
	{
		for (int i = 0, j = gap; j < n; j++, i++)
		{
			if (i == j)
			{
				dp[i][j] = 1;
				continue;
			}

			int middleString = dp[i + 1][j - 1];
			int excludingLast = dp[i][j - 1];
			int excludingFirst = dp[i + 1][j];

			int ans = excludingFirst + excludingLast;
			dp[i][j] = (s[i] == s[j]) ? ans + 1 : ans - middleString;
		}
	}
	return dp[0][n - 1];
}

//==================================================================================

void solve()
{
	// set1();
	// pathSet();
	set2();
}

int main(int argc, char **argv)
{
	solve();
	return 0;
}
