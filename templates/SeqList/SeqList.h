/******************
SeqListģ���� �����б�
ʵ�ֻ������ܣ�
	1.����
	2.��ӣ���ĩβ�����б�������λ��
	3.ɾ�����������ɾ������������ɾ��
	4.��ѯ�������±��ѯ���ݡ��������ݲ�ѯ�±�

����ڿα��������˶�̬�ռ�����ܣ�
	1.���Ԫ��ʱ��������������������ޣ���һ���µĴ����飬���������
	2.ɾ��Ԫ��ʱ�����Ԫ������ԶԶС������������С�����ʡ�ռ�

*********************/


#pragma once
#include <iostream>
#include <algorithm>

typedef unsigned int position;

// ��ʼ�������ޣ�һ��ϴ� Ϊ�˲�������ȡ�Ľ�С
unsigned int const INIT_CAPACITY = 4;


/*�����б� �ڲ���������ʵ��*/
template <typename T>
class SeqList
{
	// Ϊ�˲��� ȫ��public
public:
	
	T* data; // ������ 
	position _size, _capacity; //Ԫ�ظ��� ��ǰ��������

	// �ڲ�����
	void init(); // ��ʼ��
	bool expand(); // ����
	bool shrink(); // ѹ��

	SeqList() { init(); }	// ���캯��
	~SeqList() { delete[] data; }	// ��������

	// ֻ�����ʽӿ�
	bool empty() { return (!_size); };// �б��Ƿ�Ϊ��
	unsigned int size() { return _size; } // Ԫ�ظ���
	int find(T const e); //���� 
	void show(); // ��ʾ

	// ��д���ʽӿ�
	void add(T e);// ���һ���� ��ĩβ
	void insert(position const p, T const e);// ����
	void clear(); // ����б��ͷſռ�
	void Delete(position const p);// ɾ�� ����λ��
	void remove(T const a);	// ɾ�� ����ֵ
	void sort(); // ����
	void PickAscendList(); // ��ȡ���������У��������ȥ�أ�

};


/********  ����Ϊʵ��  ********/

// ��ʼ��
template <typename T>
void SeqList<T>::init() {
	_size = 0; // û��Ԫ��
	_capacity = INIT_CAPACITY; // ��ʼ����
	data = new T[_capacity]; // �������ݿռ�
}

/* ���� ����������ʱ ����Ϊԭ��������*/
template <typename T>
inline bool SeqList<T>::expand() {
	if (_size < _capacity) return false; // ���������ͷ���
	if (_capacity < INIT_CAPACITY) _capacity = INIT_CAPACITY; // ��֤��������������
	_capacity <<= 1; // �����ӱ�
	T* oldData = data; // ��¼������
	data = new T[_capacity]; // Ϊ�����ݿ��ռ�
	for (int i = 0; i < _size; i++) { // ��������
		data[i] = oldData[i];
	}
	delete[] oldData; // �ͷ�ԭ�ռ�
	return true;
}

/* ѹ�� ��������ʣ��ռ�ý�Ϊ25%��ʱ ѹ���ռ�Ϊһ��*/
template <typename T>
inline bool SeqList<T>::shrink() {
	if (_size << 2 > _capacity) return false; // ���κ�expand()��ȫ����
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

/* ���� ���ص�һ��ֵΪe��Ԫ�ص�λ�� �Ҳ����ͷ���-1*/
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

/* ��ʾ�б���Ϣ�� cout<< �������Ļ �ǵ������������
�����ʽ�������� [��ַ] * Ԫ�ظ��� / �������� */
template <typename T>
void SeqList<T>::show() {
	printf("\n%s [%X]*%d /%d:\n", typeid (this).name(), (int)data, _size, _capacity); //������Ϣ
	printf("[");
	for (int i = 0; i < _size; i++) {
		if (i && i% 10 == 0) printf("\n ");
		std::cout << data[i]; 
		if (i < _size - 1) printf(", ");
	}
	printf(" ]\n");
}

// ���һ���� ��ĩβ
template <typename T>
void SeqList<T>::add(T e) {
	expand();
	data[_size++] = e;
}

/* ���� ��λ��pǰ����һ��Ԫ��e */
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

/* ����б��ͷſռ� */
template <typename T>
void SeqList<T>::clear() {
	delete data;
	init();
}

/* ɾ�� λ����p��Ԫ��*/
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

/*ɾ�� ֵΪa��Ԫ��*/
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

/*���������������� �õ��ǵݼ����� ����<T>��"<"�����*/
template <typename T>
void SeqList<T>::sort() {
	std::sort(data, data + _size);
}

/*������� ȥ�أ�������� ��ȡ�����������У�����<T>��"<"����� */
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

