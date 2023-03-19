#pragma once

#include <stdio.h>

#ifndef true
#define true 1
#endif // !true

#ifndef false
#define false 0
#endif // !false

#define MAXM 99
#define MAXN 99

#include "Point.h"

#define QueueElemType Point
#include "LinkQueue.h"
#define StackElemType Point
#include "LinkStack.h"

