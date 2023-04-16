/*

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "p6.h"



int main() {

	//freopen("p6.in", "r", stdin);
	//freopen("p6.out", "w", stdout);

	char preSec[128], inSec[128];
	gets(preSec);
	gets(inSec);
	BinTree tree = makeTreeFromPreIn(preSec, inSec);

	char ch1, ch2;
	scanf("%c%c", &ch1, &ch2);
	int lca = getLCA(tree, ch1, ch2);
	printf("%d\n", lca);



	return 0;
}

