/******************
SeqList模板类 有序列表
实现基本功能：
	1.创建
	2.添加：在末尾、在列表中任意位置
	3.删除：根据序号删除、根据内容删除
	4.查询：根据下标查询内容、根据内容查询下标

相比于课本，增加了动态空间管理功能：
	1.添加元素时，如果超过数组容量上限，开一个新的大数组，提高容纳量
	2.删除元素时，如果元素数量远远小于容量，换回小数组节省空间

*********************/


#pragma once
#include <iostream>
#include <algorithm>

typedef unsigned int position;

// 初始容量上限，一般较大， 为了测试这里取的较小
unsigned int const INIT_CAPACITY = 4;


/*有序列表 内部采用数组实现*/
template <typename T>
class SeqList
{
	// 为了测试 全部public
public:
	
	T* data; // 数据域 
	position _size, _capacity; //元素个数 当前数组容量

	// 内部函数
	void init(); // 初始化
	bool expand(); // 扩容
	bool shrink(); // 压缩

	SeqList() { init(); }	// 构造函数
	~SeqList() { delete[] data; }	// 析构函数

	// 只读访问接口
	bool empty() { return (!_size); };// 判别是否为空
	unsigned int size() { return _size; } // 元素个数
	int find(T const e); //查找 
	void show(); // 显示

	// 可写访问接口
	void add(T e);// 添加一个数 在末尾
	void insert(position const p, T const e);// 插入
	void clear(); // 清空列表，释放空间
	void Delete(position const p);// 删除 根据位置
	void remove(T const a);	// 删除 根据值
	void sort(); // 排序
	void PickAscendList(); // 提取简单上升序列（对有序表去重）

};


/********  下面为实现  ********/

// 初始化
template <typename T>
void SeqList<T>::init() {
	_size = 0; // 没有元素
	_capacity = INIT_CAPACITY; // 初始容量
	data = new T[_capacity]; // 开辟数据空间
}

/* 扩容 当容量不足时 扩充为原来的两倍*/
template <typename T>
inline bool SeqList<T>::expand() {
	if (_size < _capacity) return false; // 容量不满就返回
	if (_capacity < INIT_CAPACITY) _capacity = INIT_CAPACITY; // 保证容量不低于下限
	_capacity <<= 1; // 容量加倍
	T* oldData = data; // 记录旧数据
	data = new T[_capacity]; // 为新数据开空间
	for (int i = 0; i < _size; i++) { // 复制数据
		data[i] = oldData[i];
	}
	delete[] oldData; // 释放原空间
	return true;
}

/* 压缩 当容量过剩（占用仅为25%）时 压缩空间为一半*/
template <typename T>
inline bool SeqList<T>::shrink() {
	if (_size << 2 > _capacity) return false; // 整段和expand()完全类似
	if (_capacity < INIT_CAPACITY << 1)return false;
	_capacity >>= 1;
	T* oldData = data;
	data = new T[_capacity];
	for (int i = 0; i < _size; i++) {
		data[i] = oldData[i];
	}
	delete[] oldData;
	return true;
}

/* 查找 返回第一个值为e的元素的位置 找不到就返回-1*/
template <typename T>
int SeqList<T>::find(T const e) {
	for (int i = 0; i < _size; i++)
	{
		if (e == data[i]) {
			return i;
		}
	}
	return -1;
}

/* 显示列表信息。 cout<< 输出到屏幕 记得重载运算符；
输出格式：类型名 [地址] * 元素个数 / 容量上限 */
template <typename T>
void SeqList<T>::show() {
	printf("\n%s [%X]*%d /%d:\n", typeid (this).name(), (int)data, _size, _capacity); //基本信息
	printf("[");
	for (int i = 0; i < _size; i++) {
		if (i && i% 10 == 0) printf("\n ");
		std::cout << data[i]; 
		if (i < _size - 1) printf(", ");
	}
	printf(" ]\n");
}

// 添加一个数 在末尾
template <typename T>
void SeqList<T>::add(T e) {
	expand();
	data[_size++] = e;
}

/* 插入 在位置p前插入一个元素e */
template <typename T>
void SeqList<T>::insert(position const p, T const e) {
	expand();
	if (p < _size) {
		_size++;
		for (int i = _size; i > p; i--)
		{
			data[i] = data[i - 1];
		}
		data[p] = e;
	}
	else {
		printf("position error\n");
	}
}

/* 清空列表，释放空间 */
template <typename T>
void SeqList<T>::clear() {
	delete data;
	init();
}

/* 删除 位置在p的元素*/
template <typename T>
void SeqList<T>::Delete(position const p) {
	shrink();
	if (empty()) return;
	if (p >= _size) return;
	_size--;
	for (int i = p; i < _size; i++) {
		data[i] = data[i + 1];
	}
}

/*删除 值为a的元素*/
template <typename T>
void SeqList<T>::remove(T const a) {
	shrink();
	if (empty()) return;
	for (int i = 0; i < _size; i++)
	{
		if (a == data[i])
		{
			_size--;
			for (int j = i; j < _size; j++)
			{
				data[i] = data[i + 1];
			}
			return;
		}
	}
	printf("field\n");
}

/*对整个数据域排序 得到非递减序列 依据<T>的"<"运算符*/
template <typename T>
void SeqList<T>::sort() {
	std::sort(data, data + _size);
}

/*对有序表 去重；对无序表 提取简单上升子序列；依据<T>的"<"运算符 */
template <typename T>
void SeqList<T>::PickAscendList() {
	if (size() < 1) return;
	int p = 0, q = 0;
	for (q = 0; q < size(); q++) {
		if (data[p] < data[q]) {
			data[++p] = data[q];
		}
	}
	_size = p + 1;
	while (shrink());
}

