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
	printf("%c", node->data);
}

#define StackElemType BinTreeNode
#include "LinkStack.h"

/* 使用栈中序遍历二叉树
参数：
tree : 二叉树的指针；visit：函数指针，执行对二叉树节点的访问操作
*/
void travIn_Sta(BinTree tree, void (*visit)(BinTreeNode node))
{
	Stack stack = newStack();
	BinTreeNode itNode = tree->root;		// 从二叉树根节点开始遍历
	while (itNode != NULL || !isStaEmpty(stack)) {		// 二叉树非空或栈非空
		while (itNode != NULL) {		// 遍历左子树
			pushSta(stack, itNode);
			itNode = itNode->left;
		}
		if (!isStaEmpty(stack)) {		// 回退，遍历右子树
			itNode = getStaTop(stack);	// 获取栈顶元素
			popSta(stack);
			visit(itNode);
			itNode = itNode->right;		// 遍历右子树
		}
	}
	destoryBinTreeNode(itNode);
}

