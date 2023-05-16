/***
5.根据输入的无向图的邻接矩阵A，判断此图的连通分量的个数。请使用邻接矩阵的存储结构创建图的存储，并采用BFS遍历算法实现。
language: C++. BFS部分使用了C++
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
邻接矩阵存储结构
***/

#define VertexData int		// 顶点数据类型
#define AdjType bool 		// 邻接矩阵元素类型
#define EdgeData int 		// 边上权值类型

/* 邻接矩阵存储结构 */
typedef struct EdgeNode {
	AdjType adj;
	//EdgeData weight;
} EdgeNode;

/* 顶点数组存储结构 */
typedef struct MatGraph {
	//VertexData vexs[MAXN];			// 顶点数组
	EdgeNode edge[MAXN][MAXN];		// 邻接矩阵
	int n, e;	// 顶点数，边数
} MatGraph;

MatGraph* newMatGraph();			// 创建图
void destroyGraph(MatGraph* g);		// 销毁图
void readGraph(MatGraph* g);		// 读取图
void printGraph(MatGraph* const g);	// 打印图

/*创建图*/
MatGraph* newMatGraph()
{
	MatGraph* g = (MatGraph*)malloc(sizeof(MatGraph));
	if (g == NULL) exit(OVERFLOW);
	memset(g->edge, false, sizeof(g->edge));
	g->n = g->e = 0;
	return g;
}

/*销毁图*/
void destroyGraph(MatGraph* g)
{
	free(g);
	g = NULL;
}

/*读取图*/
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
				assert(x == 0);		// 邻接矩阵元素只能为0或1
			}
		}
	}
}

/*打印图*/
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
题目功能实现
***/

#include <queue>
int countComponent(MatGraph* const g);	// 计算连通分量个数

// 计算连通分量个数
int countComponent(MatGraph* const g)
{
	int i, j;
	int cnt = 0;		// 连通分量个数
	int curr;			// 当前顶点
	bool visited[MAXN] = { false };		// 访问标记数组
	std::queue <int> que;			// 辅助队列
	for (i = 1; i <= g->n; i++) {		// 遍历所有顶点
		if (!visited[i]) {				// 未访问过
			que.push(i);				// 入队
			cnt++;						// 连通分量个数加1
			while (!que.empty()) {		// 队列非空
				curr = que.front();		// 更新当前顶点
				que.pop();				// 出队
				visited[curr] = true;	// 标记为已访问
				for (j = 1; j <= g->n; j++) {		// 遍历所有顶点
					if (g->edge[curr][j].adj) {		// 与当前顶点相邻
						if (!visited[j]) {			// 未访问过
							que.push(j);			// 入队
						}
					}
				}
			}
		}
	}
	return cnt;			// 返回连通分量个数
}


/***
"p0505.c"
主函数
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



