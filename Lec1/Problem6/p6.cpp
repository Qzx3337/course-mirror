/*********************
* 
六、已知由如下单链表(a1,a2,a3,a4,…,an)，
要求编写一个时间复杂度为O(n)，空间复杂度为O(1)的算法，
将该单链表转换成如下结构（an,an-2,…，a4,a2,a1,a3, …，an-3,an-1）
（注意：该单链表长度为偶数；要求时间复杂度为O(n)，空间复杂度为O(1)）

language: C++;

********************/


#define _CRT_SECURE_NO_WARNINGS 1

#include "p6.h"
#include <stack>
#include <iostream>

using namespace std;

int main() {

	// freopen("p6.in", "r", stdin);

	LinkList<int> la;			// 创建并生成数据
	createMyList(la);
	// la.show();

	if (RearrangeOdd(la)) la.showElem();		// 重排成功，输出链表
	else printf("Rearrange failed\n");		// 重排失败，输出错误信息

	return 0;
}

