/*
* 交叉链表矩阵模板类
* 
* Cross Link List Matrix Template Class
* Class: XLLMat
* 
* language:C.
*/

#pragma once

#ifndef ElemType
#define ElemType int
#endif // !ElemType

// cross link list
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

// ******** interface ********

XLLMatPtr createXLLMat(int rows, int cols);			// create a matrix
void destoryXLLMat(XLLMatPtr mat);					// destory a matrx
bool insertXLLMat(XLLMatPtr mat, int x, int y, ElemType v);				// insert a node
bool eraseXLLMat(XLLMatPtr mat, int x, int y);		// erase a node
XLLMatPtr addXLLMat(XLLMatPtr const mat1, XLLMatPtr const mat2);		// add two matrix
bool readXLLMat(XLLMatPtr mat, int const len);		// read a matrix from keybord
bool printXLLMat(XLLMatPtr const mat);				// print a matrix

// ******** implementation  ********

// create a matrix
XLLMatPtr createXLLMat(int rows, int cols)
{
	XLLMatPtr mat = mnew(XLLMat);			// create a matrix
	if (!mat) exit(OVERFLOW);
	mat->rows = rows;
	mat->cols = cols;
	mat->len = 0;
	if (!(mat->rowHead = mnewarr(XLList, rows+1))) exit(OVERFLOW);	// create rowHead and colHead arr
	if (!(mat->colHead = mnewarr(XLList, cols+1))) exit(OVERFLOW);
	int i;
	for (i = 0; i < rows; i++){				// create rowHead and colHead node
		makeNew(mat->rowHead[i], XLNode);
		mat->rowHead[i]->right = NULL;
	}
	for (i = 0; i < cols; i++) {
		makeNew(mat->colHead[i], XLNode);
		mat->colHead[i]->down = NULL;
	}
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
	if (x<1 || x>mat->rows || y<1 || y>mat->cols) {		// check input
		printf("error input\n");
		return false;
	}
	if (v == 0) {							// if (v == 0) erase the node
		eraseXLLMat(mat, x, y);
		return true;
	}

	XLList p = mnew(XLNode);		// create a new node
	if (!p) exit(OVERFLOW);
	p->row = x;
	p->col = y;
	p->value = v;

	XLList q = mat->rowHead[x];
	while (q->right!=NULL && q->right->col < y) q = q->right;

	if (q->right != NULL) if (q->right->col == y) {	// the node already exist 
		free(p); p = NULL;
		q->right->value = v;
		return true;
	}

	p->right = q->right;			// insert in row
	q->right = p;

	q = mat->colHead[y];
	while (q->down && q->down->row < x) q = q->down;
	p->down = q->down;				// insert in col
	q->down = p;

	mat->len++;
	return true;
}

// erase a node
bool eraseXLLMat(XLLMatPtr mat, int x, int y)
{
    if (x<1 || x>mat->rows || y<1 || y>mat->cols) {		// check input
		printf("error input\n");
		return false;
	}
	if (mat->len == 0) return false;					// no node in matrix

	XLList p = mat->rowHead[x];
	while (p->right && p->right->col < y) p = p->right;				// find the node in row
	if (p->right == NULL || p->right->col > y) return false;		// the node not exist
	XLList q = mat->colHead[y];
	while (q->down && q->down->row < x) q = q->down;				// find the node in col

	XLList r = p->right;				// erase the node
	p->right = r->right;
	p->down = r->down;
	free(r); r = NULL;

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
		XLList p = mat1->rowHead[i]->right;
		XLList q = mat2->rowHead[i]->right;
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
	if (!mat) return false;				// check input
	int i;
	int x, y, v;
	for (i = 0; i < len; i++) {			// read nodes
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
		XLList p = mat->rowHead[i]->right;
		while (p) {
			//printf("(%d,%d,%d) ", p->row, p->col, p->value);
			printf("%d %d %d\n", p->row, p->col, p->value);
			p = p->right;
		}
	}
	printf("\n");
	return true;
}



