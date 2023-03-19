/*******************

输入字符串，四则运算

language: C++

*******************/
#include "calculator.h"
using namespace std;

int main() {

	string s;
	getline(cin, s);

	// auto ans = CalculateStr(s);
	auto ans = CalculateStrStepwise(s);

	printf("\nans = ");
	cout << ans << endl;

	return 0;
}

