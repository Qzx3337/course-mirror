#pragma once

#include <iostream>
#include "SeqList.h"
using namespace std;


/*�Ӽ�������n��Ԫ�أ�����*/
void creat_from_keybord(SeqList<int>& la) {
	int a, n;
	cout << "\nԪ��Ϊ����\n";
	cout << "����Ԫ�ظ�����\n";
	cin >> n;
	cout << "�����������ݣ�\n";
	for (int i = 0; i < n; i++) {
		cin >> a;
		la.add(a);
	}
}

/*���������ģ���� ʹ�ü�����������ķ�ʽ Ԫ��Ϊint����*/
void test_by_keybord(SeqList<int>& la) {

	int a, p, e;
	la.show(); // ���

	creat_from_keybord(la);
	la.show();
	
	// ����
	cout << "\n��������ҵ�����" << endl;
	cin >> a;
	cout << "�±�Ϊ��";
	cout << la.find(a) << endl;

	// ����
	cout << "\n���� p e �����±�p������Ԫ��e\n";
	cin >> p >> e;
	la.insert(p, e);
	la.show();

	// ɾ��
	cout << "\n����k��ɾ���±�Ϊk��Ԫ��\n";
	cin >> a;
	la.Delete(a);
	la.show();

}

