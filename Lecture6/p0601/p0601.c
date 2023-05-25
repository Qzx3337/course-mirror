/***
1、拓扑排序
顶点编号从0开始。

language: C.
***/

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#define MAXN 5008
#define MAXM 200008

typedef int VertexData;

typedef struct Edge {
	int adjVex;
	struct Edge* next;
}Edge;

typedef struct Vertex{
	Edge* head;
	VertexData data;
}Vertex;

typedef struct Graph {
	Vertex vex[MAXN];
	int vexNum, edgeNum;
}Graph;

// 创建一个新边
inline Edge* newEdge(int const adjVex, Edge* const next)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	if (e == NULL) exit(OVERFLOW);
	e->adjVex = adjVex;
	e->next = next;
	return e;
}

//创建一个新图，返回指针
inline Graph* newGraph()
{
	Graph* g = (Graph*)malloc(sizeof(Graph));
	if (g == NULL) exit(OVERFLOW);
	g->edgeNum = 0;
	g->vexNum = 0;
	return g;
}

// 向图中添加新结点
void addVertex(Graph* g, VertexData const data)
{
	g->vex[g->vexNum].data = data;
	g->vex[g->vexNum].head = newEdge(0, NULL);
	g->vexNum++;
}


// 向图中添加新边
void addEdge(Graph* g, int const start, int const end)
{
	g->edgeNum++;
	g->vex[start].head->next = newEdge(end, g->vex[start].head->next);
}

#define STACK_SIZE MAXN
typedef struct Stack {
	int top;
	int mem[STACK_SIZE];
}Stack;

int inDegree[MAXN];

// 打印结点
void printVex(int vex)
{
	printf("%d ", vex);
}

int main(int argc, char const **argv) {
	//freopen("p0601.in", "r", stdin);
	//freopen("p0601.out", "w", stdout);

	int i, j;
	int m, n;
	int head, tail;
	Graph* g = newGraph();
	// TODO: 编号从0开始
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &m);
		addVertex(g, m);
	}
	for (;;) {
		scanf("%d%d", &head, &tail);
		if (head == -1 && tail == -1) {
			break;
		}
		else {
			addEdge(g, head, tail);
			inDegree[tail]++;
		}
	}

	Stack sVex;
	sVex.top = 0;
	for (i = 0; i < g->vexNum; i++) {		// 源点入栈
		if (inDegree[i] == 0) {
			sVex.mem[sVex.top++] = i;
		}
	}

	Edge* it_edge;
	int cur_vex;
	int printList[MAXN];
	int cnt = 0;
	while (sVex.top != 0) {
		cur_vex = sVex.mem[--sVex.top];
		//printVex(cur_vex);
		printList[cnt++] = cur_vex;
		for (it_edge = g->vex[cur_vex].head->next; it_edge != NULL; it_edge = it_edge->next) {
			if ((--inDegree[it_edge->adjVex]) == 0) {
				sVex.mem[sVex.top++] = it_edge->adjVex;
			}
		}
	}

	if (cnt != g->vexNum) {
		printf("ERROR");
	}
	else {
		for (i = 0; i < cnt; i++) {
			printf("%d ", printList[i]);
		}
	}
	printf("\n");

	return 0;
}

