/********************

�ˡ���һ��ѭ�������ʾ��ϡ�����ʽ�ֽ����������ʽ��
ʹ������������ʽ�и��Խ������������ż���
Ҫ��ռ临�Ӷ�Ϊ O��1����

language: C;

**********************/


#include "p8.h"

int main() {

	// freopen("p8_00.in", "r", stdin);

	LinkList la;
	InitCLinkList(&la);

	readPolymer(la);
	// ShowList(la);

	LinkList lb;
	InitCLinkList(&lb);
	splitPoly(la, lb);

	ShowList(la);
	ShowList(lb);

	return 0;
}