/***
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

#define MAXN 5000
#define MAXL 128

// ��λ���ṩ MAXN����λ������������� MAXL
char seat[MAXN][MAXL];

// ����������������λ�ţ����ַ�
int find(char* name, int left, int right)
{
	int l = left, r = right, mid;
	while (l <= r) {
		mid = (l + r) / 2;
		int cmp = strcmp(name, seat[mid]);
		if (cmp == 0) {
			return mid;
		}
		else if (cmp < 0) {
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	return -1;
}

int main(int argc, char const** argv)
{
	freopen("p0003.in", "r", stdin);
	//freopen("p0003.out", "w", stdout);

	int i;
	int n;	// ��λ������n���ˣ�����
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%s", seat[i]);
	}

	char name[MAXL];		// �����ҵ�����
	scanf("%s", name);
	int pos = find(name, 0, n - 1);	// ����������������λ��
	if (pos == -1) {
		printf("None\n");
	}
	else {
		printf("%d\n", pos);
	}

	return 0;
}

