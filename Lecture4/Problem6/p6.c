/*
假设二叉树采用二叉链表方式存储，root指向根结点，p所指结点和q所指结点为二叉树中的两个不同结点，且互不成为根到该结点的路径上的点，编程求解距离它们最近的共同祖先。
language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1

#include "p6.h"

int main() {

	//freopen("p6.in", "r", stdin);
	//freopen("p6.out", "w", stdout);

	char preSec[128], inSec[128];			// 前序遍历序列和中序遍历序列
	gets(preSec);
	gets(inSec);
	BinTree tree = makeTreeFromPreIn(preSec, inSec);	// 从前序遍历序列和中序遍历序列建立二叉树

	//travPre(tree, printTreeNode);				// 输出验证创建结果
	//printf("\n");
	//travIn(tree, printTreeNode);
	//printf("\n");

	char ch1, ch2, ch3;					// 输入的两个结点数据
	scanf("%c%c", &ch1, &ch2);
	if (getLCA(tree, ch1, ch2, &ch3)) {			// 获取两个结点的最近公共祖先
		printf("%c\n", ch3);
	}
	else {
		printf("NULL\n");
	}
	
	destoryBinTree(tree);				// 销毁二叉树

	return 0;
}

