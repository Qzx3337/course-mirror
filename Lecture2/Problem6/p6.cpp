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
	int tIn, tNeed;						// ����ʱ�� ��Ҫʱ��
	int tNow[MAX_M] = { 0 };			// ��������ʱ��
	queue<int> tWait;					// ��Ҫ�ȴ���ʱ��

	for (int i = 0; i < total; i++) {	// �� total����

		cin >> tIn >> tNeed;			// �� i��������

		// �������
		//for (int j = 0; j < m; j++) {
		//	printf("win[%d]: %d\n", j, tNow[j]);
		//}
		//printf("\n");
		//printf("time= %d, need= %d\n", tIn, tNeed);

		int minWindow = 0;				// ����еĴ���
		for (int j = 0; j < m; j++) {	// �����Ҵ���
			if (tNow[j] < tNow[minWindow]) minWindow = j;
		}
		if (tNow[minWindow] <= tIn) {	// ���õȴ�
			tNow[minWindow] = tIn + tNeed;
		}
		else {							// ��Ҫ�ȴ�
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

	int m;			// ������
	int total;		// �ͻ���

	double ans;	
	for (int i = 0; i < 3; i++) {
		cin >> m >> total;
		ans = solveAve(m, total);
		printf("%.2lf\n", ans);
	}

	return 0;
}


