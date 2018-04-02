#ifndef __TOPICLINKNODE_H__
#define __TOPICLINKNODE_H__
//#pragma once
#include<stdio.h>
#include<stdlib.h>
#define DIVE_LINE printf("\n=============%s============\n",__FUNCTION__)

typedef char TypeChar;

typedef struct LinkNode{
	struct LinkNode* next;
	TypeChar data;
}LinkNode;

// 对链表进行初始化。
void InitLinkNode(LinkNode** head);
// 创建一个节点。 LinkNode* CreatNode(TypeChar value); // 打印 void PrintLinkNode(LinkNode* head);

//尾插一个元素
LinkNode* PushBackLinkNode(LinkNode** head, TypeChar value);

//创建一个节点
LinkNode* CreatNode(TypeChar value); // 从尾到头打印单链表。 void PrintBackLinkNode(LinkNode* head);

// 删除一个无头单链表的非尾节点（不能遍历链表）
void EraseLinkNode(LinkNode* head, LinkNode* pos);

// 单链表实现约瑟夫环。
LinkNode* JosephCycle(LinkNode* head, size_t food);

// 逆置单链表/反转单链表。
void ReverseLinkNode(LinkNode** head);

// 单链表排序（冒泡）。
void BubbleSortLinkNode(LinkNode* head);

// 合并两个有序列表，合并后任然有序。
LinkNode* MergeOrderLinkNode(LinkNode** head1, LinkNode** head2);

// 查找单链表的中间节点，要求只能变脸一次链表。
LinkNode* FindMidNodeLinkNode(LinkNode* head);

// 查找单链表的倒数第K个节点，要求只遍历一次链表。
LinkNode* FindBackKNodeLinkNode(LinkNode* head, size_t k);

// 删除链表倒数第K个节点。
void EraserBackKNodeLinkNode(LinkNode** head, size_t k);

// 判断单链表是否带环？若带环，求环的长度？求环的入口点？并计算每个算法的时间复杂度。
int  DecideLoopLinkNode(LinkNode* head,int *length,LinkNode** enter);

// 判断两个链表是否相交，若相交，求出交点。（假设链表不带环）
int DecideIntersectLinkNode(LinkNode* head1, LinkNode* head2,LinkNode** intersect);

//判断两个链表是否相交，若相交，求出交点。（假设链表可能带环）
int DecideIntersectLinkNode1(LinkNode* head1, LinkNode* head2);

// 复杂链表的复制。一个链表的每个节点，有一个指向next指针指向下一个节点，还有
// 一个random指针指向这个链表中的一个随机节点或者NULL，现在要求实现复制这条链
// 表，返回复制厚的新链表。
typedef struct ComplexLinkNode{
	TypeChar data;
	struct ComplexLinkNode* next;
    struct ComplexLinkNode *random;
}ComplexLinkNode;

ComplexLinkNode *CreatComplexNode(TypeChar value);

ComplexLinkNode *CypeComplexLinkNode(ComplexLinkNode *head);

ComplexLinkNode *CypeComplexLinkNode2(ComplexLinkNode *head);
// 求两个已排序单链表中相同的数据。
void UnionSet(LinkNode* l1, LinkNode* l2);
#endif
