/**************

Problem 5: ��׺���ʽת��׺���ʽ
�������Ķ� README.MD

 language: C++

*****************/

#include "p5.h"

using namespace std;

int main() {
	
	// freopen("p5.in", "r", stdin);

	string s1;					// �ַ��� ��׺���ʽ
	cin >> s1;					// �����ַ��� ��׺���ʽ
	s1.erase(s1.end() - 1);		// ɾ��ĩλ����Ч�ַ� '#'
	// cout << s1 << endl;

	string s2;					// ��׺���ʽ
	if (Infix2Postfix(s1, s2)) {	//��׺ת��׺���ж��Ƿ�Ϸ�
		cout << s2 << endl;		// �Ϸ������׺���ʽ
	}
	else {
		cout << "error!\n";		// ���Ϸ�
	}

	return 0;
}

