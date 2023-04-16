/*

language: C.
*/
#pragma once

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

#include "BinaryTree.h"
#include "LinkStack.h"


/* 打印结点内容 */
void printTreeNode(BinTreeNode const node)
{
	assert(node != NULL);
	printf("%c", node->data);
}


BinTree makeTreeFromPreIn(char* const preSec, char* const inSec);
Stack getPath(char const ch1);
int getLCA(BinTree const tree, char const ch1, char const ch2);


BinTree makeTreeFromPreIn(char* const preSec, char* const inSec)
{
	int indexInSec[128] = { 0 };


	// pass

	return NULL;
}

Stack getPath(char const ch1)
{
	// pass
	return NULL;
}

int getLCA(BinTree const tree, char const ch1, char const ch2)
{
	Stack s1 = getPath(ch1);
	Stack s2 = getPath(ch2);
	if (getStaSize(s1) > getStaSize(s2)) {
		Stack tmpSta = s1;
		s1 = s2;
		s2 = tmpSta;
	}
	while (getStaSize(s2) > getStaSize(s1)) {
		popSta(s2);
	}

	// pass

	return 0;
}




