/********************

�ࣺ����ģ���� LinkList
1.��ʼ����
	��ʼ��Ϊ������
	��������������ʼ��Ϊ�丱��������һ�飩
2.������1.ǰ�� 2.��� ������
3.�����ݲ��ң�������
4.������
5.ɾ�����

*****************/
#pragma once
#include "ListNode.h" //�����б�����
#include <iostream>
#include <typeinfo>
#include <cstdio>

template <typename T>
class LinkList
{
	// ������� ȫ��public
public:
	Rank _size;						// ���ݽ�����
	ListNode<T> *header, *trailer;	// ͷ��㡢β��� ��֤����Ԫ�ض�����ǰ���к�̵�
	ListNode<T> *trail;				// βָ�룬��¼���һ��Ԫ�صĵ�ַ�������ڴ˺���룩


	void init();					//�б���ʱ�ĳ�ʼ��
	ListNode<T>* LocatePre(Rank r);
	void ResetTrail();

	// ���캯��
	LinkList() { init(); } //Ĭ��	
	LinkList(LinkList<T> const& L); //���帴���б�L
	// ��������
	~LinkList(); //�ͷţ�����ͷ������ڵģ����н��

	// ֻ�����ʽӿ�
	unsigned int size() const { return _size; }	//��ģ
	bool empty() const { return _size <= 0; }	//�п�
	T operator[](Rank r) const;					//����[]��֧���±���ʣ�Ч�ʵͣ�
	ListNode<T>* first() const { return header->next; }	//�׽��λ��
	ListNode<T>* last() const { return trail; }			//ĩ���λ��
	ListNode<T>* Locate(T const& e);	/*�������ݲ��ҽ��ĵ�ַ*/
	int Find(T const& e);				/*�������ݲ���Ԫ�ص���*/
	void show();						// ��ʾ�б�
	T* GetLast(Rank k);					/* ���ҵ�����k��Ԫ��*/

	// ��д���ʽӿ�

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


/* ��ʼ��Ϊ������ */
template <typename T>
void LinkList<T>::init() {
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->next = trailer;
	trailer->next = NULL;
	_size = 0;
	trail = header;
}

/* ������Ϊr�Ľ���ǰ���ĵ�ַ����֤����Ϸ���*/
template <typename T>
ListNode<T>* LinkList<T>::LocatePre(Rank r) {
	if (r > size() + 1) return NULL;
	ListNode<T>* p = header;
	while (r--) p = p->next;
	return p;
}

/* �����ڲ�����trail��ָ�����һλԪ�ء� */
template<typename T>
inline void LinkList<T>::ResetTrail()
{
	ListNode<T>* p = header;
	while (p->next != trailer) p = p->next;
	trail = p;
}

/* ���������б���й��� */
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


/* �����±����������ͨ���±�ֱ�ӷ��ʽ�㣨O(r)Ч�ʣ����ã�*/
template <typename T>
inline T LinkList<T>::operator[](Rank r) const { // 0 <= r < size
	if (r < 0) return 0;				// ���ֲ��Ϸ�����
	if (r >= size()) return 0;
	ListNode<T>* p = first();			//���׽�����
	while (0 < r--) p = p->next;		//˳����r����㼴��
	return p->data;						//Ŀ����
}

/*�������ݲ���Ԫ�� �˴�Ϊ��������*/
template <typename T>
ListNode<T>* LinkList<T>::Locate(T const& e) {
	for (ListNode<T>* p = first(); p != trailer; p = p->next) {
		if (p->data == e) {
			return p;
		}
	}
	return NULL;
}

/*�������ݲ���Ԫ�� �˴�Ϊ��������*/
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

/* ��ʾ�б���Ϣ�����ݡ�ʹ��cout�������Ļ���ǵ�����"<<"�����
�����ʽ�����������ͣ�ʵ����֮�󣩣���ַ������Ԫ�ظ������б����� */
template<typename T>
void LinkList<T>::show() {
	printf("\n%s, [%X]*%d:\n", typeid (this).name(), (int)this, _size); //������Ϣ
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

/* ���ҵ����� k��Ԫ�أ��������������ָ�롣��������ڵ����� k���򷵻� NULL ��
��Ŀ��Lecture1 Problem4 */
template <typename T>
T* LinkList<T>::GetLast(Rank k) {
	if (k > _size) return NULL;						// ����Ԫ���������⣬������
	if (k == 0) return NULL;						// ���ҵ�����0����������
	ListNode<T>* p, * q;
	for (p = q = first(); k--; q = q->next);		// �� p, q �������Ϊ k
	for (; q != trailer; q = q->next, p = p->next);	// ʹ p, q ƽ���ƶ�������β
	return &(p->data);								// ���� p ��λ��
}

/*��e��Ϊ��Ԫ�ز���*/
template <typename T>
ListNode<T>* LinkList<T>::insertAsFirst(T const& e) {
	ListNode<T>* px = new ListNode<T>(e, header->next);
	header->next = px;
	_size++;
	return px;
}

/*�����p��Ϊ��һ��������*/
template <typename T>
ListNode<T>* LinkList<T>::insertAsFirst(ListNode<T>* px) {
	px->next = header->next;
	header->next = px;
	_size++;
	return px;
}

/*��e��ΪĩβԪ�ز���*/   
template <typename T>
ListNode<T>* LinkList<T>::insertAsLast(T const& e) {
	ListNode<T>* px = new ListNode<T>(e, trailer);
	trail->next = px;
	trail = px;
	_size++;
	return px;
}

/*�ڽ��p�����Ԫ��e*/
template <typename T>
ListNode<T>* LinkList<T>::insert(ListNode<T>* p, T const& e) {
	ListNode<T>* x = new ListNode<T>(e, p->next);
	p->next = x;
	_size++;
	if (x->next == trailer) trail = x;
	return x;
}

/* �������*/
template<typename T>
inline Rank LinkList<T>::clear()
{
	Rank oldSize = _size;
	while (0 < _size) removeNext(header); //����ɾ���׽�㣬ֱ���б���
	return oldSize;
}


/*�Ƴ���Ϊr��Ԫ��*/
template<typename T>
inline bool LinkList<T>::remove(Rank r) {
	if (r >= _size) return false;
	ListNode<T> *p = first(), *oldNode;
	for (int i = 0; i < r-1; i++) p = p->next;
	oldNode = p->next;
	p->next = oldNode->next;
	delete oldNode;
	_size--;
	if (r == _size) ResetTrail(); // ά�� trail
	return true;
}

/*�Ƴ��Ϸ���� p->next��
ʹ����<T>�ķ�ֵ�����"="��ע������"="�������ע�������ĸ��Ӷ� */
template<typename T>
inline T LinkList<T>::removeNext(ListNode<T>* p)
{
	if (p == trailer || p->next == trailer) return NULL;
	ListNode<T>* oldNode = p->next;
	T oldData = oldNode->data;
	p->next = oldNode->next;
	delete oldNode;
	_size--;
	if (p->next == trailer) trail = p; // ά�� trail
	return oldData;
}

/* ��������ȡ����һ��㣬���ؽ���ַ */
template<typename T>
ListNode<T>* LinkList<T>::PickNextNode(ListNode<T>* p) {

	if (p == trailer || p->next == trailer) return NULL;
	ListNode<T>* oldNode = p->next;
	p->next = oldNode->next;
	_size--;
	if (p->next == trailer) trail = p; // ά�� trail
	return oldNode;
}


/* �� [l, r] ֮���Ԫ�ط�ת��
ʵ����Ŀ��lecture1 problem5 */
template<typename T>
inline bool LinkList<T>::reverse(Rank left, Rank right) {
	if (left > right) std::swap(left, right);	// ��֤ left������ right
	if (right == left) return true;				// ���䳤 1 ֱ�ӷ���
	if (right >= _size) return false;			// ���䳬���б� ֱ�ӷ���
	ListNode<T>* p, * q, * l, * r, * i;
	p = LocatePre(left);				// left ��ǰ����������ǰһλ
	l = p->next;						// left ������λ
	r = LocatePre(right + 1);			// right ����ĩλ
	q = r->next;						// right�ĺ�� ��������һλ
	p->next = q;						// �������Ƴ�����
	for (;l != q;) {					// ��������
		i = l;							// ��¼��ǰ���ڴ���Ľ��
		l = l->next;					// ������λ����
		i->next = p->next;				// ǰ���������
		p->next = i;					// -
	}
	return true;
}

