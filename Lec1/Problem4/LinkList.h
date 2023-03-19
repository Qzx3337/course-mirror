/********************

类：链表模板类 LinkList
1.初始化：
	初始化为空链表
	根据已有链表，初始化为其副本（复制一遍）
2.建立：1.前插 2.后插 都可以
3.按内容查找（遍历）
4.插入结点
5.删除结点

*****************/
#pragma once
#include "ListNode.h" //引入列表结点类
#include <iostream>
#include <typeinfo>
#include <cstdio>

template <typename T>
class LinkList
{
	// 方便测试 全部public
public:
	Rank _size;						// 数据结点个数
	ListNode<T> *header, *trailer;	// 头结点、尾结点 保证所有元素都是有前驱有后继的
	ListNode<T> *trail;				// 尾指针，记录最后一个元素的地址（方便在此后插入）


	void init();					//列表创建时的初始化
	ListNode<T>* LocatePre(Rank r);
	void ResetTrail();

	// 构造函数
	LinkList() { init(); } //默认	
	LinkList(LinkList<T> const& L); //整体复制列表L
	// 析构函数
	~LinkList(); //释放（包含头结点在内的）所有结点

	// 只读访问接口
	unsigned int size() const { return _size; }	//规模
	bool empty() const { return _size <= 0; }	//判空
	T operator[](Rank r) const;					//重载[]，支持下标访问（效率低）
	ListNode<T>* first() const { return header->next; }	//首结点位置
	ListNode<T>* last() const { return trail; }			//末结点位置
	ListNode<T>* Locate(T const& e);	/*依据内容查找结点的地址*/
	int Find(T const& e);				/*依据内容查找元素的秩*/
	void show();						// 显示列表
	T* GetLast(Rank k);					/* 查找倒数第k个元素*/

	// 可写访问接口

	ListNode<T>* insertAsFirst(T const& e);
	ListNode<T>* insertAsFirst(ListNode<T>* p);
	ListNode<T>* insertAsLast(T const& e);
	ListNode<T>* insert(ListNode<T>* p, T const& e);
	Rank clear();
	bool remove(Rank r);
	T removeNext(ListNode<T>* p);
	ListNode<T>* PickNextNode(ListNode<T>* p);
	bool reverse(Rank l, Rank r);

};

/****************************************/


/* 初始化为空链表 */
template <typename T>
void LinkList<T>::init() {
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->next = trailer;
	trailer->next = NULL;
	_size = 0;
	trail = header;
}

/* 返回秩为r的结点的前驱的地址。保证输入合法。*/
template <typename T>
ListNode<T>* LinkList<T>::LocatePre(Rank r) {
	if (r > size() + 1) return NULL;
	ListNode<T>* p = header;
	while (r--) p = p->next;
	return p;
}

/* 重置内部变量trail，指向最后一位元素。 */
template<typename T>
inline void LinkList<T>::ResetTrail()
{
	ListNode<T>* p = header;
	while (p->next != trailer) p = p->next;
	trail = p;
}

/* 复制已有列表进行构造 */
template <typename T>
LinkList<T>::LinkList(LinkList<T> const& L) {
	init();
	for (ListNode<T>* p = L.first(); p != trailer; p = p->next) {
		insertAsLast(p->data);
	}
}

template<typename T>
inline LinkList<T>::~LinkList()
{
	clear();
	delete header;
	delete trailer;
}


/* 重载下标操作符，以通过下标直接访问结点（O(r)效率，少用）*/
template <typename T>
inline T LinkList<T>::operator[](Rank r) const { // 0 <= r < size
	if (r < 0) return 0;				// 两种不合法输入
	if (r >= size()) return 0;
	ListNode<T>* p = first();			//从首结点出发
	while (0 < r--) p = p->next;		//顺数第r个结点即是
	return p->data;						//目标结点
}

/*依据内容查找元素 此处为遍历查找*/
template <typename T>
ListNode<T>* LinkList<T>::Locate(T const& e) {
	for (ListNode<T>* p = first(); p != trailer; p = p->next) {
		if (p->data == e) {
			return p;
		}
	}
	return NULL;
}

/*依据内容查找元素 此处为遍历查找*/
template <typename T>
int LinkList<T>::Find(T const& e) {
	Rank r = 0;
	for (ListNode<T>* p = first(); p != trailer; p = p->next, r++) {
		if (p->data == e) {
			return r;
		}
	}
	return -1;
}

/* 显示列表信息及内容。使用cout输出到屏幕，记得重载"<<"运算符
输出格式：变量的类型（实例化之后），地址，链表元素个数：列表内容 */
template<typename T>
void LinkList<T>::show() {
	printf("\n%s, [%X]*%d:\n", typeid (this).name(), (int)this, _size); //基本信息
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

/* 查找倒数第 k个元素，返回其数据域的指针。如果不存在倒数第 k个则返回 NULL 。
题目：Lecture1 Problem4 */
template <typename T>
T* LinkList<T>::GetLast(Rank k) {
	if (k > _size) return NULL;						// 查找元素在链表外，不存在
	if (k == 0) return NULL;						// 查找倒数第0个，不存在
	ListNode<T>* p, * q;
	for (p = q = first(); k--; q = q->next);		// 将 p, q 拉开间距为 k
	for (; q != trailer; q = q->next, p = p->next);	// 使 p, q 平行移动到链表尾
	return &(p->data);								// 返回 p 的位置
}

/*将e作为首元素插入*/
template <typename T>
ListNode<T>* LinkList<T>::insertAsFirst(T const& e) {
	ListNode<T>* px = new ListNode<T>(e, header->next);
	header->next = px;
	_size++;
	return px;
}

/*将结点p作为第一个结点插入*/
template <typename T>
ListNode<T>* LinkList<T>::insertAsFirst(ListNode<T>* px) {
	px->next = header->next;
	header->next = px;
	_size++;
	return px;
}

/*将e作为末尾元素插入*/   
template <typename T>
ListNode<T>* LinkList<T>::insertAsLast(T const& e) {
	ListNode<T>* px = new ListNode<T>(e, trailer);
	trail->next = px;
	trail = px;
	_size++;
	return px;
}

/*在结点p后插入元素e*/
template <typename T>
ListNode<T>* LinkList<T>::insert(ListNode<T>* p, T const& e) {
	ListNode<T>* x = new ListNode<T>(e, p->next);
	p->next = x;
	_size++;
	if (x->next == trailer) trail = x;
	return x;
}

/* 清空链表*/
template<typename T>
inline Rank LinkList<T>::clear()
{
	Rank oldSize = _size;
	while (0 < _size) removeNext(header); //反复删除首结点，直至列表变空
	return oldSize;
}


/*移除秩为r的元素*/
template<typename T>
inline bool LinkList<T>::remove(Rank r) {
	if (r >= _size) return false;
	ListNode<T> *p = first(), *oldNode;
	for (int i = 0; i < r-1; i++) p = p->next;
	oldNode = p->next;
	p->next = oldNode->next;
	delete oldNode;
	_size--;
	if (r == _size) ResetTrail(); // 维护 trail
	return true;
}

/*移除合法结点 p->next。
使用了<T>的幅值运算符"="，注意重载"="运算符，注意隐含的复杂度 */
template<typename T>
inline T LinkList<T>::removeNext(ListNode<T>* p)
{
	if (p == trailer || p->next == trailer) return NULL;
	ListNode<T>* oldNode = p->next;
	T oldData = oldNode->data;
	p->next = oldNode->next;
	delete oldNode;
	_size--;
	if (p->next == trailer) trail = p; // 维护 trail
	return oldData;
}

/* 从链表中取出下一结点，返回结点地址 */
template<typename T>
ListNode<T>* LinkList<T>::PickNextNode(ListNode<T>* p) {

	if (p == trailer || p->next == trailer) return NULL;
	ListNode<T>* oldNode = p->next;
	p->next = oldNode->next;
	_size--;
	if (p->next == trailer) trail = p; // 维护 trail
	return oldNode;
}


/* 将 [l, r] 之间的元素反转。
实验题目：lecture1 problem5 */
template<typename T>
inline bool LinkList<T>::reverse(Rank left, Rank right) {
	if (left > right) std::swap(left, right);	// 保证 left不大于 right
	if (right == left) return true;				// 区间长 1 直接返回
	if (right >= _size) return false;			// 区间超出列表 直接返回
	ListNode<T>* p, * q, * l, * r, * i;
	p = LocatePre(left);				// left 的前驱，区间外前一位
	l = p->next;						// left 区间首位
	r = LocatePre(right + 1);			// right 区间末位
	q = r->next;						// right的后继 区间外下一位
	p->next = q;						// 将区间移出链表
	for (;l != q;) {					// 遍历区间
		i = l;							// 记录当前正在处理的结点
		l = l->next;					// 区间首位后移
		i->next = p->next;				// 前向插入链表
		p->next = i;					// -
	}
	return true;
}

