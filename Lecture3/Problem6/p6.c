/*******************
* 
* �����������ģ��
* 
* language: C.
* 
**********************/
#define _CRT_SECURE_NO_WARNINGS 1
#include "p6.h"

int main() {

	//freopen("p6.in", "r", stdin);
	//freopen("p6.out", "w", stdout);


	XLLMatPtr mat1 = createXLLMat(10, 10);	// ������������
	XLLMatPtr mat2 = createXLLMat(10, 10);

	int len1, len2;
	scanf("%d%d", &len1, &len2);
	readXLLMat(mat1, len1);					// �������
	readXLLMat(mat2, len2);

	XLLMatPtr mat3 = addXLLMat(mat1, mat2);	// �������
	
	if (mat3->len) printXLLMat(mat3);		// �������
	else printf("-1 -1 -1\n");

	destoryXLLMat(mat1);					// �ͷž���
	destoryXLLMat(mat2);
	destoryXLLMat(mat3);

	return 0;
}

