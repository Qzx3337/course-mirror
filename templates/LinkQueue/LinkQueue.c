



#define _CRT_SECURE_NO_WARNINGS 1

#include "LinkQueue.h"
#include <stdio.h>

void printQueInfo(Queue que);

int main() {


	Queue que;
	initQue(&que);

	int x, y;
	for (;;) {
		scanf("%d", &x);
		if (x == 0) {
			popQue(que);
		}
		else {
			pushQue(que, x);
		}
		
		printQueInfo(que);
	}

	return 0;
}

void printQueInfo(Queue que) {
	printf("\nQueue Size = %d\n", getQueSize(que));
	printf("back- ");
	QueNode* it;
	for (it=que->back->next; it!=NULL; it=it->next) {
		printf("%d, ", it->data);
	}
	printf("-front\n");
}