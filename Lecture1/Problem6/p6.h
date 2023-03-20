#pragma once

#include "LinkList.h"

/*读数据*/
void createMyList(LinkList<int>& la) {
	int n, x;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> x;
		la.insertAsLast(x);
	}
}


/* 重排链表，题目：problem6 */
template<typename T>
bool RearrangeOdd(LinkList<T>& la) {
	if (la.empty()) return true;	// 空链表
	int len = la.size();			// 链表长度
	if (len % 2) return false;		// 元素个数为奇数则无法处理

	ListNode<T>* p = la.first();		// 预存下次处理的元素的前驱
	int n = len >> 1;				// 循环 length/2 遍
	for (int i = 0; i < n; i++) {
		// la.insertAsFirst(la.removeNext(p));		// 取出2,4,6,8插在最前
		la.insertAsFirst(la.PickNextNode(p));		// 取出2,4,6,8插在最前
		p = p->next;								// 更新p
	}
	return true;
}

