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

	BinTree tree = createBinTree_Pre(posSeq);	// 先序创建树结点

	// 输出验证创建结果

	//travPre(tree, printTreeNode);
	//printf("\n");
	//travIn(tree, printTreeNode);
	//printf("\n");
	//travPost(tree, printTreeNode);
	//printf("\n");
	//travLevel(tree, printTreeNode);
	//printf("\n");

	// 交换左右子树，并统计叶子数量

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

