/*
����������ʵ��
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


/* ��ӡ������� */
void printTreeNode(BinTreeNode const node)
{
	assert(node != NULL);
	printf("%c", node->data);
}


/* �Ӵ���չ������������д������������ڲ���������Խ��ݹ飩������Ϊ������ĸ��'.'��ʾ��ĩ */
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
		//assert(false);	// �Ƿ��ַ�
		exit(1);
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

