/*
4������ͼ�Ľ��������
������������
����������Ϣ����ͼ�������ڽӱ����ʽ�洢��ͼ������������ȱ����㷨������ͼ������ӱ����С���㿪ʼ�ı������С�
���������������Ϊint�͡�

���⣺
��Ŀ���������Ǹ���Ϊ��������ȱ�����ƺõġ�
Ϊʲô�ݹ�ʵ��ʱ����������С�����˳�򣬶��ǵݹ����˳����ң�
DFS�㷨Ϊ�α�P226 �㷨 7.6��7.7��

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#define INF 0x7FFFFFFF

#define VerDataType int
#define MAXN 100
#define MAXM 9999

/// <summary>
/// ������ͼ�ṹ�Ķ��壬���ֽӿ�ʵ��
/// </summary>

// �ڽӱ�
typedef struct Arc {
	int adjVex;
	struct Arc* nextArc;
}Arc;

// ����
typedef struct Vertex {
	VerDataType data;
	struct Arc* head;
}Vertex;

// ͼ
typedef struct _AdjGraph {
	int vexNum, arcNum;
	Vertex vex[MAXN + 1];
}AdjGraph;

// �����µĻ�
inline Arc* newArc(int adjVex, Arc* nextArc) {
	Arc* pa = (Arc*)malloc(sizeof(Arc));
	if (pa == NULL) exit(OVERFLOW);
	pa->adjVex = adjVex;
	pa->nextArc = nextArc;
	return pa;
}

// �����µ�ͼ
inline AdjGraph* newAdjGraph() {
	AdjGraph* pag = (AdjGraph*)malloc(sizeof(AdjGraph));
	if (pag == NULL) exit(OVERFLOW);
	pag->vexNum = 0;
	pag->arcNum = 0;
	return pag;
}

// ��Ӷ���
inline void addVex(AdjGraph* pag, VerDataType data) {
	pag->vexNum++;
	pag->vex[pag->vexNum].data = data;
	pag->vex[pag->vexNum].head = newArc(0, NULL);
}

// ��ӻ�
inline void addArc(AdjGraph* pag, int start, int end) {
	pag->arcNum++;
	pag->vex[start].head->nextArc = newArc(end, pag->vex[start].head->nextArc);
}

// ����ͼ
inline void destroyAdjGraph(AdjGraph* pag) {
	int i;
	Arc* p, * q;
	for (i = 1; i <= pag->vexNum; i++) {
		p = pag->vex[i].head;
		while (p) {
			q = p;
			p = p->nextArc;
			free(q);
		}
	}
	free(pag);
}

/// <summary>
/// ��������Ŀ��صķ���ʵ��
/// p0504.h
/// </summary>

bool visited[MAXN] = { 0 };

/* �ݹ鷽��ʵ�ֶ�ͼ�ı��� */
void DFS_AdjGraph(AdjGraph* g, int v0) {
	Arc* p;
	visited[v0] = true;
	printf("%d ", g->vex[v0].data);
	p = g->vex[v0].head->nextArc;
	while (p) {
		if (!visited[p->adjVex]) {
			DFS_AdjGraph(g, p->adjVex);
		}
		p = p->nextArc;
	}
}

/* �ǵݹ鷽��ʵ�ֶ�ͼ�ı��� */
void DFS_AdjGraph_1(AdjGraph* ag) {
	int i, j;
	int stack[MAXN], top = 0;
	bool visited[MAXN] = { 0 };
	Arc* p;
	for (i = 1; i <= 1; i++) {
	//for (i = 1; i <= ag->vexNum; i++) {
		if (visited[i]) continue;
		stack[top++] = i;
		while (top) {
			j = stack[--top];	
			if (visited[j]) continue;
			printf("%d ", ag->vex[j].data);
			visited[j] = true;
			p = ag->vex[j].head->nextArc;
			while (p) {
				if(!visited[p->adjVex]) stack[top++] = p->adjVex;
				p = p->nextArc;
			}
		}
	}
	
}


int main() {
	//freopen("p0504.in", "r", stdin);
	//freopen("p0504.out", "w", stdout);

	int i, j, k;

	// ����

	int n, data;
	AdjGraph* ag = newAdjGraph();
	scanf("%d", &n);
	assert(n <= MAXN);
	for (i = 1; i <= n; i++) {
		scanf("%d", &data);
		addVex(ag, data);
	} 
	for (;;) {
		scanf("%d %d", &j, &k);
		if(j == -1 && k == -1) break;
		addArc(ag, j, k);
		//addArc(ag, k, j);
	}

	// DFS����

	DFS_AdjGraph(ag, 1);
	printf("\n");
	//DFS_AdjGraph_1(ag);
	//printf("\n");

	return 0;
}

