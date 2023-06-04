/***
language: C.

6�������������Ľ�������������

������������
�������������ݴ���һ�ö�����������Ȼ��ִ����Ӧ������
1 ɾ��ĳһֵΪx�Ľ��
2 ��ָ�����y�ڶ����������еĲ���

��������ʽ��
������ݣ���0����������롣
��ɾ����x�����������y

�������ʽ��
ɾ����Ķ���������������������
y���ڵĲ���

���������롿
29 39 15 25 28 10 11 2 0
10
11

�����������
2 11 15 25 28 29 39
4

������˵����
����ɾ���Ľ��������������������������������ҽ���������

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
	if (*root == NULL) {		// �ݹ�߽�
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

// �ͷ� BSTree
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
	if (p == NULL) return false;	// δ�ҵ����

	BSTNode* s = NULL;
	BSTNode* q = NULL;
	if (p->left == NULL) {		// p û������� 
		if (f == NULL) {		// p ������
			s = p->right;
			*p = *(p->right);
			free(s);
		}
		else if (p = f->left) {	// p �������
			f->left = p->right;
			free(p);
		}
		else {					// p ���Ҷ���
			f->right = p->right;
			free(p);
		}
	}
	else {				// p��������
		q = p;			// q�� s�ĸ��ڵ�
		s = p->left;	// s�� p������ǰ����������� p
		while (s->right != NULL) {		// �ҵ� s
			q = s;
			q = q->right;
		}
		if (q == p) {	// ���У� s�� p������������
			q->left = s->left;		// ���� q->left
		}
		else {			// ��ͨ���
			q->right = s->left;	// ���� q->right
		}
		p->key = s->key;
		free(s);
	}
	return true;		// ɾ���ɹ�
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

