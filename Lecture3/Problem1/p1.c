/*
*  3.1 利用三元组完成矩阵加法
* 
* language: C.
*/

#include "p1.h"

int main() {

	int tu1, tu2;
	scanf("%d%d", &tu1, &tu2);

	TSMatrix M, N, Q;
	ReadMatrix(&M, tu1);
	ReadMatrix(&N, tu2);

	//PrintMatrix(M);

	if (AddMatrix(M, N, &Q)) {
		PrintMatrix(Q);
	}
	else {
		printf("ERROR");
	}

	DestroyMatrix(&M);
	DestroyMatrix(&N);
	DestroyMatrix(&Q);

	//printf("fin\n");
	return 0;
}

