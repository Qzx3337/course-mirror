/****************
* 
�塢����һ��������
������������left��right��
��������ĵ�left�͵�right��������һ���ַ�ת��
Ҫ��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)��

language: C++;

******************/

#include "p5.h"
using namespace std;

int main() {

	// freopen("p5.in", "r", stdin);

	int n, left, right;
	cin >> n >> left >> right;
	left--; right--;
	LinkList<int> la;
	createMyList(la, n);
	//la.show();

	// rintf("\n��ת���� [%d, %d]\n", left, right);
	if (la.reverse(left, right)) {
		la.showElem();
	}
	else {
		printf("Position is error!\n");
	}

	return 0;
}