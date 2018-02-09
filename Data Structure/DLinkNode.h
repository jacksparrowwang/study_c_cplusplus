#pragma once

#include<stdio.h>
#include<stdlib.h>

#define FUNCTIONNAME printf("\n================%s=============\n",__FUNCTION__)

typedef char LinkType;

typedef struct DLinkNode{
	LinkType data;
	struct DLinkNode *prev;
	struct DLinkNode *next;
}DLinkNode;

// 初始化链表。
void DLinkNodeInit(DLinkNode *head);

// 尾插一个元素。
void DLninkNodePushBack(DLinkNode *head, LinkType value);

// 尾删一个元素。
void DLinkNodePopBack(DLinkNode *head);

// 头插入一个元素。
void DLinkNodePushFront(DLinkNode *head, LinkType value);

// 头删一个元素。
void DLinkNodePopFront(DLinkNode *head);

// 查找指定元素。
DLinkNode* DLinkNodeFind(DLinkNode *head, LinkType find);

// 在指定位置之前插入一个元素。
void DLinkNodeInsertFront(DLinkNode *pos, LinkType value);

// 在指定元素之后插入一个元素。
void DLinkNodeInsertBack(DLinkNode *pos, LinkType value);

// 删除指定位置的节点。
void DLinkNodeErase(DLinkNode *head,DLinkNode *pos);

// 删除指定元素的第一个节点。
void DLinkNodeRemove(DLinkNode *head, LinkType value);

// 删除指定元素的所有节点。
void DLinkNodeRemoveAll(DLinkNode *head, LinkType value);

// 求链表的长度
size_t DLinkNodeSize(DLinkNode *head);

// 判读链表是否为空。
int DLinkNodeEmpty(DLinkNode *head);
