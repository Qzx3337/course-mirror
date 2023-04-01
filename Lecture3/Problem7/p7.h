/*
* 
* KMPÀ„∑®£ª
* 
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#define mnew(typeName) (typeName*)malloc(sizeof(typeName))
#define mnewarr(typeName, size) (typeName*)malloc(sizeof(typeName)*(size))
#define INF 0x7FFFFFFF

#define MAX_LINE_LENGTH 256

void printIndex(int line, int col) {
	//printf("Pattern found at index (%d, %d)\n", line, col);
	printf("%d %d\n", line, col);
}

void getNext(char* pattern, int* next) {
	int i = 0;
	int j = -1;
	size_t patternLen = strlen(pattern);
	next[0] = -1;
	while (i < patternLen) {
		if (j == -1 || pattern[i] == pattern[j]) {
			i++, j++;
			next[i] = j;
		}
		else {
			j = next[j];
		}
	}
}

int myKMP(char* text, char* pattern, int* next, int lineNum) {
	int cnt = 0;
	int i = 0;
	int j = 0;
	size_t textLen = strlen(text);
	size_t patternLen = strlen(pattern);
	while (i < textLen) {
		if (j == -1 || text[i] == pattern[j]) {
			i++, j++;
		}
		else {
			j = next[j];
		}
		if (j == patternLen) {
			printIndex(lineNum, i - j + 1);
			cnt++;
			j = next[j];
		}
	}
	return cnt;
}

// Path: Lecture3\Problem8\p8.h
