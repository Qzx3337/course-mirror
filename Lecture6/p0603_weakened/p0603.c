/***
language: C.

3、迪杰斯特拉算法求最短路径

【输入形式】
输入的第一行依次是2个正整数n和s，表示图中共有n个顶点，且源点编号为s（顶点编号从0~n-1）。其中n不超过50，s小于n。
以后的n行中每行有n个用空格隔开的整数。
对于第i行的第j个整数，如果大于0，则表示第i个顶点有指向第j个顶点的有向边，且权值为对应的整数值；
如果这个整数为0，则表示没有i指向j的有向边。
当i和j相等的时候，对应的整数也是0。

【输出形式】
只有一行，共有n-1个整数，表示源点至其它每个顶点 (编号从小到大顺序) 各自的最短路径长度。
如果不存在从源点至相应顶点的路径，则输出-1。
注意: 各输出数据间用1个空格分隔, 行尾输出换行。

弱化版，不使用堆查找最短边，而是使用直接法

TODO: 没有用 locateVex() 函数寻通过 id 查找结点，而是直接使用了数组下标，

***/

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

/***   题目背景_h    ****/

#define INF 0x7fffffff
#define MAXN 5008
#define MAXM 200008

//*** 邻接链表图结构_h    *********/

typedef int VertexData;

typedef struct Edge {
    int adjVex;
    int dis;
    struct Edge* next;
}Edge;

typedef struct Vertex {
    Edge* head;
    VertexData data;
}Vertex;

typedef struct Graph {
    Vertex vex[MAXN];
    int vexNum, edgeNum;
}Graph;

// 创建一个新边
inline Edge* newEdge(int const adjVex, int const dis, Edge* const next)
{
    Edge* e = (Edge*)malloc(sizeof(Edge));
    if (e == NULL) exit(OVERFLOW);
    e->adjVex = adjVex;
    e->dis = dis;
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

// 销毁图，编号从0开始
void destoryGraph(Graph* g)
{
    int i;
    Edge* it1, * it2;
    for (i = 0; i < g->vexNum; i++) {
        it1 = g->vex[i].head;
        while (it1 != NULL) {
            it2 = it1;
            it1 = it1->next;
            free(it2);
        }
    }
    free(g);
}

// 向图中添加新结点，编号从0开始
void addVertex(Graph* g, VertexData const data)
{
    g->vex[g->vexNum].data = data;
    g->vex[g->vexNum].head = newEdge(0, 0, NULL);
    g->vexNum++;
}

// 向图中添加新边
void addEdge(Graph* g, int const start, int const end, int const distance)
{
    g->edgeNum++;
    g->vex[start].head->next = newEdge(end, distance, g->vex[start].head->next);
}

//********* !Graph_h

//**** 题目方法
//添加注释

int dis[MAXN];          // 距离
int preOnPath[MAXN];    // 前驱
bool visited[MAXN];     // 是否访问过

int getClosest(Graph* const g)
{
    int i, min = INF;
    int pos = -1;
    for (i = 0; i < g->vexNum; i++) {
        if (!visited[i] && dis[i] < min) {
            min = dis[i];
            pos = i;
        }
    }
    return pos;
}

int main(int argc, char const** argv) {
    //freopen("p0603.in", "r", stdin);
    //freopen("p0603.out", "w", stdout);

    int i, j;
    int n, s, v;       // 编号 0 到 n-1
    Graph* g = newGraph();
    scanf("%d%d", &n, &s);      // 读入
    for (i = 0; i < n; i++) {
        addVertex(g, i);
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &v);
            if (v != 0) {
                addEdge(g, i, j, v);
            }
        }
    }

    // djkstra 初始化
    for (i = 0; i < n; i++) {
        dis[i] = INF;
    }
    dis[s] = 0;
    preOnPath[s] = -1;

    // djstra 计算，核心算法

    Edge* itEdge;
    int curNode;
    while (true) {
        curNode = getClosest(g);
        if (curNode == -1) break;   // 如果没有找到，则退出
        visited[curNode] = true;    // 标记为已访问
        for (itEdge = g->vex[curNode].head->next; itEdge != NULL; itEdge = itEdge->next) {  // 遍历该元素的所有邻接边
            if (dis[itEdge->adjVex] > dis[curNode] + itEdge->dis) {     // 如果该边的另一个顶点的距离大于该边的权值加上该元素的距离
                dis[itEdge->adjVex] = dis[curNode] + itEdge->dis;	    // 更新该顶点的距离
                preOnPath[itEdge->adjVex] = curNode;                    // 更新该顶点的前驱
            }
        }
    }

    // 总结djstra算法思路
    // 1.初始化所有点的距离为无穷大，起点的距离为0
    // 2.从起点开始，每次选择一个距离最小的点，标记为已访问
    // 3.遍历该点的所有邻接边，如果该边的另一个顶点的距离大于该边的权值加上该元素的距离，则更新该顶点的距离，并更新前驱
    // 4.重复2，3步骤，直到所有点都访问过

    // 输出
    for (i = 0; i < n; i++) {
        if (i != s) {
            if (dis[i] == INF) {
                printf("-1 ");
            }
            else {
                printf("%d ", dis[i]);
            }
        }
    }
    printf("\n");
    destoryGraph(g);

    return 0;
}

