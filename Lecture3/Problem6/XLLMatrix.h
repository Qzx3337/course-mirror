#pragma once

#ifndef ElemType
#define ElemType int
#endif // !ElemType

// cross link node, cross link list
typedef struct _XLNode{
	int row;
	int col;
	ElemType value;
	struct _XLNode* right;
	struct _XLNode* down;
} XLNode, *XLList;

// cross link list matrix
typedef struct _XLLMat {
	int rows;
	int cols;
	int len;
	XLList* rowHead;
	XLList* colHead;
} XLLMat, *XLLMatPtr;

// *************** interface ***************

XLLMatPtr createXLLMat(int rows, int cols);			// create a matrix

void destoryXLLMat(XLLMatPtr mat);					// destory a matrx

bool insertXLLMat(XLLMatPtr mat, int x, int y, ElemType v);		// insert a node

bool eraseXLLMat(XLLMatPtr mat, int x, int y);		// erase a node

XLLMatPtr addXLLMat(XLLMatPtr const mat1, XLLMatPtr const mat2);		// add two matrix

bool readXLLMat(XLLMatPtr mat, int const len);		// read a matrix from keybord

bool printXLLMat(XLLMatPtr const mat);				// print a matrix

// *************** implementation  ***************

XLLMatPtr createXLLMat(int rows, int cols)			// create a matrix
{
	XLLMatPtr mat = mnew(XLLMat);
	if (!mat) exit(OVERFLOW);
	mat->rows = rows;
	mat->cols = cols;
	mat->len = 0;
	if (!(mat->rowHead = mnewarr(XLList, rows))) exit(OVERFLOW);
	if (!(mat->colHead = mnewarr(XLList, cols))) exit(OVERFLOW);
	memset(mat->rowHead, 0, sizeof(XLList)*rows);				// set all pointer to NULL
	memset(mat->colHead, 0, sizeof(XLList)*cols);
	return mat;
}

// destory a matrx
void destoryXLLMat(XLLMatPtr mat)					
{
	if (!mat) return;
	int i;
	for (i = 0; i < mat->rows; i++) {		// free all nodes
		XLList p = mat->rowHead[i];
		while (p) {
			XLList q = p;
			p = p->right;
			free(q);
		}
	}
	free(mat->rowHead);			// free all pointer
	free(mat->colHead);
	free(mat);
}

// insert a node
bool insertXLLMat(XLLMatPtr mat, int x, int y, ElemType v)		
{
	if (x<0 || x>mat->rows - 1 || y<0 || y>mat->cols - 1) {		// check input
		printf("error input\n");
		return false;
	}
	if (v == 0) {
		eraseXLLMat(mat, x, y);
		return true;
	}

	XLList p = mnew(XLNode);		// create a new node
	if (!p) exit(OVERFLOW);
	p->row = x;
	p->col = y;
	p->value = v;

	if (!mat->rowHead[x]) {			// insert to rowHead
		p->right = NULL;
		mat->rowHead[x] = p;
	}
	else {
		XLList q = mat->rowHead[x];
		while (q->right!=NULL && q->right->col < y) q = q->right;
		if (q->right != NULL) {
			if (q->right->col == y) {	// the node already exist 
				free(p); p = NULL;
				if(v==0)
				{
					// ************************************
					//eraseNextXLNode()
					//q->right = q->right->right;
				}
				else q->right->value = v;
			}
		}
		if (p) {
			p->right = q->right;
			q->right = p;
		}
	}

	if (p) {					// insert to colHead
		if (!mat->colHead[y]) {
			p->down = NULL;
			mat->colHead[y] = p;
		}
		else {
			XLList q = mat->colHead[y];
			while (q->down && q->down->row < x) q = q->down;
			p->down = q->down;
			q->down = p;
		}
	}

	mat->len++;
	return true;
}

// erase a node
bool eraseXLLMat(XLLMatPtr mat, int x, int y)
{
	if (x<0 || x>mat->rows - 1 || y<0 || y>mat->cols - 1) {		// check input
			printf("error input\n");
			return false;
		}
	XLList p = mat->rowHead[x];
	XLList q = mat->colHead[y];
	if (!p || !q) return false;
	if (p->col == y) {			// erase from rowHead
			mat->rowHead[x] = p->right;
			free(p);
			p = NULL;
		}
	else {
		while (p->right && p->right->col < y) p = p->right;
		if (p->right && p->right->col == y) {
			XLList q = p->right;
			p->right = q->right;
			free(q);
			q = NULL;
		}
	}
	if (q->row == x) {			// erase from colHead
			mat->colHead[y] = q->down;
			free(q);
			q = NULL;
		}
	else {
		while (q->down && q->down->row < x) q = q->down;
		if (q->down && q->down->row == x) {
			XLList p = q->down;
			q->down = p->down;
			free(p);
			p = NULL;
		}
	}
	mat->len--;
	return true;
}

// add two matrix
XLLMatPtr addXLLMat(XLLMatPtr const mat1, XLLMatPtr const mat2)
{
    if (!mat1 || !mat2) return NULL;		// check input
	if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
		printf("can not add\n");
		return NULL;
	}

	XLLMatPtr mat = createXLLMat(mat1->rows, mat2->cols);
    if (!mat) exit(OVERFLOW);
	int i;
	for (i = 0; i < mat1->rows; i++) {		// add row by row
		XLList p = mat1->rowHead[i];
		XLList q = mat2->rowHead[i];
		while (p && q) {					// add two node
			if (p->col == q->col) {
				insertXLLMat(mat, i, p->col, p->value + q->value);
				p = p->right;
				q = q->right;
			}
			else if (p->col < q->col) {
				insertXLLMat(mat, i, p->col, p->value);
				p = p->right;
			}
			else {
				insertXLLMat(mat, i, q->col, q->value);
				q = q->right;
			}
		}
							// add the rest node
		while (p) {
			insertXLLMat(mat, i, p->col, p->value);
			p = p->right;
		}
		while (q) {
			insertXLLMat(mat, i, q->col, q->value);
			q = q->right;
		}
	}
	return mat;
}

// read a matrix from keybord
bool readXLLMat(XLLMatPtr mat, int const len)
{
	if (!mat) return false;
	int i;
	int x, y, v;
	for (i = 0; i < len; i++) {
		scanf("%d%d%d", &x, &y, &v);
		insertXLLMat(mat, x, y, v);
	}
	return true;
}

// print a matrix
bool printXLLMat(XLLMatPtr const mat)
{
	if (!mat) return false;
	int i;
	for (i = 0; i < mat->rows; i++) {
		XLList p = mat->rowHead[i];
		while (p) {
			//printf("(%d,%d,%d) ", p->row, p->col, p->value);
			printf("%d %d %d\n", p->row, p->col, p->value);
			p = p->right;
		}
	}
	printf("\n");
	return true;
}





