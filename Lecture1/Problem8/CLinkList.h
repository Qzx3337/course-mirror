#pragma once

#include <stdlib.h>
#include <typeinfo>

/* Ĭ������Ϊ int*/
#ifndef ElemType
#define ElemType int
#endif // !ElemType

/* ������ */
typedef struct Node {
	ElemType data;
	struct Node* next;
}Node, * LinkList;

/********* �ӿ� **********/

void InitCLinkList(LinkList* cll);
Node* InsertNode(Node* a, Node* p);
Node* InsertElem(LinkList la, ElemType e);
Node* PickNextNode(Node* p);
void ShowList(LinkList la);


/********* ʵ�� ************/

/*��ʼ��ѭ������*/
void InitCLinkList(LinkList* cll) {
	*cll = (LinkList)malloc(sizeof(Node));
	(*cll)->next = *cll;
}

/*����һ�����, �ڽ��a�������p*/
Node* InsertNode(Node* a, Node* p) {
	p->next = a->next;
	a->next = p;
	return p;
}

/*����Ԫ�� ͷ�巨*/
Node* InsertElem(LinkList la, ElemType e) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	InsertNode(la, p);
	return la;
}

/*ȡ����һ�����*/
Node* PickNextNode(Node* p) {
	if (p->next == NULL) return NULL;
	Node* pickedNodePos = p->next;
	p->next = pickedNodePos->next;
	return pickedNodePos;
}
