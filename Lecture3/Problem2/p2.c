/*******************
* 
* language: C.
* 
**********************/
#define _CRT_SECURE_NO_WARNINGS 1
#include "p2.h"
#define MAXN 1000

int main() {

	//freopen("p2.in", "r", stdin);
	//freopen("p2.out", "w", stdout);

    int n, k;
    int a[MAXN];
    scanf("%d%d", &k, &n);
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    shiftL(a, n, k);
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

	return 0;
}

