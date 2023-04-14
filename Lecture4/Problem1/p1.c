/*

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "p1.h"

int main() {

	freopen("p1.in", "r", stdin);
	//freopen("p1.out", "w", stdout);
	char preSeq[MAXLEN];
	gets(preSeq);

	BinTree tree = createBinTree_Pre(preSeq);	// 先序创建树结点

	//printf("\n---\n");

	travPre(tree, printTreeNode);
    printf("\n");
	travIn(tree, printTreeNode);
	printf("\n");
	travPost(tree, printTreeNode);
	printf("\n");
	//travLevel(tree, printTreeNode);
	//printf("\n");

	return 0;
}

