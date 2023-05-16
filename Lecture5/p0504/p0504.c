/*
4、无向图的建立与遍历
【问题描述】
根据输入信息创建图，采用邻接表的形式存储该图，并用深度优先遍历算法遍历该图，输出从编号最小顶点开始的遍历序列。
各顶点的数据类型为int型。

问题：
题目测试数据是根据为了深度优先遍历设计好的。
为什么递归实现时可以做到从小到大的顺序，而非递归遍历顺序会乱？
DFS算法为课本P226 算法 7.6，7.7。

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
/// 下面是图结构的定义，部分接口实现
/// </summary>

// 邻接表
typedef struct Arc {
	int adjVex;
	struct Arc* nextArc;
}Arc;

// 顶点
typedef struct Vertex {
	VerDataType data;
	struct Arc* head;
}Vertex;

// 图
typedef struct _AdjGraph {
	int vexNum, arcNum;
	Vertex vex[MAXN + 1];
}AdjGraph;

// 创建新的弧
inline Arc* newArc(int adjVex, Arc* nextArc) {
	Arc* pa = (Arc*)malloc(sizeof(Arc));
	if (pa == NULL) exit(OVERFLOW);
	pa->adjVex = adjVex;
	pa->nextArc = nextArc;
	return pa;
}

// 创建新的图
inline AdjGraph* newAdjGraph() {
	AdjGraph* pag = (AdjGraph*)malloc(sizeof(AdjGraph));
	if (pag == NULL) exit(OVERFLOW);
	pag->vexNum = 0;
	pag->arcNum = 0;
	return pag;
}

// 添加顶点
inline void addVex(AdjGraph* pag, VerDataType data) {
	pag->vexNum++;
	pag->vex[pag->vexNum].data = data;
	pag->vex[pag->vexNum].head = newArc(0, NULL);
}

// 添加弧
inline void addArc(AdjGraph* pag, int start, int end) {
	pag->arcNum++;
	pag->vex[start].head->nextArc = newArc(end, pag->vex[start].head->nextArc);
}

// 销毁图
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
/// 下面是题目相关的方法实现
/// p0504.h
/// </summary>

bool visited[MAXN] = { 0 };

/* 递归方法实现对图的遍历 */
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

/* 非递归方法实现对图的遍历 */
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

	// 读入

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

	// DFS遍历

	DFS_AdjGraph(ag, 1);
	printf("\n");
	//DFS_AdjGraph_1(ag);
	//printf("\n");

	return 0;
}

