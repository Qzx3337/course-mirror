/*

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "p5.h"
#define MAXLEN 128

int main() {

	//freopen("p5.in", "r", stdin);
	//freopen("p5.out", "w", stdout);

	char posSeq[MAXLEN];
	gets(posSeq);

	BinTree tree = createBinTree_Pre(posSeq);	// ���򴴽������

	//travPre(tree, printTreeNode);
	//printf("\n");
	//travIn(tree, printTreeNode);
	//printf("\n");
	travPost(tree, printTreeNode);
	printf("\n");
	//travLevel(tree, printTreeNode);
	//printf("\n");

	destoryBinTree(tree);


	return 0;
}

