#pragma once

#define _CRT_SECURE_NO_WARNINGS 1


#include "SeqList.h"
#include <iostream>

void creat_not_decrease(SeqList<int>& la, int n, int m);

/* �������һ��int�Ͳ��½����� ����SeqList<int>�С������г���Ϊn����ֵ��Χ[0, m) */
void creat_not_decrease(SeqList<int>& la, int n, int m) {
	for (int i = 0; i < n; i++) {
		la.add(rand() % m);
		//la.show();
	}
	la.sort();
}

void readMyList(SeqList<int> &la) {
	int n;
	int x;
	std::cin >> n;
	while (n--) {
		std::cin >> x;
		la.add(x);
	}
}


