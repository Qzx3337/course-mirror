/**************

��ʽ�����࣬�ṩ���������ӿڡ�
Ĭ�ϴ洢����Ϊ int

language: C.

****************/

#pragma once

#ifndef QueueElemType
#define QueueElemType int
#endif // !QueueElemType

/*********************************************/

// ���н����
typedef struct QueNode {
	QueueElemType data;
	struct QueNode* next;
} QueNode;

// ��ʼ��
QueNode* newQueNode(QueueElemType data, QueNode* next) {
	QueNode* pn = (QueNode*)malloc(sizeof(QueNode));
	if (pn == NULL) exit(OVERFLOW);
	pn->data = data;
	pn->next = next;
	return pn;
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
typedef struct _Queue {
	int size;
	QueNode* front;
	QueNode* back;
}_Queue, * Queue;

// ֻ�������ӿ�

int getQueSize(Queue const que) { return que->size; }
QueueElemType getBack(Queue const que) { return que->back->next->data; }
int isEmptyQue(Queue const que) { return que->size == 0; }
QueueElemType getFront(Queue const que) { return que->front->data; }

// ��д�����ӿ�

Queue newQueue();
bool popQue(Queue que);
void pushQue(Queue que, QueueElemType data);


/******** ʵ��  **************/
// �½�����
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

// ���� �ͷŶ�β���
inline bool popQue(Queue que) {
	if (que->size == 0) return false;
	eraseNext(que->back);
	que->size--;
	if (que->size == 0) que->front = que->back;
	return true;
}

// ���
inline void  pushQue(Queue que, QueueElemType data) {
	QueNode* newNode = newQueNode(data, NULL);
	insertAsNext(que->front, newNode);
	que->front = newNode;
	que->size++;
}

void freeQueue(Queue que) {
	// �ͷſռ�
	while (popQue(que));
	free(que->back);
	free(que);
}

