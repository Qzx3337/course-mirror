/***
language: C.

3���Ͻ�˹�����㷨�����·��

��������ʽ��
����ĵ�һ��������2��������n��s����ʾͼ�й���n�����㣬��Դ����Ϊs�������Ŵ�0~n-1��������n������50��sС��n��
�Ժ��n����ÿ����n���ÿո������������
���ڵ�i�еĵ�j���������������0�����ʾ��i��������ָ���j�����������ߣ���ȨֵΪ��Ӧ������ֵ��
����������Ϊ0�����ʾû��iָ��j������ߡ�
��i��j��ȵ�ʱ�򣬶�Ӧ������Ҳ��0��

�������ʽ��
ֻ��һ�У�����n-1����������ʾԴ��������ÿ������ (��Ŵ�С����˳��) ���Ե����·�����ȡ�
��������ڴ�Դ������Ӧ�����·���������-1��
ע��: ��������ݼ���1���ո�ָ�, ��β������С�

***/

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

/***   ��Ŀ����_h    ****/

#define INF 0x7fffffff
#define MAXN 5008
#define MAXM 200008

//*** �ڽ�����ͼ�ṹ_h    *********/

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

// ����һ���±�
inline Edge* newEdge(int const adjVex, int const dis, Edge* const next)
{
    Edge* e = (Edge*)malloc(sizeof(Edge));
    if (e == NULL) exit(OVERFLOW);
    e->adjVex = adjVex;
    e->dis = dis;
    e->next = next;
    return e;
}

//����һ����ͼ������ָ��
inline Graph* newGraph()
{
    Graph* g = (Graph*)malloc(sizeof(Graph));
    if (g == NULL) exit(OVERFLOW);
    g->edgeNum = 0;
    g->vexNum = 0;
    return g;
}

// ����ͼ����Ŵ�0��ʼ
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

// ��ͼ������½�㣬��Ŵ�0��ʼ
void addVertex(Graph* g, VertexData const data)
{
    g->vex[g->vexNum].data = data;
    g->vex[g->vexNum].head = newEdge(0, 0, NULL);
    g->vexNum++;
}

// ��ͼ������±�
void addEdge(Graph* g, int const start, int const end, int const distance)
{
    g->edgeNum++;
    g->vex[start].head->next = newEdge(end, distance, g->vex[start].head->next);
}

/*** djstra ��� **/
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
        // ����һ�����õ�ֵ
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

//**** ��Ŀ����
//���ע��

int dis[MAXN];          // ����
int preOnPath[MAXN];    // ǰ��
bool visited[MAXN];     // �Ƿ���ʹ�

int main(int argc, char const **argv) {
    //freopen("p0603.in", "r", stdin);
    //freopen("p0603.out", "w", stdout);

    int i, j;
    int n, s, v;       // ��� 0 �� n-1
    Graph* g = newGraph();
    scanf("%d%d", &n, &s);      // ����
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

    // djkstra ˼·��
    //1. ��ʼ����������dis�������s�ľ�����Ϊ0��������ľ�����Ϊ�����
    //2. ��ʼ����h�������s������У�����Ϊ0
    //3. �Ѳ��գ�ȡ���Ѷ�Ԫ�أ������Ԫ��û�б����ʹ�������Ϊ�ѷ��ʣ�������Ը�Ԫ��
    //4. ������Ԫ�ص������ڽӱߣ�����ñߵ���һ������ľ�����ڸñߵ�Ȩֵ���ϸ�Ԫ�صľ��룬����¸ö���ľ��룬���ö���������
    //5. �ظ�3��4����
    // 
    // djkstra ��ʼ��
    for (i = 0; i < n; i++) {
        dis[i] = INF;
    }
    dis[s] = 0;
    preOnPath[s] = -1;
    Heap* h = newHeap(cmpDjs);
    pushHeap(h, makeDjsNode(0, s));     // �����������

    // djstra ���㣬�����㷨

    Edge* itEdge;
    while (!isEmptyHeap(h)) {           // �Ѳ���
        DjsNode curNode = getTopHeap(h);    // ȡ���Ѷ�Ԫ��
        popHeap(h);
        if (!visited[curNode.pos]) {    // �����Ԫ��û�б����ʹ�
            visited[curNode.pos] = true;    // ���Ϊ�ѷ���
            for (itEdge = g->vex[curNode.pos].head->next; itEdge != NULL; itEdge = itEdge->next) {  // ������Ԫ�ص������ڽӱ�
                if (dis[itEdge->adjVex] > dis[curNode.pos] + itEdge->dis) {     // ����ñߵ���һ������ľ�����ڸñߵ�Ȩֵ���ϸ�Ԫ�صľ���
                    dis[itEdge->adjVex] = dis[curNode.pos] + itEdge->dis;	    // ���¸ö���ľ���
                    preOnPath[itEdge->adjVex] = curNode.pos;                    // ���¸ö����ǰ��
                    pushHeap(h, makeDjsNode(dis[itEdge->adjVex], itEdge->adjVex));  // ���ö���������
                }
            }
        }
    }
    destroyHeap(h);



    // ���
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

