#pragma once

#include <iostream>
#include "SeqList.h"
using namespace std;


/*从键盘输入n个元素，整型*/
void creat_from_keybord(SeqList<int>& la) {
	int a, n;
	cout << "\n元素为整型\n";
	cout << "输入元素个数：\n";
	cin >> n;
	cout << "输入数据内容：\n";
	for (int i = 0; i < n; i++) {
		cin >> a;
		la.add(a);
	}
}

/*测试有序表模板类 使用键盘输入输出的方式 元素为int类型*/
void test_by_keybord(SeqList<int>& la) {

	int a, p, e;
	la.show(); // 输出

	creat_from_keybord(la);
	la.show();
	
	// 查找
	cout << "\n输入待查找的数：" << endl;
	cin >> a;
	cout << "下标为：";
	cout << la.find(a) << endl;

	// 插入
	cout << "\n输入 p e ：在下标p处插入元素e\n";
	cin >> p >> e;
	la.insert(p, e);
	la.show();

	// 删除
	cout << "\n输入k：删除下标为k的元素\n";
	cin >> a;
	la.Delete(a);
	la.show();

}

