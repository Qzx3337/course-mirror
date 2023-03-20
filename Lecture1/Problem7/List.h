/********************

˫������List

*****************/
#pragma once

#include <iostream>
#include <cstdio>
#include <typeinfo>
#include "ListNode.h" //������������

template <typename T>
class List { //����ģ����

private:
	Rank _size;
	ListNode<T>* header, * trailer;	//��ģ��ͷ��㡢β���

protected:
	void init();		//�б���ʱ�ĳ�ʼ��
	Rank clear();		//������н��
	void copyNodes(ListNode<T>*, Rank);		//�����б�����λ��p���n��
	ListNode<T>* merge(ListNode<T>*, Rank, List<T>&, ListNode<T>*, Rank); //�鲢
	void mergeSort(ListNode<T>*&, Rank);	//�Դ�p��ʼ������n�����鲢����
	void radixSort(ListNode<T>*, Rank);		//�Դ�p��ʼ������n������������

public:

	// ���캯��
	List() { init(); }			//Ĭ��
	List(List<T> const& L);		//���帴���б�L
	List(List<T> const& L, Rank r, Rank n); //�����б�L���Ե�r�����n��
	List(ListNode<T>* p, Rank n); //�����б�����λ��p���n��
	// ��������
	~List(); //�ͷţ�����ͷ��β���ڵģ����н��
	
// ֻ�����ʽӿ�

	Rank size() const { return _size; }			//��ģ
	bool empty() const { return _size <= 0; }	//�п�
	ListNode<T>* operator[](Rank r) const;		//���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
	ListNode<T>* first() const { return header->next; } //�׽��λ��
	ListNode<T>* last() const { return trailer->pred; } //ĩ���λ��
	bool valid(ListNode<T>* p)					//�ж�λ��p�Ƿ����Ϸ�
	{
		return p && (trailer != p) && (header != p);
	} //��ͷ��β����ͬ��NULL
	ListNode<T>* find(T const& e) const		//�����б����
	{
		return find(e, _size, trailer);
	}
	ListNode<T>* find(T const& e, Rank n, ListNode<T>* p) const; //�����������
	ListNode<T>* search(T const& e) const	//�����б����
	{
		return search(e, _size, trailer);
	}
	ListNode<T>* search(T const& e, Rank n, ListNode<T>* p) const;	//�����������
	ListNode<T>* selectMax(ListNode<T>* p, Rank n);					//��p����n-1�������ѡ�������
	ListNode<T>* selectMax() { return selectMax(header->succ, _size); } //���������
	void show();
	void showElem();
 
// ��д���ʽӿ�

	ListNode<T>* insertAsFirst(T const& e);		//��e�����׽�����
	ListNode<T>* insertAsLast(T const& e);		//��e����ĩ������
	ListNode<T>* insert(ListNode<T>* p, T const& e); //��e����p�ĺ�̲���
	ListNode<T>* insert(T const& e, ListNode<T>* p); //��e����p��ǰ������
	T remove(ListNode<T>* p); //ɾ���Ϸ�λ��p���Ľ��,���ر�ɾ�����
	void merge(List<T>& L) { merge(header->succ, _size, L, L.header->succ, L._size); } //ȫ�б�鲢
	void sort(ListNode<T>*, Rank); //�б���������
	void sort() { sort(first(), _size); } //�б���������
	Rank deduplicate(); //����ȥ��
	Rank uniquify(); //����ȥ��
	void reverse(); //ǰ����  
}; //List

/* չʾ������Ϣ��
��ʽ�� ������ [��ַ] * ��С */
template<typename T>
inline void List<T>::show()
{
	printf("\n%s [%X]*%d:\n", typeid (this).name(), (int)this, _size); //������Ϣ
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

/* չʾ����Ԫ�� */
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

// e�����׽�����
template <typename T> ListNode<T>* List<T>::insertAsFirst(T const& e)
{
	_size++; return header->insertAsSucc(e);
}

// e����ĩ������
template <typename T> ListNode<T>* List<T>::insertAsLast(T const& e)
{
	_size++; return trailer->insertAsPred(e);
} 

// e����p�ĺ�̲���
template <typename T> ListNode<T>* List<T>::insert(ListNode<T>* p, T const& e)
{
	_size++; return p->insertAsSucc(e);
} 

// e����p��ǰ������
template <typename T> ListNode<T>* List<T>::insert(T const& e, ListNode<T>* p)
{
	_size++; return p->insertAsPred(e);
} 

/* ��ʼ��Ϊ������  */
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

/* ����������������������ͷ�ͷ���β��㡣 */
template<typename T>
inline List<T>::~List()
{
	clear(); 
	delete header;
	delete trailer;
}

/* ��������ͷ����н�� */
template <typename T>
Rank List<T>::clear() { 
	Rank oldSize = _size;
	while (0 < _size) remove(header->next); //����ɾ���׽�㣬ֱ���б���
	return oldSize;
}

// ɾ���Ϸ����p����������ֵ���������ڸ�ֵ��
template <typename T>
T List<T>::remove(ListNode<T>* p) { 
	T e = p->data;				//���ݴ�ɾ��������ֵ
	p->pred->next = p->next;
	p->next->pred = p->pred;	//��̡�ǰ��
	delete p;
	_size--;					//�ͷŽ�㣬���¹�ģ
	return e;					//���ر��ݵ���ֵ
}

//ǰ����
template <typename T> void List<T>::reverse() { 
	if (_size < 2) return;							//ƽ�����
	for (ListNode<T>* p = header; p; p = p->pred)	//��ǰ������α���
		std::swap(p->pred, p->next);				//����������ǰ�������ָ��
	std::swap(header, trailer);						//ͷ��β��㻥��
}

