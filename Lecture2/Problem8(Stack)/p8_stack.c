/**********************

Problem 8: �Թ�����

Description: README.MD

language: C.

**************************/


#define _CRT_SECURE_NO_WARNINGS 1

#include "p8_stack.h"

#define DIRECTION_MODE 4	// ����ģʽ��4��ʾ�ķ����ƶ���ֻ�����������ߣ���8��ʾ�˷��򣨿���б���ߣ�

// ȫ�ֱ���

int mmap[MAXM][MAXN];	// ��ͼ
int pre[MAXM][MAXN];	// ����Ѱ��ǰ����㣬һ�����ִ�����
int vis[MAXM][MAXN] = { 0 };// ��������
Point deltaP[9];		// ���еĶ�����Ӧ��λ��


// �����б�

void InitMap(int m, int n);
void PrintMap(int m, int n);
void InitDelta();
int IsAvailable(Point pnt);
int DFSpath(Point src, Point dst);
void PrintPath(Point src, Point dst);


// ������
int main() {

	freopen("p8.in", "r", stdin);		// �ļ�����
	//freopen("p8.out", "w", stdout);		// �ļ����

	int m, n;
	scanf("%d%d", &m, &n);
	InitMap(m, n);
	//PrintMap(m, n);

	Point src, dst;
	scanf("%d%d%d%d", &src.x, &src.y, &dst.x, &dst.y);

	InitDelta();
	
	if (DFSpath(src, dst)) {		// �ҵ���·��
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

// ����·��������¼���
int DFSpath(Point src, Point dst)
{
	// ���������src���յ�dst
	// ����ֵ���Ƿ��ҵ���·��
	// ��ʼ��ջ
	Stack sta;
	initSta(&sta);
	// ��ʼ��ջ
	pushSta(sta, src);
	// ��ʼ����������
	vis[src.x][src.y] = 1;
	// ��ʼ����
	while (!isEmpty(sta)) {		// ջ��Ϊ��
		Point cur = getTop(sta);	// ȡջ��Ԫ��
		popSta(sta);				// ��ջ
		// �ж��Ƿ����յ�
		if (cur.x == dst.x && cur.y == dst.y) {
			destroySta(sta);			// �ͷ���Դ
			return true;
		}
		// ���γ������еĶ���
		int i;
		for (i = 1; i <= DIRECTION_MODE; ++i) {		// ע�⣺�����1��ʼ����ΪdeltaP[0]����Ч��
			Point next = { cur.x + deltaP[i].x, cur.y + deltaP[i].y };		// ������һ����
			// �ж��Ƿ����
			if (IsAvailable(next) && !vis[next.x][next.y]) {	// ������δ�����ʹ�
				pushSta(sta, next);
				vis[next.x][next.y] = 1;
				pre[next.x][next.y] = i;
			}
		}
	}
	destroySta(sta);	// �ͷ���Դ
	return false;		// û���ҵ�·��
}

// ��ӡ��ͼ
void PrintMap(int m, int n) {
	printf("\n");
	int i, j;
	for (i = 1; i <= m; ++i) {
		for (j = 1; j <= n; ++j) {			// ǽ��
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

// ��ӡ·��
void PrintPath(Point src, Point dst) {

	Stack ans;
	initSta(&ans);
	Point it = dst;
	for (; pre[it.x][it.y] != 0;) {	// ���ڼ�¼��ʽ��ǰ������ֻ���������
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
		mmap[nxt.x][nxt.y] = 2;			// ���·��;����
	}
	mmap[it.x][it.y] = 2;
	printf("\n");

	destroySta(ans);
}

