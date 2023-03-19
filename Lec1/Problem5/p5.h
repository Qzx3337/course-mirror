#pragma once

#define _CRT_SECURE_NO_WARNINGS 1

#include "LinkList.h"
#include <iostream>

/* ¶ÁÊý¾Ý */
void createMyList(LinkList<int>& la, int n) {
	int x;
	for (int i = 0; i < n; ++i) {
		std::cin >> x;
		la.insertAsLast(x);
	}
}
