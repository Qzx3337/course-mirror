/*

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

