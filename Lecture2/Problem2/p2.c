/*****************

��ʹ��˳��ջʵ�ֻ��Ĵ����жϡ�

language: C

***************/


#include "p2.h"

int main() {

	// ����
	char str[MAX_LENGTH];
	gets(str);
	int len = strlen(str);

	// ����ջ
	Stack s;
	InitStack(&s);

	// ��ջ
	int i;			// �����־λ
	for (i = 0; i < len >> 1 ; i++) {	// ��ջǰһ����ַ�
		PushStack(&s, str[i]);
	}
	if (len % 2) i++;
	//printf("%c\n", str[i]);
	//printf("%d\n", GetSize(&s));

	// ��ջ
	int ans = 1;
	for (; !IsEmpty(&s);i++) {			// ȫ����ջ
		if (GetTop(&s) != str[i]) {		// ���ַ��ȶԣ��������ñ�־λ
			ans = 0;
			break;
		}
		PopStack(&s);
	}
	if (i != len) ans = 0;				// Ҫ��ȫ����ջ

	// �����������ݱ�־λ
	if (ans) printf("yes!\n");
	else printf("no!\n");

	return 0;
}
