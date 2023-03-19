#pragma once

#define STACK_SIZE 10000
#define true 1
#define false 0

#ifndef ElemType
#define ElemType int
#endif // !ElemType

typedef struct {
	ElemType elem[STACK_SIZE];
	int top;
}Stack;

/******** ֻ���ӿ� **********/

int IsEmpty(Stack* s);
int IsFull(Stack* s);
unsigned int GetSize(Stack* s);
ElemType GetTop(Stack* s);

/******** ��д�ӿ� ************/

void InitStack(Stack* s);
int PopStack(Stack* s);
int PushStack(Stack* s, ElemType x);

/******** ʵ�� *********/

/* ��ʼ�� */
void InitStack(Stack* s) {
	s->top = 0;
}

/* �п� */
int IsEmpty(Stack* s) {
	return (!s->top);
}

/* ���� */
int IsFull(Stack* s) {
	return !(s->top < STACK_SIZE);
}

/* ��ջ */
int PopStack(Stack* s) {
	if (IsEmpty(s)) return false;
	s->top--;
	return true;
}

/* ��ջ */
int PushStack(Stack* s, ElemType x) {
	if (IsFull(s)) return false;
	s->elem[s->top++] = x;
	return true;
}

/* ��ȡԪ�ظ��� */
unsigned int GetSize(Stack* s) {
	return s->top;
}

/* ��ȡջ��Ԫ�� */
ElemType GetTop(Stack* s) {
	return s->elem[s->top - 1];
}

