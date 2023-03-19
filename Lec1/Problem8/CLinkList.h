#pragma once

#include <stdlib.h>
#include <typeinfo>

/* 默认类型为 int*/
#ifndef ElemType
#define ElemType int
#endif // !ElemType

/* 单链表 */
typedef struct Node {
	ElemType data;
	struct Node* next;
}Node, * LinkList;

/********* 接口 **********/

void InitCLinkList(LinkList* cll);
Node* InsertNode(Node* a, Node* p);
Node* InsertElem(LinkList la, ElemType e);
Node* PickNextNode(Node* p);
void ShowList(LinkList la);


/********* 实现 ************/

/*初始化循环链表*/
void InitCLinkList(LinkList* cll) {
	*cll = (LinkList)malloc(sizeof(Node));
	(*cll)->next = *cll;
}

/*插入一个结点, 在结点a后面插结点p*/
Node* InsertNode(Node* a, Node* p) {
	p->next = a->next;
	a->next = p;
	return p;
}

/*插入元素 头插法*/
Node* InsertElem(LinkList la, ElemType e) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	InsertNode(la, p);
	return la;
}

/*取出下一个结点*/
Node* PickNextNode(Node* p) {
	if (p->next == NULL) return NULL;
	Node* pickedNodePos = p->next;
	p->next = pickedNodePos->next;
	return pickedNodePos;
}
