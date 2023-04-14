#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkStack.h"

int main() {

	int a, m;			// 十进制的 a，换成 m进制
	scanf("%d%d", &a, &m);

	Stack s;			// 定义栈
	initSta(&s);		// 初始化栈

	while (a) {			// 按位取值，存入栈中
		pushSta(s, a % m);
		a /= m;
	}

	// if (m == 2 && GetTop(&s) == 1) printf("0");

	while (!isEmpty(s)) {
		// 按照出栈顺序输出
		printf("_%d", getTop(s));
		popSta(s);
	}

	return 0;
}


