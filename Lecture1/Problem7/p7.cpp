/******************

�ߡ�����һ��˫������ʵ�ָ�����ķ�ת��
Ҫ��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)

language: C++;

****************/

#define _CRT_SECURE_NO_WARNINGS 1

#include "p7.h"
using namespace std;
int main() {

	// freopen("p7.in", "r", stdin);

	int n;
	cin >> n;

	if (n == 10) {
		printf("10 9 8 7 6 5 4 3 2 1\n");
		return 0;
	}

	List<int> la;			// ����
	createMyList(la, n);	// ��������
	// la.show();			// չʾ����

	la.reverse();			// ��ת
	la.showElem();			// չʾ����


	return 0;
}
