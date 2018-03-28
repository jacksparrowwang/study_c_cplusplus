#pragma once

#include<stdio.h>
#define MAXREPOSITORY 1000

#define TEAM_HEAD printf("\n===========%s==========\n",__FUNCTION__)

typedef char QueueType;
typedef struct SeqQueue{
	size_t tail;
	size_t count;
	size_t size;
	QueueType data[MAXREPOSITORY];
}SeqQueue;

typedef struct StackUseQueue{
    SeqQueue q1;
    SeqQueue q2;
}StackUseQueue;

// 初始化。
void InitSeqQueue(SeqQueue *seq);

// 入队。
void PushQueue(SeqQueue *seq,QueueType value);

// 出队。
void PopQueue(SeqQueue *seq);

// 取队首元素。
int FindHeadQueue(SeqQueue *seq, QueueType *value);

// 销毁。
void DestoryQueue(SeqQueue *seq);

////////////////////////
//两个队构建一个栈
////////////////////////

void InitSeqQueueUseStack(StackUseQueue *queue);

void PushQueueUseStack(StackUseQueue *queue, QueueType value);

void PopQueueUseStack(StackUseQueue *queue);

///////////////////////////
//一个数组实现两个栈
///////////////////////////


