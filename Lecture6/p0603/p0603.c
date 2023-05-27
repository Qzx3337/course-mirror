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

/*** djstra 结点 **/
typedef struct DjsNode {
    int dis;
    int pos;
}DjsNode;

DjsNode makeDjsNode(int const dis, int const pos)
{
    DjsNode n;
    n.dis = dis;
    n.pos = pos;
    return n;
}

bool cmpDjs(DjsNode a, DjsNode b)
{
    if (a.dis < b.dis) {
        return true;
    }
    else {
        return false;
    }
}

//********* !Graph_h

//*********** heap_h 

#define HCAPACITY MAXN
#ifndef HeapDataType
#define HeapDataType DjsNode
#endif // !HeapDataType

typedef struct Heap {
    HeapDataType* data;
    int size;
    int capacity;
    bool (*cmp)(HeapDataType, HeapDataType);
}Heap;

Heap* newHeap(bool (*cmp)(HeapDataType, HeapDataType)) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (heap == NULL) exit(OVERFLOW);
    heap->data = (HeapDataType*)malloc(HCAPACITY * sizeof(HeapDataType));
    heap->capacity = HCAPACITY;
    heap->size = 0;
    heap->cmp = cmp;
    return heap;
}

void destroyHeap(Heap* heap) {
    free(heap->data);
    free(heap);
}

bool pushHeap(Heap* heap, HeapDataType value) {
    if (heap->size >= heap->capacity) {
        return false;
    }
    heap->data[heap->size++] = value;
    int i = heap->size - 1;
    while (i > 0 && heap->cmp(heap->data[i], heap->data[(i - 1) / 2])) {
        HeapDataType tmp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = tmp;
        i = (i - 1) / 2;
    }
    return true;
}

HeapDataType getTopHeap(Heap* heap) {
    if (heap->size <= 0) {
        // 返回一个无用的值
        HeapDataType tmp;
        memset(&tmp, 0, sizeof(HeapDataType));
        return tmp;
    }
    return heap->data[0];
}

bool popHeap(Heap* heap) {
    if (heap->size <= 0) {
        return false;
    }
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i = 0;
    while (i * 2 + 1 < heap->size) {
        int left = i * 2 + 1, right = i * 2 + 2;
        int smallerChild = left;
        if (right < heap->size && heap->cmp(heap->data[right], heap->data[left])) {
            smallerChild = right;
        }
        if (heap->cmp(heap->data[smallerChild], heap->data[i])) {
            HeapDataType tmp = heap->data[smallerChild];
            heap->data[smallerChild] = heap->data[i];
            heap->data[i] = tmp;
            i = smallerChild;
        }
        else {
            break;
        }
    }
    return true;
}

bool isEmptyHeap(Heap* heap) {
    return heap->size == 0;
}

//***** ! heap_h

//**** 题目方法
//添加注释

int dis[MAXN];          // 距离
int preOnPath[MAXN];    // 前驱
bool visited[MAXN];     // 是否访问过

int main(int argc, char const **argv) {
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

    // djkstra 思路：
    //1. 初始化距离数组dis，将起点s的距离设为0，其他点的距离设为无穷大
    //2. 初始化堆h，将起点s加入堆中，距离为0
    //3. 堆不空，取出堆顶元素，如果该元素没有被访问过，则标记为已访问，否则忽略该元素
    //4. 遍历该元素的所有邻接边，如果该边的另一个顶点的距离大于该边的权值加上该元素的距离，则更新该顶点的距离，将该顶点加入堆中
    //5. 重复3，4步骤
    // 
    // djkstra 初始化
    for (i = 0; i < n; i++) {
        dis[i] = INF;
    }
    dis[s] = 0;
    preOnPath[s] = -1;
    Heap* h = newHeap(cmpDjs);
    pushHeap(h, makeDjsNode(0, s));     // 将起点加入堆中

    // djstra 计算，核心算法

    Edge* itEdge;
    while (!isEmptyHeap(h)) {           // 堆不空
        DjsNode curNode = getTopHeap(h);    // 取出堆顶元素
        popHeap(h);
        if (!visited[curNode.pos]) {    // 如果该元素没有被访问过
            visited[curNode.pos] = true;    // 标记为已访问
            for (itEdge = g->vex[curNode.pos].head->next; itEdge != NULL; itEdge = itEdge->next) {  // 遍历该元素的所有邻接边
                if (dis[itEdge->adjVex] > dis[curNode.pos] + itEdge->dis) {     // 如果该边的另一个顶点的距离大于该边的权值加上该元素的距离
                    dis[itEdge->adjVex] = dis[curNode.pos] + itEdge->dis;	    // 更新该顶点的距离
                    preOnPath[itEdge->adjVex] = curNode.pos;                    // 更新该顶点的前驱
                    pushHeap(h, makeDjsNode(dis[itEdge->adjVex], itEdge->adjVex));  // 将该顶点加入堆中
                }
            }
        }
    }
    destroyHeap(h);



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

