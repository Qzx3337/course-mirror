/**************

��ʽ�����࣬�ṩ���������ӿڡ�
Ĭ�ϴ洢����Ϊ int

language: C.

****************/

#pragma once

#include <stdlib.h>
#define true 1
#define false 0

#ifndef ElemType
#define ElemType int
#endif // !ElemType


/*********************************************/
// ���н����
typedef struct QueNode {
	ElemType data;
	struct QueNode* next;
} QueNode;

// ��ʼ��
void InitQueNode(QueNode* pn, ElemType data, QueNode* next) {
	pn->data = data;
	pn->next = next;
}

// �ڽ�� pa����� px
void InsertAsNext(QueNode* pa, QueNode* px) {
	px->next = pa->next;
	pa->next = px;
}

// ������һ����㣬�ɹ����� 1�����ɹ����� 0
int EraseNext(QueNode* pn) {
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

int GetSizeQue(Queue const que) { return que->size; }
ElemType GetBack(Queue const que) { return que->back->next->data; }
int IsEmptyQue(Queue const que) { return que->size == 0; }
ElemType GetFront(Queue const que) { return que->front->data; }


// ��д�����ӿ�

void InitQue(Queue* que);
int PopQue(Queue que);
int PushQue(Queue que, ElemType data);


/******** ʵ��  **************/
// ��ʼ������
void InitQue(Queue* que) {
	(*que) = (Queue)malloc(sizeof(QueueBody));
	(*que)->size = 0;
	(*que)->front = (QueNode*)malloc(sizeof(QueNode));
	(*que)->front->next = NULL;
	(*que)->back = (*que)->front;
}

// ���� �ͷŶ�β���
inline int PopQue(Queue que) {
	if (que->size == 0) return false;
	EraseNext(que->back);
	que->size--;
	if (que->size == 0) que->front == que->back;
	return true;
}

// ���
inline int PushQue(Queue que, ElemType data) {
	QueNode* newNode = (QueNode*)malloc(sizeof(QueNode));
	newNode->data = data;
	InsertAsNext(que->front, newNode);
	que->front = newNode;
	que->size++;
	return true;
}



