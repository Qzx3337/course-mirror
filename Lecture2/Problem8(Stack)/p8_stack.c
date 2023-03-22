/**********************

Problem 8: 迷宫问题

Description: README.MD

language: C.

**************************/


#define _CRT_SECURE_NO_WARNINGS 1

#include "p8_stack.h"

#define DIRECTION_MODE 4	// 方向模式：4表示四方向移动（只能上下左右走），8表示八方向（可以斜着走）

// 全局变量

int mmap[MAXM][MAXN];	// 地图
int pre[MAXM][MAXN];	// 用于寻找前驱结点，一个数字代表动作
int vis[MAXM][MAXN] = { 0 };// 访问数组
Point deltaP[9];		// 所有的动作对应的位移


// 方法列表

void InitMap(int m, int n);
void PrintMap(int m, int n);
void InitDelta();
int IsAvailable(Point pnt);
int DFSpath(Point src, Point dst);
void PrintPath(Point src, Point dst);


// 主函数
int main() {

	freopen("p8.in", "r", stdin);		// 文件读入
	//freopen("p8.out", "w", stdout);		// 文件输出

	int m, n;
	scanf("%d%d", &m, &n);
	InitMap(m, n);
	//PrintMap(m, n);

	Point src, dst;
	scanf("%d%d%d%d", &src.x, &src.y, &dst.x, &dst.y);

	InitDelta();
	
	if (DFSpath(src, dst)) {		// 找到了路径
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

// 搜索路径，并记录结果
int DFSpath(Point src, Point dst)
{
	// 参数：起点src，终点dst
	// 返回值：是否找到了路径
	// 初始化栈
	Stack sta;
	initSta(&sta);
	// 初始化栈
	pushSta(sta, src);
	// 初始化访问数组
	vis[src.x][src.y] = 1;
	// 开始搜索
	while (!isEmpty(sta)) {		// 栈不为空
		Point cur = getTop(sta);	// 取栈顶元素
		popSta(sta);				// 出栈
		// 判断是否是终点
		if (cur.x == dst.x && cur.y == dst.y) {
			destroySta(sta);			// 释放资源
			return true;
		}
		// 依次尝试所有的动作
		int i;
		for (i = 1; i <= DIRECTION_MODE; ++i) {		// 注意：这里从1开始，因为deltaP[0]是无效的
			Point next = { cur.x + deltaP[i].x, cur.y + deltaP[i].y };		// 计算下一个点
			// 判断是否可行
			if (IsAvailable(next) && !vis[next.x][next.y]) {	// 可行且未被访问过
				pushSta(sta, next);
				vis[next.x][next.y] = 1;
				pre[next.x][next.y] = i;
			}
		}
	}
	destroySta(sta);	// 释放资源
	return false;		// 没有找到路径
}

// 打印地图
void PrintMap(int m, int n) {
	printf("\n");
	int i, j;
	for (i = 1; i <= m; ++i) {
		for (j = 1; j <= n; ++j) {			// 墙体
			if (mmap[i][j] == 2) {
				printf("* ");
			}
			//else if (vis[i][j]) {
			//	printf("+ ");
			//}
			else {
				printf("%d ", mmap[i][j]);
			}
		}
		printf("\n");
	}
}

// 打印路径
void PrintPath(Point src, Point dst) {

	Stack ans;
	initSta(&ans);
	Point it = dst;
	for (; pre[it.x][it.y] != 0;) {	// 由于记录方式是前驱，故只能逆序遍历
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
		mmap[nxt.x][nxt.y] = 2;			// 标记路径途径点
	}
	mmap[it.x][it.y] = 2;
	printf("\n");

	destroySta(ans);
}

