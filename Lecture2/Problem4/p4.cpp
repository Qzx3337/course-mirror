/********************
【问题描述】

已知Q是一个非空队列，S是一个空栈。
仅使用少量工作变量以及对队列和栈的基本操作，编写一个算法，
将队列Q中的所有元素逆置。

【输入形式】

输入的第一行为队列元素个数，第二行为队列从首至尾的元素

【输出形式】

输出队列的逆置

【样例输入】

3

1 2 3


【样例输出】

3 2 1


【评分标准】

需采用队列与栈的知识，否则不能得分

language: C++

**********************/


#include <queue>
#include <stack>
#include "p4.h"
using namespace std;

int main() {
	queue<int> que;			// 新建队列
	stack<int> sta;			// 新建栈
	int n;					// 元素个数
	cin >> n;				// 读入 n
	for (int a; n--;) {		// 读数据
		cin >> a;
		que.push(a);
	}

	// 队列创建完成，下面逆置

	while (!que.empty()) {			// 按照队列顺序全部入栈
		sta.push(que.front());
		que.pop();
	}
	while (!sta.empty()) {			// 全部出栈入队
		que.push(sta.top());
		sta.pop();
	}

	// 逆置完成，现在输出

	while (!que.empty()) {
		cout << que.front() << " ";
		que.pop();
	}

	return 0;
}
