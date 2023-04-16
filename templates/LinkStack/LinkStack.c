#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkStack.h"

int main() {

	int a, m;			// 十进制的 a，转换成 m进制
	scanf("%d%d", &a, &m);

	Stack s = newStack();

	while (a) {			// 按位取值，存入栈中
		pushSta(s, a % m);
		a /= m;
	}

	// if (m == 2 && GetTop(&s) == 1) printf("0");

	while (!isStaEmpty(s)) {
		// 按照出栈顺序输出
		printf("_%d", getStaTop(s));
		popSta(s);
	}

	destoryStack(s);

	return 0;
}


