#pragma once

void printTreeNode(BinTreeNode const node);
void createBinNode_Pre(BinTreeNode* father, char** ppData);
BinTree createBinTree_Pre(char* const arrData);


/* 打印结点内容 */
void printTreeNode(BinTreeNode const node)
{
	assert(node != NULL);
	printf("%c", node->data);
}


/* 从带扩展的先序遍历序列创建二叉树（内部函数，针对结点递归）。数据为单个字母，'.'表示树末 */
void createBinNode_Pre(BinTreeNode* father, char** ppData)
{
	assert(father != NULL && ppData != NULL);

	if ((**ppData) == '.') {
		(*ppData)++;
	}
	else if (isalpha(**ppData)) {
		//printf("%c", **ppData);
		(*father) = newBinTreeNode(**ppData);
		(*ppData)++;
		createBinNode_Pre(&((*father)->left), ppData);
		createBinNode_Pre(&((*father)->right), ppData);
	}
	else {
		assert(false);	// 非法字符
		//exit(1);
	}
}

/* 从带扩展的先序遍历序列创建二叉树。（外部接口）数据为单个字母，'.'表示树末 */
BinTree createBinTree_Pre(char* const arrData)
{
	BinTree tree = newBinTree();
	if (arrData == NULL) return tree;
	char* itData = arrData;
	createBinNode_Pre(&(tree), &itData);
	return tree;
}





