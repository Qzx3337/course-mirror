/********************
������������

��֪Q��һ���ǿն��У�S��һ����ջ��
��ʹ���������������Լ��Զ��к�ջ�Ļ�����������дһ���㷨��
������Q�е�����Ԫ�����á�

��������ʽ��

����ĵ�һ��Ϊ����Ԫ�ظ������ڶ���Ϊ���д�����β��Ԫ��

�������ʽ��

������е�����

���������롿

3

1 2 3


�����������

3 2 1


�����ֱ�׼��

����ö�����ջ��֪ʶ�������ܵ÷�

language: C++

**********************/


#include <queue>
#include <stack>
#include "p4.h"
using namespace std;

int main() {
	queue<int> que;			// �½�����
	stack<int> sta;			// �½�ջ
	int n;					// Ԫ�ظ���
	cin >> n;				// ���� n
	for (int a; n--;) {		// ������
		cin >> a;
		que.push(a);
	}

	// ���д�����ɣ���������

	while (!que.empty()) {			// ���ն���˳��ȫ����ջ
		sta.push(que.front());
		que.pop();
	}
	while (!sta.empty()) {			// ȫ����ջ���
		que.push(sta.top());
		sta.pop();
	}

	// ������ɣ��������

	while (!que.empty()) {
		cout << que.front() << " ";
		que.pop();
	}

	return 0;
}
