/*
��Ŀ��
���������ն�������ķ�ʽ�洢����д���򣬼����������Ҷ�ӽ�����Ŀ�������
��д���򣬽���������ÿ�����������������н�����
��ע�ⲻ��ֻ��������dataֵ���������Һ���ָ��ָ��Ľ�����
������������Ķ������ĺ���������С�

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "p5.h"
#define MAXLEN 128
int g_treeNodeCount;

int main() {

	//freopen("p5.in", "r", stdin);
	//freopen("p5.out", "w", stdout);

	char posSeq[MAXLEN];
	gets(posSeq);

	BinTree tree = createBinTree_Pre(posSeq);	// ���򴴽������

	// �����֤�������

	//travPre(tree, printTreeNode);
	//printf("\n");
	//travIn(tree, printTreeNode);
	//printf("\n");
	//travPost(tree, printTreeNode);
	//printf("\n");
	//travLevel(tree, printTreeNode);
	//printf("\n");

	// ����������������ͳ��Ҷ������

	g_treeNodeCount = 0;				// Ҷ������
	travPost(tree, swapChilds);			// ���������������������
	printf("%d\n", g_treeNodeCount);	// ���Ҷ������
	//travPost(tree, printTreeNode);
	//printf("\n");
	printLeaves(tree->root);			// �������չ�ı�������
	printf("\n");

	destoryBinTree(tree);

	return 0;
}

