#pragma once

#include<stdio.h>
#include<malloc.h>
//#ifndef __D_SEQLIST_H__
//#define __D_SEQLIST_H__
//#endif 

typedef char CHAR;

typedef struct seqlist
{
	CHAR *elem;
	size_t size;
	size_t capacity;
}seqlist;

seqlist seq;

//打印顺序表
void seqlist_print(seqlist *seq);

//对动态顺序表的初始化
void seqlist_init(seqlist *seq);

//进行顺序表的尾插
void seqlist_push_back(seqlist *seq,CHAR value);

//对容器的扩容
void seqlist_expand_capacity(seqlist *seq);

//对顺序表的销毁
void seqlist_destroy(seqlist *seq);


