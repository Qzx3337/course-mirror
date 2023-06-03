/***
language: C.
四、弗洛伊德算法求最短路径
***/

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#define INF 9999
#define MAXN 55

typedef struct MatGraph {
	int vexNum;
	//int edgeNum;
	int dis[MAXN][MAXN];
}MatGraph;

void readGraph(MatGraph* g)
{
	int i, j;
	scanf("%d", &g->vexNum);
	for (i = 0; i < g->vexNum; i++) {
		for (j = 0; j < g->vexNum; j++) {
			scanf("%d", &g->dis[i][j]);
		}
	}
}

void Floyd(MatGraph* const g, int dis[MAXN][MAXN], int path[MAXN][MAXN])
{
	int i, j, k;
	//memset(path, 0, sizeof(path));
	for (i = 0; i < g->vexNum; i++) {
		for (j = 0; j <= g->vexNum; j++) {
			path[i][j] = -1;
		}
	}
	//for (i = 0; i < g->vexNum; i++) {
	//	for (j = 0; j <= g->vexNum; j++) {
	//		printf("%d ", path[i][j]);
	//	}
	//	printf("\n");
	//}
	//printf("\n");

	for (i = 0; i <= g->vexNum; i++) {
		for (j = 0; j <= g->vexNum; j++) {
			if (i == j) {
				dis[i][j] = 0;
			}
			else {
				dis[i][j] = g->dis[i][j];
			}
		}
	}
	for (k = 0; k < g->vexNum; k++) {
		for (i = 0; i <= g->vexNum; i++) {
			for (j = 0; j <= g->vexNum; j++) {
				if (dis[i][j] > dis[i][k] + dis[k][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
					path[i][j] = k;
				}
			}
		}
	}
}

inline void printPathRecur(int const path[MAXN][MAXN], int const u, int const v)
{
	if (u == v) {
		return;
	}
	if (path[u][v] == -1) {
		printf("%d ", v);
	}
	else {
		printPathRecur(path, u, path[u][v]);
		printPathRecur(path, path[u][v], v);
	}
}

void printShortestPath(MatGraph* const g, int dis[MAXN][MAXN], int path[MAXN][MAXN])
{
	int i, j;
	//for (i = 0; i < g->vexNum; i++) {
	//	for (j = 0; j <= g->vexNum; j++) {
	//		printf("%d ", path[i][j]);
	//	}
	//	printf("\n");
	//}
	//printf("\n");

	for (i = 0; i < g->vexNum; i++) {
		for (j = 0; j < g->vexNum; j++) {
			printf("from %d to %d: dist = %d path:%d ", i, j, dis[i][j], i);
			printPathRecur(path, i, j);
			printf("\n"); 
		}
	}

}

void printGraph(MatGraph* const g)
{
	int i, j;
	for (i = 0; i < g->vexNum; i++) {
		for (j = 0; j < g->vexNum; j++) {
			printf("%5d", g->dis[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char const **argv)
{
	//freopen("p0604_2.in", "r", stdin);
	//freopen("p0604.out", "w", stdout);
	
	MatGraph _g;
	MatGraph* g = &_g;
	readGraph(g);
	//printGraph(g);
	int dis[MAXN][MAXN], path[MAXN][MAXN];
	Floyd(g, dis, path);
	printShortestPath(g, dis, path);
	
	return 0;
}

