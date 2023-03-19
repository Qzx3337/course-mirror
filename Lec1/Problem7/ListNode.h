#pragma once

/*�����rank �������±� rank=0, 1, 2, ... , n-1 */
typedef unsigned int Rank;
#ifndef NULL
#define NULL 0
#endif // !NULL


template <typename T>
class ListNode {
public:
    T data;
    ListNode<T>* pred;
    ListNode<T>* next;

    // ����

    ListNode() {}
    ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL)
        : data(e), pred(p), next(s) {}

    // �ӿ�

    ListNode<T>* insertAsPred(T const& e);
    ListNode<T>* insertAsNext(T const& e);

};

template<typename T>
inline ListNode<T>* ListNode<T>::insertAsPred(T const& e)
{
    ListNode<T>* p = new ListNode<T>(e, pred, this);
    pred->next = p;
    pred = p;
    return p;
}

template<typename T>
inline ListNode<T>* ListNode<T>::insertAsNext(T const& e)
{
    ListNode<T>* p = new ListNode<T>(e, this, next);
    next->pred = p;
    next = p;
    return p;
}

