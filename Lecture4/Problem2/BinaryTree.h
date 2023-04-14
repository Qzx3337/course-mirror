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

// 二叉树结构体
typedef struct _BinTree
{
	_BinTreeNode *root;
}_BinTree, *BinTree;


// 二叉树结点接口

BinTreeNode newBinTreeNode(DataType data);
void travPreNode(BinTreeNode root, void (*visit) (BinTreeNode));
void travInNode(BinTreeNode root, void (*visit) (BinTreeNode));
void travPostNode(BinTreeNode root, void (*visit) (BinTreeNode));
void travLevelNode(BinTreeNode root, void (*visit) (BinTreeNode));
int getTreeDepthNode(BinTreeNode root);

// 二叉树接口

BinTree newBinTree();
void travPre(BinTree tree, void (*visit) (BinTreeNode));
void travIn(BinTree tree, void (*visit) (BinTreeNode));
void travPost(BinTree tree, void (*visit) (BinTreeNode));
void travLevel(BinTree tree, void (*visit) (BinTreeNode));
int getTreeDepth(BinTree tree);


// 二叉树结点接口实现

// 创建新结点
BinTreeNode newBinTreeNode(DataType data)
{
	_BinTreeNode *node = (_BinTreeNode *)malloc(sizeof(_BinTreeNode));
	if (node == NULL) exit(OVERFLOW);
	node->left = NULL;
	node->right = NULL;
	node->data = data;
	return node;
}

// 前序遍历结点
inline void travPreNode(BinTreeNode root, void(*visit)(BinTreeNode))
{
	if (root != NULL)
	{
		visit(root);
		travPreNode(root->left, visit);
		travPreNode(root->right, visit);
	}
}

// 中序遍历结点
inline void travInNode(BinTreeNode root, void(*visit)(BinTreeNode))
{
	if (root != NULL)
	{
		travInNode(root->left, visit);
		visit(root);
		travInNode(root->right, visit);
	}
}


// 后序遍历结点
inline void travPostNode(BinTreeNode root, void (*visit) (BinTreeNode)) {
    if (root != NULL)
	{
		travPostNode(root->left, visit);
		travPostNode(root->right, visit);
		visit(root);
	}
}

// 接口实现准备：引入队列。 接口：层序遍历结点

#define QueueElemType BinTreeNode
#include "LinkQueue.h"

// 层序遍历结点
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

// 获取树的深度
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


// 二叉树接口实现

// 创建新树
BinTree newBinTree()
{
	BinTree tree;
	tree = (BinTree)malloc(sizeof(_BinTree));
	if (tree == NULL) exit(OVERFLOW);
	tree->root = NULL;
	return tree;
}

// 前序遍历
inline void travPre(BinTree tree, void (*visit)(BinTreeNode))
{
	assert(tree->root != NULL);
	if (tree->root) {
		travPreNode(tree->root, visit);
	}
}

// 中序遍历
inline void travIn(BinTree tree, void (*visit)(BinTreeNode))
{
	assert(tree->root != NULL);
	if (tree->root) {
		travInNode(tree->root, visit);
	}
}

// 后序遍历
inline void travPost(BinTree tree, void (*visit)(BinTreeNode)) {
	assert(tree->root != NULL);
	if (tree->root) {
		//printf("root exist\n");
		travPostNode(tree->root, visit);
	}
}

// 层序遍历
inline void travLevel(BinTree tree, void(*visit)(BinTreeNode))
{
	assert(tree->root != NULL);
	if (tree->root) {
		travLevelNode(tree->root, visit);
	}
}

// 获取树的深度
inline int getTreeDepth(BinTree const tree)
{
	return getTreeDepthNode(tree->root);
}

