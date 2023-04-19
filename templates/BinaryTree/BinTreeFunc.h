#pragma once

void printTreeNode(BinTreeNode const node);
void createBinNode_Pre(BinTreeNode* father, char** ppData);
BinTree createBinTree_Pre(char* const arrData);


/* ��ӡ������� */
void printTreeNode(BinTreeNode const node)
{
	assert(node != NULL);
	printf("%c", node->data);
}


/* �Ӵ���չ������������д������������ڲ���������Խ��ݹ飩������Ϊ������ĸ��'.'��ʾ��ĩ */
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
		assert(false);	// �Ƿ��ַ�
		//exit(1);
	}
}

/* �Ӵ���չ������������д��������������ⲿ�ӿڣ�����Ϊ������ĸ��'.'��ʾ��ĩ */
BinTree createBinTree_Pre(char* const arrData)
{
	BinTree tree = newBinTree();
	if (arrData == NULL) return tree;
	char* itData = arrData;
	createBinNode_Pre(&(tree), &itData);
	return tree;
}





