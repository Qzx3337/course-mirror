#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkStack.h"

int main() {

	int a, m;			// ʮ���Ƶ� a������ m����
	scanf("%d%d", &a, &m);

	Stack s;			// ����ջ
	initSta(&s);		// ��ʼ��ջ

	while (a) {			// ��λȡֵ������ջ��
		pushSta(s, a % m);
		a /= m;
	}

	// if (m == 2 && GetTop(&s) == 1) printf("0");

	while (!isEmpty(s)) {
		// ���ճ�ջ˳�����
		printf("_%d", getTop(s));
		popSta(s);
	}

	return 0;
}


