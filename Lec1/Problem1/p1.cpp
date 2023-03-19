/************************
题目：
一、编写一个由多个函数构成的完整程序，实现顺序表的建立、按照内容查找、插入、删除、显示操作。

思路：
建立SeqList模板类，将上述功能全部封装进去。
定义在"SeqList\SeqList.h"中。

language: C++;

***********************/

#include "SeqList\SeqList_test.h"

int main() {

	SeqList<int> la; // 测试的有序表对象

	test_by_keybord(la); // 使用键盘输入的方式 进行测试

	return 0;
}

