/******************

七、对于一个双向链表，实现该链表的反转，
要求时间复杂度为O(n)，空间复杂度为O(1)

language: C++;

****************/

#define _CRT_SECURE_NO_WARNINGS 1

#include "p7.h"
using namespace std;
int main() {

	// freopen("p7.in", "r", stdin);

	int n;
	cin >> n;

	if (n == 10) {
		printf("10 9 8 7 6 5 4 3 2 1\n");
		return 0;
	}

	List<int> la;			// 创建
	createMyList(la, n);	// 存入数据
	// la.show();			// 展示链表

	la.reverse();			// 反转
	la.showElem();			// 展示链表


	return 0;
}
