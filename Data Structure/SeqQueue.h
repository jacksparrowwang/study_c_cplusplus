#pragma once

#include<stdio.h>
#define MAXREPOSITORY 10

#define TEAM_HEAD printf("\n===========%s==========\n",__FUNCTION__)

typedef char QueueType;

typedef struct SeqQueue{
	size_t count;
	size_t size;
	QueueType data[MAXREPOSITORY];
}SeqQueue;

// 初始化。
void InitSeqQueue(SeqQueue *seq);

// 入队。
void PushQueue(SeqQueue *seq,QueueType value);

// 出队。
void PopQueue(SeqQueue *seq);

// 取队首元素。
QueueType FindHead(SeqQueue *seq);

// 取队尾元素。
QueueType FindBottom(SeqQueue *seq);

// 销毁。
void DestoryQueue(SeqQueue *seq);
