/*
�������������������
��Ŀ������һ�ö��������ҵ�������������������ȡ�
���룺��������ǰ��������к�����������У��Լ������������ݡ�
���������������ȵ����ݡ�
˼·������ǰ��������к�����������н�����������Ȼ�����������������ȡ������������·��������·����β����ʼ�Ƚϣ��ҵ����һ����ͬ�Ľ�㣬��Ϊ����������ȡ�
ʱ�临�Ӷȣ�O(n)��nΪ�������Ľ������
�ռ临�Ӷȣ�O(n)��nΪ�������Ľ������

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


/* ��ӡ������� */
void printTreeNode(BinTreeNode const node)
{
	assert(node != NULL);
	printf("%c", node->data);
}

char* g_indexIn[128];			// �������������ÿ������λ��

/// ��������

BinTreeNode makeNodeFromPreIn(char** ppData, char* const secLeft, char* const secRight);
BinTree makeTreeFromPreIn(char* const preSec, char* const inSec);
void myDFS(BinTreeNode const root, Stack sta, char ch, bool* flag);
Stack getPath(BinTree const tree, char const ch);
bool getLCA(BinTree const tree, char const ch1, char const ch2, char* ch3);
void viewSta(Stack sta);

/// ����ʵ��

/*
��ǰ��������к�����������н����������Ľ�㡣
ppData: ǰ��������е�ָ�룻secLeft: ����������е���߽磻secRight: ����������е��ұ߽硣
���أ��½���������㡣
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
�Ӹ���ǰ��������к�����������н���������
preSec: ǰ��������У�inSec: ����������С�
���أ��½���������
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
���������������ȡ��������·��������ջ�С�
root: ����㣻sta: �洢��������·����ch: Ŀ�������ݣ�flag: ����Ƿ��ҵ��˽�㣻
���أ�void��
*/
void myDFS(BinTreeNode const root, Stack sta, char const ch, bool* flag)
{
	if (*flag) return;				// �Ѿ��ҵ��˽�㣬���ټ�������
	if (root == NULL) return;		// �ս�㣬���ټ�������
	if (root->data == ch) {			// �ҵ���Ŀ����
		pushSta(sta, root);			// ��Ŀ������ջ
		*flag = true;				// ����Ѿ��ҵ��˽��
		return;
	}
	pushSta(sta, root);				// �����ֳ�
	myDFS(root->left, sta, ch, flag);
	myDFS(root->right, sta, ch, flag);
	if (!(*flag)) popSta(sta);		// ���û���ҵ�Ŀ���㣬�ָ��ֳ�
}

/*
��ȡ��������·��������ջ�С�
tree: ��������ch: Ŀ�������ݣ�
���أ��洢��������·����ջ��
*/
Stack getPath(BinTree const tree, char const ch)
{
	Stack sta = newStack();			// �洢��������·��
	bool flag = false;				// ����Ƿ��ҵ��˽��
	myDFS(tree->root, sta, ch, &flag);	// ���������������ȡ��������·��������ջ��
	if(flag) {
		return sta;
	}
	else {
		destoryStack(sta);
		return NULL;
	}
}

// ��ӡջ�е�����
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
��ȡ�������������������
tree: ��������ch1: ���1��ch2: ���2��ch3: �����������
���أ��Ƿ��ҵ��������������
*/
bool getLCA(BinTree const tree, char const ch1, char const ch2, char* ch3)
{
	assert(ch3 != NULL);
	Stack path1 = getPath(tree, ch1);			// ��ȡ��������·��������ջ��
	Stack path2 = getPath(tree, ch2);

	//assert(path1 != 0);
	//assert(path2 != 0);
	if(path1 == NULL || path2 == NULL) {			// �����һ����㲻���ڣ�����false
		destoryStack(path1);
		destoryStack(path2);
		return false;
	}

	//viewSta(path1);
	//viewSta(path2);

	if (getStaSize(path1) > getStaSize(path2)) {	// ����path1����̵�·��
		Stack tmpSta = path1;
		path1 = path2;
		path2 = tmpSta;
	}
	while (getStaSize(path2) > getStaSize(path1)) {	// ��֤path1�Ĵ�СС�ڵ���path2�Ĵ�С
		popSta(path2);
	}
	if (getStaTop(path1) == getStaTop(path2)) {		// �������·�����ص�������false
		destoryStack(path1);
		destoryStack(path2);
		return false;
	}
	while (getStaTop(path1) != getStaTop(path2)) {	// �ҵ������������
		popSta(path1);
		popSta(path2);
	}
	*ch3 = getStaTop(path1)->data;

	destoryStack(path1);					// �ͷ�ջ�ռ�
	destoryStack(path2);
	return true;
}




