/*
给出一个按照“扩展遍历序列”的扩展先序遍历序列字符串，'.' 代表空的子节点，大写字母代表节点内容。
请通过这个字符串建立二叉树，并分别采用“递归”的先序、中序、后序遍历算法输出该树的每个非空节点构成的序列。

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
#define MAXLEN 128

// 从带扩展的先序遍历序列创建二叉树
void createBinTreeNode_Pre(BinTreeNode* parent, char** pData) {
	assert(parent != NULL && pData != NULL);

	if ((**pData) == '.') {
		(*pData)++;
	}
	else if (isalpha(**pData)) {
		//printf("%c", **pData);
		(*parent) = newBinTreeNode(**pData);
		(*pData)++;
		createBinTreeNode_Pre(&(*parent)->left, pData);
		createBinTreeNode_Pre(&(*parent)->right, pData);
	}
	else {
		assert(false);	// 非法字符
	}
}

// 先序创建树结点
BinTree createBinTree_Pre(char* const arrData) {
	BinTree tree = newBinTree();
	if (arrData == NULL) return tree;
	char* itData = arrData;
	createBinTreeNode_Pre(&tree->root, &itData);
	return tree;
}

// 打印结点内容
void printTreeNode(BinTreeNode const node) {
	printf("%c", node->data);
}

