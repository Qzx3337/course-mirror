/*
题目：
 给出一个按照“扩展遍历序列”的扩展先序遍历序列字符串，'#' 代表空的子节点，大写字母代表节点内容。
 请通过这个字符串建立二叉树，并使用栈实现非递归的中序遍历该二叉树。

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "p4.h"
#define MAXLEN 128

int main() {

	//freopen("p4.in", "r", stdin);
	//freopen("p4.out", "w", stdout);

	char posSeq[MAXLEN];
	gets(posSeq);

	BinTree tree = createBinTree_Pre(posSeq);	// 先序创建树结点

	//travPre(tree, printTreeNode);
	//printf("\n");
	//travIn(tree, printTreeNode);
	//printf("\n");
	//travPost(tree, printTreeNode);
	//printf("\n");
	//travLevel(tree, printTreeNode);
	//printf("\n");
	travIn_Sta(tree, printTreeNode);
	printf("\n");

	destoryBinTree(tree);

	return 0;
}

