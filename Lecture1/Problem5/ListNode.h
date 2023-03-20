
#pragma once

/*链表的rank 类似于数组的下标 链表中的元素下标依次为 rank=0, 1, 2, ... , n-1 */
typedef unsigned int Rank;

template <typename T>
struct ListNode { //链表结点

    T data;
    ListNode<T>* next;

    // 构造
    ListNode() {}
    ListNode(T e, ListNode<T>* s) : data(e), next(s) {}

};


