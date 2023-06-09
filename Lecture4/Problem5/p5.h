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


/* 从带扩展的先序遍历序列创建二叉树（内部函数，针对结点递归）。数据为单个字母，'.'表示树末 */
void createBinTreeNode_Pre(BinTreeNode* parent, char** pData)
{
	assert(parent != NULL && pData != NULL);

	if ((**pData) == '#') {
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

/* 打印结点内容 */
void printTreeNode(BinTreeNode const node)
{
	assert(node != NULL);
	printf("%c", node->data);
}

/* 交换结点的左右子树 */
void swapChilds(BinTreeNode node)
{
	assert(node != NULL);
	if (node->left == NULL && node->right == NULL) {
		extern int g_treeNodeCount;
		g_treeNodeCount++;
	}
	else {
		BinTreeNode temp = node->left;
		node->left = node->right;
		node->right = temp;
	}
}

/* 输出带拓展的遍历序列 */
void printLeaves(BinTreeNode const node)
{
	if (node == NULL) {
		printf("#");
	}
	else {
		printLeaves(node->left);
		printLeaves(node->right);
		printf("%c", node->data);
	}
}

