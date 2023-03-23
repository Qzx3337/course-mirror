/**************

Problem 5: 中缀表达式转后缀表达式
介绍请阅读 README.MD

 language: C++

*****************/

#include "p5.h"

using namespace std;

int main() {
	
	// freopen("p5.in", "r", stdin);

	string s1;					// 字符串 中缀表达式
	cin >> s1;					// 读入字符串 中缀表达式
	s1.erase(s1.end() - 1);		// 删除末位的无效字符 '#'
	// cout << s1 << endl;

	string s2;					// 后缀表达式
	if (Infix2Postfix(s1, s2)) {	//中缀转后缀，判断是否合法
		cout << s2 << endl;		// 合法输出后缀表达式
	}
	else {
		cout << "error!\n";		// 不合法
	}

	return 0;
}

