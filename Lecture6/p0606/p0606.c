/***
language: C.

6、二叉排序树的建立及基本操作

【问题描述】
请根据输入的数据创建一棵二叉排序树。然后执行相应操作。
1 删除某一值为x的结点
2 求指定结点y在二叉排序树中的层数

【输入形式】
结点数据，以0代表结束输入。
待删除的x，待求层数的y

【输出形式】
删除后的二叉排序树的中序遍历结果
y所在的层数

【样例输入】
29 39 15 25 28 10 11 2 0
10
11

【样例输出】
2 11 15 25 28 29 39
4

【样例说明】
若待删除的结点包含左右子树，则以其左子树的最右结点代替它。

***/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#ifndef KeyType
#define KeyType int
#endif // !KeyType

typedef struct BSTNode {
	KeyType key;
	struct BSTNode* left;
	struct BSTNode* right;
}BSTNode, * BSTree;

inline BSTNode* newBSTNode(KeyType const key, BSTNode* const left, BSTNode* const right)
{
	BSTNode* n = (BSTNode*)malloc(sizeof(BSTNode));
	if (n == NULL) exit(OVERFLOW);
	n->key = key;
	n->left = left;
	n->right = right;
	return n;
}

inline void insertBST(BSTree* root, KeyType const key)
{
	if (*root == NULL) {		// 递归边界
		*root = newBSTNode(key, NULL, NULL);
		return;
	}
	if (key < (*root)->key) {		// left child
		insertBST(&((*root)->left), key);
	}
	else if (key > (*root)->key) {		// right child
		insertBST(&((*root)->right), key);
	}
}

// 释放 BSTree
void freeBST(BSTree tree)
{
	if (tree == NULL) return;
	freeBST(tree->left);
	freeBST(tree->right);
	free(tree);
}

void readTree(BSTree* tree)
{
	int key;
	*tree = NULL;
	for (;;) {
		scanf("%d", &key);
		if (key == 0) return;
		else insertBST(tree, key);
	}
}

void printBSTTravIn(BSTree const tree)
{
	if (tree == NULL) return;
	printBSTTravIn(tree->left);
	printf("%d ", tree->key);
	printBSTTravIn(tree->right);
}

bool removeBST(BSTree tree, KeyType const key)
{
	BSTNode* p = tree;
	BSTNode* f = NULL;
	while (p) {
		if (p->key == key) break;
		f = p;
		if (key < p->key)  p = p->left;
		else p = p->right;
	}
	if (p == NULL) return false;	// 未找到结点

	BSTNode* s = NULL;
	BSTNode* q = NULL;
	if (p->left == NULL) {		// p 没有左儿子 
		if (f == NULL) {		// p 是树根
			s = p->right;
			*p = *(p->right);
			free(s);
		}
		else if (p = f->left) {	// p 是左儿子
			f->left = p->right;
			free(p);
		}
		else {					// p 是右儿子
			f->right = p->right;
			free(p);
		}
	}
	else {				// p有左子树
		q = p;			// q存 s的父节点
		s = p->left;	// s存 p的中序前驱，用于替代 p
		while (s->right != NULL) {		// 找到 s
			q = s;
			q = q->right;
		}
		if (q == p) {	// 特判， s是 p的左子树树根
			q->left = s->left;		// 链接 q->left
		}
		else {			// 普通情况
			q->right = s->left;	// 链接 q->right
		}
		p->key = s->key;
		free(s);
	}
	return true;		// 删除成功
}

BSTNode* findBST(BSTree const tree, KeyType const key)
{
	assert(tree != NULL);
	BSTNode* p = tree;
	int depth;
	for (depth = 1; p != NULL; depth++) {
		if (key == p->key) break;
		else if (key < p->key) p = p->left;
		else p = p->right;
	}
	printf("%d\n", depth);
	return p;
}

int main(int argc, char const **argv)
{
	freopen("p0606.in", "r", stdin);
	//freopen("p0606.out", "w", stdout);

	BSTree tree = NULL;
	readTree(&tree);
	//printBSTTravIn(tree);
	//printf("\n");

	int x, y;
	scanf("%d%d", &x, &y);
	removeBST(tree, x);
	printBSTTravIn(tree);
	printf("\n");
	findBST(tree, y);
	freeBST(tree);

	return 0;
}

