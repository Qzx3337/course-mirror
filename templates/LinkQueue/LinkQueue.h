/**************

链式队列类，提供基本操作接口。
默认存储类型为 int

language: C.

****************/

#pragma once

#include <stdlib.h>
#define true 1
#define false 0

#ifndef QueueElemType
#define QueueElemType int
#endif // !QueueElemType

#define mcreate(type, n) ((type)*)malloc((n)*sizeof((type)))
#define mcreate(type) ((type)*)malloc(sizeof((type)))

/*********************************************/
// 队列结点类
typedef struct QueNode {
	QueueElemType data;
	struct QueNode* next;
} QueNode;

// 初始化
void initQueNode(QueNode* pn, QueueElemType data, QueNode* next) {
	pn->data = data;
	pn->next = next;
}

// 在结点 pa后插入 px
void insertAsNext(QueNode* pa, QueNode* px) {
	px->next = pa->next;
	pa->next = px;
}

// 消除下一个结点，成功返回 1，不成功返回 0
int eraseNext(QueNode* pn) {
	if (pn->next == NULL) return false;
	QueNode* oldNode = pn->next;
	pn->next = oldNode->next;
	free(oldNode);
	return true;
}


/***********************************************/
// 链式队列类
typedef struct QueueBody {
	int size;
	QueNode* front;
	QueNode* back;
} QueueBody, * Queue;

// 只读操作接口

int getQueSize(Queue const que) { return que->size; }
QueueElemType getBack(Queue const que) { return que->back->next->data; }
int isEmptyQue(Queue const que) { return que->size == 0; }
QueueElemType getFront(Queue const que) { return que->front->data; }


// 可写操作接口

void initQue(Queue* que);
int popQue(Queue que);
int pushQue(Queue que, QueueElemType data);


/******** 实现  **************/
// 初始化队列
void initQue(Queue* que) {
	(*que) = (Queue)malloc(sizeof(QueueBody));
	(*que)->size = 0;
	(*que)->front = (QueNode*)malloc(sizeof(QueNode));
	(*que)->front->next = NULL;
	(*que)->back = (*que)->front;
}

// 出队 释放队尾结点
inline int popQue(Queue que) {
	if (que->size == 0) return false;
	eraseNext(que->back);
	que->size--;
	if (que->size == 0) que->front = que->back;
	return true;
}

// 入队
inline int pushQue(Queue que, QueueElemType data) {
	QueNode* newNode = (QueNode*)malloc(sizeof(QueNode));
	newNode->data = data;
	insertAsNext(que->front, newNode);
	que->front = newNode;
	que->size++;
	return true;
}

void freeQueue(Queue que) {
	// 释放空间
	while (popQue(que));
	free(que->back);
	free(que);
}

