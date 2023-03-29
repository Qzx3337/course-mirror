#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include "TSMatrix.h"

// 打印
void PrintMatrix(TSMatrix M) {
	//printf("矩阵的三元组表示为：\n");
	//printf("行数\t列数\t非零元素个数\n");
	//printf("%d\t%d\t%d\n", M->mu, M->nu, M->tu);
	//printf("行号\t列号\t元素值\n");

	if (M->tu == 0) {
		printf("-1 -1 -1\n");
		return;
	}

	int i;
	for (i = 1; i <= M->tu; i++) {
		printf("%d %d %d\n", M->data[i].row, M->data[i].col, M->data[i].e);
	}
}

// 读入
void ReadMatrix(TSMatrix* M, int tu) {
	int mu, nu;
	mu = nu = 10;
	(*M) = mnew(TSMatrixBody);
	(*M)->mu = mu;
	(*M)->nu = nu;
	(*M)->tu = tu;

	int i;
	for (i = 1; i <= tu; i++) {
		scanf("%d%d%d", &(*M)->data[i].row, &(*M)->data[i].col, &(*M)->data[i].e);
	}

}
