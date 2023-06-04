/***
language: C.

 5�����ֲ���

������������
������10��������һά����a�У�������ð�������㷨����10��������С��������
Ȼ������һ����������n�������ö��ֲ��ҷ��жϸ����Ƿ�Ϊ����a�е�һ������
���������yes�������������no����

���������롿
10 9 8 7 6 5 4 3 2 1
5

�����������
yes
yes

***/

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#define MAXN 10
int arr[MAXN + 1];

int cmpFun(int* const a, int* const b)
{
	return (*a - *b);
}

void bubbling_sort(int* arr)
{
	qsort(arr, MAXN, sizeof(int), cmpFun);
}

bool recursive_find(int const x, int const l, int const r)
{
	if (l + 1 == r) return (x == arr[l]);
	int mid = (l + r) >> 1;
	if (x < arr[mid]) return recursive_find(x, l, mid);
	else return recursive_find(x, mid, r);
}

bool nonrecursive_find(int const x)
{
	int l = 0;
	int r = MAXN;
	while (l + 1 != r) {
		int mid = (l + r) >> 1;
		if (x < arr[mid]) r = mid;
		else l = mid;
	}
	return (x == arr[l]);
}


int main(int argc, char const **argv)
{
	//freopen("p0605.in", "r", stdin);
	//freopen("p0605.out", "w", stdout);

	int i;
	for (i = 0; i < MAXN; i++) {
		scanf("%d", &arr[i]);
	}
	bubbling_sort(arr);
	//for (i = 0; i < MAXN; i++) {
	//	printf("%d ", arr[i]);
	//}

	int x;
	scanf("%d", &x);

	// �ݹ鷽��
	if (recursive_find(x, 0, MAXN)) printf("yes\n");
	else printf("no\n"); 

	// �ǵݹ鷽��
	if (nonrecursive_find(x)) printf("yes\n"); 
	else printf("no\n"); 

	return 0;
}

