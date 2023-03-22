/**********************

Problem 8: �Թ�����

Description: README.MD

language: C.

**************************/


#define _CRT_SECURE_NO_WARNINGS 1

#include "p8.h"

#define DIRECTION_MODE 4	// ����ģʽ��4��ʾ�ķ����ƶ���ֻ�����������ߣ���8��ʾ�˷��򣨿���б���ߣ�

// ȫ�ֱ���

int mmap[MAXM][MAXN];	// ��ͼ
int pre[MAXM][MAXN];	// ����Ѱ��ǰ����㣬һ�����ִ�����
Point deltaP[9];		// ���еĶ�����Ӧ��λ��

// �����б�

void InitMap(int m, int n);
void PrintMap(int m, int n);
void InitDelta();
int IsAvailable(Point pnt);
int BFSpath(Point src, Point dst);
void PrintPath(Point src, Point dst);


// ������
int main() {

	freopen("p8.in", "r", stdin);		// �ļ�����

	int m, n;
	scanf("%d%d", &m, &n);
	InitMap(m, n);
	//PrintMap(m, n);

	Point src, dst;
	scanf("%d%d%d%d", &src.x, &src.y, &dst.x, &dst.y);

	InitDelta();

	// BFS
	if (BFSpath(src, dst)) {		// �ҵ���·��
		PrintPath(src, dst);
		PrintMap(m, n);
	}
	else {							// δ�ҵ�·��
		printf("No Path!\n");
	}

	return 0;
}


/********* ����ʵ�� *****************/


// �����ͼ
void InitMap(int m, int n) {
	int i, j;
	for (i = 0; i <= m + 1; ++i) {			// ��Χ��ԵΧǽ
		mmap[i][0] = mmap[i][n + 1] = 1;
	}
	for (j = 0; j <= n + 1; ++j) {
		mmap[0][j] = mmap[m + 1][j] = 1;
	}

	for (i = 1; i <= m; ++i) {				// ͼ��Χǽ�������
		for (j = 1; j <= n; ++j) {
			scanf("%d", &mmap[i][j]);
		}
	}

}

// ��ӡ��ͼ
void PrintMap(int m, int n) {
	//printf("\nm=%d; n=%d\n", m, n);

	printf("\n");
	int i, j;
	//for (i = 0; i <= m + 1; ++i) {			// ���������Χ��Ե
	//	for (j = 0; j <= n + 1; ++j) {
	for (i = 1; i <= m; ++i) {
		for (j = 1; j <= n; ++j) {			// ǽ��
			if (mmap[i][j]) {
				printf("1 ");
			}
			else if (pre[i][j] == -1) {		// ·��;����
				printf("* ");
			}
			else {
				printf("0 ");				// �ո���
			}
		}
		printf("\n");
	}
	printf("\n");
}

// ����������λ��
void InitDelta() {
	deltaP[0] = (Point){ 0,0 };		// ԭ�ز���
	deltaP[1] = (Point){ 0,1 };		// ��
	deltaP[2] = (Point){ 1,0 };		// ��
	deltaP[3] = (Point){ 0,-1 };	// ��
	deltaP[4] = (Point){ -1,0 };	// ��
	deltaP[5] = (Point){ 1,1 };		// ����
	deltaP[6] = (Point){ 1,-1 };	// ����
	deltaP[7] = (Point){ -1,1 };	// ����
	deltaP[8] = (Point){ -1,-1 };	// ����
}

// �жϵ��Ƿ����ߣ��õ�������û���߹���
int IsAvailable(Point pnt) {
	if (mmap[pnt.x][pnt.y]) return false;
	if (pre[pnt.x][pnt.y]) return false;
	return true;
}

// �����������
int BFSpath(Point src, Point dst) {

	if (cmpPnt(src, dst)) return true;		// ����ص��غ����
	
	int i;

	//for (i = 1; i <= 4; ++i) {
	//	printf("x=%d, y=%d\n", deltaP[i].x, deltaP[i].y);
	//}
	
	Queue que;			// �������еĽ��
	initQue(&que);

	pre[src.x][src.y] = -1;					// ������ڵ�
	pushQue(que, src);

	for (; !isEmptyQue(que);) {				// ��������
		Point current = getBack(que);
		for (i = 1; i <= DIRECTION_MODE; i++) {			// ������б����
			Point next = addPnt(current, deltaP[i]);	// ��һ��λ��
			if (IsAvailable(next)) {		// ����
				pushQue(que, next);			// ��¼ΪҶ�ӽ��
				pre[next.x][next.y] = i;	// ��¼ǰ��
				if (cmpPnt(next, dst)) {	// �ж��Ƿ��Ѿ�����Ŀ�ĵ�
					return true;
				}
			}
		}
		popQue(que);			// ���׽��������
	}
	return false;			// ȫ����һ��û�ѵ���˵���޷�����

}

// ��ӡ·��
void PrintPath(Point src, Point dst) {

	Stack ans;
	initSta(&ans);
	Point it = dst;
	for (; pre[it.x][it.y] != -1;) {	// ���ڼ�¼��ʽ��ǰ������ֻ���������
		pushSta(ans, it);				// ѹջ
		it = subtractPnt(it, deltaP[pre[it.x][it.y]]);
	}
	pushSta(ans, it);

	Point nxt;
	for (; getStaSize(ans) > 1;) {		// ��ջ˳��Ϊ����
		it = getTop(ans);
		popSta(ans);
		nxt = getTop(ans);
		printf("(%d,%d,%d),", it.x, it.y, pre[nxt.x][nxt.y]);
		pre[nxt.x][nxt.y] = -1;			// ���·��;����
	}
	printf("\n");

}

