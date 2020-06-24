#include <iostream>
#include <vector>

using namespace std;

//===============================PRINT===================================
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
//=======================================================================

void pathSet()
{

	display(dp);
	display2D(dp);
}

void set1()
{
	pathSet();
}

void solve()
{
	set1();
}

int main(int argc, char **argv)
{
	solve();
	return 0;
}
