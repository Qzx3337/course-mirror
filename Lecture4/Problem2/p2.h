/*

language: C.
*/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#define mnew(typeName) (typeName*)malloc(sizeof(typeName))
#define mnewarr(typeName, size) (typeName*)malloc(sizeof(typeName)*(size))
#define INF 0x7FFFFFFF

#include "BinaryTree.h"




