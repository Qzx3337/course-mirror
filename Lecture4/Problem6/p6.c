/*
������������ö�������ʽ�洢��rootָ�����㣬p��ָ����q��ָ���Ϊ�������е�������ͬ��㣬�һ�����Ϊ�����ý���·���ϵĵ㣬�����������������Ĺ�ͬ���ȡ�
language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1

#include "p6.h"

int main() {

	//freopen("p6.in", "r", stdin);
	//freopen("p6.out", "w", stdout);

	char preSec[128], inSec[128];			// ǰ��������к������������
	gets(preSec);
	gets(inSec);
	BinTree tree = makeTreeFromPreIn(preSec, inSec);	// ��ǰ��������к�����������н���������

	//travPre(tree, printTreeNode);				// �����֤�������
	//printf("\n");
	//travIn(tree, printTreeNode);
	//printf("\n");

	char ch1, ch2, ch3;					// ����������������
	scanf("%c%c", &ch1, &ch2);
	if (getLCA(tree, ch1, ch2, &ch3)) {			// ��ȡ�������������������
		printf("%c\n", ch3);
	}
	else {
		printf("NULL\n");
	}
	
	destoryBinTree(tree);				// ���ٶ�����

	return 0;
}

