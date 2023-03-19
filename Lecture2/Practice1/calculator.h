/****************

进行优化：
允许使用空格（方便我们看算式结构）
允许输入小数（运算过程使用 double 变量）
允许使用幂运算（允许小数幂，也就是开根号啦）

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

stack<NumberType> numb;		// 存操作数
stack<char> oper;			// 存操作符
map<char, int> opLv;		// 存运算符优先级表

/*运算符 优先级制表*/
void MakeMap() {
	opLv['^'] = 1;
	opLv['*'] = 2;
	opLv['/'] = 2;
	opLv['+'] = 3;
	opLv['-'] = 3;
	opLv['('] = 4;
	opLv['#'] = 9;
}

/*判断运算符优先级*/
bool IsPriority(char a, char b) {
	return opLv[a] < opLv[b];
}

/*判断是否为数字*/
bool IsNumber(char ch) {
	return ('0' <= ch && ch <= '9');
}

/* 判断是否为运算符 */
bool IsOperator(char ch) {
	return (opLv.find(ch) != opLv.end());
}

/*计算单步字符运算*/
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

/* 发现非法输入*/
bool FoundIllegalInput() {
	return false;
}

/*获取一个整数*/
NumberType GetaNumber(string::iterator& it) {
	NumberType temp = 0;
	// 适用于int
	for (; IsNumber(*it); it++)
		temp = temp * 10 + (int)(*it - '0');
	// 特判小数
	if (*it == '.') {
		it++;
		for (double pt = 0.1; IsNumber(*it); it++, pt *= 0.1) {
			temp += pt * (int)(*it - '0');
		}
	}
	return temp;
}

/* 向下计算一步 */
bool SimpOneStep() {

	// 判断非法输入

	if (numb.size() < 2) return FoundIllegalInput();
	if (oper.size() < 1) return FoundIllegalInput();

	// 合法输入可以化简

	NumberType tb = numb.top();
	numb.pop();
	NumberType ta = numb.top();
	numb.pop();
	ta = CalcChar(oper.top(), ta, tb);
	numb.push(ta);

	// 输出过程
	// printf("发生运算 %c 得到 %lf\n", oper.top(), ta);

	oper.pop();
	return true;
}

/*计算四则运算，字符串类型*/
bool CalculateStr(NumberType& x, string& formula) {
	MakeMap();							// 初始化运算符优先级列表
	formula = "(" + formula + ")#";		// 初始化待处理数组
	oper.push('#');						// 初始化运算符栈
	for (string::iterator it = formula.begin(); *it != '#';) {
		if (IsNumber(*it)) {			// 读到数字字符，录入整个数字部分
			NumberType temp = GetaNumber(it);

			// 输出过程
			// printf("读入数值：%lf\n", temp);
			numb.push(temp);
		}
		else if (*it == '(') {			// 读到'(' 直接入栈
			oper.push('(');
			it++;
		}
		else if (*it == ')') {			// 读到')' 化简整个括号区间
			while (oper.top() != '(')
				if (!SimpOneStep()) return false;
			oper.pop();
			it++;
		}
		else if (IsOperator(*it)) {					// 读到运算符
			if (*it == '-' && *(it - 1) == '(') {	// 特判'-'是否表示负号		
				numb.push(0);
			}
			if (IsPriority(*it, oper.top())) {	// 更优先
				oper.push(*it);
				it++;
			}
			else {								// 不优先
				if (!SimpOneStep()) return false;
			}
		}
		else {									// 读到非法字符
			return FoundIllegalInput();
		}
	}

	if (numb.size() == 1) {					// 输入合法，则操作数栈顶为结果
		x = numb.top();
		return true;
	}
	else {
		return FoundIllegalInput();			// 数值与数值之间空格是不允许的
	}

}


/******** 以下是为了输出步骤专用，还在测试中 ****************************/

void PrintWithBracket(NumberType x) {
	if (x < 0) cout << "(" << x << ")";
	else cout << x;
}

/* 输出当前运算步骤 */
void ShowCurrentStep(string::iterator it) {
	stack<NumberType> temNumb;		// 存操作数
	stack<char> temOper;			// 存操作符

	// 逆向阅读两个栈
	while (oper.top() != '#') {
		temOper.push(oper.top());
		oper.pop();
	}
	while (!numb.empty()) {
		temNumb.push(numb.top());
		numb.pop();
	}

	// 输出栈内的表达式 
	while (!temOper.empty()) {
		if (temOper.top() == '(') {				// 栈顶是括号
			printf("(");
		}
		else {									// 栈顶是运算符
			PrintWithBracket(temNumb.top());					// 打印一个数字
			if (temOper.top() == '+' || temOper.top() == '-')	// 对于加减号多打印空格以便观察
				cout << " " << temOper.top() << " ";
			else cout << temOper.top();
			numb.push(temNumb.top()); temNumb.pop();			// 复原操作数栈
		}
		oper.push(temOper.top()); temOper.pop();				// 复原操作符栈
	}
	PrintWithBracket(temNumb.top());			// 打印剩余的一个数
	numb.push(temNumb.top()); temNumb.pop();	// 复原操作数栈

	// 输出还没入栈的表达式
	for (; *it != '#'; it++) {
		cout << *it;
	}
	printf("\n");

}

/* 向下计算一步，还要输出当前步骤 */
bool SimpOneStep(string::iterator const it) {

	// 判断非法输入

	if (numb.size() < 2) return FoundIllegalInput();
	if (oper.size() < 1) return FoundIllegalInput();

	// 合法输入可以化简

	NumberType tb = numb.top();
	numb.pop();
	NumberType ta = numb.top();
	numb.pop();
	ta = CalcChar(oper.top(), ta, tb);
	numb.push(ta);

	oper.pop();
	// 输出过程
	ShowCurrentStep(it);

	return true;
}

/* 计算四则运算，字符串类型，还要求输出步骤 */
NumberType CalculateStrStepwise(string& formula) {
	MakeMap();						// 初始化运算符优先级列表
	formula = "(" + formula + ")#";	// 初始化待处理数组
	oper.push('#');					// 初始化运算符栈
	for (string::iterator it = formula.begin(); *it != '#';) {
		if (IsNumber(*it)) {		// 读到数字字符，录入整个数字部分
			NumberType temp = GetaNumber(it);

			numb.push(temp);
		}
		else if (*it == '(') {		// 读到'(' 直接入栈
			oper.push('(');
			it++;
		}
		else if (*it == ')') {		// 读到')' 化简整个括号区间
			while (oper.top() != '(')
				if (!SimpOneStep(it)) return 0;
			oper.pop();
			it++;
		}
		else if (IsOperator(*it)) {					// 读到运算符
			if (*it == '-' && *(it - 1) == '(') {	// 特判'-'是否表示负号		
				numb.push(0);
			}
			if (IsPriority(*it, oper.top())) {	// 更优先
				oper.push(*it);
				it++;
			}
			else {								// 不优先
				if (!SimpOneStep(it)) return 0;
			}
		}
		else if (*it == ' ') {					// 读到空格，忽略空格。不加此判断则不允许存在空格。
			it++;
		}
		else {					// 读到非法字符
			return FoundIllegalInput();
		}
	}

	if (numb.size() == 1) return numb.top();
	else return FoundIllegalInput();			// 数值与数值之间空格是不允许的

}


