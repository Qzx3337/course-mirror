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

�����棬��ʹ�öѲ�����̱ߣ�����ʹ��ֱ�ӷ�

TODO: û���� locateVex() ����Ѱͨ�� id ���ҽ�㣬����ֱ��ʹ���������±꣬

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

//********* !Graph_h

//**** ��Ŀ����
//���ע��

int dis[MAXN];          // ����
int preOnPath[MAXN];    // ǰ��
bool visited[MAXN];     // �Ƿ���ʹ�

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

    // djkstra ��ʼ��
    for (i = 0; i < n; i++) {
        dis[i] = INF;
    }
    dis[s] = 0;
    preOnPath[s] = -1;

    // djstra ���㣬�����㷨

    Edge* itEdge;
    int curNode;
    while (true) {
        curNode = getClosest(g);
        if (curNode == -1) break;   // ���û���ҵ������˳�
        visited[curNode] = true;    // ���Ϊ�ѷ���
        for (itEdge = g->vex[curNode].head->next; itEdge != NULL; itEdge = itEdge->next) {  // ������Ԫ�ص������ڽӱ�
            if (dis[itEdge->adjVex] > dis[curNode] + itEdge->dis) {     // ����ñߵ���һ������ľ�����ڸñߵ�Ȩֵ���ϸ�Ԫ�صľ���
                dis[itEdge->adjVex] = dis[curNode] + itEdge->dis;	    // ���¸ö���ľ���
                preOnPath[itEdge->adjVex] = curNode;                    // ���¸ö����ǰ��
            }
        }
    }

    // �ܽ�djstra�㷨˼·
    // 1.��ʼ�����е�ľ���Ϊ��������ľ���Ϊ0
    // 2.����㿪ʼ��ÿ��ѡ��һ��������С�ĵ㣬���Ϊ�ѷ���
    // 3.�����õ�������ڽӱߣ�����ñߵ���һ������ľ�����ڸñߵ�Ȩֵ���ϸ�Ԫ�صľ��룬����¸ö���ľ��룬������ǰ��
    // 4.�ظ�2��3���裬ֱ�����е㶼���ʹ�

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

