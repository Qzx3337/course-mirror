#pragma once

#include <iostream>
#include "List.h"

/*������*/
void createMyList(List<int>& la, int n) {
	int x;
	for (int i = 0; i < n; ++i) {
		std::cin >> x;
		la.insertAsLast(x);
	}
}
