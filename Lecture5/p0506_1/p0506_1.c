/***
������������

����ץ���� n ���ﷸ��������ݾ���֪���������ڲ�ͬ�ķ����Żȴ�����ж��ж��ٸ��Ż
��ͨ���������Ѷ��֪�����е�һЩ�ﷸ֮���໥��ʶ����֪ͬһ�����Ż�ĳ�Ա֮��ֱ�ӻ�����ʶ��
�п���һ�������Ż�ֻ��һ���ˡ�
���������֪�ﷸ֮��Ĺ�ϵ��ȷ�������Ż��������
��֪�ﷸ�ı�Ŵ� 1 �� n��

language: C.
***/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#define INF 0x7FFFFFFF

#define MAXN 1001
#define MAXM 5001

int fa[MAXN];		// father

int getFather(int const cur)
{
	if (fa[cur] == cur) return cur;
	return (fa[cur] = getFather(fa[cur]));
}

int main(int argc, char const **argv) {
	freopen("p0506.in", "r", stdin);
	//freopen("p0506.out", "w", stdout);

	int i;
	int m, n;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) fa[i] = i;
	int head, tail;
	for (i = 1; i <= m; i++) {
		scanf("%d%d", &head, &tail);
		fa[getFather(tail)] = head;
	}

	int ans = 0;
	for (i = 1; i <= n; i++) {
		if (getFather(i) == i) {
			ans++;
		}
	}
	printf("%d\n", ans);

	return 0;
}

