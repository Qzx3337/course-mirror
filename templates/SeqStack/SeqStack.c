/**********************

������������

��ʹ��˳��ջʵ��ʮ����������r���ƣ�2<=r<=8����ת����

��������ʽ��

��һ��Ϊ��ת����ʮ��������
�ڶ���Ϊ������Ƶ�����

���������롿

123
8

�����������

173

language: C

*************************/
#define _CRT_SECURE_NO_WARNINGS 1

#include "SeqStack.h"
#include "stdio.h"

int main() {

	int a, m;			// ʮ���Ƶ� a������ m����
	scanf("%d%d", &a, &m);

	Stack s;			// ����ջ
	InitStack(&s);		// ��ʼ��ջ

	while (a) {			// ��λȡֵ������ջ��
		PushStack(s, a % m);
		a /= m;
	}

	// if (m == 2 && GetTop(&s) == 1) printf("0");

	while (!IsEmpty(s)) {
		// ���ճ�ջ˳�����
		printf("%d", GetTop(s));
		PopStack(s);
	}

	return 0;
}




