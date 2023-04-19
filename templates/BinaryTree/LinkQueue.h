/**************

��ʽ�����࣬�ṩ���������ӿڡ�
Ĭ�ϴ洢����Ϊ int

language: C.

****************/

#pragma once

#ifndef QueueElemType
#define QueueElemType int
#endif // !QueueElemType

/******** ��ʽ���н���� ********/

// ���н��ṹ��
typedef struct QueNode {
	QueueElemType data;
	struct QueNode* next;
} QueNode;

// ��ʼ��
QueNode* newQueNode(QueueElemType data, QueNode* next) 
{
	QueNode* pn = (QueNode*)malloc(sizeof(QueNode));
	if (pn == NULL) exit(OVERFLOW);
	pn->data = data;
	pn->next = next;
	return pn;
}

// �ڽ�� pa����� px
void insertAsNext(QueNode* pa, QueNode* px) 
{
	px->next = pa->next;
	pa->next = px;
}

// ������һ����㣬�ɹ����� 1�����ɹ����� 0
bool eraseNext(QueNode* pn) {
	if (pn->next == NULL) return false;
	QueNode* oldNode = pn->next;
	pn->next = oldNode->next;
	free(oldNode);
	return true;
}

/******** ��ʽ������ ********/

// ��ʽ���нṹ��
typedef struct _Queue {
	int size;
	QueNode* front;
	QueNode* back;
}_Queue, *Queue;

// ����������

Queue newQueue();
void destoryQueue(Queue que);

// ֻ�������ӿ�

int getSizeQue(Queue const que) { return que->size; }
bool isEmptyQue(Queue const que) { return que->size == 0; }
QueueElemType getBack(Queue const que) { return que->back->next->data; }
QueueElemType getFront(Queue const que) { return que->front->data; }

// ��д�����ӿ�

bool popQue(Queue que);
void pushQue(Queue que, QueueElemType data);

/******** ʵ�� ********/

/* �½����У����ؿն��� */
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

/* ���ٶ��У��ͷſռ� */
inline void destoryQueue(Queue que)
{
	if (que == NULL) return;
	while (popQue(que));
	free(que->back);
	free(que);
}

/* ���� */
inline bool popQue(Queue que)
{
	if (que == NULL) return false;
	if (que->size == 0) return false;
	eraseNext(que->back);
	que->size--;
	if (que->size == 0) que->front = que->back;
	return true;
}

/* ��� */
inline void  pushQue(Queue que, QueueElemType data)
{
	QueNode* newNode = newQueNode(data, NULL);
	insertAsNext(que->front, newNode);
	que->front = newNode;
	que->size++;
}

