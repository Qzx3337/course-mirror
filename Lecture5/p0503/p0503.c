/*
3������������
����n���ַ�����Ӧ��Ȩֵ������һ�ù����������Ե���������ÿһ���ַ���Ӧ�Ĺ��������룬�����������
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
#define MAXN 20				// ����ַ���
#define MAXM (2 * MAXN - 1)		// �������

// �����������ṹ��
typedef struct HTNode
{
	int weight;                 // ����Ȩֵ
	int father;                 // ˫�׵��±�
	int LChild;                 // ���ӽ����±�
	int RChild;                 // �Һ��ӽ����±�
} HTNode;

int n;		// �ַ���
HTNode HuffmanTree[MAXM + 1];		// ��������

int main() {
	//freopen("p0503.in", "r", stdin);
	//freopen("p0503.out", "w", stdout);

	// ����

	int i, j, k;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &HuffmanTree[i].weight);		// ��ʼ��
		HuffmanTree[i].father = 0;
		HuffmanTree[i].LChild = 0;
		HuffmanTree[i].RChild = 0;
	}

	// �����������

	int min1, min2;		// ��С������Ȩֵ
	int x1, x2;			// ��С������Ȩֵ�����±�
	for (i = n + 1; i <= 2 * n - 1; i++) {		 // һ����Ҫ����n-1��
		min1 = min2 = INF;		// Ѱ����С������Ȩֵ
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
		// �ϲ�
		HuffmanTree[x1].father = i;
		HuffmanTree[x2].father = i;
		HuffmanTree[i].LChild = x1;
		HuffmanTree[i].RChild = x2;
		HuffmanTree[i].weight = min1 + min2;
	}

	// ���

	char code[MAXN + 1];
    code[n] = '\0';
	for (i = 1; i <= n; i++) {		// �������ÿ���ַ��ı���
		j = i;					// ��Ҷ�ӽ�㿪ʼ
		k = n - 1;				// ��������һλ
		while (HuffmanTree[j].father != 0) {		// һֱ����ֱ�������
			if (HuffmanTree[HuffmanTree[j].father].LChild == j) {
				code[k] = '0';		//  ���ӱ���Ϊ0
			}
			else if(HuffmanTree[HuffmanTree[j].father].RChild == j){
				code[k] = '1';		// �Һ��ӱ���Ϊ1
			}
			else {
				assert(false);		// �Ƿ� // һ�㲻�����
			}
			k--;			// ��������
			j = HuffmanTree[j].father;
		}
		printf("%s\n", code + k + 1);
	}


	return 0;
}

