#pragma once
/*************

模板：二叉树
语言：标准C.

*************/

#ifndef OVERFLOW
#define OVERFLOW 3
#endif // !OVERFLOW
#ifndef DataType
#define DataType char
#endif // !DataType

// 二叉树结点结构体
typedef struct _BinTreeNode
{
	DataType data;
	struct _BinTreeNode *left;
	struct _BinTreeNode *right;
} _BinTreeNode, * BinTreeNode;

BinTreeNode newBinTreeNode(DataType const data);
void destoryBinTreeNode(BinTreeNode node);

inline BinTreeNode newBinTreeNode(DataType const data)
{
	BinTreeNode node = (_BinTreeNode*)malloc(sizeof(_BinTreeNode));
	if (node == NULL) exit(OVERFLOW);
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

inline void destoryBinTreeNode(BinTreeNode node)
{
	if (node == NULL) return;
	free(node);
}

// 二叉树结构体
typedef BinTreeNode BinTree;


// 二叉树接口

BinTree newBinTree();
void destoryBinTree(BinTree tree);
void travPre(BinTree tree, void (*visit)(BinTreeNode));
void travIn(BinTree tree, void (*visit)(BinTreeNode));
void travPost(BinTree tree, void (*visit)(BinTreeNode));
void travLevel(BinTree tree, void (*visit)(BinTreeNode));
int getTreeDepth(BinTree tree);


BinTree newBinTree()
{
	BinTree tree = (_BinTreeNode*)malloc(sizeof(_BinTreeNode));
	if (tree == NULL) exit(OVERFLOW);
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

void destoryBinTree(BinTree tree)
{
	if (tree == NULL) return;
	destoryBinTree(tree->left);
	destoryBinTree(tree->right);
	free(tree);
}

void travPre(BinTree tree, void (*visit)(BinTreeNode))
{
	if (tree == NULL) return;
	visit(tree);
	travPre(tree->left, visit);
	travPre(tree->right, visit);
}

void travIn(BinTree tree, void (*visit)(BinTreeNode))
{
	if (tree == NULL) return;
	travIn(tree->left, visit);
	visit(tree);
	travIn(tree->right, visit);
}

void travPost(BinTree tree, void (*visit)(BinTreeNode))
{
	if (tree == NULL) return;
	travPost(tree->left, visit);
	travPost(tree->right, visit);
	visit(tree);
}


#define QueueElemType BinTreeNode
#include "LinkQueue.h"

void travLevel(BinTree tree, void (*visit)(BinTreeNode))
{
	if (tree == NULL) return;
	Queue queue = newQueue();
	pushQue(queue, tree);
	while (!isEmptyQue(queue))
	{
		BinTreeNode node = getBack(queue);
		popQue(queue);
		visit(node);
		if (node->left != NULL) pushQue(queue, node->left);
		if (node->right != NULL) pushQue(queue, node->right);
	}
	destoryQueue(queue);
}
#undef QueueElemType

int getTreeDepth(BinTree tree)
{
	if (tree == NULL) return 0;
	int left = getTreeDepth(tree->left);
	int right = getTreeDepth(tree->right);
	return left > right ? left + 1 : right + 1;
}

