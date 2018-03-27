#pragma once

#include<stdio.h>
#include<stdilb.h>


// 线索化二叉树
typedef char ThreadType;

typedef enum Flag{
	CHILD;
	THREAD;
}Flag;

typedef struct ThreadNode{
	ThreadType data;
	struct ThreadNode *left;
	struct ThreadNode *right;
	Flag lflag;
	Flag rflag;
}ThreadNode;

// 创建树,用二叉树先序结果带空指针域创建
ThreadNode *ThreadTreeCreat(ThreadType arr[], size_t size, TreadType nullnode);

// 先序线索化
void PreThreading(ThreadNode *root);

// 先序线索化遍历。(相当于链表)
void PreOrderByThreading(ThreadNode *root);

// 中序线索化
void InThreading(ThreadNode *root);

// 中序线索化遍历。(相当于链表)
void InOrderByThreading(ThreadNode *root);

// 后序线索化
void PostThreading(ThreadNode *root);

// 后序线索化遍历。(相当于链表)
void PostOrderByThreading(ThreadNode *root);
