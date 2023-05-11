/*

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

// �����½��
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

/* �Ӵ���չ������������д������������ڲ���������Խ��ݹ飩������Ϊ������ĸ��'.'��ʾ��ĩ */
void createBinTreeNode_Pre(BinTree* father, char** pData)
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
    BinTree tree = NULL;
    if (arrData == NULL) return tree;
    char* itData = arrData;
    createBinTreeNode_Pre(&tree, &itData);
    return tree;
}

/* ����������*/
inline void travInNode(BinTree root, void(*visit)(BinTree))
{
    if (root != NULL)
    {
        travInNode(root->left, visit);
        visit(root);
        travInNode(root->right, visit);
    }
}

/*������*/
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

/*����������*/
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
        if (p = p->right == NULL) return;
    }
    //visit(p);
}


/* ��ӡ������� */
void printTreeNode(BinTree const node)
{
    assert(node != NULL);
    printf("%c", node->data);
}


int main()
{
    char strPre[128];
    gets(strPre);
    BinTree root = createBinTree_Pre(strPre);
    //travInNode(root, printTreeNode);
    //printf("\n");

    BinTreeNode* pre = NULL;
    inThreading(root, &pre);
    travInThread(root, printTreeNode);
    printf("\n");

    return 0;
}

