/****************

�����Ż���
����ʹ�ÿո񣨷������ǿ���ʽ�ṹ��
��������С�����������ʹ�� double ������
����ʹ�������㣨����С���ݣ�Ҳ���ǿ���������

*****************/
#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <stack>
#include <map>
using namespace std;

#define NumberType double

stack<NumberType> numb;		// �������
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
	return ('0' <= ch && ch <= '9');
}

/* �ж��Ƿ�Ϊ����� */
bool IsOperator(char ch) {
	return (opLv.find(ch) != opLv.end());
}

/*���㵥���ַ�����*/
NumberType CalcChar(char op, NumberType a, NumberType b) {
	switch (op) {
	case '+':
		return (a + b);
	case '-':
		return (a - b);
	case '*':
		return (a * b);
	case '/':
		return (a / b);
	case '^':
		return pow(a, b);
	default:
		break;
	}
	return 0;
}

/* ���ַǷ�����*/
bool FoundIllegalInput() {
	return false;
}

/*��ȡһ������*/
NumberType GetaNumber(string::iterator& it) {
	NumberType temp = 0;
	// ������int
	for (; IsNumber(*it); it++)
		temp = temp * 10 + (int)(*it - '0');
	// ����С��
	if (*it == '.') {
		it++;
		for (double pt = 0.1; IsNumber(*it); it++, pt *= 0.1) {
			temp += pt * (int)(*it - '0');
		}
	}
	return temp;
}

/* ���¼���һ�� */
bool SimpOneStep() {

	// �жϷǷ�����

	if (numb.size() < 2) return FoundIllegalInput();
	if (oper.size() < 1) return FoundIllegalInput();

	// �Ϸ�������Ի���

	NumberType tb = numb.top();
	numb.pop();
	NumberType ta = numb.top();
	numb.pop();
	ta = CalcChar(oper.top(), ta, tb);
	numb.push(ta);

	// �������
	// printf("�������� %c �õ� %lf\n", oper.top(), ta);

	oper.pop();
	return true;
}

/*�����������㣬�ַ�������*/
bool CalculateStr(NumberType& x, string& formula) {
	MakeMap();							// ��ʼ����������ȼ��б�
	formula = "(" + formula + ")#";		// ��ʼ������������
	oper.push('#');						// ��ʼ�������ջ
	for (string::iterator it = formula.begin(); *it != '#';) {
		if (IsNumber(*it)) {			// ���������ַ���¼���������ֲ���
			NumberType temp = GetaNumber(it);

			// �������
			// printf("������ֵ��%lf\n", temp);
			numb.push(temp);
		}
		else if (*it == '(') {			// ����'(' ֱ����ջ
			oper.push('(');
			it++;
		}
		else if (*it == ')') {			// ����')' ����������������
			while (oper.top() != '(')
				if (!SimpOneStep()) return false;
			oper.pop();
			it++;
		}
		else if (IsOperator(*it)) {					// ���������
			if (*it == '-' && *(it - 1) == '(') {	// ����'-'�Ƿ��ʾ����		
				numb.push(0);
			}
			if (IsPriority(*it, oper.top())) {	// ������
				oper.push(*it);
				it++;
			}
			else {								// ������
				if (!SimpOneStep()) return false;
			}
		}
		else {									// �����Ƿ��ַ�
			return FoundIllegalInput();
		}
	}

	if (numb.size() == 1) {					// ����Ϸ����������ջ��Ϊ���
		x = numb.top();
		return true;
	}
	else {
		return FoundIllegalInput();			// ��ֵ����ֵ֮��ո��ǲ������
	}

}


/******** ������Ϊ���������ר�ã����ڲ����� ****************************/

void PrintWithBracket(NumberType x) {
	if (x < 0) cout << "(" << x << ")";
	else cout << x;
}

/* �����ǰ���㲽�� */
void ShowCurrentStep(string::iterator it) {
	stack<NumberType> temNumb;		// �������
	stack<char> temOper;			// �������

	// �����Ķ�����ջ
	while (oper.top() != '#') {
		temOper.push(oper.top());
		oper.pop();
	}
	while (!numb.empty()) {
		temNumb.push(numb.top());
		numb.pop();
	}

	// ���ջ�ڵı��ʽ 
	while (!temOper.empty()) {
		if (temOper.top() == '(') {				// ջ��������
			printf("(");
		}
		else {									// ջ���������
			PrintWithBracket(temNumb.top());					// ��ӡһ������
			if (temOper.top() == '+' || temOper.top() == '-')	// ���ڼӼ��Ŷ��ӡ�ո��Ա�۲�
				cout << " " << temOper.top() << " ";
			else cout << temOper.top();
			numb.push(temNumb.top()); temNumb.pop();			// ��ԭ������ջ
		}
		oper.push(temOper.top()); temOper.pop();				// ��ԭ������ջ
	}
	PrintWithBracket(temNumb.top());			// ��ӡʣ���һ����
	numb.push(temNumb.top()); temNumb.pop();	// ��ԭ������ջ

	// �����û��ջ�ı��ʽ
	for (; *it != '#'; it++) {
		cout << *it;
	}
	printf("\n");

}

/* ���¼���һ������Ҫ�����ǰ���� */
bool SimpOneStep(string::iterator const it) {

	// �жϷǷ�����

	if (numb.size() < 2) return FoundIllegalInput();
	if (oper.size() < 1) return FoundIllegalInput();

	// �Ϸ�������Ի���

	NumberType tb = numb.top();
	numb.pop();
	NumberType ta = numb.top();
	numb.pop();
	ta = CalcChar(oper.top(), ta, tb);
	numb.push(ta);

	oper.pop();
	// �������
	ShowCurrentStep(it);

	return true;
}

/* �����������㣬�ַ������ͣ���Ҫ��������� */
NumberType CalculateStrStepwise(string& formula) {
	MakeMap();						// ��ʼ����������ȼ��б�
	formula = "(" + formula + ")#";	// ��ʼ������������
	oper.push('#');					// ��ʼ�������ջ
	for (string::iterator it = formula.begin(); *it != '#';) {
		if (IsNumber(*it)) {		// ���������ַ���¼���������ֲ���
			NumberType temp = GetaNumber(it);

			numb.push(temp);
		}
		else if (*it == '(') {		// ����'(' ֱ����ջ
			oper.push('(');
			it++;
		}
		else if (*it == ')') {		// ����')' ����������������
			while (oper.top() != '(')
				if (!SimpOneStep(it)) return 0;
			oper.pop();
			it++;
		}
		else if (IsOperator(*it)) {					// ���������
			if (*it == '-' && *(it - 1) == '(') {	// ����'-'�Ƿ��ʾ����		
				numb.push(0);
			}
			if (IsPriority(*it, oper.top())) {	// ������
				oper.push(*it);
				it++;
			}
			else {								// ������
				if (!SimpOneStep(it)) return 0;
			}
		}
		else if (*it == ' ') {					// �����ո񣬺��Կո񡣲��Ӵ��ж���������ڿո�
			it++;
		}
		else {					// �����Ƿ��ַ�
			return FoundIllegalInput();
		}
	}

	if (numb.size() == 1) return numb.top();
	else return FoundIllegalInput();			// ��ֵ����ֵ֮��ո��ǲ������

}


