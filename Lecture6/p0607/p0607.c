/***
language: C.

7、二叉排序树的判别

【问题描述】
试写一个判别给定二叉树是否为二叉排序树的算法。以前序遍历序列和中序遍历序列给出该二叉树的结点，并创建该二叉树。然后再进行判断。请注意，树中结点关键字可能相同。

【样例输入】
6 4 5 8 6 9 0
4 5 6 6 8 9 0

【样例输出】
true

【提示】若直接根据给定的中序是否有序来进行判断，此种判断方法不得分。务必先创建二叉树的链式存储，再对其进行判断。

***/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#define MAXN 200

void test1()
{
	int i;
	int n;
	int a[MAXN];
	for (i = 0; ; i++) {
		scanf("%d", &a[i]);
		if (a[i] == 0) break;
	}
	for (i = 0; ; i++) {
		scanf("%d", &a[i]);
		if (a[i] == 0) break;
	}
	n = i;
	bool flag = true;
	for (i = 1; i < n; i++) {
		if (a[i] < a[i - 1]) {
			flag = false;
			break;
		}
	}
	if (flag) {
		printf("true\n");
	}
	else {
		printf("false\n");
	}

}

int main(int argc, char const **argv)
{
	//freopen("p0607.in", "r", stdin);
	//freopen("p0607.out", "w", stdout);

	test1();

	return 0;
}

