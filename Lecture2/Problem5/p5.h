#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <stack>
#include <map>
using namespace std;

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
	return ('A' <= ch && ch <= 'Z');
}

/* 判断是否为运算符 */
bool IsOperator(char ch) {
	return (opLv.find(ch) != opLv.end());
}

/* 向下计算一步 */
bool SimpOneStep(string& formPos) {
	if (oper.size() < 1) return false;	// 判断非法输入，直接返回
	formPos = formPos + oper.top();		// 合法输入，化成后缀表达式
	oper.pop();							// 操作符栈 出栈
	return true;
}

/* 中缀表达式 化为 后缀表达式 */
bool Infix2Postfix(string& formInfi, string& formPos) {
	MakeMap();							// 初始化运算符优先级列表
	formInfi = "(" + formInfi + ")#";	// 初始化待处理数组
	oper.push('#');						// 初始化运算符栈
	for (string::iterator it = formInfi.begin(); *it != '#';) {
		if (IsNumber(*it)) {			// 读到数字字符，直接放入后缀表达式
			formPos = formPos + (*it);
			it++;
		}
		else if (*it == '(') {			// 读到'(' 直接入栈
			oper.push('(');
			it++;
		}
		else if (*it == ')') {			// 读到')' 化简整个括号区间
			while (oper.top() != '(')
				if (!SimpOneStep(formPos)) return false;
			oper.pop();					// 操作符 '('出栈
			it++;
		}
		else if (IsOperator(*it)) {				// 读到运算符
			if (IsPriority(*it, oper.top())) {	// 更优先
				oper.push(*it);
				it++;
			}
			else {								// 不优先
				if (!SimpOneStep(formPos)) return false;
			}
		}
		else {					// 读到非法字符
			return false;
		}
	}

	return true;
}
