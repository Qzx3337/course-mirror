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

// 内部函数

void createBinTreeNode_Pre(BinTreeNode* parent, char** pData);
void createBinTreeNode_Pos(BinTreeNode* parent, char** pData);
void printTreeNode(BinTreeNode const node);
void printTransTreeNode(BinTreeNode const node, int const depth);

// 外部接口

BinTree createBinTree_Pre(char* const arrData);
BinTree createBinTree_Pos(char* const arrData);
void printTransTree(BinTree const tree);

// 函数实现

/* 从带扩展的先序遍历序列创建二叉树（内部函数，针对结点递归）。数据为单个字母，'.'表示树末 */
void createBinTreeNode_Pre(BinTreeNode* parent, char** pData)
{
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

/* 从带扩展的先序遍历序列创建二叉树。（外部接口）数据为单个字母，'.'表示树末 */
BinTree createBinTree_Pre(char* const arrData)
{
	BinTree tree = newBinTree();
	if (arrData == NULL) return tree;
	char* itData = arrData;
	createBinTreeNode_Pre(&(tree->root), &itData);
	return tree;
}


/* 从带扩展的后序遍历序列创建二叉树。（内部函数，针对结点递归）数据为单个字母，'#'表示树末*/ 
void createBinTreeNode_Pos(BinTreeNode* parent, char** pData)
{
	assert(parent != NULL && pData != NULL);
	if ((**pData) == '#') {
		(*pData)--;
	}
	else if (isalpha(**pData)) {
		//printf("%c", **pData);
		(*parent) = newBinTreeNode(**pData);
		(*pData)--;
		createBinTreeNode_Pos(&(*parent)->right, pData);
		createBinTreeNode_Pos(&(*parent)->left, pData);
	}
	else {
		assert(false);	// 非法字符
	}
}

/* 从带扩展的后序遍历序列创建二叉树。（外部接口）数据为单个字母，'#'表示树末*/
BinTree createBinTree_Pos(char* const arrData)
{
	BinTree tree = newBinTree();
	char* pData = arrData;
	size_t len = strlen(arrData);
	pData += len - 1;
	createBinTreeNode_Pos(&(tree->root), &pData);
	return tree;
}

/* 打印结点内容 */
void printTreeNode(BinTreeNode const node)
{
	printf("%c", node->data);
}

/* 按横向树形显示二叉树。（内部函数，遍历结点） */
void printTransTreeNode(BinTreeNode const node, int const depth)
{
	if (!node) return;
	printTransTreeNode(node->right, depth + 1);
	int i;
	for (i = 0; i < depth; i++) {
		printf("  ");
	}
	printf("%c\n", node->data);

	printTransTreeNode(node->left, depth + 1);
}

/* 按横向树形显示二叉树。（外部接口，遍历结点） */
void printTransTree(BinTree const tree)
{
	if (tree) {
		printTransTreeNode(tree->root, 0);
	}
}

