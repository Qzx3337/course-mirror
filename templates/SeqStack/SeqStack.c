/**********************

【问题描述】

请使用顺序栈实现十进制整数到r进制（2<=r<=8）的转换。

【输入形式】

第一行为待转换的十进制整数
第二行为代表进制的整数

【样例输入】

123
8

【样例输出】

173

language: C

*************************/
#define _CRT_SECURE_NO_WARNINGS 1

#include "SeqStack.h"
#include "stdio.h"

int main() {

	int a, m;			// 十进制的 a，换成 m进制
	scanf("%d%d", &a, &m);

	Stack s;			// 定义栈
	InitStack(&s);		// 初始化栈

	while (a) {			// 按位取值，存入栈中
		PushStack(s, a % m);
		a /= m;
	}

	// if (m == 2 && GetTop(&s) == 1) printf("0");

	while (!IsEmpty(s)) {
		// 按照出栈顺序输出
		printf("%d", GetTop(s));
		PopStack(s);
	}

	return 0;
}




