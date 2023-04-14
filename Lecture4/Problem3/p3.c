/*

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "p3.h"

int main() {

	//freopen("p2.in", "r", stdin);
	//freopen("p2.out", "w", stdout);

	char preSeq[MAXLEN];
	gets(preSeq);

	BinTree tree = createBinTree_Pre(preSeq);	// ���򴴽������

	travPre(tree, printTreeNode);
	printf("\n");
	travIn(tree, printTreeNode);
	printf("\n");
	travPost(tree, printTreeNode);
	printf("\n");
	travLevel(tree, printTreeNode);
	printf("\n");
	
	return 0;
}

