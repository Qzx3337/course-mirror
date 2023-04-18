/*
给出一个按照“扩展遍历序列”的扩展先序遍历序列字符串，'.' 代表空的子节点，大写字母代表节点内容。
请通过这个字符串建立二叉树，并计算及输出该二叉树的高度。

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "p2.h"

int main() {

	//freopen("p2.in", "r", stdin);
	//freopen("p2.out", "w", stdout);

	char preSeq[MAXLEN];
	gets(preSeq);

	BinTree tree = createBinTree_Pre(preSeq);	// 先序创建树结点

	int depth = getTreeDepth(tree);
	printf("%d", depth);
	
	return 0;
}

