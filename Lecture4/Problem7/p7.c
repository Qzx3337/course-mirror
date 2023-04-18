/*
给出一个按照“扩展遍历序列”的扩展先序遍历序列字符串，'.' 代表空的子节点，大写字母代表节点内容。
请通过这个字符串建立二叉树，并层次遍历该二叉树。

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "p7.h"

int main() {

	//freopen("p7.in", "r", stdin);
	//freopen("p7.out", "w", stdout);

	char strPre[128];
	gets(strPre);
	BinTree tree = createBinTree_Pre(strPre);
	travLevel(tree, printTreeNode);
	printf("\n");
	destoryBinTree(tree);

	return 0;
}

