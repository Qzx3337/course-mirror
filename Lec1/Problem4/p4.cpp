/*****************
题目：
四、建立一个单链表L，已知结点的data域为int，请设计一个尽可能高效的算法，查找链表倒数第K个位置的结点，并返回该结点的data域。

思路：
双指针p,q，先初始化p=0,q=k，然后p,q平行向后滑动，当q==n时，有p==n-k；

language: C++;

*****************/
#include "p4.h"

using namespace std;

int main() {

	// freopen("p4.in", "r", stdin);

	int n, k;
	cin >> n >> k;

	LinkList<int> la;
	creatFromKeybord(la, n);

	// la.show();

	// printf("\n请输入希望查找倒数第几个元素： ");

	int* p = la.GetLast(k);
	if (p) {
		// printf("\n倒数第%d个元素为：\n", k);
		cout << *p << endl;
	}
	else {
		printf("Position is error!\n");
	}
	

	return 0;
}