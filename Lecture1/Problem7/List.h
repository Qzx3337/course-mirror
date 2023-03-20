/********************

双向链表List

*****************/
#pragma once

#include <iostream>
#include <cstdio>
#include <typeinfo>
#include "ListNode.h" //引入链表结点类

template <typename T>
class List { //链表模板类

private:
	Rank _size;
	ListNode<T>* header, * trailer;	//规模、头结点、尾结点

protected:
	void init();		//列表创建时的初始化
	Rank clear();		//清除所有结点
	void copyNodes(ListNode<T>*, Rank);		//复制列表中自位置p起的n项
	ListNode<T>* merge(ListNode<T>*, Rank, List<T>&, ListNode<T>*, Rank); //归并
	void mergeSort(ListNode<T>*&, Rank);	//对从p开始连续的n个结点归并排序
	void radixSort(ListNode<T>*, Rank);		//对从p开始连续的n个结点基数排序

public:

	// 构造函数
	List() { init(); }			//默认
	List(List<T> const& L);		//整体复制列表L
	List(List<T> const& L, Rank r, Rank n); //复制列表L中自第r项起的n项
	List(ListNode<T>* p, Rank n); //复制列表中自位置p起的n项
	// 析构函数
	~List(); //释放（包含头、尾在内的）所有结点
	
// 只读访问接口

	Rank size() const { return _size; }			//规模
	bool empty() const { return _size <= 0; }	//判空
	ListNode<T>* operator[](Rank r) const;		//重载，支持循秩访问（效率低）
	ListNode<T>* first() const { return header->next; } //首结点位置
	ListNode<T>* last() const { return trailer->pred; } //末结点位置
	bool valid(ListNode<T>* p)					//判断位置p是否对外合法
	{
		return p && (trailer != p) && (header != p);
	} //将头、尾结点等同于NULL
	ListNode<T>* find(T const& e) const		//无序列表查找
	{
		return find(e, _size, trailer);
	}
	ListNode<T>* find(T const& e, Rank n, ListNode<T>* p) const; //无序区间查找
	ListNode<T>* search(T const& e) const	//有序列表查找
	{
		return search(e, _size, trailer);
	}
	ListNode<T>* search(T const& e, Rank n, ListNode<T>* p) const;	//有序区间查找
	ListNode<T>* selectMax(ListNode<T>* p, Rank n);					//在p及其n-1个后继中选出最大者
	ListNode<T>* selectMax() { return selectMax(header->succ, _size); } //整体最大者
	void show();
	void showElem();
 
// 可写访问接口

	ListNode<T>* insertAsFirst(T const& e);		//将e当作首结点插入
	ListNode<T>* insertAsLast(T const& e);		//将e当作末结点插入
	ListNode<T>* insert(ListNode<T>* p, T const& e); //将e当作p的后继插入
	ListNode<T>* insert(T const& e, ListNode<T>* p); //将e当作p的前驱插入
	T remove(ListNode<T>* p); //删除合法位置p处的结点,返回被删除结点
	void merge(List<T>& L) { merge(header->succ, _size, L, L.header->succ, L._size); } //全列表归并
	void sort(ListNode<T>*, Rank); //列表区间排序
	void sort() { sort(first(), _size); } //列表整体排序
	Rank deduplicate(); //无序去重
	Rank uniquify(); //有序去重
	void reverse(); //前后倒置  
}; //List

/* 展示链表信息。
格式： 类型名 [地址] * 大小 */
template<typename T>
inline void List<T>::show()
{
	printf("\n%s [%X]*%d:\n", typeid (this).name(), (int)this, _size); //基本信息
	printf("[");
	ListNode<T>* p = first();
	for (int r = 0; r < _size; r++) {
		if (r && r % 10 == 0) printf("\n ");
		std::cout << p->data;
		p = p->next;
		if (r < _size - 1) printf(", ");
	}
	printf(" ]\n");
}

/* 展示链表元素 */
template<typename T>
inline void List<T>::showElem()
{
	ListNode<T>* p = first();
	for (int r = 0; r < _size; r++) {
		std::cout << p->data << " ";
		p = p->next;
	}
	printf("\n");
}

// e当作首结点插入
template <typename T> ListNode<T>* List<T>::insertAsFirst(T const& e)
{
	_size++; return header->insertAsSucc(e);
}

// e当作末结点插入
template <typename T> ListNode<T>* List<T>::insertAsLast(T const& e)
{
	_size++; return trailer->insertAsPred(e);
} 

// e当作p的后继插入
template <typename T> ListNode<T>* List<T>::insert(ListNode<T>* p, T const& e)
{
	_size++; return p->insertAsSucc(e);
} 

// e当作p的前驱插入
template <typename T> ListNode<T>* List<T>::insert(T const& e, ListNode<T>* p)
{
	_size++; return p->insertAsPred(e);
} 

/* 初始化为空链表  */
template<typename T>
inline void List<T>::init()
{
	_size = 0;
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->pred = NULL;
	header->next = trailer;
	trailer->pred = header;
	trailer->next = NULL;
}

/* 析构函数。先清空链表，再释放头结点尾结点。 */
template<typename T>
inline List<T>::~List()
{
	clear(); 
	delete header;
	delete trailer;
}

/* 清空链表，释放所有结点 */
template <typename T>
Rank List<T>::clear() { 
	Rank oldSize = _size;
	while (0 < _size) remove(header->next); //反复删除首结点，直至列表变空
	return oldSize;
}

// 删除合法结点p，返回其数值（可以用于赋值）
template <typename T>
T List<T>::remove(ListNode<T>* p) { 
	T e = p->data;				//备份待删除结点的数值
	p->pred->next = p->next;
	p->next->pred = p->pred;	//后继、前驱
	delete p;
	_size--;					//释放结点，更新规模
	return e;					//返回备份的数值
}

//前后倒置
template <typename T> void List<T>::reverse() { 
	if (_size < 2) return;							//平凡情况
	for (ListNode<T>* p = header; p; p = p->pred)	//自前向后，依次遍历
		std::swap(p->pred, p->next);				//交换各结点的前驱、后继指针
	std::swap(header, trailer);						//头、尾结点互换
}

