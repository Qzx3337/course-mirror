/***
language: C.

7���������������б�

������������
��дһ���б�����������Ƿ�Ϊ�������������㷨����ǰ��������к�����������и����ö������Ľ�㣬�������ö�������Ȼ���ٽ����жϡ���ע�⣬���н��ؼ��ֿ�����ͬ��

���������롿
6 4 5 8 6 9 0
4 5 6 6 8 9 0

�����������
true

����ʾ����ֱ�Ӹ��ݸ����������Ƿ������������жϣ������жϷ������÷֡�����ȴ�������������ʽ�洢���ٶ�������жϡ�

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

