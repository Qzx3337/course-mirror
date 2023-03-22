/**************

��ʽ�����࣬�ṩ���������ӿڡ�
Ĭ�ϴ洢����Ϊ int

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
// ���н����
typedef struct QueNode {
	QueueElemType data;
	struct QueNode* next;
} QueNode;

// ��ʼ��
void initQueNode(QueNode* pn, QueueElemType data, QueNode* next) {
	pn->data = data;
	pn->next = next;
}

// �ڽ�� pa����� px
void insertAsNext(QueNode* pa, QueNode* px) {
	px->next = pa->next;
	pa->next = px;
}

// ������һ����㣬�ɹ����� 1�����ɹ����� 0
int eraseNext(QueNode* pn) {
	if (pn->next == NULL) return false;
	QueNode* oldNode = pn->next;
	pn->next = oldNode->next;
	free(oldNode);
	return true;
}


/***********************************************/
// ��ʽ������
typedef struct QueueBody {
	int size;
	QueNode* front;
	QueNode* back;
} QueueBody, * Queue;

// ֻ�������ӿ�

int getQueSize(Queue const que) { return que->size; }
QueueElemType getBack(Queue const que) { return que->back->next->data; }
int isEmptyQue(Queue const que) { return que->size == 0; }
QueueElemType getFront(Queue const que) { return que->front->data; }


// ��д�����ӿ�

void initQue(Queue* que);
int popQue(Queue que);
int pushQue(Queue que, QueueElemType data);


/******** ʵ��  **************/
// ��ʼ������
void initQue(Queue* que) {
	(*que) = (Queue)malloc(sizeof(QueueBody));
	(*que)->size = 0;
	(*que)->front = (QueNode*)malloc(sizeof(QueNode));
	(*que)->front->next = NULL;
	(*que)->back = (*que)->front;
}

// ���� �ͷŶ�β���
inline int popQue(Queue que) {
	if (que->size == 0) return false;
	eraseNext(que->back);
	que->size--;
	if (que->size == 0) que->front = que->back;
	return true;
}

// ���
inline int pushQue(Queue que, QueueElemType data) {
	QueNode* newNode = (QueNode*)malloc(sizeof(QueNode));
	newNode->data = data;
	insertAsNext(que->front, newNode);
	que->front = newNode;
	que->size++;
	return true;
}

void freeQueue(Queue que) {
	// �ͷſռ�
	while (popQue(que));
	free(que->back);
	free(que);
}

