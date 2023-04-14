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

// �ڲ�����

void createBinTreeNode_Pre(BinTreeNode* parent, char** pData);
void createBinTreeNode_Pos(BinTreeNode* parent, char** pData);
void printTreeNode(BinTreeNode const node);
void printTransTreeNode(BinTreeNode const node, int const depth);

// �ⲿ�ӿ�

BinTree createBinTree_Pre(char* const arrData);
BinTree createBinTree_Pos(char* const arrData);
void printTransTree(BinTree const tree);

// ����ʵ��

/* �Ӵ���չ������������д������������ڲ���������Խ��ݹ飩������Ϊ������ĸ��'.'��ʾ��ĩ */
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


/* �Ӵ���չ�ĺ���������д��������������ڲ���������Խ��ݹ飩����Ϊ������ĸ��'#'��ʾ��ĩ*/ 
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
		assert(false);	// �Ƿ��ַ�
	}
}

/* �Ӵ���չ�ĺ���������д��������������ⲿ�ӿڣ�����Ϊ������ĸ��'#'��ʾ��ĩ*/
BinTree createBinTree_Pos(char* const arrData)
{
	BinTree tree = newBinTree();
	char* pData = arrData;
	size_t len = strlen(arrData);
	pData += len - 1;
	createBinTreeNode_Pos(&(tree->root), &pData);
	return tree;
}

/* ��ӡ������� */
void printTreeNode(BinTreeNode const node)
{
	printf("%c", node->data);
}

/* ������������ʾ�����������ڲ�������������㣩 */
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

/* ������������ʾ�����������ⲿ�ӿڣ�������㣩 */
void printTransTree(BinTree const tree)
{
	if (tree) {
		printTransTreeNode(tree->root, 0);
	}
}

