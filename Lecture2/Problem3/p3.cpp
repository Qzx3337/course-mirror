/*******************

�����ַ�������������
�������Ķ� README.MD

language: C++

*******************/

#define _CRT_SECURE_NO_WARNINGS 1

#include "calculator.h"
using namespace std;

int main() {

	// freopen("p3.in", "r", stdin);

	string s;				// �����ַ���
	getline(cin, s);		// ����һ��
	s.erase(s.end() - 1);	// ɾ�����һλ����Ч '#'
	// cout << s << endl;

	double ans = 0;				// ����
	if (CalculateStr(ans, s)) {	// �ַ����Ϸ����õ����
		cout << ans << endl;
	}
	else {						// �ַ������Ϸ�
		cout << "error!\n";
	}
	return 0;
}

