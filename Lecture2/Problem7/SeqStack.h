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

/******** 只读接口 **********/

int IsEmptySta(Stack s);
int IsFull(Stack s);
unsigned int GetSizeSta(Stack s);
ElemType GetTop(Stack s);

/******** 可写接口 ************/

void InitStack(Stack* s);
int PopStack(Stack s);
int PushStack(Stack s, ElemType x);

/******** 实现 *********/

/* 初始化 */
void InitStack(Stack* s) {
	*s = (Stack)malloc(sizeof(StackBody));
	(*s)->top = 0;
}

/* 判空 */
int IsEmptySta(Stack s) {
	return (!s->top);
}

/* 判满 */
int IsFull(Stack s) {
	return !(s->top < STACK_SIZE);
}

/* 出栈 */
int PopStack(Stack s) {
	if (s->top == 0) return false;
	s->top--;
	return true;
}

/* 入栈 */
int PushStack(Stack s, ElemType x) {
	if (IsFull(s)) return false;
	s->elem[s->top++] = x;
	return true;
}

/* 获取元素个数 */
inline int GetSizeSta(Stack s) {
	return s->top;
}

/* 获取栈顶元素 */
ElemType GetTop(Stack s) {
	return s->elem[s->top - 1];
}

