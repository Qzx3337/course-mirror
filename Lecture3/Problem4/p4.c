/*******************
* 
* language: C.
* 
**********************/
#define _CRT_SECURE_NO_WARNINGS 1
#include "p4.h"
#define MAXN 12

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };

int main() {

	//freopen("p4.in", "r", stdin);
	//freopen("p4.out", "w", stdout);

	int a[MAXN][MAXN];
	int i, j, k;
	int n;
	scanf("%d", &n);
	//int** a = mnewarr(int*, n);
	//for (i = 0; i < n; ++i) {
	//	a[i] = mnewarr(int, n);
	//}

	int x=0, y=0, cnt=0;
	for (i = n - 1; i > 0; i -= 2) {
		for (j = 0; j < 4; j++) {
			for (k = 0; k < i; k++) {
				a[x][y] = ++cnt;
				x += dx[j];
				y += dy[j];
			}
		}
		x++, y++;
	}
	if (n & 1) a[x][y] = ++cnt;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

	return 0;
}

