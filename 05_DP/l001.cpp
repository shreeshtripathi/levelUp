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
	// return climbStairs_btr(n);
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


void solve()
{
	// set1();
	pathSet();
}

int main(int argc, char **argv)
{
	solve();
	return 0;
}
