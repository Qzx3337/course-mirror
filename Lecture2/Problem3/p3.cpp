/*******************

输入字符串，四则运算
介绍请阅读 README.MD

language: C++

*******************/

#define _CRT_SECURE_NO_WARNINGS 1

#include "calculator.h"
using namespace std;

int main() {

	// freopen("p3.in", "r", stdin);

	string s;				// 定义字符串
	getline(cin, s);		// 读入一行
	s.erase(s.end() - 1);	// 删除最后一位的无效 '#'
	// cout << s << endl;

	double ans = 0;				// 存结果
	if (CalculateStr(ans, s)) {	// 字符串合法，得到结果
		cout << ans << endl;
	}
	else {						// 字符串不合法
		cout << "error!\n";
	}
	return 0;
}

