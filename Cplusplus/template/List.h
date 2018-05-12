#pragma once
#include <iostream>

template<class T>
struct ListNode
{
    ListNode<T>* next;
    ListNode<T>* prev;
    T data;

    ListNode()
    {
        next = NULL;
        prev = NULL;
    }
};

template<class T>
class List
{
public:
    List():head(new ListNode<T>)
    {
        head->next = head;
        head->prev = head;
        head->data = T();
    }

    List(const List<T>& l);

    List<T>& operator=(const List<T>& l);

    void PushBack(const T& value);

    void PopBack();

    void PopFront();

    ListNode<T>* Find(const T& value);

    T& FindHead();

    void Insert(ListNode<T>* pos, const T& value);

    void Erase(ListNode<T>* pos);

    ~List()
    {
        Clear();
        delete head;
        head = NULL;
    }

    void Clear()
    {
        ListNode<T>* cur = head->next;
        while (cur != head)
        {
            ListNode<T>* cur_next = cur->next;

            head->next = cur_next;
            cur_next->prev = head;
            delete cur;
            cur = cur_next;
        }

        /* head->next = head; */
        /* head->prev = head; */
    }

    void Print()
    {
        ListNode<T>* cur = head->next;
        while (cur != head)
        {
            cout<<cur->data<<" ";
            cur = cur->next;
        }
        cout<<endl;
    }

protected:
    ListNode<T>* head;
};
