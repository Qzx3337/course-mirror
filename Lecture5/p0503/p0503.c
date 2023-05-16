/*
3、哈夫曼编码
读入n个字符所对应的权值，构造一棵哈夫曼树，自底向上生成每一个字符对应的哈夫曼编码，并依次输出。
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
#define MAXN 20				// 最大字符数
#define MAXM (2 * MAXN - 1)		// 最大结点数

// 哈夫曼树结点结构体
typedef struct HTNode
{
	int weight;                 // 结点的权值
	int father;                 // 双亲的下标
	int LChild;                 // 左孩子结点的下标
	int RChild;                 // 右孩子结点的下标
} HTNode;

int n;		// 字符数
HTNode HuffmanTree[MAXM + 1];		// 哈夫曼树

int main() {
	//freopen("p0503.in", "r", stdin);
	//freopen("p0503.out", "w", stdout);

	// 读入

	int i, j, k;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &HuffmanTree[i].weight);		// 初始化
		HuffmanTree[i].father = 0;
		HuffmanTree[i].LChild = 0;
		HuffmanTree[i].RChild = 0;
	}

	// 构造哈夫曼树

	int min1, min2;		// 最小的两个权值
	int x1, x2;			// 最小的两个权值结点的下标
	for (i = n + 1; i <= 2 * n - 1; i++) {		 // 一共需要构造n-1次
		min1 = min2 = INF;		// 寻找最小的两个权值
		x1 = x2 = 0;
		for (j = 1; j < i; j++) {
			if (HuffmanTree[j].father == 0) {
				if (HuffmanTree[j].weight < min1) {
					min2 = min1;
					x2 = x1;
					min1 = HuffmanTree[j].weight;
					x1 = j;
				}
				else if (HuffmanTree[j].weight < min2) {
					min2 = HuffmanTree[j].weight;
					x2 = j;
				}
			}
		}
		// 合并
		HuffmanTree[x1].father = i;
		HuffmanTree[x2].father = i;
		HuffmanTree[i].LChild = x1;
		HuffmanTree[i].RChild = x2;
		HuffmanTree[i].weight = min1 + min2;
	}

	// 输出

	char code[MAXN + 1];
    code[n] = '\0';
	for (i = 1; i <= n; i++) {		// 依次输出每个字符的编码
		j = i;					// 从叶子结点开始
		k = n - 1;				// 编码的最后一位
		while (HuffmanTree[j].father != 0) {		// 一直向上直到根结点
			if (HuffmanTree[HuffmanTree[j].father].LChild == j) {
				code[k] = '0';		//  左孩子编码为0
			}
			else if(HuffmanTree[HuffmanTree[j].father].RChild == j){
				code[k] = '1';		// 右孩子编码为1
			}
			else {
				assert(false);		// 非法 // 一般不会出现
			}
			k--;			// 继续向上
			j = HuffmanTree[j].father;
		}
		printf("%s\n", code + k + 1);
	}


	return 0;
}

