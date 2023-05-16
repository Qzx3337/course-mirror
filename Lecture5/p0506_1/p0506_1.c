/***
【问题描述】

警察抓到了 n 个罪犯，警察根据经验知道他们属于不同的犯罪团伙，却不能判断有多少个团伙，
但通过警察的审讯，知道其中的一些罪犯之间相互认识，已知同一犯罪团伙的成员之间直接或间接认识。
有可能一个犯罪团伙只有一个人。
请你根据已知罪犯之间的关系，确定犯罪团伙的数量。
已知罪犯的编号从 1 至 n。

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

