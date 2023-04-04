/*

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "p5.h"

int main() {

	//freopen("p5.in", "r", stdin);
	//freopen("p5.out", "w", stdout);

	GList L1 = createGList();
	readGList(L1);
	
	//printGList(L1);
	//printf("\n");
	int ans = sumGList(L1);
	printf("%d\n", ans);
	destoryGList(L1);

	return 0;
}

