/********************



language: C++

***********************/

#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <queue>

#define MAX_M 20
#define MAX_TOTAL 200
#define INF 0x7FFFFFFF

using namespace std;


double solveAve(int m, int total) {
	int tIn, tNeed;						// 到来时间 需要时间
	int tNow[MAX_M] = { 0 };			// 窗口在排时间
	queue<int> tWait;					// 需要等待的时间

	for (int i = 0; i < total; i++) {	// 共 total个人

		cin >> tIn >> tNeed;			// 第 i个人来了

		// 输出过程
		//for (int j = 0; j < m; j++) {
		//	printf("win[%d]: %d\n", j, tNow[j]);
		//}
		//printf("\n");
		//printf("time= %d, need= %d\n", tIn, tNeed);

		int minWindow = 0;				// 最空闲的窗口
		for (int j = 0; j < m; j++) {	// 挨着找窗口
			if (tNow[j] < tNow[minWindow]) minWindow = j;
		}
		if (tNow[minWindow] <= tIn) {	// 不用等待
			tNow[minWindow] = tIn + tNeed;
		}
		else {							// 需要等待
			tWait.push(tNow[minWindow] - tIn);
			tNow[minWindow] += tNeed;
		}
	}
	double ans = 0;
	while (!tWait.empty()) {
		ans += tWait.front();
		tWait.pop();
	}
	ans /= total;
	//printf("ans=%lf\n", ans);
	return ans;
}

int main() {

	//freopen("p6.in", "r", stdin);

	int m;			// 窗口数
	int total;		// 客户数

	double ans;	
	for (int i = 0; i < 3; i++) {
		cin >> m >> total;
		ans = solveAve(m, total);
		printf("%.2lf\n", ans);
	}

	return 0;
}


