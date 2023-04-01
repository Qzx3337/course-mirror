/*******************
* 
* tag: ÎÄ¼þ¶ÁÈë£»KMP;
* 
* language: C.
* 
**********************/
#define _CRT_SECURE_NO_WARNINGS 1
#include "p7.h"

int main() {

	FILE* fp;
	char str[MAX_LINE_LENGTH];

	fp = fopen("a.txt", "r");
	if (fp == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	char pattern[MAX_LINE_LENGTH];
	scanf("%s", pattern);               // read pattern string

	int next[MAX_LINE_LENGTH];
	getNext(pattern, next);             // initialize KMP

	int cnt = 0;
	int i;                              // read text line by line
	for (i = 1; fgets(str, MAX_LINE_LENGTH, fp) != NULL; i++) {
		cnt += myKMP(str, pattern, next, i);
	}

	fclose(fp);

	if (cnt) printf("%d\n", cnt);
	else printf("None\n");

	return 0;   
}

