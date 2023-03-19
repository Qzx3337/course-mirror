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

/******** 只读接口 **********/

int IsEmpty(Stack* s);
int IsFull(Stack* s);
unsigned int GetSize(Stack* s);
ElemType GetTop(Stack* s);

/******** 可写接口 ************/

void InitStack(Stack* s);
int PopStack(Stack* s);
int PushStack(Stack* s, ElemType x);

/******** 实现 *********/

/* 初始化 */
void InitStack(Stack* s) {
	s->top = 0;
}

/* 判空 */
int IsEmpty(Stack* s) {
	return (!s->top);
}

/* 判满 */
int IsFull(Stack* s) {
	return !(s->top < STACK_SIZE);
}

/* 出栈 */
int PopStack(Stack* s) {
	if (IsEmpty(s)) return false;
	s->top--;
	return true;
}

/* 入栈 */
int PushStack(Stack* s, ElemType x) {
	if (IsFull(s)) return false;
	s->elem[s->top++] = x;
	return true;
}

/* 获取元素个数 */
unsigned int GetSize(Stack* s) {
	return s->top;
}

/* 获取栈顶元素 */
ElemType GetTop(Stack* s) {
	return s->elem[s->top - 1];
}

