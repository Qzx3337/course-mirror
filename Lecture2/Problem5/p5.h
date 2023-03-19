#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <stack>
#include <map>
using namespace std;

stack<char> oper;			// �������
map<char, int> opLv;		// ����������ȼ���

/*����� ���ȼ��Ʊ�*/
void MakeMap() {
	opLv['^'] = 1;
	opLv['*'] = 2;
	opLv['/'] = 2;
	opLv['+'] = 3;
	opLv['-'] = 3;
	opLv['('] = 4;
	opLv['#'] = 9;
}

/*�ж���������ȼ�*/
bool IsPriority(char a, char b) {
	return opLv[a] < opLv[b];
}

/*�ж��Ƿ�Ϊ����*/
bool IsNumber(char ch) {
	return ('A' <= ch && ch <= 'Z');
}

/* �ж��Ƿ�Ϊ����� */
bool IsOperator(char ch) {
	return (opLv.find(ch) != opLv.end());
}

/* ���¼���һ�� */
bool SimpOneStep(string& formPos) {
	if (oper.size() < 1) return false;	// �жϷǷ����룬ֱ�ӷ���
	formPos = formPos + oper.top();		// �Ϸ����룬���ɺ�׺���ʽ
	oper.pop();							// ������ջ ��ջ
	return true;
}

/* ��׺���ʽ ��Ϊ ��׺���ʽ */
bool Infix2Postfix(string& formInfi, string& formPos) {
	MakeMap();							// ��ʼ����������ȼ��б�
	formInfi = "(" + formInfi + ")#";	// ��ʼ������������
	oper.push('#');						// ��ʼ�������ջ
	for (string::iterator it = formInfi.begin(); *it != '#';) {
		if (IsNumber(*it)) {			// ���������ַ���ֱ�ӷ����׺���ʽ
			formPos = formPos + (*it);
			it++;
		}
		else if (*it == '(') {			// ����'(' ֱ����ջ
			oper.push('(');
			it++;
		}
		else if (*it == ')') {			// ����')' ����������������
			while (oper.top() != '(')
				if (!SimpOneStep(formPos)) return false;
			oper.pop();					// ������ '('��ջ
			it++;
		}
		else if (IsOperator(*it)) {				// ���������
			if (IsPriority(*it, oper.top())) {	// ������
				oper.push(*it);
				it++;
			}
			else {								// ������
				if (!SimpOneStep(formPos)) return false;
			}
		}
		else {					// �����Ƿ��ַ�
			return false;
		}
	}

	return true;
}
