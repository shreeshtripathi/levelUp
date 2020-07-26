#include <iostream>
#include <vector>
#include <list>
#include <climits>
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

void numDistinct(string s, string t)
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
// Leetcode 1143. Longest Common Subsequence========================================
int longestCommonSubsequence_Rec(string &text1, string &text2, int i, int j, vector<vector<int>> &dp)
{
	if (i == text1.size() || j == text2.size())
		return 0;

	if (dp[i][j] != 0)
		return dp[i][j];

	int count = 0;

	if (text1[i] == text2[j])
		count = longestCommonSubsequence_Rec(text1, text2, i + 1, j + 1, dp) + 1;
	else
		count = max(longestCommonSubsequence_Rec(text1, text2, i + 1, j, dp),
					longestCommonSubsequence_Rec(text1, text2, i, j + 1, dp));

	return dp[i][j] = count;
}

int longestCommonSubsequence_DP(string &text1, string &text2, int i, int j, vector<vector<int>> &dp)
{
	// if want to print string then make dp of string
	for (i = text1.size() - 1; i >= 0; i--)
	{
		for (j = text2.size() - 1; j >= 0; j--)
		{
			int count = 0;

			if (text1[i] == text2[j])
				count = dp[i + 1][j + 1] + 1;
			else
				count = max(dp[i + 1][j], dp[i][j + 1]);

			dp[i][j] = count;
		}
	}
	return dp[0][0];
}

int longestCommonSubsequence(string text1, string text2)
{
	vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
	// return longestCommonSubsequence_Rec(text1, text2, 0, 0, dp);
	return longestCommonSubsequence_DP(text1, text2, 0, 0, dp);
}

//==================================================================================
// Link : https://practice.geeksforgeeks.org/problems/longest-common-substring/0
// Longest Common Substring=========================================================
int max_ = 0;
int longestCommonSubstring_Rec(string &str1, string &str2, int i, int j, vector<vector<int>> &dp)
{
	if (i == str1.size() || j == str2.size())
		return dp[i][j] = 0;

	if (dp[i][j] != 0)
		return dp[i][j];

	int a = longestCommonSubstring_Rec(str1, str2, i, j + 1, dp);
	int b = longestCommonSubstring_Rec(str1, str2, i + 1, j, dp);

	if (str1[i] == str2[j])
	{
		int val = longestCommonSubstring_Rec(str1, str2, i + 1, j + 1, dp);
		max_ = max(max_, val);
		return dp[i][j] = a;
	}
	return 0;
}

int longestCommonSubstring_DP(string &str1, string &str2, int i, int j, vector<vector<int>> &dp)
{
	int ans = 0;
	for (i = str1.size() - 1; i >= 0; i--)
	{
		for (j = str2.size() - 1; j >= 0; j--)
		{
			int a = dp[i][j + 1];
			int b = dp[i + 1][j];

			if (str1[i] == str2[j])
			{
				int val = dp[i + 1][j + 1];
				ans = max(ans, val);
				dp[i][j] = ans;
			}
		}
	}
	return ans;
}

//====================================================================================
// Leetcode 1035. Uncrossed Lines=====================================================
int maxUncrossedLines(vector<int> &A, vector<int> &B)
{
	int n = A.size(), m = B.size();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = m - 1; j >= 0; j--)
		{
			if (A[i] == B[j])
				dp[i][j] = dp[i + 1][j + 1] + 1;
			else
				dp[i][j] = max(dp[i][j + 1], dp[i + 1][j]);
		}
	}
	return dp[0][0];
}

//====================================================================================
// Leetcode 1458. Max Dot Product of Two Subsequences=================================
int maxDotProduct(vector<int> &nums1, vector<int> &nums2)
{
	int n = nums1.size(), m = nums2.size();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	for (int i = n; i >= 0; i--)
	{
		for (int j = m; j >= 0; j--)
		{
			if (i == n || m == j)
			{
				dp[i][j] = -1e8;
				continue;
			}

			int val = nums1[i] * nums2[j];
			int a = dp[i + 1][j + 1] + val;
			int b = dp[i + 1][j];
			int c = dp[i][j + 1];

			dp[i][j] = max(max(a, b), max(c, val));
		}
	}

	return dp[0][0];
}

//===============================================================================
//Coin_Change/Target_Type.=======================================================
int coinChangePermutation(vector<int> &arr, int tar, vector<int> &dp)
{
	if (tar == 0)
		return dp[tar] = 1;
	if (dp[tar] != 0)
		return dp[tar];

	int count = 0;
	for (int ele : arr)
		if (tar - ele >= 0)
			count += coinChangePermutation(arr, tar - ele, dp);

	return dp[tar] = count;
}

int coinChangePermutation_DP(vector<int> &arr, int tar, vector<int> &dp)
{
	int Tar = tar;
	dp[0] = 1;
	for (int tar = 0; tar <= Tar; tar++)
	{
		int count = 0;
		for (int ele : arr)
			if (tar - ele >= 0)
				count += dp[tar - ele];

		dp[tar] = count;
	}
	return dp[Tar];
}

int coinChangeCombination_DP(vector<int> &arr, int tar, vector<int> &dp)
{
	int Tar = tar;
	dp[0] = 1;
	for (int ele : arr)
		for (int tar = ele; tar <= Tar; tar++)
			dp[tar] += dp[tar - ele];

	return dp[Tar];
}

void coinChange_1()
{
	vector<int> arr{2, 3, 5, 7};
	int tar = 10;
	vector<int> dp(tar + 1, 0);
	cout << coinChangePermutation(arr, tar, dp) << endl;

	display(dp);
}

//===========================================================================================
// Link : https://www.geeksforgeeks.org/find-number-of-solutions-of-a-linear-equation-of-n-variables/
//Solution of linear Equation================================================================
int LinearEquation_DP(vector<int> &coeff, int rhs)
{
	vector<int> dp(rhs + 1, 0);
	dp[0] = 1;
	for (int ele : coeff)
		for (int tar = ele; tar <= rhs; tar++)
			dp[tar] += dp[tar - ele];

	// return not correct
	return 0;
}

//===================================================================================
// Leetcode 322. Coin Change=========================================================

int coinChange_01(vector<int> &coins, int tar, vector<int> &dp)
{
	if (tar == 0)
		return 0;

	if (dp[tar] != 0)
		return dp[tar];

	int minCoins = 1e8;
	for (int coin : coins)
		if (tar - coin >= 0)
		{
			int rminCoins = coinChange_01(coins, tar - coin, dp);
			if (rminCoins != 1e8 && rminCoins + 1 < minCoins)
				minCoins = rminCoins + 1;
		}

	return dp[tar] = minCoins;
}

int coinChange(vector<int> &coins, int tar)
{
	vector<int> dp(tar + 1, 0);
	int res = coinChange_01(coins, tar, dp);
	return res != 1e8 ? res : -1;
}

// Target Sum
//===================================================================================
// Coin change subsequence DP========================================================
int targetSum(vector<int> &coins, int idx, int tar, vector<vector<int>> &dp)
{
	if (tar == 0 || idx == coins.size())
	{
		if (tar == 0)
			return dp[idx][tar] = 1;
		return dp[idx][tar] = 0;
	}

	if (dp[idx][tar] != 0)
		return dp[idx][tar];

	int count = 0;
	if (tar - coins[idx] >= 0)
		count += targetSum(coins, idx + 1, tar - coins[idx], dp);

	count += targetSum(coins, idx + 1, tar, dp);
	return dp[idx][tar] = count;
}

// travel from ehind in the vector of coins
int targetSum_02(vector<int> &coins, int idx, int tar, vector<vector<int>> &dp)
{
	if (tar == 0 || idx == 0)
	{
		if (tar == 0)
			return dp[idx][tar] = 1;
		return dp[idx][tar] = 0;
	}

	if (dp[idx][tar] != 0)
		return dp[idx][tar];

	int count = 0;
	if (tar - coins[idx - 1] >= 0)
		count += targetSum_02(coins, idx - 1, tar - coins[idx - 1], dp);

	count += targetSum_02(coins, idx - 1, tar, dp);
	return dp[idx][tar] = count;
}

// printing the path of coins - helper function after DP filled
int printPathOfTargetSum(vector<int> &coins, int idx, int tar, string ans, vector<vector<bool>> &dp)
{
	if (tar == 0 || idx == 0)
	{
		if (tar == 0)
		{
			cout << ans << endl;
			return 1;
		}
		return 0;
	}

	int count = 0;
	if (tar - coins[idx - 1] >= 0 && dp[idx - 1][tar - coins[idx - 1]])
		count += printPathOfTargetSum(coins, idx - 1, tar - coins[idx - 1], ans + to_string(coins[idx - 1]) + " ", dp);

	if (dp[idx - 1][tar])
		count += printPathOfTargetSum(coins, idx - 1, tar, ans, dp);

	return count;
}

void targetSum_02DP(vector<int> &coins, int tar)
{
	vector<vector<bool>> dp(coins.size() + 1, vector<bool>(tar + 1, false));
	int Tar = tar;
	for (int idx = 0; idx <= coins.size(); idx++)
	{
		for (tar = 0; tar <= Tar; tar++)
		{

			if (tar == 0 || idx == 0)
			{
				if (tar == 0)
					dp[idx][tar] = true;
				continue;
			}

			if (tar - coins[idx - 1] >= 0)
				dp[idx][tar] = dp[idx - 1][tar - coins[idx - 1]];

			dp[idx][tar] = dp[idx][tar] || dp[idx - 1][tar];
		}
	}

	for (vector<bool> &ar : dp)
	{
		for (bool ele : ar)
		{
			cout << ele << " ";
		}
		cout << endl;
	}

	cout << printPathOfTargetSum(coins, coins.size(), Tar, "", dp) << endl;
}

//===================================================================================
// Link: https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem/0
// 0-1 Knapsack======================================================================
int knapsack01(vector<int> &w, vector<int> &p, int weight, int n, vector<vector<int>> &dp)
{
	if (weight == 0 || n == 0)
	{
		return 0;
	}

	if (dp[n][weight] != 0)
		return dp[n][weight];

	int maxProfit = -1e8;
	if (weight - w[n - 1] >= 0)
		maxProfit = max(maxProfit, knapsack01(w, p, weight - w[n - 1], n - 1, dp) + p[n - 1]); // dp[n-1][weight - w[n - 1]]+p[n-1]
	maxProfit = max(maxProfit, knapsack01(w, p, weight, n - 1, dp));						   // dp[n-1][weight]

	return dp[n][weight] = maxProfit;
}

//===================================================================================
// Link: https://practice.geeksforgeeks.org/problems/knapsack-with-duplicate-items/0
// Unbounded Knapsack================================================================
int unbpounded(vector<int> &w, vector<int> &p, int weight)
{
	vector<int> dp(w.size() + 1, -1e8);
	dp[0] = 0;
	for (int i = 0; i < w.size(); i++)
		for (int tar = w[i]; tar <= weight; tar++)
			dp[tar] = max(dp[tar], dp[tar - w[i]] + p[i]);

	return dp[w.size()];
}

void knapsack()
{
	vector<int> p = {100, 280, 120};
	vector<int> w = {10, 40, 20};
	int weight = 60;
	int n = w.size();
	vector<vector<int>> dp(n + 1, vector<int>(weight + 1, 0));

	cout << knapsack01(w, p, weight, n, dp) << endl;
}

//===================================================================================
// Leetcode 416. Partition Equal Subset Sum==========================================
bool canPartition_(vector<int> &nums, int n, int sum, vector<vector<int>> &dp)
{
	if (sum == 0 || n == 0)
	{
		if (sum == 0)
			return dp[n][sum] = 1;
		return dp[n][sum] = 0;
	}

	if (dp[n][sum] != -1)
		return dp[n][sum];

	bool res = false;
	if (sum - nums[n - 1] >= 0)
		res = res || canPartition_(nums, n - 1, sum - nums[n - 1], dp) == 1;
	res = res || canPartition_(nums, n - 1, sum, dp) == 1;

	return dp[n][sum] = res ? 1 : 0;
}

bool canPartition(vector<int> &nums)
{
	int sum = 0;
	for (int ele : nums)
		sum += ele;
	if (sum % 2 != 0)
		return false;

	sum /= 2;
	vector<vector<int>> dp(nums.size() + 1, vector<int>(sum + 1, -1));

	return canPartition_(nums, nums.size(), sum, dp);
}

//===================================================================================
// Leetcode 494. Target Sum==========================================================

//===================================================================================
// Leetcode 72. Edit Distance=================================================================
int minDistance(string &word1, string &word2, int n, int m, vector<vector<int>> &dp)
{
	if (n == 0 || m == 0)
	{
		return dp[n][m] = (n == 0 ? m : n);
	}

	if (dp[n][m] != 0)
		return dp[n][m];
	if (word1[n - 1] == word2[m - 1])
		return dp[n][m] = minDistance(word1, word2, n - 1, m - 1, dp);

	int insert_ = minDistance(word1, word2, n, m - 1, dp);
	int replace_ = minDistance(word1, word2, n - 1, m - 1, dp);
	int delete_ = minDistance(word1, word2, n - 1, m, dp);

	return dp[n][m] = min(min(insert_, replace_), delete_) + 1;
}

int minDistance(string str1, string str2)
{
	vector<vector<int>> dp(str1.size() + 1, vector<int>(str2.size() + 1));
	int n = str1.size();
	int m = str2.size();

	return minDistance(str1, str2, n, m, dp);
}

//===================================================================================
// LIS type question - left to right maximum
// Leetcode 300. Longest Increasing Subsequence======================================
int lisMax = 1;
int LIS_res(vector<int> &arr, vector<int> &dp, int n)
{
	if (n == 0)
		return dp[n] = 1;

	if (dp[n] != 0)
		return dp[n];

	int count = 0;
	for (int indx = n - 1; indx >= 0; indx--)
		if (arr[indx] < arr[n])
			count = max(count, LIS_res(arr, dp, indx));

	lisMax = max(lisMax, count + 1);
	return dp[n] = count + 1;
}

int LIS_leftTotRight_DP(vector<int> &arr, vector<int> &dp)
{
	int omax = 1;
	for (int n = 0; n < arr.size(); n++)
	{
		if (n == 0)
		{
			dp[n] = 1;
			continue;
		}

		int count = 0;
		for (int indx = n - 1; indx >= 0; indx--)
			if (arr[indx] < arr[n])
				count = max(count, dp[indx]);

		omax = max(omax, count + 1);
		dp[n] = count + 1;
	}
	return omax;
}

int lengthOfLIS(vector<int> &arr)
{
	if (arr.size() == 0)
		return 0;

	vector<int> dp(arr.size(), 0);
	for (int i = arr.size() - 1; i >= 0; i--)
		LIS_res(arr, dp, i);
	return lisMax;
}

//===================================================================================
// its is similar to LDS
int LIS_rightToLeft(vector<int> &arr, vector<int> &dp)
{
	int omax = 1;
	for (int n = arr.size() - 1; n >= 0; n--)
	{
		if (n == arr.size() - 1)
		{
			dp[n] = 1;
			continue;
		}

		int count = 0;
		for (int indx = n + 1; indx < arr.size(); indx++)
			if (arr[indx] < arr[n])
				count = max(count, dp[indx]);

		omax = max(omax, count + 1);
		dp[n] = count + 1;
	}
	display(dp);
	return omax;
}

//===================================================================================
// bitonic
int lbs(vector<int> &arr)
{
	vector<int> lisDP(arr.size(), 0);
	vector<int> ldsDP(arr.size(), 0);
	LIS_leftTotRight_DP(arr, lisDP);
	LIS_rightToLeft(arr, ldsDP);

	int ans = 0;
	for (int i = 0; i < arr.size(); i++)
		ans = max(ans, lisDP[i] + ldsDP[i] - 1);

	return ans;
}

//===================================================================================
// inverse bitonic

//===================================================================================
// maximum increasingg sum subsequence
// Link: https://practice.geeksforgeeks.org/problems/maximum-sum-increasing-subsequence/0
int maximumSumIncreasingSubseq(vector<int> &arr)
{
	// for subseq we not use Rec because it requires 2D matrix,
	// with DP we can do it in O(n) space.
	int n = arr.size();
	vector<int> dp(n, 0);

	int omax = 0; // overall max in dp

	for (int i = 0; i < n; i++)
	{
		int count = 0;
		for (int j = i - 1; j >= 0; j--)
		{
			if (arr[j] < arr[i])
				count = max(count, dp[j]);
		}
		omax = max(omax, count + arr[i]);
		dp[i] = count + arr[i];
	}
	return omax;
}

//===================================================================================
// maximum bitonic sum subsequence
// Link: https://practice.geeksforgeeks.org/problems/maximum-sum-bitonic-subsequence/0

// helper function 1
void lis_sum_hlpr(vector<int> &arr, vector<int> &dp)
{
	for (int i = 0; i < arr.size(); i++)
	{
		int count = 0;
		for (int j = i - 1; j >= 0; j--)
			if (arr[j] < arr[i])
				count = max(count, dp[j]);

		dp[i] = count + arr[i];
	}
	display(dp);
}

// helper function 2
void lds_sum_hlpr(vector<int> &arr, vector<int> &dp)
{
	for (int i = arr.size() - 1; i >= 0; i--)
	{
		int count = 0;
		for (int j = i + 1; j < arr.size(); j++)
			if (arr[j] < arr[i])
				count = max(count, dp[j]);
		dp[i] = count + arr[i];
	}
	display(dp);
}

int maxSumBitonicSubseq(vector<int> &arr)
{
	int n = arr.size();
	// find maximum sum increasing subseq
	vector<int> lis_sum(n, 0);
	lis_sum_hlpr(arr, lis_sum);

	// find maximum sum Decreasing subseq(if consider from left to right)
	// OR, maximum sum increasing subseq(if consider from right to left)
	vector<int> lds_sum(n, 0);
	lds_sum_hlpr(arr, lds_sum);

	// find max bitonic sum subseq
	int omax = 0;
	for (int i = 0; i < n; i++)
		if (omax < lis_sum[i] + lds_sum[i] - arr[i])
			omax = lis_sum[i] + lds_sum[i] - arr[i];

	return omax;
}

//===================================================================================
// Leetcode 673. Number of Longest Increasing Subsequence

//===================================================================================
// Leetcode 354. Russian Doll Envelopes

//===================================================================================
// Leetcode 1027

//===================================================================================
// Leetcode 1235

//===================================================================================

void LIS_type()
{
	vector<int> arr{47, 58, 116, 114};
	// vector<int> dp(arr.size(), 0);
	// cout << LIS_rightToLeft(arr, dp) << endl;

	cout << maxSumBitonicSubseq(arr) << endl;
}

//===================================================================================
// Cut Type
//===================================================================================
// Matrix chain multiplication
// Link: https://practice.geeksforgeeks.org/problems/matrix-chain-multiplication/0
int mcm_res(vector<int> &arr, int si, int ei, vector<vector<int>> &dp)
{
	if (si + 1 == ei)
		return dp[si][ei] = 0;

	if (dp[si][ei] != -1)
		return dp[si][ei];

	int ans = 1e8;
	for (int cut = si + 1; cut < ei; cut++)
	{
		int leftCost = mcm_res(arr, si, cut, dp);
		int rightCost = mcm_res(arr, cut, ei, dp);

		int myCost = leftCost + arr[si] * arr[cut] * arr[ei] + rightCost;
		if (myCost < ans)
			ans = myCost;
	}
	return dp[si][ei] = ans;
}

int mcm_DP(vector<int> &arr, int si, int ei, vector<vector<int>> &dp)
{
	for (int gap = 1; gap < arr.size(); gap++)
	{
		for (si = 0, ei = gap; ei < arr.size(); si++, ei++)
		{
			if (si + 1 == ei)
			{
				dp[si][ei] = 0;
				continue;
			}

			int ans = 1e8; // during submission always use INT_MAX;
			for (int cut = si + 1; cut < ei; cut++)
			{
				int leftCost = dp[si][cut];	 // mcm_res(arr, si, cut, dp);
				int rightCost = dp[cut][ei]; // mcm_res(arr, cut, ei, dp);

				int myCost = leftCost + arr[si] * arr[cut] * arr[ei] + rightCost;
				if (myCost < ans)
					ans = myCost;
			}
			dp[si][ei] = ans;
		}
	}
	return dp[0][dp.size() - 1];
}

// Brackets in matric chain multiplication=====================================
// Link: https://practice.geeksforgeeks.org/problems/brackets-in-matrix-chain-multiplication/0/
void bracket_mcm_DP(vector<int> &arr)
{
	int n = arr.size(), si = 0, ei = 0;
	vector<vector<int>> dp(n, vector<int>(n, -1));
	vector<vector<string>> dp_str(n, vector<string>(n, ""));

	for (int gap = 1; gap < arr.size(); gap++)
	{
		for (si = 0, ei = gap; ei < arr.size(); si++, ei++)
		{
			if (si + 1 == ei)
			{
				dp[si][ei] = 0;
				dp_str[si][ei] = (char)('A' + si);
				continue;
			}

			int ans = INT_MAX; // during submission always use INT_MAX;
			string str = "";
			for (int cut = si + 1; cut < ei; cut++)
			{
				int leftCost = dp[si][cut];	 // mcm_res(arr, si, cut, dp);
				int rightCost = dp[cut][ei]; // mcm_res(arr, cut, ei, dp);

				int myCost = leftCost + arr[si] * arr[cut] * arr[ei] + rightCost;
				if (myCost < ans)
				{
					ans = myCost;
					str = "(" + dp_str[si][cut] + dp_str[cut][ei] + ")";
				}
			}
			dp[si][ei] = ans;
			dp_str[si][ei] = str;
		}
	}
	cout << dp_str[0][dp.size() - 1];
}

void mcm()
{
	vector<int> arr{40, 20, 30, 10, 30};
	int n = arr.size();
	vector<vector<int>> dp(n, vector<int>(n, -1));
	// cout << mcm_res(arr, 0, n - 1, dp) << endl;
	// cout << mcm_DP(arr, 0, n - 1, dp) << endl;
	// bracket_mcm_DP(arr);

	// display2D(dp);
}

//===================================================================================
// Optimal BST
// Note : if array of tree is unsorted then sort tree and freq simultaneously
int costOfSearching(vector<int> &arr, int si, int ei)
{
	int sum = 0;
	for (int i = si; i <= ei; i++)
		sum += arr[i];
	return sum;
}

int optimalBST_rec(vector<int> &freq, int si, int ei, vector<vector<int>> &dp)
{
	if (dp[si][ei] != 0)
		return dp[si][ei];

	int ans = INT_MAX;
	for (int cut = si; cut <= ei; cut++)
	{
		int leftTreeCost = cut == si ? 0 : optimalBST_rec(freq, si, cut - 1, dp);
		int rightTreeCost = cut == ei ? 0 : optimalBST_rec(freq, cut + 1, ei, dp);

		int myCost = leftTreeCost + costOfSearching(freq, si, ei) + rightTreeCost;

		if (ans > myCost)
			ans = myCost;
	}

	return dp[si][ei] = ans;
}

int optimalBST_DP(vector<int> &freq, int si, int ei, vector<vector<int>> &dp)
{
	// make an Optimal previous sum
	vector<int> psum(freq.size() + 1, 0);
	for (int i = 1; i < psum.size(); i++)
		psum[i] = psum[i - 1] + freq[i - 1];

	// DP
	for (int gap = 1; gap < freq.size(); gap++)
	{
		for (si = 0, ei = gap; ei < freq.size(); si++, ei++)
		{
			int ans = INT_MAX;
			for (int cut = si; cut <= ei; cut++)
			{
				int leftTreeCost = cut == si ? 0 : dp[si][cut - 1];	 // optimalBST_rec(freq, si, cut - 1, dp);
				int rightTreeCost = cut == ei ? 0 : dp[cut + 1][ei]; // optimalBST_rec(freq, cut + 1, ei, dp);

				int myCost = leftTreeCost + psum[ei + 1] - psum[si] + rightTreeCost;

				if (ans > myCost)
					ans = myCost;
			}
			dp[si][ei] = ans;
		}
	}
	return dp[0][freq.size() - 1];
}

void optimalBST()
{
	vector<int> keys{10, 12, 20};
	vector<int> freq{34, 8, 50};

	int n = freq.size();
	vector<vector<int>> dp(n, vector<int>(n, 0));

	// cout << optimalBST_rec(freq, 0, n - 1, dp) << endl;
	cout << optimalBST_DP(freq, 0, n - 1, dp) << endl;

	display2D(dp);
}

//===================================================================================
// Leetcode 312. Burst Balloons
int maxCoins(vector<int> &nums)
{
	return 0;
}

//===================================================================================
// Leetcode 91. Decode Ways
int numDecodings_rec(string &s, int vidx, vector<int> &dp)
{
	if (vidx == s.size())
		return dp[vidx] = 1;

	if (dp[vidx] != -1)
		return dp[vidx];

	char ch = s[vidx];
	if (ch == '0')
		return dp[vidx] = 0;

	int count = 0;
	count += numDecodings_rec(s, vidx + 1, dp);
	if (vidx < s.size() - 1)
	{
		int num = (ch - '0') * 10 + (s[vidx + 1] - '0');
		if (num <= 26)
			count += numDecodings_rec(s, vidx + 2, dp);
	}
	return dp[vidx] = count;
}

int numDecodings_btr(string &s)
{
	int a = 0;
	int b = 1;

	int ans = 0;

	for (int i = s.size() - 1; i >= 0; i--)
	{
		char ch = s[i];
		ans = 0;
		if (ch != '0')
		{
			ans = b;
			if (i < s.size() - 1)
			{
				int num = (ch - '0') * 10 + (s[i + 1] - '0');
				if (num <= 25)
					ans += a;
			}
		}

		a = b;
		b = ans;
	}

	return ans;
}

int numDecodings(string s)
{
	vector<int> dp(s.size() + 1, -1);
	int ans = numDecodings_rec(s, 0, dp);

	cout << ans << endl;
	display(dp);

	return ans;
}

//===================================================================================
// Leetcode 639. Decode Ways II
int AiBjCk(string str)
{
	int acount = 0;
	int bcount = 0;
	int ccount = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == 'a')
			acount = acount + (1 + acount);
		else if (str[i] == 'b')
			bcount = bcount + (acount + bcount);
		else
			ccount = ccount + (bcount + ccount);
	}

	return ccount;
}

// https://www.hackerearth.com/practice/math/number-theory/basic-number-theory-1/tutorial/

// (a+b)%c = (a%c + b%c)%c
// (a-b)%c = (a%c - b%c + c)%c
// (a*b)%c = (a%c * b%c )%c
int distinctSubseqII(string str)
{
	int mod = 1e9 + 7;
	str = '$' + str;
	int n = str.length();
	vector<long> dp(n, 0);
	vector<int> lastOccu(26, -1);

	for (int i = 0; i < n; i++)
	{
		if (i == 0) // empty String.
		{
			dp[i] = 1;
			continue;
		}

		char ch = str[i];
		dp[i] = (dp[i - 1] % mod * 2) % mod;
		if (lastOccu[ch - 'a'] != -1)
			dp[i] = dp[i] % mod - dp[lastOccu[ch - 'a'] - 1] % mod + mod;

		lastOccu[ch - 'a'] = i;
	}
	return dp[n - 1] % mod - 1;
}

long mod = 1e9 + 7;
long numDecodingsII_recu(string &str, int idx, vector<long> &dp)
{
	if (idx == str.length())
		return 1;
	if (dp[idx] != 0)
		return dp[idx];

	int count = 0;
	if (str[idx] == '*')
	{
		count = (count % mod + 9 * numDecodingsII_recu(str, idx + 1, dp) % mod) % mod;
		if (idx < str.length() - 1 && str[idx + 1] >= '0' && str[idx + 1] <= '6')
			count = (count % mod + 2 * numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
		else if (idx < str.length() - 1 && str[idx + 1] >= '7')
			count = (count % mod + numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
		else if (idx < str.length() - 1 && str[idx + 1] == '*')
			count = (count % mod + 15 * numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
	}
	else if (str[idx] > '0')
	{

		count = (count % mod + numDecodingsII_recu(str, idx + 1, dp) % mod) % mod;
		if (idx < str.length() - 1)
		{
			if (str[idx + 1] != '*')
			{
				int num = (str[idx] - '0') * 10 + (str[idx + 1] - '0');
				if (num <= 26)
					count = (count % mod + numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
			}
			else if (str[idx] == '1')
				count = (count % mod + 9 * numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
			else if (str[idx] == '2')
				count = (count % mod + 6 * numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
		}
	}
	return dp[idx] = count;
}

long numDecodingsII_DP(string &str, int idx, vector<long> &dp)
{
	for (idx = str.length(); idx >= 0; idx--)
	{
		if (idx == str.length())
		{
			dp[idx] = 1;
			continue;
		}

		int count = 0;
		if (str[idx] == '*')
		{
			count = (count % mod + 9 * dp[idx + 1] % mod) % mod;
			if (idx < str.length() - 1 && str[idx + 1] >= '0' && str[idx + 1] <= '6')
				count = (count % mod + 2 * dp[idx + 2] % mod) % mod;
			else if (idx < str.length() - 1 && str[idx + 1] >= '7')
				count = (count % mod + dp[idx + 2] % mod) % mod;
			else if (idx < str.length() - 1 && str[idx + 1] == '*')
				count = (count % mod + 15 * dp[idx + 2] % mod) % mod;
		}
		else if (str[idx] > '0')
		{

			count = (count % mod + dp[idx + 1] % mod) % mod;
			if (idx < str.length() - 1)
			{
				if (str[idx + 1] != '*')
				{
					int num = (str[idx] - '0') * 10 + (str[idx + 1] - '0');
					if (num <= 26)
						count = (count % mod + dp[idx + 2] % mod) % mod;
				}
				else if (str[idx] == '1')
					count = (count % mod + 9 * dp[idx + 2] % mod) % mod;
				else if (str[idx] == '2')
					count = (count % mod + 6 * dp[idx + 2]) % mod;
			}
		}
		dp[idx] = count;
	}
	return dp[0];
}

long numDecodingsII_Fast(string &str, int idx, vector<long> &dp)
{
	long a = 0;
	long b = 1;
	long count = 0;
	for (idx = str.length() - 1; idx >= 0; idx--)
	{
		count = 0;
		if (str[idx] == '*')
		{
			count = (count % mod + 9 * b % mod) % mod;
			if (idx < str.length() - 1 && str[idx + 1] >= '0' && str[idx + 1] <= '6')
				count = (count % mod + 2 * a % mod) % mod;
			else if (idx < str.length() - 1 && str[idx + 1] >= '7')
				count = (count % mod + a % mod) % mod;
			else if (idx < str.length() - 1 && str[idx + 1] == '*')
				count = (count % mod + 15 * a % mod) % mod;
		}
		else if (str[idx] > '0')
		{

			count = (count % mod + b % mod) % mod;
			if (idx < str.length() - 1)
			{
				if (str[idx + 1] != '*')
				{
					int num = (str[idx] - '0') * 10 + (str[idx + 1] - '0');
					if (num <= 26)
						count = (count % mod + a % mod) % mod;
				}
				else if (str[idx] == '1')
					count = (count % mod + 9 * a % mod) % mod;
				else if (str[idx] == '2')
					count = (count % mod + 6 * a) % mod;
			}
		}

		a = b;
		b = count;
	}
	return count;
}

// DP toDo :
// 1. 132
// 2. 044
// 3. https://www.geeksforgeeks.org/boolean-parenthesization-problem-dp-37/
// 4. 096
// 5. 095

void questionSet()
{
	string s = "1423101112";
	numDecodings(s);
}

void cutType()
{
	// mcm();
	// optimalBST();
	questionSet();
}

void solve()
{
	// set1();
	// pathSet();
	// set2();
	// LIS_type();
	cutType();
}

int main(int argc, char **argv)
{
	solve();
	return 0;
}