/*
链式栈的接口
*/

#pragma once

#ifndef StackElemType
#define StackElemType int
#endif // !StackElemType
#ifndef OVERFLOW
#define OVERFLOW 3
#endif // !OVERFLOW


typedef struct LinkStackNode {
	StackElemType data;
	struct LinkStackNode* next;
} LinkStackNode;

typedef struct _LinkStack {
	int size;
	LinkStackNode* top;
} _LinkStack, * Stack;


/******** 只读接口 **********/

bool isEmptySta(Stack const s);
int getSizeSta(Stack const s);
StackElemType getTopSta(Stack const s);

/******** 可写接口 ************/

Stack newStack();
void destoryStack(Stack sta);
bool popSta(Stack sta);
void pushSta(Stack sta, StackElemType const data);


/******** 实现  **************/

inline bool isEmptySta(Stack s)
{
	return s->size == 0;
}

inline int getSizeSta(Stack s)
{
	return s->size;
}

inline StackElemType getTopSta(Stack s)
{
	return s->top->next->data;
}

// 新建栈
Stack newStack()
{
	Stack sta = (Stack)malloc(sizeof(_LinkStack));
	if (!sta) exit(OVERFLOW);				// 分配失败
	sta->size = 0;
	sta->top = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	if (sta->top == NULL) exit(OVERFLOW);
	sta->top->next = NULL;
	return sta;
}

inline void destoryStack(Stack sta)
{
	if(sta==NULL) return;
	while (sta->size > 0) {
		popSta(sta);
	}
	free(sta->top);
	free(sta);
}

// 出栈，成功返回 1 ，失败返回 0 
inline bool popSta(Stack sta)
{
	if (sta->size == 0) return false;

	//EraseNext(sta->top);
	LinkStackNode* oldNode = sta->top->next;
	sta->top->next = oldNode->next;
	free(oldNode);

	sta->size--;
	return true;
}

// 压栈
inline void pushSta(Stack sta, StackElemType const data)
{
	LinkStackNode* newNode = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	if (newNode == NULL) exit(OVERFLOW);			// 分配失败
	newNode->data = data;

	//InsertAsNext(sta->top, newNode);
	newNode->next = sta->top->next;
	sta->top->next = newNode;

	sta->size++;
}
