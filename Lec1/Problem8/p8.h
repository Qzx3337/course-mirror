#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "PolyElem.h"		// 引用多项式结构
#define ElemType PolyElem	// 定义链表结点数据域类型为多项式结构
#include "CLinkList.h"		// 引用循环链表结构

/********* 函数列表 *********/

void ShowList(LinkList la);			/*展示链表内容，多项式格式*/
void readPolymer(LinkList la);		/*读入一个多项式到链表中*/


/******** 函数实现 *********/

/*展示链表内容，多项式格式*/
void ShowList(LinkList la) {
	// printf("\n%s [%X]:\n", typeid(la).name(), (int)la); //基本信息
	// printf("[");
	Node* p;
	int i;
	for (p = la->next, i = 0; p != la; p = p->next, i++) {
		// if (i && i % 5 == 0) printf("\n");
		// if (i) printf("+ ");
		printf("%d ", p->data.coef);
	}
	// printf("]\n");
	// printf("size = %d\n", i);

	printf("\n");
}

/*读入一个多项式到链表中*/
void readPolymer(LinkList la) {
	int n;
	PolyElem e;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		e.expo = i;
		scanf("%d", &e.coef);
		InsertElem(la, e);
	}
}

/*拆分多项式，偶数幂项拆到lb中*/
void splitPoly(LinkList &la, LinkList &lb) {
	for (Node* p = la, *q; p->next != la; ) {
		if (p->next->data.expo % 2 == 0) { // 偶数幂
			q = PickNextNode(p);
			InsertNode(lb, q);
		}
		else { // 奇数幂
			p = p->next;
		}
	}
	LinkList lx;
	InitCLinkList(&lx);
	for (Node* p = la, *q; p->next != la;) {
		q = PickNextNode(p);
		InsertNode(lx, q);
	}

	// 交换lx la
	LinkList lTemp = la;
	la = lx;
	lx = lTemp;
	// 释放旧链表
	free(lx);

}

