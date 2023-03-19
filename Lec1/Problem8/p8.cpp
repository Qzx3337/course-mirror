/********************

八、将一个循环链表表示的稀疏多项式分解成两个多项式，
使得这两个多项式中各自仅含奇数项或者偶数项，
要求空间复杂度为 O（1）。

language: C;

**********************/


#include "p8.h"

int main() {

	// freopen("p8_00.in", "r", stdin);

	LinkList la;
	InitCLinkList(&la);

	readPolymer(la);
	// ShowList(la);

	LinkList lb;
	InitCLinkList(&lb);
	splitPoly(la, lb);

	ShowList(la);
	ShowList(lb);

	return 0;
}