/*
二叉树功能实现
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

void printTreeNode(BinTreeNode const node);
void createBinTreeNode_Pre(BinTreeNode* father, char** pData);
BinTree createBinTree_Pre(char* const arrData);


/* 打印结点内容 */
void printTreeNode(BinTreeNode const node)
{
	assert(node != NULL);
	printf("%c", node->data);
}


/* 从带扩展的先序遍历序列创建二叉树（内部函数，针对结点递归）。数据为单个字母，'.'表示树末 */
void createBinTreeNode_Pre(BinTreeNode* father, char** pData)
{
	assert(father != NULL && pData != NULL);

	if ((**pData) == '.') {
		(*pData)++;
	}
	else if (isalpha(**pData)) {
		//printf("%c", **pData);
		(*father) = newBinTreeNode(**pData);
		(*pData)++;
		createBinTreeNode_Pre(&(*father)->left, pData);
		createBinTreeNode_Pre(&(*father)->right, pData);
	}
	else {
		//assert(false);	// 非法字符
		exit(1);
	}
}

/* 从带扩展的先序遍历序列创建二叉树。（外部接口）数据为单个字母，'.'表示树末 */
BinTree createBinTree_Pre(char* const arrData)
{
	BinTree tree = newBinTree();
	if (arrData == NULL) return tree;
	char* itData = arrData;
	createBinTreeNode_Pre(&(tree->root), &itData);
	return tree;
}

