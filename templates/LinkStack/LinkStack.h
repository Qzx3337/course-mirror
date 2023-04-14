/*
��ʽջ�Ľӿ�
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


/******** ֻ���ӿ� **********/

bool isEmpty(Stack const s);
int getStaSize(Stack const s);
StackElemType getTop(Stack const s);

/******** ��д�ӿ� ************/

Stack newStack();
bool popSta(Stack sta);
void pushSta(Stack sta, StackElemType const data);


/******** ʵ��  **************/

bool isEmpty(Stack s)
{
	return s->size == 0;
}

inline int getStaSize(Stack s)
{
	return s->size;
}

StackElemType getTop(Stack s)
{
	return s->top->next->data;
}

// �½�ջ
Stack newStack()
{
	Stack sta = (Stack)malloc(sizeof(_LinkStack));
	if (!sta) exit(OVERFLOW);				// ����ʧ��
	sta->size = 0;
	sta->top = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	if (sta->top == NULL) exit(OVERFLOW);
	sta->top->next = NULL;
	return sta;
}

// ��ջ���ɹ����� 1 ��ʧ�ܷ��� 0 
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

// ѹջ
inline void pushSta(Stack sta, StackElemType const data)
{
	LinkStackNode* newNode = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	if (newNode == NULL) exit(OVERFLOW);			// ����ʧ��
	newNode->data = data;

	//InsertAsNext(sta->top, newNode);
	newNode->next = sta->top->next;
	sta->top->next = newNode;

	sta->size++;
}
