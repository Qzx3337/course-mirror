/*

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

	g_treeNodeCount = 0;
	travPost(tree, swapChilds);
	printf("%d\n", g_treeNodeCount);
	//travPost(tree, printTreeNode);
	//printf("\n");
	printLeaves(tree->root);
	printf("\n");

	destoryBinTree(tree);

	return 0;
}

