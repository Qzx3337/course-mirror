/*****************
��Ŀ��
������дһ���ɶ���������ɵ���������ʵ�ֵ�����ĳ�ʼ�����������������ݲ��ҡ������㡢ɾ����㡢��ʾ��������Ĳ�����

˼·��
����LinkListģ���࣬����������ȫ����װ��ȥ��
������"LinkList\LinkList.h"�С�

language: C++;

***************/

#include "P3.h"

using namespace std;

int main() {

	LinkList<int> la;
	la.show();
	printf("\n����쳲��������ɣ�");
	creatFromFibo(la, 500);
	la.show();

	int a;
	printf("\n������������ҵ�����");
	cin >> a;
	cout << "�±�Ϊ��" << la.Find(a) << endl;

	printf("\n������ż���������0��");
	insertZero(la);
	la.show();

	printf("\nɾ������������");
	removeOdd(la);
	la.show();

	return 0;
}