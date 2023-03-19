/****************
* 
五、给定一个单链表，
给定两个整数left、right，
将该链表的第left和第right个结点的这一部分反转，
要求时间复杂度为O(n)，空间复杂度为O(1)。

language: C++;

******************/

#include "p5.h"
using namespace std;

int main() {

	// freopen("p5.in", "r", stdin);

	int n, left, right;
	cin >> n >> left >> right;
	left--; right--;
	LinkList<int> la;
	createMyList(la, n);
	//la.show();

	// rintf("\n反转区间 [%d, %d]\n", left, right);
	if (la.reverse(left, right)) {
		la.showElem();
	}
	else {
		printf("Position is error!\n");
	}

	return 0;
}