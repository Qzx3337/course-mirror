/*
二叉树的最近公共祖先
题目：给定一棵二叉树，找到两个结点的最近公共祖先。
输入：二叉树的前序遍历序列和中序遍历序列，以及两个结点的数据。
输出：最近公共祖先的数据。
思路：根据前序遍历序列和中序遍历序列建立二叉树，然后深度优先搜索，获取根到两个结点的路径，最后从路径的尾部开始比较，找到最后一个相同的结点，即为最近公共祖先。
时间复杂度：O(n)，n为二叉树的结点数。
空间复杂度：O(n)，n为二叉树的结点数。

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
#define StackElemType BinTreeNode
#include "LinkStack.h"


/* 打印结点内容 */
void printTreeNode(BinTreeNode const node)
{
	assert(node != NULL);
	printf("%c", node->data);
}

char* g_indexIn[128];			// 中序遍历序列中每个结点的位置

/// 函数声明

BinTreeNode makeNodeFromPreIn(char** ppData, char* const secLeft, char* const secRight);
BinTree makeTreeFromPreIn(char* const preSec, char* const inSec);
void myDFS(BinTreeNode const root, Stack sta, char ch, bool* flag);
Stack getPath(BinTree const tree, char const ch);
bool getLCA(BinTree const tree, char const ch1, char const ch2, char* ch3);
void viewSta(Stack sta);

/// 函数实现

/*
从前序遍历序列和中序遍历序列建立二叉树的结点。
ppData: 前序遍历序列的指针；secLeft: 中序遍历序列的左边界；secRight: 中序遍历序列的右边界。
返回：新建二叉树结点。
*/
BinTreeNode makeNodeFromPreIn(char** ppData, char* const secLeft, char* const secRight)
{
    char* pData = *ppData;
	if(secLeft == secRight) return NULL;
	if(*pData == '\0') return NULL;

	BinTreeNode node = newBinTreeNode(*pData);
	*ppData = pData + 1;
	char* pMid = g_indexIn[*pData];
	node->left = makeNodeFromPreIn(ppData, secLeft, pMid);
	node->right = makeNodeFromPreIn(ppData, pMid + 1, secRight);
	return node;
}

/*
从根据前序遍历序列和中序遍历序列建立二叉树
preSec: 前序遍历序列；inSec: 中序遍历序列。
返回：新建二叉树。
*/ 
BinTree makeTreeFromPreIn(char* const preSec, char* const inSec)
{
	assert(inSec != NULL);
	BinTree tree = newBinTree();
	char* i;
	for (i = inSec; *i != '\0'; i++) {
		g_indexIn[*i] = i;
	}
	char* pData = preSec;
	tree->root = makeNodeFromPreIn(&pData, inSec, inSec + strlen(inSec));

	return tree;
}

/* 
深度优先搜索，获取根到结点的路径，存入栈中。
root: 根结点；sta: 存储根到结点的路径；ch: 目标结点数据；flag: 标记是否找到了结点；
返回：void。
*/
void myDFS(BinTreeNode const root, Stack sta, char const ch, bool* flag)
{
	if (*flag) return;				// 已经找到了结点，不再继续搜索
	if (root == NULL) return;		// 空结点，不再继续搜索
	if (root->data == ch) {			// 找到了目标结点
		pushSta(sta, root);			// 将目标结点入栈
		*flag = true;				// 标记已经找到了结点
		return;
	}
	pushSta(sta, root);				// 保护现场
	myDFS(root->left, sta, ch, flag);
	myDFS(root->right, sta, ch, flag);
	if (!(*flag)) popSta(sta);		// 如果没有找到目标结点，恢复现场
}

/*
获取根到结点的路径，存入栈中。
tree: 二叉树；ch: 目标结点数据；
返回：存储根到结点的路径的栈。
*/
Stack getPath(BinTree const tree, char const ch)
{
	Stack sta = newStack();			// 存储根到结点的路径
	bool flag = false;				// 标记是否找到了结点
	myDFS(tree->root, sta, ch, &flag);	// 深度优先搜索，获取根到结点的路径，存入栈中
	if(flag) {
		return sta;
	}
	else {
		destoryStack(sta);
		return NULL;
	}
}

// 打印栈中的内容
void viewSta(Stack sta)
{
	printf("\nview stack: ");
	printf("size= %d\n(", getStaSize(sta));

	LinkStackNode* p = sta->top->next;
	while (p != NULL) {
		printf("%c", p->data->data);
		p = p->next;
	}
	printf(")\n");
}

/*
获取两个结点的最近公共祖先
tree: 二叉树；ch1: 结点1；ch2: 结点2；ch3: 最近公共祖先
返回：是否找到了最近公共祖先
*/
bool getLCA(BinTree const tree, char const ch1, char const ch2, char* ch3)
{
	assert(ch3 != NULL);
	Stack path1 = getPath(tree, ch1);			// 获取根到结点的路径，存入栈中
	Stack path2 = getPath(tree, ch2);

	//assert(path1 != 0);
	//assert(path2 != 0);
	if(path1 == NULL || path2 == NULL) {			// 如果有一个结点不存在，返回false
		destoryStack(path1);
		destoryStack(path2);
		return false;
	}

	//viewSta(path1);
	//viewSta(path2);

	if (getStaSize(path1) > getStaSize(path2)) {	// 排序，path1存更短的路径
		Stack tmpSta = path1;
		path1 = path2;
		path2 = tmpSta;
	}
	while (getStaSize(path2) > getStaSize(path1)) {	// 保证path1的大小小于等于path2的大小
		popSta(path2);
	}
	if (getStaTop(path1) == getStaTop(path2)) {		// 如果两个路径的重叠，返回false
		destoryStack(path1);
		destoryStack(path2);
		return false;
	}
	while (getStaTop(path1) != getStaTop(path2)) {	// 找到最近公共祖先
		popSta(path1);
		popSta(path2);
	}
	*ch3 = getStaTop(path1)->data;

	destoryStack(path1);					// 释放栈空间
	destoryStack(path2);
	return true;
}




