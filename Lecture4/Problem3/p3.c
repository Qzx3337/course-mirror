/*

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "p3.h"
#define MAXLEN 128

int main() {

	//freopen("p3.in", "r", stdin);
	//freopen("p3.out", "w", stdout);

	char posSeq[MAXLEN];
	gets(posSeq);

	BinTree tree = createBinTree_Pos(posSeq);	// 先序创建树结点

	//travPre(tree, printTreeNode);
	//printf("\n");
	//travIn(tree, printTreeNode);
	//printf("\n");
	//travPost(tree, printTreeNode);
	//printf("\n");
	//travLevel(tree, printTreeNode);
	//printf("\n");

	//printf("\n--------------\n\n");

	printTransTree(tree);

	destoryBinTree(tree);
	
	return 0;
}

