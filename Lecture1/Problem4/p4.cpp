/*****************
��Ŀ��
�ġ�����һ��������L����֪����data��Ϊint�������һ�������ܸ�Ч���㷨��������������K��λ�õĽ�㣬�����ظý���data��

˼·��
˫ָ��p,q���ȳ�ʼ��p=0,q=k��Ȼ��p,qƽ����󻬶�����q==nʱ����p==n-k��

language: C++;

*****************/
#include "p4.h"

using namespace std;

int main() {

	// freopen("p4.in", "r", stdin);

	int n, k;
	cin >> n >> k;

	LinkList<int> la;
	creatFromKeybord(la, n);

	// la.show();

	// printf("\n������ϣ�����ҵ����ڼ���Ԫ�أ� ");

	int* p = la.GetLast(k);
	if (p) {
		// printf("\n������%d��Ԫ��Ϊ��\n", k);
		cout << *p << endl;
	}
	else {
		printf("Position is error!\n");
	}
	

	return 0;
}