/*
2、查找线索二叉树的前驱及后继
 以扩展先序遍历序列建立一个二叉树，并将该二叉树中序线索化，输入一个节点，输出在该中序线索二叉树中，该节点的直接前驱及直接后继节点
language: C.
*/

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

typedef char DataType;
typedef enum { Link, Thread } PointerTag;

typedef struct BinTreeNode
{
	DataType data;
	struct BinTreeNode* left;
	struct BinTreeNode* right;
	PointerTag ltag;
	PointerTag rtag;
} BinTreeNode, * BinTree;


BinTree locaInTree[256] = { NULL };     // 记录结点位置

// 创建新结点
BinTreeNode* newBinTreeNode(DataType data)
{
	BinTreeNode* node = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	if (node == NULL) exit(OVERFLOW);
	node->data = data;
	node->ltag = Link;
	node->rtag = Link;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/* 从带扩展的先序遍历序列创建二叉树（内部函数，针对结点递归）。数据为单个字母，'.'表示树末 */
void createBinTreeNode_Pre(BinTree* father, char** pData)
{
	assert(father != NULL && pData != NULL);        // 传入参数合法性检查

	if ((**pData) == '.') {
		(*pData)++;
	}
	else if (isalpha(**pData)) {
		//printf("%c", **pData);
		(*father) = newBinTreeNode(**pData);        // 创建新结点

		locaInTree[**pData] = *father;              // 记录结点位置

		(*pData)++;
		createBinTreeNode_Pre(&(*father)->left, pData);
		createBinTreeNode_Pre(&(*father)->right, pData);
	}
	else {
		//assert(false);		// 非法字符
		exit(1);
	}
}


/* 从带扩展的先序遍历序列创建二叉树。（外部接口）数据为单个字母，'.'表示树末 */
BinTree createBinTree_Pre(char* const arrData)
{
	BinTree tree = NULL;
	if (arrData == NULL) return tree;
	char* itData = arrData;
	createBinTreeNode_Pre(&tree, &itData);      // 递归创建
	return tree;
}

/* 中序遍历结点*/
inline void travInNode(BinTree root, void(*visit)(BinTree))
{
	if (root != NULL)
	{
		travInNode(root->left, visit);
		visit(root);
		travInNode(root->right, visit);
	}
}

/*线索化*/
void inThreading(BinTree root, BinTree* pre)
{
	if (root) {			// 递归结束条件
		inThreading(root->left, pre);		// 左子树线索化
		if (!root->left) {					// 左子树为空，建立前驱线索
			root->ltag = Thread;
			root->left = *pre;
		}
		if (*pre && !(*pre)->right) {		// 建立前驱结点的后继线索
			(*pre)->rtag = Thread;
			(*pre)->right = root;
		}
		*pre = root;						// 保持pre指向p的前驱
		inThreading(root->right, pre);		// 右子树线索化
	}
}

/*遍历线索树*/
void travInThread(BinTree root, void(*visit)(BinTree))
{
	BinTree p = root->left;			// p指向根结点
	while (p != root) {				// 空树或遍历结束时，p==root
		while (p->ltag == Link) {	// 左子树不为空时，p!=root
			p = p->left;			// 沿着左子树向下
		}
		visit(p);
		while (p->rtag == Thread && p != root) {	// 右子树为空或遍历结束时，p==root
			p = p->right;							// 沿着后继线索向下
			visit(p);
		}
		if ((p = p->right) == NULL) return;			// 遍历结束，p==NULL
	}
}

/*寻找线索树结点前驱*/
BinTree getPre(BinTree root)
{
	BinTree p = root->left;		// p指向根结点
	if (root->ltag == Thread) {	// 左子树为空
		return p;
	}
	else {						// 左子树不为空
		if (p == NULL) return NULL;		// 空树
		while (p->rtag == Link) p = p->right;	// 右子树不为空
		return p;
	}
}

/*寻找线索树后继*/
BinTree getNext(BinTree root)
{
	BinTree p = root->right;		// p指向根结点
	if (root->rtag == Thread) {		// 右子树为空
		return p;
	}
	else {							// 右子树不为空
		if (p == NULL) return NULL;		// 空树
		while (p->ltag == Link) p = p->left;	// 左子树不为空
		return p;
	}
}


/* 打印结点内容 */
void printTreeNode(BinTree const node)
{
	assert(node != NULL);
	printf("%c", node->data);
}


int main()
{

	//freopen("p0502.in", "r", stdin);
	//freopen("p7.out", "w", stdout);

	char strPre[128];
	gets(strPre);
	char curr = getchar();				// 获取当前结点
	BinTree root = createBinTree_Pre(strPre);
	//travInNode(root, printTreeNode);
	//printf("\n");

	// 线索化
	BinTreeNode* pre = NULL;
	inThreading(root, &pre);
	//travInThread(root, printTreeNode);
	//printf("\n");
	
	//printf("curr char = %c\n", curr);
	BinTreeNode* currNode = locaInTree[curr];				// 获取当前结点位置
	assert(currNode != NULL);
	BinTreeNode* preNode = getPre(currNode);				// 获取前驱
	BinTreeNode* nextNode = getNext(currNode);				// 获取后继
	if (preNode != NULL) printf("%c\n", preNode->data);		// 打印前驱
	else printf("NULL\n");
	if (nextNode != NULL) printf("%c\n", nextNode->data);	// 打印后继
	else printf("NULL\n");

	return 0;
}

