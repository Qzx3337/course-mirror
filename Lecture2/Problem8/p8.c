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

// 全局变量

int mmap[MAXM][MAXN];	// 地图
int pre[MAXM][MAXN];	// 用于寻找前驱结点，一个数字代表动作
Point deltaP[9];		// 所有的动作对应的位移

// 方法列表

void InitMap(int m, int n);
void PrintMap(int m, int n);
void InitDelta();
int IsAvailable(Point pnt);
int BFSpath(Point src, Point dst);
void PrintPath(Point src, Point dst);


// 主函数
int main() {

	freopen("p8.in", "r", stdin);		// 文件读入

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


/********* 方法实现 *****************/


// 建造地图
void InitMap(int m, int n) {
	int i, j;
	for (i = 0; i <= m + 1; ++i) {			// 外围边缘围墙
		mmap[i][0] = mmap[i][n + 1] = 1;
	}
	for (j = 0; j <= n + 1; ++j) {
		mmap[0][j] = mmap[m + 1][j] = 1;
	}

	for (i = 1; i <= m; ++i) {				// 图内围墙读入进来
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
		for (j = 1; j <= n; ++j) {			// 墙体
			if (mmap[i][j]) {
				printf("1 ");
			}
			else if (pre[i][j] == -1) {		// 路径途径点
				printf("* ");
			}
			else {
				printf("0 ");				// 空格子
			}
		}
		printf("\n");
	}
	printf("\n");
}

// 各个动作的位移
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

// 判断点是否能走：该点能走且没有走过。
int IsAvailable(Point pnt) {
	if (mmap[pnt.x][pnt.y]) return false;
	if (pre[pnt.x][pnt.y]) return false;
	return true;
}

// 广度优先搜索
int BFSpath(Point src, Point dst) {

	if (cmpPnt(src, dst)) return true;		// 起点重点重合情况
	
	int i;

	//for (i = 1; i <= 4; ++i) {
	//	printf("x=%d, y=%d\n", deltaP[i].x, deltaP[i].y);
	//}
	
	Queue que;			// 存搜索中的结点
	initQue(&que);

	pre[src.x][src.y] = -1;					// 制造根节点
	pushQue(que, src);

	for (; !isEmptyQue(que);) {				// 向下搜索
		Point current = getBack(que);
		//for (i = 1; i <= 8; i++) {		// 允许斜着走
		for (i = 1; i <= 4; i++) {			// 不允许斜着走
			Point next = addPnt(current, deltaP[i]);	// 下一步位置
			if (IsAvailable(next)) {		// 能走
				pushQue(que, next);			// 记录为叶子结点
				pre[next.x][next.y] = i;	// 记录前驱
				if (cmpPnt(next, dst)) {	// 判断是否已经到达目的地
					return true;
				}
			}
		}
		popQue(que);			// 父亲结点搜完了
	}
	return false;			// 全部搜一遍没搜到，说明无法到达

}

// 打印路径
void PrintPath(Point src, Point dst) {

	Stack ans;
	initSta(&ans);
	Point it = dst;
	for (; pre[it.x][it.y] != -1;) {	// 由于记录方式是前驱，故只能逆序遍历
		pushSta(ans, it);				// 压栈
		it = subtractPnt(it, deltaP[pre[it.x][it.y]]);
	}
	pushSta(ans, it);

	Point nxt;
	for (; getStaSize(ans) > 1;) {		// 出栈顺序为正序
		it = getTop(ans);
		popSta(ans);
		nxt = getTop(ans);
		printf("(%d,%d,%d),", it.x, it.y, pre[nxt.x][nxt.y]);
		pre[nxt.x][nxt.y] = -1;			// 标记路径途径点
	}
	printf("\n");

}

