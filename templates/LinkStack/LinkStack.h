/*
* @Description: ��ʽջ�Ľӿ�
*/

#pragma once

#include <stdlib.h>
#define true 1
#define false 0

#define mcreate(type, n) ((type)*)malloc((n)*sizeof((type)))
#define mcreate(type) ((type)*)malloc(sizeof((type)))

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


/******** ֻ���ӿ� **********/

int isEmpty(Stack s);
int getStaSize(Stack s);
StackElemType getTop(Stack s);

/******** ��д�ӿ� ************/

int initSta(Stack* s);
int popSta(Stack s);
int pushSta(Stack s, StackElemType data);


/******** ʵ��  **************/

int isEmpty(Stack s) {
	return s->size == 0;
}

inline int getStaSize(Stack s) {
	return s->size;
}

StackElemType getTop(Stack s) {
	return s->top->next->data;
}

// ��ʼ��ջ
int initSta(Stack* sta) {
	(*sta) = (Stack)malloc(sizeof(LinkStackBody));
	if (!(*sta)) return false;				// ����ʧ��
	(*sta)->size = 0;
	(*sta)->top = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	(*sta)->top->next = NULL;
	return true;
}

// ��ջ���ɹ����� 1 ��ʧ�ܷ��� 0 
inline int popSta(Stack sta) {
	if (sta->size == 0) return false;

	//EraseNext(sta->top);
	LinkStackNode* oldNode = sta->top->next;
	sta->top->next = oldNode->next;
	free(oldNode);

	sta->size--;
	return true;
}

// ѹջ
inline int pushSta(Stack sta, StackElemType data) {
	LinkStackNode* newNode = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	if (!newNode) return false;			// ����ʧ��
	newNode->data = data;

	//InsertAsNext(sta->top, newNode);
	newNode->next = sta->top->next;
	sta->top->next = newNode;

	sta->size++;
	return true;
}
