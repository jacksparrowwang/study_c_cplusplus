#include "LinkList.h"
using namespace std;

void Link::PrintLinkList(const char* msg)
{
    LinkNode* cur = head->next;
    while (cur != head)
    {
        printf("%c ", cur->data);
        cur = cur->next;
    }
    printf("\n");
    printf("%s\n",msg);
}


Link::Link(const Link& l)
{
    // 一定要初始化.
    head = new LinkNode(LinkType());
    head->next = head;
    head->prev = head;

    LinkNode* cur = l.head->next;
    while (cur != l.head)
    {
        LinkNode* new_node = new LinkNode(cur->data);
        LinkNode* pre = head->prev;

        new_node->prev = pre;
        pre->next = new_node;

        head->prev = new_node;
        new_node->next = head;

        cur = cur->next;
    }
}

Link::~Link()
{
    while (head->next != head)
    {
        LinkNode* to_delete = head->next;
        head->next = to_delete->next;
        to_delete->next->prev = head;
        delete to_delete;
    }
    delete head;
}

Link& Link::operator=(const Link& l)
{
    // 先释放原来的链表结点，除头结点
    while (head->next != head)
    {
        LinkNode* to_delete = head->next;
        head->next = to_delete->next;
        to_delete->next->prev = head;
        delete to_delete;
    }
    // 再进行拷贝
    LinkNode* cur = l.head->next;
    while (cur != l.head)
    {
        LinkNode* new_node = new LinkNode(cur->data);
        LinkNode* pre = head->prev;

        new_node->prev = pre;
        pre->next = new_node;

        pre = new_node;
        new_node->next = head;
        cur = cur->next;
    }
    return *this;
}

LinkNode* Link::PushBack(LinkType value)
{
    LinkNode* new_node = new LinkNode(value);
    LinkNode* pre = head->prev;

    new_node->prev = pre;
    pre->next = new_node;

    new_node->next = head;
    head->prev = new_node;
    return new_node;
}

void Link::PushFront(LinkType value)
{
    LinkNode* new_node = new LinkNode(value);
    LinkNode* nex = head->next;

    head->next = new_node;
    new_node->prev = head;

    new_node->next = nex;
    nex->prev = new_node;
}

void Link::PopBack()
{
    if (head->next != head)
    {
        LinkNode* to_delete = head->prev;
        head->prev = to_delete->prev;
        to_delete->prev->next = head;
        delete to_delete;
    }
}

void Link::PopFront()
{
    if (head->next != head)
    {
        LinkNode* to_delete = head->next;

        head->next = to_delete->next;
        to_delete->next->prev = head;

        delete to_delete;
    }
}

LinkNode* Link::Find(LinkType value)
{
    LinkNode* cur = head->next;
    while (cur != head)
    {
        if (cur->data == value)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

bool Link::Insert(LinkNode* pos, LinkType value)
{
    if (pos == NULL)
    {
        return false;
    }
    LinkNode* cur = head->next;
    while (cur != head)
    {
        if (cur == pos)
        {
            LinkNode* new_node = new LinkNode(value);
            LinkNode* nex = cur->next;
            cur->next = new_node;
            new_node->prev = cur;

            new_node->next = nex;
            nex->prev = new_node;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool Link::Erase(LinkNode* pos)
{
    if (pos == NULL)
    {
        return false;
    }
    LinkNode* cur = head->next;
    while (cur != head)
    {
        if (cur == pos)
        {
            LinkNode* pre = pos->prev;
            LinkNode* nex = pos->next;
            pre->next = nex;
            nex->prev = pre;
            delete pos;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

///////////////////////////////
//测试代码
///////////////////////////////

#define TESTHEAD printf("\n================%s=============\n", __FUNCTION__)

void TestStruct()
{
    TESTHEAD;
    Link l1;
    l1.PushBack('a');
    l1.PrintLinkList("构造链表并尾插一个元素，打印一个a");
}

void TestCopyStrcut()
{
    TESTHEAD;
    Link l1;
    l1.PushBack('a');

    Link l2(l1);
    l2.PrintLinkList("构造拷贝，打印一个a");
}

void Testfuzhi()
{
    TESTHEAD;
    Link l1;
    /* l1.PushBack('a'); */
    /* l1.PushBack('b'); */

    Link l2;
    l2.PushBack('e');
    l1 = l2;
    l1.PrintLinkList("赋值运算符重载，l1 a b 赋值为 l2 e");
}

void TestPushFront()
{
    TESTHEAD;
    Link l1;
    l1.PushBack('a');
    l1.PushBack('b');
    l1.PushFront('c');
    l1.PrintLinkList("头插一个元素c");
}

void TestPopBack()
{
    TESTHEAD;
    Link l1;
    l1.PushBack('a');
    l1.PushBack('b');
    l1.PushFront('c');
    l1.PopBack();
    l1.PrintLinkList("尾删一个元素");
}

void TestPopFront()
{
    TESTHEAD;
    Link l1;
    l1.PushBack('a');
    l1.PushBack('b');
    l1.PushFront('c');
    l1.PopFront();
    l1.PrintLinkList("头删一个元素");
}

void TestFind()
{
    TESTHEAD;
    Link l1;
    l1.PushBack('a');
    LinkNode* ret = l1.PushBack('b');
    printf("except %p actual %p\n", ret, l1.Find('b'));
}

void TestInsert()
{
    TESTHEAD;
    Link l1;
    l1.PushBack('a');
    l1.PushBack('b');
    LinkNode* ret = l1.PushBack('c');
    l1.PushBack('d');
    l1.Insert(ret, 'e');
    l1.PrintLinkList("在c的下一个插入一个e结点");
}

void TestErase()
{
    TESTHEAD;
    Link l1;
    l1.PushBack('a');
    l1.PushBack('b');
    LinkNode* ret = l1.PushBack('c');
    l1.PushBack('d');
    l1.Erase(ret);
    l1.PrintLinkList("删除abcd中的c");
}

int main()
{
    TestStruct();
    TestCopyStrcut();
    Testfuzhi();
    TestPushFront();
    TestPopBack();
    TestPopFront();
    TestFind();
    TestInsert();
    TestErase();
    return 0;
}
