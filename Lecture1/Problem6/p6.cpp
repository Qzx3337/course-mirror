/*********************
* 
������֪�����µ�����(a1,a2,a3,a4,��,an)��
Ҫ���дһ��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)���㷨��
���õ�����ת�������½ṹ��an,an-2,����a4,a2,a1,a3, ����an-3,an-1��
��ע�⣺�õ�������Ϊż����Ҫ��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)��

language: C++;

********************/


#define _CRT_SECURE_NO_WARNINGS 1

#include "p6.h"
#include <stack>
#include <iostream>

using namespace std;

int main() {

	// freopen("p6.in", "r", stdin);

	LinkList<int> la;			// ��������������
	createMyList(la);
	// la.show();

	if (RearrangeOdd(la)) la.showElem();		// ���ųɹ����������
	else printf("Rearrange failed\n");		// ����ʧ�ܣ����������Ϣ

	return 0;
}

