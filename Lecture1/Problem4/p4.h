#pragma once

#define _CRT_SECURE_NO_WARNINGS 1

#include "LinkList.h"


/*按照斐波那契数列生成链表*/
void creatFromKeybord(LinkList<int>& la, int n) {
	/*
	for (int i = 1, j = 1; i < l; j = i + j, i = j - i) {
		la.insertAsLast(i);
	}
	return true;
*/
	int x;
	for (int i = 0; i < n; i++) {
		std::cin >> x;
		la.insertAsLast(x);
	}
}
