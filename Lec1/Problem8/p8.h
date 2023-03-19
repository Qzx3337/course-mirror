#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "PolyElem.h"		// ���ö���ʽ�ṹ
#define ElemType PolyElem	// ��������������������Ϊ����ʽ�ṹ
#include "CLinkList.h"		// ����ѭ������ṹ

/********* �����б� *********/

void ShowList(LinkList la);			/*չʾ�������ݣ�����ʽ��ʽ*/
void readPolymer(LinkList la);		/*����һ������ʽ��������*/


/******** ����ʵ�� *********/

/*չʾ�������ݣ�����ʽ��ʽ*/
void ShowList(LinkList la) {
	// printf("\n%s [%X]:\n", typeid(la).name(), (int)la); //������Ϣ
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

/*����һ������ʽ��������*/
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

/*��ֶ���ʽ��ż�������lb��*/
void splitPoly(LinkList &la, LinkList &lb) {
	for (Node* p = la, *q; p->next != la; ) {
		if (p->next->data.expo % 2 == 0) { // ż����
			q = PickNextNode(p);
			InsertNode(lb, q);
		}
		else { // ������
			p = p->next;
		}
	}
	LinkList lx;
	InitCLinkList(&lx);
	for (Node* p = la, *q; p->next != la;) {
		q = PickNextNode(p);
		InsertNode(lx, q);
	}

	// ����lx la
	LinkList lTemp = la;
	la = lx;
	lx = lTemp;
	// �ͷž�����
	free(lx);

}

