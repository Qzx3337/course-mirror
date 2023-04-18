/*

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

