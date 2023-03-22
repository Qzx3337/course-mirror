#pragma once

#include <stdlib.h>
#define true 1
#define false 0

#ifndef StackElemType
#define StackElemType int
#endif // !StackElemType

typedef struct LinkStackNode {
	StackElemType data;
	struct LinkStackNode* next;
} LinkStackNode;

typedef struct LinkStackBody{
	int size;
	LinkStackNode* top;
} LinkStackBody,*Stack;


/******** 只读接口 **********/

int isEmpty(Stack s);
int getStaSize(Stack s);
StackElemType getTop(Stack s);

/******** 可写接口 ************/

void initSta(Stack* s);
int popSta(Stack s);
void pushSta(Stack s, StackElemType data);


/******** 实现  **************/

int isEmpty(Stack s) {
	return s->size == 0;
}

inline int getStaSize(Stack s) {
	return s->size;
}

StackElemType getTop(Stack s) {
	return s->top->next->data;
}

// 初始化栈
void initSta(Stack* sta) {
	(*sta) = (Stack)malloc(sizeof(LinkStackBody));
	(*sta)->size = 0;
	(*sta)->top = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	(*sta)->top->next = NULL;
}

// 出栈，成功返回 1 ，失败返回 0 
inline int popSta(Stack sta) {
	if (sta->size == 0) return false;

	//EraseNext(sta->top);
	LinkStackNode* oldNode = sta->top->next;
	sta->top->next = oldNode->next;
	free(oldNode);

	sta->size--;
	return true;
}

// 压栈
inline void pushSta(Stack sta, StackElemType data) {
	LinkStackNode* newNode = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	newNode->data = data;

	//InsertAsNext(sta->top, newNode);
	newNode->next = sta->top->next;
	sta->top->next = newNode;

	sta->size++;
}
