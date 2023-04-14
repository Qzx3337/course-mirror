#pragma once
/*************

ģ�壺������
���ԣ���׼C.

*************/

#ifndef OVERFLOW
#define OVERFLOW 3
#endif // !OVERFLOW
#ifndef DataType
#define DataType char
#endif // !DataType

// ���������ṹ��
typedef struct _BinTreeNode
{
	DataType data;
	struct _BinTreeNode *left;
	struct _BinTreeNode *right;
} _BinTreeNode, * BinTreeNode;

// �������ṹ��
typedef struct _BinTree
{
	_BinTreeNode *root;
}_BinTree, *BinTree;


// ���������ӿ�

BinTreeNode newBinTreeNode(DataType data);
void travPreNode(BinTreeNode root, void (*visit) (BinTreeNode));
void travInNode(BinTreeNode root, void (*visit) (BinTreeNode));
void travPostNode(BinTreeNode root, void (*visit) (BinTreeNode));
void travLevelNode(BinTreeNode root, void (*visit) (BinTreeNode));
int getTreeDepthNode(BinTreeNode root);

// �������ӿ�

BinTree newBinTree();
void travPre(BinTree tree, void (*visit) (BinTreeNode));
void travIn(BinTree tree, void (*visit) (BinTreeNode));
void travPost(BinTree tree, void (*visit) (BinTreeNode));
void travLevel(BinTree tree, void (*visit) (BinTreeNode));
int getTreeDepth(BinTree tree);


// ���������ӿ�ʵ��

// �����½��
BinTreeNode newBinTreeNode(DataType data)
{
	_BinTreeNode *node = (_BinTreeNode *)malloc(sizeof(_BinTreeNode));
	if (node == NULL) exit(OVERFLOW);
	node->left = NULL;
	node->right = NULL;
	node->data = data;
	return node;
}

// ǰ��������
inline void travPreNode(BinTreeNode root, void(*visit)(BinTreeNode))
{
	if (root != NULL)
	{
		visit(root);
		travPreNode(root->left, visit);
		travPreNode(root->right, visit);
	}
}

// ����������
inline void travInNode(BinTreeNode root, void(*visit)(BinTreeNode))
{
	if (root != NULL)
	{
		travInNode(root->left, visit);
		visit(root);
		travInNode(root->right, visit);
	}
}


// ����������
inline void travPostNode(BinTreeNode root, void (*visit) (BinTreeNode)) {
    if (root != NULL)
	{
		travPostNode(root->left, visit);
		travPostNode(root->right, visit);
		visit(root);
	}
}

// �ӿ�ʵ��׼����������С� �ӿڣ�����������

#define QueueElemType BinTreeNode
#include "LinkQueue.h"

// ����������
inline void travLevelNode(BinTreeNode root, void(*visit)(BinTreeNode))
{
    Queue q = newQueue();
	pushQue(q, root);
	while (!isEmptyQue(q))
	{
		BinTreeNode tmpNode = getBack(q);
		popQue(q);
		visit(tmpNode);
		if (tmpNode->left) {
			pushQue(q, tmpNode->left);
		}
		if (tmpNode->right) {
			pushQue(q, tmpNode->right);
		}
	}
	freeQueue(q);
}
#undef QueueElemType

// ��ȡ�������
inline int getTreeDepthNode(BinTreeNode root) // che
{
	int hl, hr, max;
    if (root == NULL) return 0;
	else {
		hl = getTreeDepthNode(root->left);
		hr = getTreeDepthNode(root->right);
		max = (hl > hr) ? hl : hr;
		return (max + 1);
	}
}


// �������ӿ�ʵ��

// ��������
BinTree newBinTree()
{
	BinTree tree;
	tree = (BinTree)malloc(sizeof(_BinTree));
	if (tree == NULL) exit(OVERFLOW);
	tree->root = NULL;
	return tree;
}

// ǰ�����
inline void travPre(BinTree tree, void (*visit)(BinTreeNode))
{
	assert(tree->root != NULL);
	if (tree->root) {
		travPreNode(tree->root, visit);
	}
}

// �������
inline void travIn(BinTree tree, void (*visit)(BinTreeNode))
{
	assert(tree->root != NULL);
	if (tree->root) {
		travInNode(tree->root, visit);
	}
}

// �������
inline void travPost(BinTree tree, void (*visit)(BinTreeNode)) {
	assert(tree->root != NULL);
	if (tree->root) {
		//printf("root exist\n");
		travPostNode(tree->root, visit);
	}
}

// �������
inline void travLevel(BinTree tree, void(*visit)(BinTreeNode))
{
	assert(tree->root != NULL);
	if (tree->root) {
		travLevelNode(tree->root, visit);
	}
}

// ��ȡ�������
inline int getTreeDepth(BinTree const tree)
{
	return getTreeDepthNode(tree->root);
}

