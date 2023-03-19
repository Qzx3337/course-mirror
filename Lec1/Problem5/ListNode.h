
#pragma once

/*�����rank ������������±� �����е�Ԫ���±�����Ϊ rank=0, 1, 2, ... , n-1 */
typedef unsigned int Rank;

template <typename T>
struct ListNode { //������

    T data;
    ListNode<T>* next;

    // ����
    ListNode() {}
    ListNode(T e, ListNode<T>* s) : data(e), next(s) {}

};


