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
    assert(father != NULL && pData != NULL);        // 断言

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
        //assert(false);	// 非法字符
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
    if (root)
    {
        inThreading(root->left, pre);
        if (!root->left)
        {
            root->ltag = Thread;
            root->left = *pre;
        }
        if (*pre && !(*pre)->right)
        {
            (*pre)->rtag = Thread;
            (*pre)->right = root;
        }
        *pre = root;
        inThreading(root->right, pre);
    }
}

/*遍历线索树*/
void travInThread(BinTree root, void(*visit)(BinTree))
{
    BinTree p = root->left;
    while (p != root)
    {
        while (p->ltag == Link)
        {
            p = p->left;
        }
        visit(p);
        while (p->rtag == Thread && p != root)
        {
            p = p->right;
            visit(p);
        }
        if ((p = p->right) == NULL) return;
    }
    //visit(p);
}

/*寻找线索树结点前驱*/
BinTree getPre(BinTree root)
{
    BinTree p = root->left;
    if (root->ltag == Thread)
    {
        return p;
    }
    else
    {
        if(p==NULL) return NULL;
        while (p->rtag == Link)
        {
            p = p->right;
        }
        return p;
    }
}

/*寻找线索树后继*/
BinTree getNext(BinTree root)
{
    BinTree p = root->right;
    if (root->rtag == Thread)
    {
        return p;
    }
    else
    {
        if (p == NULL) return NULL;
        while (p->ltag == Link)
        {
            p = p->left;
        }
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
    char curr = getchar();
    BinTree root = createBinTree_Pre(strPre);
    //travInNode(root, printTreeNode);
    //printf("\n");

    BinTreeNode* pre = NULL;
    inThreading(root, &pre);
    //travInThread(root, printTreeNode);
    //printf("\n");
    
    //printf("curr char = %c\n", curr);
    BinTreeNode* currNode = locaInTree[curr];
    assert(currNode != NULL);
    BinTreeNode* preNode = getPre(currNode);
    BinTreeNode* nextNode = getNext(currNode);
    if (preNode != NULL) printf("%c\n", preNode->data);
    else printf("NULL\n");
    if (nextNode != NULL) printf("%c\n", nextNode->data);
    else printf("NULL\n");

    return 0;
}

