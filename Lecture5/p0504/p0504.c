/*
4������ͼ�Ľ��������
������������
����������Ϣ����ͼ�������ڽӱ����ʽ�洢��ͼ������������ȱ����㷨������ͼ������ӱ����С���㿪ʼ�ı������С�
���������������Ϊint�͡�

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

typedef struct Arc {
	int adjVex;
	struct Arc* nextArc;
}Arc;

typedef struct Vertex {
	VerDataType data;
	struct Arc* head;
}Vertex;

typedef struct _AdjGraph {
	int vexNum, arcNum;
	Vertex vex[MAXN + 1];
}AdjGraph;

inline Arc* newArc(int adjVex, Arc* nextArc) {
	Arc* pa = (Arc*)malloc(sizeof(Arc));
	if (pa == NULL) exit(OVERFLOW);
	pa->adjVex = adjVex;
	pa->nextArc = nextArc;
	return pa;
}

inline AdjGraph* newAdjGraph() {
	AdjGraph* pag = (AdjGraph*)malloc(sizeof(AdjGraph));
	if (pag == NULL) exit(OVERFLOW);
	pag->vexNum = 0;
	pag->arcNum = 0;
	return pag;
}

inline void addVex(AdjGraph* pag, VerDataType data) {
	pag->vexNum++;
	pag->vex[pag->vexNum].data = data;
	pag->vex[pag->vexNum].head = newArc(0, NULL);
}

inline void addArc(AdjGraph* pag, int start, int end) {
	pag->arcNum++;
	pag->vex[start].head->nextArc = newArc(end, pag->vex[start].head->nextArc);
}

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


int main() {

	//freopen("p0504.in", "r", stdin);
	//freopen("p0504.out", "w", stdout);

	// ����
	int i, j, k;
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

	// ������ȱ���
	int stack[MAXN], top = 0;
	bool visited[MAXN] = { 0 };
	Arc* p;
	for (i = 1; i <= ag->vexNum; i++) {
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
	

	return 0;
}

