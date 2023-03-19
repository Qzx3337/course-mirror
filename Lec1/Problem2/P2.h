#pragma once

#define _CRT_SECURE_NO_WARNINGS 1


#include "SeqList.h"
#include <iostream>

void creat_not_decrease(SeqList<int>& la, int n, int m);

/* 随机生成一个int型不下降序列 存入SeqList<int>中。该序列长度为n，数值范围[0, m) */
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


