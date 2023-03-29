#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include "TSMatrix.h"

// ��ӡ
void PrintMatrix(TSMatrix M) {
	//printf("�������Ԫ���ʾΪ��\n");
	//printf("����\t����\t����Ԫ�ظ���\n");
	//printf("%d\t%d\t%d\n", M->mu, M->nu, M->tu);
	//printf("�к�\t�к�\tԪ��ֵ\n");

	if (M->tu == 0) {
		printf("-1 -1 -1\n");
		return;
	}

	int i;
	for (i = 1; i <= M->tu; i++) {
		printf("%d %d %d\n", M->data[i].row, M->data[i].col, M->data[i].e);
	}
}

// ����
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
