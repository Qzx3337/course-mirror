#pragma once

#include <stdlib.h>

#define STACK_SIZE 10000
#define true 1
#define false 0

#ifndef ElemType
#define ElemType int
#endif // !ElemType

typedef struct StackBody {
	ElemType elem[STACK_SIZE];
	int top;
} StackBody, * Stack;

/******** ֻ���ӿ� **********/

int IsEmptySta(Stack s);
int IsFull(Stack s);
unsigned int GetSizeSta(Stack s);
ElemType GetTop(Stack s);

/******** ��д�ӿ� ************/

void InitStack(Stack* s);
int PopStack(Stack s);
int PushStack(Stack s, ElemType x);

/******** ʵ�� *********/

/* ��ʼ�� */
void InitStack(Stack* s) {
	*s = (Stack)malloc(sizeof(StackBody));
	(*s)->top = 0;
}

/* �п� */
int IsEmptySta(Stack s) {
	return (!s->top);
}

/* ���� */
int IsFull(Stack s) {
	return !(s->top < STACK_SIZE);
}

/* ��ջ */
int PopStack(Stack s) {
	if (s->top == 0) return false;
	s->top--;
	return true;
}

/* ��ջ */
int PushStack(Stack s, ElemType x) {
	if (IsFull(s)) return false;
	s->elem[s->top++] = x;
	return true;
}

/* ��ȡԪ�ظ��� */
inline int GetSizeSta(Stack s) {
	return s->top;
}

/* ��ȡջ��Ԫ�� */
ElemType GetTop(Stack s) {
	return s->elem[s->top - 1];
}

