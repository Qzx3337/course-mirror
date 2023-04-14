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


/* �Ӵ���չ������������д������������ڲ���������Խ��ݹ飩������Ϊ������ĸ��'.'��ʾ��ĩ */
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
		assert(false);	// �Ƿ��ַ�
	}
}

/* �Ӵ���չ������������д��������������ⲿ�ӿڣ�����Ϊ������ĸ��'.'��ʾ��ĩ */
BinTree createBinTree_Pre(char* const arrData)
{
	BinTree tree = newBinTree();
	if (arrData == NULL) return tree;
	char* itData = arrData;
	createBinTreeNode_Pre(&(tree->root), &itData);
	return tree;
}

/* ��ӡ������� */
void printTreeNode(BinTreeNode const node)
{
	printf("%c", node->data);
}

#define StackElemType BinTreeNode
#include "LinkStack.h"

/* ʹ��ջ������������� */
void travIn_Sta(BinTree tree, void (*visit)(BinTreeNode const node))
{
	Stack stack = newLinkStack();
	BinTreeNode* itNode = &(tree->root);
	while (itNode != NULL || !isLinkStackEmpty(stack)) {
		while (itNode != NULL) {
			pushLinkStack(stack, itNode);
			itNode = &((*itNode)->left);
		}
		if (!isLinkStackEmpty(stack)) {
			itNode = popLinkStack(stack);
			visit(**itNode);
			itNode = &((*itNode)->right);
		}
	}
}
