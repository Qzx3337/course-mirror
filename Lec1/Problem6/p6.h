#pragma once

#include "LinkList.h"

/*������*/
void createMyList(LinkList<int>& la) {
	int n, x;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> x;
		la.insertAsLast(x);
	}
}


/* ����������Ŀ��problem6 */
template<typename T>
bool RearrangeOdd(LinkList<T>& la) {
	if (la.empty()) return true;	// ������
	int len = la.size();			// ������
	if (len % 2) return false;		// Ԫ�ظ���Ϊ�������޷�����

	ListNode<T>* p = la.first();		// Ԥ���´δ����Ԫ�ص�ǰ��
	int n = len >> 1;				// ѭ�� length/2 ��
	for (int i = 0; i < n; i++) {
		// la.insertAsFirst(la.removeNext(p));		// ȡ��2,4,6,8������ǰ
		la.insertAsFirst(la.PickNextNode(p));		// ȡ��2,4,6,8������ǰ
		p = p->next;								// ����p
	}
	return true;
}

