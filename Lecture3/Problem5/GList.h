
/*
GList.h
GList Class Template

language: C.
*/

#pragma once

#ifndef AtomType
#define AtomType int
#endif

typedef enum { ATOM, LIST } ElemTag;	// ATOM==0: atom, LIST==1: list

typedef struct GLNode {
	ElemTag tag;
	union {
		AtomType atom;
		struct {
			struct GLNode* hp, * tp;
		} ptr;
	} a;
} GLNode, *GList;


GList createGList();			// Create a new GList
void destoryGList(GList L);		// Destroy a GList
void printGList(GList L);		// Print a GList
void readGList(GList L);		// Read a GList
int sumGList(GList L);			// Sum a GList


// Create a new GList
GList createGList() {
	GList L = (GList)malloc(sizeof(GLNode));
	if (!L) exit(OVERFLOW);
	L->tag = LIST;  
	L->a.ptr.hp = NULL;
	L->a.ptr.tp = NULL;
	return L;
}

// Destroy a GList
void destoryGList(GList L) {
	if (L->tag == ATOM) {
		free(L);
		return;
	}
	if (L->a.ptr.hp) destoryGList(L->a.ptr.hp);
	if (L->a.ptr.tp) destoryGList(L->a.ptr.tp);
	free(L);
}

// Print a GList
void printGList(GList L) {
	if (L->tag == ATOM) {
		printf("%d", L->a.atom);
	}
	else {
		printf("(");
		while (L->a.ptr.tp) {				// print list
			printGList(L->a.ptr.hp);		
			printf(",");
			L = L->a.ptr.tp;
		}
		printGList(L->a.ptr.hp);			// L->a.ptr.tp == NULL
		printf(")");
	}
}

// Read a GList
void readGList(GList L) {
	char c = getchar();
	if (c == '(') {						// L is a list
		L->tag = LIST;
		L->a.ptr.hp = createGList();
		readGList(L->a.ptr.hp);			// read the list head
	}
	else if(isdigit(c)) {				// L is an atom
		L->tag = LIST;
		L->a.ptr.hp = createGList();
		L->a.ptr.hp->tag = ATOM;
		L->a.ptr.hp->a.atom = c - '0';	// convert char to int
			//printf("%d ", c - '0');
	}
	else {
		printf("\nascii= %d\n", c);
		assert(false && "impossible getchar()");	// impossible
	}

	if ((c = getchar()) == ',') {		// read the rest elements
		L->a.ptr.tp = createGList();
		readGList(L->a.ptr.tp);
	}
	else {
		L->a.ptr.tp = NULL;				// no more elements
	}

}

// Sum a GList (only for integer)
int sumGList(GList L) {
	if (L->tag == ATOM) {			// L is an atom
		return L->a.atom;
	}
	int sum = 0;
	if (L->a.ptr.hp) sum += sumGList(L->a.ptr.hp);
	if (L->a.ptr.tp) sum += sumGList(L->a.ptr.tp);
	return sum;
}






