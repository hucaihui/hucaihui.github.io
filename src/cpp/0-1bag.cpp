#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int** bag(const int W, const int num, int w[], int v[]) {
	int **dp = new int*[num];   
	for (int i = 0; i < num ; ++i) {
		dp[i] = new int[W + 1];
	}
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j < W + 1; ++j) {
			dp[i][j] = 0;    //必须先分配初值
		}
	}
	
	for (int i = 1; i < num; ++i) {
		for (int j = 1; j < W + 1; ++j) {
			if (w[i] > j)
				dp[i][j] = dp[i - 1][j];
			else
				dp[i][j] = max( dp[i - 1][j],dp[i - 1][j - w[i]] + v[i] );			
		}
	}

	return dp;
};

void findWhat(int** &dp, int w[], int v[], int i, int j) {
	if (i > 0) {
		if (dp[i][j] == dp[i - 1][j]) {
			findWhat(dp, w, v, i - 1, j);
		}
		else if(j>=w[i]&&dp[i][j]==dp[i-1][j-w[i]]+v[i]){
			cout << i << " ";
			findWhat(dp, w, v, i - 1, j - w[i]);
		}

	}
}
int main03() {
	const int W = 8;
	int w[5] = {0,2,3,4,5 };
	int v[5] = { 0,3,5,4,6 };
	int num = 5;
	int **dp = bag(W, num, w, v);

	for (int i = 0; i < num; ++i) {
		for (int j = 0; j < W + 1; ++j) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}

	findWhat(dp, w, v, num-1, W);



	system("pause");
	return 0;
}