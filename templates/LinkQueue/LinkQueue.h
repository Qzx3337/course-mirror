/**************

链式队列类，提供基本操作接口。
默认存储类型为 int

language: C.

****************/

#pragma once

#ifndef QueueElemType
#define QueueElemType int
#endif // !QueueElemType

/******** 链式队列结点类 ********/

// 队列结点结构体
typedef struct QueNode {
	QueueElemType data;
	struct QueNode* next;
} QueNode;

// 初始化
QueNode* newQueNode(QueueElemType data, QueNode* next) 
{
	QueNode* pn = (QueNode*)malloc(sizeof(QueNode));
	if (pn == NULL) exit(OVERFLOW);
	pn->data = data;
	pn->next = next;
	return pn;
}

// 在结点 pa后插入 px
void insertAsNext(QueNode* pa, QueNode* px) 
{
	px->next = pa->next;
	pa->next = px;
}

// 消除下一个结点，成功返回 1，不成功返回 0
bool eraseNext(QueNode* pn) {
	if (pn->next == NULL) return false;
	QueNode* oldNode = pn->next;
	pn->next = oldNode->next;
	free(oldNode);
	return true;
}

/******** 链式队列类 ********/

// 链式队列结构体
typedef struct _Queue {
	int size;
	QueNode* front;
	QueNode* back;
}_Queue, *Queue;

// 构造与析构

Queue newQueue();
void destoryQueue(Queue que);

// 只读操作接口

int getSizeQue(Queue const que) { return que->size; }
bool isEmptyQue(Queue const que) { return que->size == 0; }
QueueElemType getBack(Queue const que) { return que->back->next->data; }
QueueElemType getFront(Queue const que) { return que->front->data; }

// 可写操作接口

bool popQue(Queue que);
void pushQue(Queue que, QueueElemType data);

/******** 实现 ********/

/* 新建队列，返回空队列 */
inline Queue newQueue()
{
	Queue que = (Queue)malloc(sizeof(_Queue));
	if (!que) exit(OVERFLOW);
	que->size = 0;
	que->front = (QueNode*)malloc(sizeof(QueNode));	
	if (!que->front) exit(OVERFLOW);
	que->front->next = NULL;
	que->back = que->front;
	return que;
}

/* 销毁队列，释放空间 */
inline void destoryQueue(Queue que)
{
	if (que == NULL) return;
	while (popQue(que));
	free(que->back);
	free(que);
}

/* 出队 */
inline bool popQue(Queue que)
{
	if (que == NULL) return false;
	if (que->size == 0) return false;
	eraseNext(que->back);
	que->size--;
	if (que->size == 0) que->front = que->back;
	return true;
}

/* 入队 */
inline void  pushQue(Queue que, QueueElemType data)
{
	QueNode* newNode = newQueNode(data, NULL);
	insertAsNext(que->front, newNode);
	que->front = newNode;
	que->size++;
}

