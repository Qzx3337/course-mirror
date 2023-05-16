/***
5.�������������ͼ���ڽӾ���A���жϴ�ͼ����ͨ�����ĸ�������ʹ���ڽӾ���Ĵ洢�ṹ����ͼ�Ĵ洢��������BFS�����㷨ʵ�֡�
language: C++. BFS����ʹ����C++
***/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#define INF 0x7FFFFFFF


#define MAXN 100

/***
"MatGraph.h"
�ڽӾ���洢�ṹ
***/

#define VertexData int		// ������������
#define AdjType bool 		// �ڽӾ���Ԫ������
#define EdgeData int 		// ����Ȩֵ����

/* �ڽӾ���洢�ṹ */
typedef struct EdgeNode {
	AdjType adj;
	//EdgeData weight;
} EdgeNode;

/* ��������洢�ṹ */
typedef struct MatGraph {
	//VertexData vexs[MAXN];			// ��������
	EdgeNode edge[MAXN][MAXN];		// �ڽӾ���
	int n, e;	// ������������
} MatGraph;

MatGraph* newMatGraph();			// ����ͼ
void destroyGraph(MatGraph* g);		// ����ͼ
void readGraph(MatGraph* g);		// ��ȡͼ
void printGraph(MatGraph* const g);	// ��ӡͼ

/*����ͼ*/
MatGraph* newMatGraph()
{
	MatGraph* g = (MatGraph*)malloc(sizeof(MatGraph));
	if (g == NULL) exit(OVERFLOW);
	memset(g->edge, false, sizeof(g->edge));
	g->n = g->e = 0;
	return g;
}

/*����ͼ*/
void destroyGraph(MatGraph* g)
{
	free(g);
	g = NULL;
}

/*��ȡͼ*/
void readGraph(MatGraph* g)
{
	int i, j;
	int x;
	scanf("%d", &g->n);
	for (i = 1; i <= g->n; i++) {
		for (j = 1; j <= g->n; j++) {
			scanf("%d", &x);
			if (x == 1) {
				g->e++;
				g->edge[i][j].adj = (bool)x;
			}
			else {
				assert(x == 0);		// �ڽӾ���Ԫ��ֻ��Ϊ0��1
			}
		}
	}
}

/*��ӡͼ*/
void printGraph(MatGraph* const g)
{
	int i, j;
	printf("n=%d, e=%d\n", g->n, g->e);
	for (i = 1; i <= g->n; i++) {
		for (j = 1; j <= g->n; j++) {
			printf("%d ", g->edge[i][j].adj);
		}
		printf("\n");
	}
	printf("\n");
}


/***
"p0505.h"
��Ŀ����ʵ��
***/

#include <queue>
int countComponent(MatGraph* const g);	// ������ͨ��������

// ������ͨ��������
int countComponent(MatGraph* const g)
{
	int i, j;
	int cnt = 0;		// ��ͨ��������
	int curr;			// ��ǰ����
	bool visited[MAXN] = { false };		// ���ʱ������
	std::queue <int> que;			// ��������
	for (i = 1; i <= g->n; i++) {		// �������ж���
		if (!visited[i]) {				// δ���ʹ�
			que.push(i);				// ���
			cnt++;						// ��ͨ����������1
			while (!que.empty()) {		// ���зǿ�
				curr = que.front();		// ���µ�ǰ����
				que.pop();				// ����
				visited[curr] = true;	// ���Ϊ�ѷ���
				for (j = 1; j <= g->n; j++) {		// �������ж���
					if (g->edge[curr][j].adj) {		// �뵱ǰ��������
						if (!visited[j]) {			// δ���ʹ�
							que.push(j);			// ���
						}
					}
				}
			}
		}
	}
	return cnt;			// ������ͨ��������
}


/***
"p0505.c"
������
***/
int main() {
	//freopen("p0505.in", "r", stdin);
	//freopen("p0505.out", "w", stdout);

	MatGraph* g = newMatGraph();
	readGraph(g);
	//printGraph(g);

	printf("%d\n", countComponent(g));

	destroyGraph(g);

	return 0;
}



