#pragma once

#include <stdio.h>

#ifndef true
#define true 1
#endif // !true
#ifndef false
#define false 0
#endif // !false

#define MAXM 99			// ��ͼ��ģ
#define MAXN 99			

#include "Point.h"		// ���� ��ͼ������

#define QueueElemType Point		// ����Ԫ������
#include "LinkQueue.h"			// ���� ջ�ࡢ������
#define StackElemType Point
#include "LinkStack.h"

