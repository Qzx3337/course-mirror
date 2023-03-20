#pragma once

#include <iostream>
#include "LinkList\LinkList.h"

/*����쳲�����������������*/
bool creatFromFibo(LinkList<int>& la, int l) {
	for (int i = 1, j = 1; i < l; j = i + j, i = j - i) {
		la.insertAsLast(i);
	}
	return true;
}
bool creatFromFibo(LinkList<int>& la) {
	return creatFromFibo(la, 200);
}

/*��ż���������0*/
void insertZero(LinkList<int>& la) {
	for (ListNode<int>* p = la.first(); p != la.trailer; p = p->next) {
		if ((p->data) % 2 == 0) {
			p = la.insert(p, 0);
		}
	}
}

/*ɾ����������*/
void removeOdd(LinkList<int>& la) {
	for (ListNode<int>* p = la.header; p->next != la.trailer;) {
		if ((p->next->data) % 2 == 1) {
			la.removeNext(p);
		}
		else {
			p = p->next;
		}
	}

}

