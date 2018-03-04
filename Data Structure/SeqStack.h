#pragma once

#include<stdio.h>

#define MAXREPOSITORY 1000
#define PRINTSEQSTACKNAME printf("\n=============%s==========\n",__FUNCTION__)

typedef char SeqType;

typedef struct SeqStack{
	size_t size;
	SeqType data[MAXREPOSITORY];
}SeqStack;

// 初始化。
void SeqStackInit(SeqStack *seq);

// 入栈。
void SeqStackPushStack(SeqStack *seq, SeqType value);

// 出栈。
void SeqStackPopStack(SeqStack *seq);

// 取栈顶元素。
SeqType SeqStackFindTop(SeqStack *seq);

// 销毁。
void SeqStackDestory(SeqStack *seq);
