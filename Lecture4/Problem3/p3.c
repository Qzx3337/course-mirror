/*
 ����һ�����ա���չ�������С�����չ������������ַ�����'#' ����յ��ӽڵ㣬��д��ĸ����ڵ����ݡ�
 ��ͨ������ַ��������������������̲���ʾ�ĺ�����ʾ����״��ӡ�Ķ�����

language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include "p3.h"
#define MAXLEN 128

int main() {

	//freopen("p3.in", "r", stdin);
	//freopen("p3.out", "w", stdout);

	char posSeq[MAXLEN];
	gets(posSeq);

	BinTree tree = createBinTree_Pos(posSeq);	// ���򴴽������

	//travPre(tree, printTreeNode);
	//printf("\n");
	//travIn(tree, printTreeNode);
	//printf("\n");
	//travPost(tree, printTreeNode);
	//printf("\n");
	//travLevel(tree, printTreeNode);
	//printf("\n");

	//printf("\n--------------\n\n");

	printTransTree(tree);

	destoryBinTree(tree);
	
	return 0;
}

