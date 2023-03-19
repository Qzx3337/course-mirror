/*****************
题目：
三、编写一个由多个函数构成的完整程序，实现单链表的初始化、建立、按照内容查找、插入结点、删除结点、显示整个链表的操作。

思路：
建立LinkList模板类，将上述功能全部封装进去。
定义在"LinkList\LinkList.h"中。

language: C++;

***************/

#include "P3.h"

using namespace std;

int main() {

	LinkList<int> la;
	la.show();
	printf("\n依据斐波那契生成：");
	creatFromFibo(la, 500);
	la.show();

	int a;
	printf("\n请输入你想查找的数：");
	cin >> a;
	cout << "下标为：" << la.Find(a) << endl;

	printf("\n在所有偶数后面插入0：");
	insertZero(la);
	la.show();

	printf("\n删除所有奇数：");
	removeOdd(la);
	la.show();

	return 0;
}