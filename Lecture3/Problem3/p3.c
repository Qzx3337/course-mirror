/*******************
* 
* p3 Çó¾ØÕó°°µã
* language: C.
* 
**********************/
#define _CRT_SECURE_NO_WARNINGS 1

#include "p3.h"

int main() {

	//freopen("p3.in", "r", stdin);
	//freopen("p3.out", "w", stdout);

	int i, j;
	int m, n;
	scanf("%d %d", &m, &n);

	int a[MAXM][MAXN];
	for (i = 0; i < m; i++) {			// read the matrix
		for (j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
		}
	}

	int minRow[MAXM], maxCol[MAXN];
	for (i = 0; i < m; i++) {			// initialize the minRow and maxCol
		minRow[i] = INF;
		maxCol[i] = -INF;
	}

	for (i = 0; i < m; i++) {			// find the minRow and maxCol
		for (j = 0; j < n; j++) {
			if (a[i][j] < minRow[i]) {
				minRow[i] = a[i][j];
			}
			if (a[i][j] > maxCol[j]) {
				maxCol[j] = a[i][j];
			}
		}
	}

	bool flag = false;
	for (i = 0; i < m; i++) {			// find the saddle point
		for (j = 0; j < n; j++) {
			if ( minRow[i]  == maxCol[j]) {
				flag = true;
				//printf("a[%d,%d]= %d\n", i, j, a[i][j]);
				printf("%4d", a[i][j]);
			}
		}
	}
	if (flag == false) {				// no saddle point
		printf("no");
	}

	return 0;
}

