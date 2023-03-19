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
Point deltaP[9];

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
	//printf("\nm=%d; n=%d\n", m, n);

	printf("\n");
	int i, j;
	//for (i = 0; i <= m + 1; ++i) {
	//	for (j = 0; j <= n + 1; ++j) {
	for (i = 1; i <= m; ++i) {
		for (j = 1; j <= n; ++j) {
			if (mmap[i][j]) {
				printf("1 ");
			}
			else if (pre[i][j] == -1) {
				printf("* ");
			}
			else {
				printf("0 ");
			}
		}
		printf("\n");
	}
	printf("\n");
}


void InitDelta() {
	deltaP[0] = (Point){ 0,0 };		// 原地不动
	deltaP[1] = (Point){ 0,1 };		// 东
	deltaP[2] = (Point){ 1,0 };		// 南
	deltaP[3] = (Point){ 0,-1 };	// 西
	deltaP[4] = (Point){ -1,0 };	// 北
	deltaP[5] = (Point){ 1,1 };		// 东南
	deltaP[6] = (Point){ 1,-1 };	// 西南
	deltaP[7] = (Point){ -1,1 };	// 东北
	deltaP[8] = (Point){ -1,-1 };	// 西北
}

// 该点能走且没有走过
int IsAvailable(Point pnt) {
	if (mmap[pnt.x][pnt.y]) return false;
	if (pre[pnt.x][pnt.y]) return false;
	return true;
}

// 搜！
int BFSpath(Point src, Point dst) {

	if (cmpPnt(src, dst)) return true;		// 起点重点重合
	
	int i;

	//for (i = 1; i <= 4; ++i) {
	//	printf("x=%d, y=%d\n", deltaP[i].x, deltaP[i].y);
	//}
	
	Queue que;
	initQue(&que);

	pre[src.x][src.y] = -1;			// 制造根节点
	pushQue(que, src);

	for (; !isEmptyQue(que);) {		// 向下搜索
		Point current = getBack(que);
		//for (i = 1; i <= 8; i++) {		// 允许斜着走
		for (i = 1; i <= 4; i++) {			// 不允许斜着走
			Point next = addPnt(current, deltaP[i]);
			if (IsAvailable(next)) {
				pushQue(que, next);
				pre[next.x][next.y] = i;
				if (cmpPnt(next, dst)) {
					return true;
				}
			}
		}
		popQue(que);
	}
	return false;

}

// 打印路径
void PrintPath(Point src, Point dst) {

	Stack ans;
	initSta(&ans);
	Point it = dst;
	for (; pre[it.x][it.y] != -1;) {
		pushSta(ans, it);
		it = subtractPnt(it, deltaP[pre[it.x][it.y]]);
	}
	pushSta(ans, it);

	Point nxt;
	for (; getStaSize(ans) > 1;) {
		it = getTop(ans);
		popSta(ans);
		nxt = getTop(ans);
		printf("(%d,%d,%d),", it.x, it.y, pre[nxt.x][nxt.y]);
		pre[nxt.x][nxt.y] = -1;
	}
	printf("\n");

}


int main() {
	
	freopen("p8.in", "r", stdin);

	int m, n;
	scanf("%d%d", &m, &n);
	InitMap(m, n);
	//PrintMap(m, n);

	Point src, dst;
	scanf("%d%d%d%d", &src.x, &src.y, &dst.x, &dst.y);

	InitDelta();

	// BFS
	if (BFSpath(src, dst)) {		// 找到了路径
		PrintPath(src, dst);
		PrintMap(m, n);
	}
	else {							// 未找到路径
		printf("No Path!\n");
	}

	return 0;
}

