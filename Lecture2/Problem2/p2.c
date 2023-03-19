/*****************

请使用顺序栈实现回文串的判断。

language: C

***************/


#include "p2.h"

int main() {

	// 读入
	char str[MAX_LENGTH];
	gets(str);
	int len = strlen(str);

	// 定义栈
	Stack s;
	InitStack(&s);

	// 入栈
	int i;			// 结果标志位
	for (i = 0; i < len >> 1 ; i++) {	// 入栈前一半的字符
		PushStack(&s, str[i]);
	}
	if (len % 2) i++;
	//printf("%c\n", str[i]);
	//printf("%d\n", GetSize(&s));

	// 出栈
	int ans = 1;
	for (; !IsEmpty(&s);i++) {			// 全部出栈
		if (GetTop(&s) != str[i]) {		// 逐字符比对，出错则置标志位
			ans = 0;
			break;
		}
		PopStack(&s);
	}
	if (i != len) ans = 0;				// 要求全部出栈

	// 输出结果，根据标志位
	if (ans) printf("yes!\n");
	else printf("no!\n");

	return 0;
}
