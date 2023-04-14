/**************

链式队列类，提供基本操作接口。
默认存储类型为 int

language: C.

****************/

#pragma once

#ifndef QueueElemType
#define QueueElemType int
#endif // !QueueElemType

/*********************************************/

// 队列结点类
typedef struct QueNode {
	QueueElemType data;
	struct QueNode* next;
} QueNode;

// 初始化
QueNode* newQueNode(QueueElemType data, QueNode* next) {
	QueNode* pn = (QueNode*)malloc(sizeof(QueNode));
	if (pn == NULL) exit(OVERFLOW);
	pn->data = data;
	pn->next = next;
	return pn;
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
typedef struct _Queue {
	int size;
	QueNode* front;
	QueNode* back;
}_Queue, * Queue;

// 只读操作接口

int getQueSize(Queue const que) { return que->size; }
QueueElemType getBack(Queue const que) { return que->back->next->data; }
int isEmptyQue(Queue const que) { return que->size == 0; }
QueueElemType getFront(Queue const que) { return que->front->data; }

// 可写操作接口

Queue newQueue();
bool popQue(Queue que);
void pushQue(Queue que, QueueElemType data);


/******** 实现  **************/
// 新建队列
Queue newQueue() {
	Queue que = (Queue)malloc(sizeof(_Queue));
	if (!que) exit(OVERFLOW);
	que->size = 0;
	que->front = (QueNode*)malloc(sizeof(QueNode));
	if (!que->front) exit(OVERFLOW);
	que->front->next = NULL;
	que->back = que->front;
	return que;
}

// 出队 释放队尾结点
inline bool popQue(Queue que) {
	if (que->size == 0) return false;
	eraseNext(que->back);
	que->size--;
	if (que->size == 0) que->front = que->back;
	return true;
}

// 入队
inline void  pushQue(Queue que, QueueElemType data) {
	QueNode* newNode = newQueNode(data, NULL);
	insertAsNext(que->front, newNode);
	que->front = newNode;
	que->size++;
}

void freeQueue(Queue que) {
	// 释放空间
	while (popQue(que));
	free(que->back);
	free(que);
}

