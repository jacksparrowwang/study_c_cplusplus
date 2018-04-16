#pragma once
#include <iostream>

typedef char LinkType;

struct LinkNode
{
    LinkType data;
    LinkNode* prev;
    LinkNode* next;

    LinkNode(LinkType x)
        :data(x)
         ,prev(NULL)
         ,next(NULL)
    {}
};
class Link
{
public:
    // 这里调用了结点的构造函数
    Link():head(new LinkNode(LinkType()))
    {
        head->prev = head;
        head->next = head;
    }
    Link(const Link& l);
    Link& operator=(const Link& l);
    ~Link();

    void PrintLinkList(const char* msg);
    LinkNode* PushBack(LinkType value);
    void PushFront(LinkType value);
    void PopBack();
    void PopFront();
    LinkNode* Find(LinkType value);
    bool Insert(LinkNode* pos, LinkType value);
    bool Erase(LinkNode* pos);

private:
    LinkNode* head;
};
