#include <iostream>
using namespace std;
#include <assert.h>
#include <unistd.h>
#include <string>
#include "List.h"

template<class T>
List<T>::List(const List<T>& l)
{
    head = new ListNode<T>;
    head->next = head;
    head->prev = head;
    head->data = T();
    ListNode<T>* cur = l.head->next;
    while (cur != l.head)
    {
        /* ListNode<T>* new_node = new ListNode<T>(cur->data); */
        PushBack(cur->data);
        cur = cur->next;
    }
    cout<<head<<" "<<l.head<<endl;
}

// 注意
// 这里是必须要返回的是本对象，用的是一个对象不是一个节点。
template<class T>
List<T>& List<T>::operator=(const List<T>& l)
{
    if (this != &l)
    {
        Clear();
        ListNode<T>* cur = l.head->next;
        while (cur != l.head)
        {
            /* ListNode<T>* new_node = new ListNode<T>(cur->data); */
            PushBack(cur->data);
            cur = cur->next;
        }
    }
    return *this;
}


// 这里采用的插入为在该节点的前面插入
template<class T>
void List<T>::Insert(ListNode<T>* pos, const T& value)
{
    assert(pos);
    ListNode<T>* pre = pos->prev;    
    ListNode<T>* new_node = new ListNode<T>;
    new_node->data = value;

    pre->next = new_node;
   new_node->prev = pre;

    new_node->next = pos;
    pos->prev = new_node;
}

template<class T>
void List<T>::PushBack(const T& value)
{
    Insert(head, value);
}

template<class T>
void List<T>::Erase(ListNode<T>* pos)
{
    assert(pos);
    // 保存前后指针
    ListNode<T>* pre = pos->prev;
    ListNode<T>* nex = pos->next;

    // 互相指向
    pre->next = nex;
    nex->prev = pre;

    delete pos;
}

template<class T>
void List<T>::PopBack()
{
    Erase(head->prev);
}

template<class T>
void List<T>::PopFront()
{
    Erase(head->next);
}

template<class T>
ListNode<T>* List<T>::Find(const T& value)
{
    ListNode<T>* cur = head->next;
    while (cur != head)
    {
        if (cur->data == value)
        {
            return cur;
        }
    }
    return NULL;
}

template<class T>
T& List<T>::FindHead()
{
    // 这里注意
    /* if (IsEmpty()) */
    /* { */
    /*     return ? */
    /* } */
    return head->next->data;
}

#if 0
void TestPushBack()
{
    List<int> l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.Print();

    List<string> l1;
    l1.PushBack("112233");
    l1.PushBack("112233");
    l1.Print();
}

void TestPop()
{
    List<int> l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.PopBack();
    l.Print();

    List<string> l1;
    l1.PushBack("112233");
    l1.PushBack("112233");
    l1.PopBack();
    cout<<l1.Find("112233")<<endl;
    l1.Print();
}

void TestCopy()
{
    List<int> l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.Print();
    List<int> l1(l);
    l1.PushBack(5);
    l1.Print();

    /* l.operator=(l1); */
    /* l.Print(); */

}

void TestO()
{
    
    List<int> l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.Print();
    List<int> l1;
    l1.PushBack(5);
    l1.Print();

    l.operator=(l1);
    l.Print();
}

int main()
{
    /* TestPushBack(); */
    /* TestPop(); */
    /* TestCopy(); */
    TestO();
    return 0;
}
#endif
