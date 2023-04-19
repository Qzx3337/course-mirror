/*

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "test_BinTree.h"

int main() {

	freopen("test_BinTree.in", "r", stdin);
	//freopen("test_BinTree.out", "w", stdout);

	char preSeq[128];
	gets(preSeq);
	BinTree tree = createBinTree_Pre(preSeq);

	travPre(tree, printTreeNode);
	printf("\n");
	travIn(tree, printTreeNode);
	printf("\n");
	travPost(tree, printTreeNode);
	printf("\n");
	travLevel(tree, printTreeNode);
	printf("\n");

	destoryBinTree(tree);

	return 0;
}

