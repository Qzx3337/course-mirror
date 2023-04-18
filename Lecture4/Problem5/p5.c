/*
题目：
二叉树按照二叉链表的方式存储。编写程序，计算二叉树中叶子结点的数目并输出；
编写程序，将二叉树的每个结点的左、右子树进行交换，
请注意不是只交换结点的data值，而是左、右孩子指针指向的交换，
最后输出交换后的二叉树的后序遍历序列。

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

	g_treeNodeCount = 0;				// 叶子数量
	travPost(tree, swapChilds);			// 后序遍历，交换左右子树
	printf("%d\n", g_treeNodeCount);	// 输出叶子数量
	//travPost(tree, printTreeNode);
	//printf("\n");
	printLeaves(tree->root);			// 输出带拓展的遍历序列
	printf("\n");

	destoryBinTree(tree);

	return 0;
}

