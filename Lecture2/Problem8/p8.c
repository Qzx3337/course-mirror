/**********************

������������
��һ��m*n�ĳ������ʾ�Թ���0��1�ֱ��ʾ�Թ��е�ͨ·���ϰ������һ�����򣬶������趨���Թ������һ������ڵ����ڵ�ͨ·����ó�û��ͨ·�Ľ��ۡ�

��������ʽ��
����һ��m*n�ĳ�����0��1�ֱ��ʾ�Թ��е�ͨ·���ϰ���

�������ʽ��
һ������ڵ����ڵ�ͨ·������ͼ�α�ʾ(�����������ͨ·�еĵ����ַ�*�滻)��

���������롿
���Ͻǣ�1��1��Ϊ��ڣ����½ǣ�9��8��Ϊ���ڡ�

 0	 0	 1	 0	 0	 0	 1	 0
 0	 0	 1	 0	 0	 0	 1	 0
 0	 0	 0	 0	1	1	 0	 1
 0	 1	 1	 1	 0	 0	 1	 0
 0	 0	 0	 1	 0	 0	 0	 0
 0	 1	 0	 0	 0	 1	 0	 1
 0	 1	 1	 1	 1	 0	 0	 1
 1	 1	 0	 0	 0	 1	 0	 1
 1	 1	 0	 0	 0	 0	 0	 0


�����������
(1,1,1),(1,2,2),(2,2,2),(3,2,3),(3,1,2),(4,1,2),(5,1,1),(5,2,1),(5,3,2),(6,3,1),(6,4,1),(6,5,4),(5,5,1),(5,6,1),(5,7,2),(6,7,2),(7,7,2),(8,7,2),(9,7,1)

������˵����
��һ��9x8�ĳ�����ÿ��Ԫ�ص�ֵΪ0��1������0��1�ֱ��ʾ�Թ��е�ͨ·���ϰ���ͨ·����Ԫ�飨i,j,d) ����ʽ��������У���i,j) ָʾ�Թ��е�һ�����꣬d ��ʾ�ߵ���һ����ķ��򡣶����ϡ�����������Ϊ1��2��3��4�����ϡ����ϡ���������������Ϊ5��6��7��8��


language: C.

**************************/


#define _CRT_SECURE_NO_WARNINGS 1

#include "p8.h"


int mmap[MAXM][MAXN];
int pre[MAXM][MAXN];

// �����ͼ
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

// ��ӡ��ͼ
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
		(Point) {0,1},	// ��
		(Point) {1,0},	// ��
		(Point) {0,-1},	// ��
		(Point) {-1,0}	// ��
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
	if (BFSpath(src, dst)) {		// �ҵ���·��
		PrintPath(src, dst);
	}
	else {							// δ�ҵ�·��
		printf("No Path!\n");
	}

	return 0;
}

