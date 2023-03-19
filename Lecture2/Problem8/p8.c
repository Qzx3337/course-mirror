/**********************

【问题描述】
以一个m*n的长方阵表示迷宫，0和1分别表示迷宫中的通路和障碍。设计一个程序，对任意设定的迷宫，求出一条从入口到出口的通路，或得出没有通路的结论。

【输入形式】
输入一个m*n的长方阵，0和1分别表示迷宫中的通路和障碍。

【输出形式】
一条从入口到出口的通路，并用图形表示(输出矩阵，属于通路中的点用字符*替换)。

【样例输入】
左上角（1，1）为入口，右下角（9，8）为出口。

 0	 0	 1	 0	 0	 0	 1	 0
 0	 0	 1	 0	 0	 0	 1	 0
 0	 0	 0	 0	1	1	 0	 1
 0	 1	 1	 1	 0	 0	 1	 0
 0	 0	 0	 1	 0	 0	 0	 0
 0	 1	 0	 0	 0	 1	 0	 1
 0	 1	 1	 1	 1	 0	 0	 1
 1	 1	 0	 0	 0	 1	 0	 1
 1	 1	 0	 0	 0	 0	 0	 0


【样例输出】
(1,1,1),(1,2,2),(2,2,2),(3,2,3),(3,1,2),(4,1,2),(5,1,1),(5,2,1),(5,3,2),(6,3,1),(6,4,1),(6,5,4),(5,5,1),(5,6,1),(5,7,2),(6,7,2),(7,7,2),(8,7,2),(9,7,1)

【样例说明】
设一个9x8的长方阵，每个元素的值为0或1，其中0和1分别表示迷宫中的通路和障碍。通路以三元组（i,j,d) 的形式输出，其中：（i,j) 指示迷宫中的一个坐标，d 表示走到下一坐标的方向。东、南、西、北依次为1，2，3，4。东南、西南、东北、西北依次为5，6，7，8。


language: C.

**************************/


#define _CRT_SECURE_NO_WARNINGS 1

#include "p8.h"


int mmap[MAXM][MAXN];
int pre[MAXM][MAXN];

// 建造地图
void InitMap(int m, int n) {
	int i, j;
	for (i = 0; i <= m + 1; ++i) {
		mmap[i][0] = mmap[i][n + 1] = 1;
	}
	for (j = 0; j <= n + 1; ++j) {
		mmap[0][j] = mmap[m + 1][j] = 1;
	}

	for (i = 1; i <= m; ++i) {
		for (j = 1; j <= n; ++j) {
			scanf("%d", &mmap[i][j]);
		}
	}

}

// 打印地图
void PrintMap(int m, int n) {
	printf("\nm=%d; n=%d\n", m, n);

	int i, j;
	for (i = 0; i <= m+1; ++i) {
		for (j = 0; j <= n+1; ++j) {
			printf("%d ", mmap[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


int IsAvailable(Point pnt) {
	if (mmap[pnt.x][pnt.y]) return false;
	if (pre[pnt.x][pnt.y]) return false;
	return true;
}


int BFSpath(Point src, Point dst) {
	
	Point const deltaP[4] = {
		(Point) {0,1},	// 东
		(Point) {1,0},	// 南
		(Point) {0,-1},	// 西
		(Point) {-1,0}	// 北
	};

	//int i;
	//for (i = 0; i < 4; ++i) {
	//	printf("x=%d, y=%d\n", deltaP[i].x, deltaP[i].y);
	//}

	int i;
	Queue que;
	initQue(&que);
	pushQue(que, src);
	for (; !isEmptyQue(que);) {
		Point current = getBack(que);
		for (i = 0; i < 4; i++) {
			Point next = addPoint(current, deltaP[i]);
			if (IsAvailable(next)) {
				pushQue(que, next);
				pre[next.x][next.y] = i + 1;
				if (cmpPoint(next, dst)) {
					return true;
				}
			}
		}
		popQue(que);
	}
	return false;

}


void PrintPath(src, dst) {
	printf("aa\n");
}


int main() {
	
	freopen("p8.in", "r", stdin);

	int m, n;
	scanf("%d%d", &m, &n);
	InitMap(m, n);
	PrintMap(m, n);

	Point src, dst;
	scanf("%d%d%d%d", &src.x, &src.y, &dst.x, &dst.y);

	// BFS
	if (BFSpath(src, dst)) {		// 找到了路径
		PrintPath(src, dst);
	}
	else {							// 未找到路径
		printf("No Path!\n");
	}

	return 0;
}

