#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#define mnew(typeName) (typeName*)malloc(sizeof(typeName))
#define mnewarr(typeName, size) (typeName*)malloc(sizeof(typeName)*(size))
#define INF 0x7FFFFFFF

#include "LinkQueue.h"

void printQueInfo(Queue que);

int main() {


	Queue que = newQueue();

	int x;
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

