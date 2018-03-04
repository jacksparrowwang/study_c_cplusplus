#ifndef __LINKSTACK_H__
#define __LINKSTACK_H__

#include<stdio.h>
#include<stdlib.h>
#define LINKSTACKNAME printf("\n=========%s========\n",__FUNCTION__)

typedef char LinkType;

typedef struct LinkNode{
	LinkType data;
	struct LinkNode *next;
}LinkNode;

// 初始化。带头不带环单链表。
void LinkStackInit(LinkNode *head);

// 入栈。
void LinkStackPushStack(LinkNode *head, LinkType value);

// 出栈。
void LinkStackPopStack(LinkNode *head);

// 取栈顶元素。
LinkType LinkStackFindTop(LinkNode *head);

// 销毁。
void LinkStackDestory(LinkNode *head);
#endif
