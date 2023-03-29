#pragma once

#define mnew(typeName) ( (typeName*)malloc(sizeof(typeName)) )
#define false 0
#define true 1

// ��׼C���ԣ���Ԫ���ʾϡ�����ģ��
#define MAXSIZE 100

#ifndef ElemType
#define ElemType int
#endif // !ElemType


typedef struct {
	int row, col;
	ElemType e;
}Triple;

typedef struct {
	Triple data[MAXSIZE + 1];
	int mu, nu, tu;
}*TSMatrix, TSMatrixBody;

// ��ʼ��
void InitMatrix(TSMatrix* M) {
	(*M) = mnew(TSMatrixBody);
	(*M)->mu = 0;
	(*M)->nu = 0;
	(*M)->tu = 0;
}

// ����
void DestroyMatrix(TSMatrix* M) {
	free(*M);
	(*M) = NULL;
}

// ��ֵ
void Assign(TSMatrix M, int mu, int nu, int tu, Triple* data) {
	M->mu = mu;
	M->nu = nu;
	M->tu = tu;
	int i;
	for (i = 0; i < tu; i++) {
		M->data[i] = data[i];
	}
}


// �ӷ�������Q��ָ���κ�ʵ��
int AddMatrix(TSMatrix M, TSMatrix N, TSMatrix* Q) {
	if (M->mu != N->mu || M->nu != N->nu) {
		return false;
	}
	(*Q) = mnew(TSMatrixBody);
	(*Q)->mu = M->mu;
	(*Q)->nu = M->nu;
	(*Q)->tu = 0;
	int i = 1, j = 1;
	while (i <= M->tu && j <= N->tu) {				// �������������ص�����
		if (M->data[i].row < N->data[j].row) {		// ��ͬ��
			(*Q)->tu++;
			(*Q)->data[(*Q)->tu] = M->data[i];
			i++;
		}
		else if (M->data[i].row > N->data[j].row) {
			(*Q)->tu++;
			(*Q)->data[(*Q)->tu] = N->data[j];
			j++;
		}
		else {										// ͬ��
			if (M->data[i].col < N->data[j].col) {	// ��ͬ��
				(*Q)->tu++;
				(*Q)->data[(*Q)->tu] = M->data[i];
				i++;
			}
			else if (M->data[i].col > N->data[j].col) {
				(*Q)->tu++;
				(*Q)->data[(*Q)->tu] = N->data[j];
				j++;
			}
			else {									// ͬ��ͬ��
				(*Q)->tu++;
				(*Q)->data[(*Q)->tu].row = M->data[i].row;
				(*Q)->data[(*Q)->tu].col = M->data[i].col;
				(*Q)->data[(*Q)->tu].e = M->data[i].e + N->data[j].e;
				i++;
				j++;
			}
		}
		if (0 == (*Q)->data[(*Q)->tu].e) (*Q)->tu--;	// ����������ӣ����Ϊ0�����洢
	}
	while (i <= M->tu) {							// ����ʣ�ಿ��
		(*Q)->tu++;
		(*Q)->data[(*Q)->tu] = M->data[i];
		i++;
	}
	while (j <= N->tu) {
		(*Q)->tu++;
		(*Q)->data[(*Q)->tu] = N->data[j];
		j++;
	}
	return true;
}

// Path: Lecture3\Problem1\p1.c
