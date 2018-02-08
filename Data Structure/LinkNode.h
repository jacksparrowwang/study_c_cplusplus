#pragma once

#include<stdio.h>
#include<stdlib.h>


#define DIV_LINE printf("\n\n===========%s==========\n\n",__FUNCTION__);

typedef char TypeChar;

typedef struct LinkNode
{
	TypeChar data;
	struct LinkNode *next;
}LinkNode;

//对单链表进行初始化
void InitLinkNode(LinkNode **head);

//打印
void LinkNodePrint(LinkNode *head);

//创建节点
LinkNode *CreatNode(TypeChar value);

//对单链表进行尾插;
LinkNode* PushBackLinkNode(LinkNode** head, TypeChar Value);

//对单链表进行尾删
void PopBackLinkNode(LinkNode** head);

//对单链表进行头插
void PushFrontLinkNode(LinkNode** head, TypeChar Value);

//对单链表进行头删
void PopFrontLinkNode(LinkNode** head);

//对单链表进行值位置的查找，返回对应值的地址
LinkNode* FindLinkNode(LinkNode* head, TypeChar value);

//在链表的指定位置之前插入元素，普通放方法,时间复杂度O(n)
void InsertFrontLinkNode(LinkNode** head, LinkNode* pos, TypeChar value);

//在链表的指定位置之前插入元素。（移花接木大法）时间复杂度为o(1).
void InsertFrontLinkNode1(LinkNode** head, LinkNode* pos, TypeChar value);

//在单链表指定位置之后插入元素。
void InsertAfterLinkNode(LinkNode* head, LinkNode* pos, TypeChar value);

//删除单链表中任意指定位置的节点。时间复杂度为o(n)
void EraseLinkNode(LinkNode** head, LinkNode* pos);

//删除单链表中指定位置的节点，（除过尾节点）时间复杂度为o(1).
void EraseLinkNode1(LinkNode* head, LinkNode* pos);

//删除指定值的节点，（在无头单链表中第一个出现的值的节点）
void RemoveLinkNode(LinkNode** head, TypeChar value);

//删除指定值的所有元素。
void RemoveLinkNodeAll(LinkNode** head, TypeChar value);

//判断链表是否为空
int EmotyLinkNode(LinkNode* head);

//求链表长度
size_t SizeLinkNode(LinkNode* head);

//将链表逆序打印
void BackPrintLinkNode(LinkNode* head);