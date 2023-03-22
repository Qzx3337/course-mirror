#pragma once

#include <stdio.h>

#ifndef true
#define true 1
#endif // !true
#ifndef false
#define false 0
#endif // !false

#define MAXM 99			// 地图规模
#define MAXN 99			

#include "Point.h"		// 引入 地图坐标类

#define QueueElemType Point		// 定义元素类型
#include "LinkQueue.h"			// 引入 栈类、队列类
#define StackElemType Point
#include "LinkStack.h"

