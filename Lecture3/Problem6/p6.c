/*******************
* 
* 交叉链表矩阵模板
* 
* language: C.
* 
**********************/
#define _CRT_SECURE_NO_WARNINGS 1
#include "p6.h"

int main() {

	//freopen("p6.in", "r", stdin);
	//freopen("p6.out", "w", stdout);


	XLLMatPtr mat1 = createXLLMat(10, 10);	// 创建两个矩阵
	XLLMatPtr mat2 = createXLLMat(10, 10);

	int len1, len2;
	scanf("%d%d", &len1, &len2);
	readXLLMat(mat1, len1);					// 读入矩阵
	readXLLMat(mat2, len2);

	XLLMatPtr mat3 = addXLLMat(mat1, mat2);	// 矩阵相加
	
	if (mat3->len) printXLLMat(mat3);		// 输出矩阵
	else printf("-1 -1 -1\n");

	destoryXLLMat(mat1);					// 释放矩阵
	destoryXLLMat(mat2);
	destoryXLLMat(mat3);

	return 0;
}

