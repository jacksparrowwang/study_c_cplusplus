#pragma once

#include<stdio.h>
#define MAXREPOSITORY 1000

#define TEAM_HEAD printf("\n===========%s==========\n",__FUNCTION__)

#if 0
typedef char QueueType;
#else
	struct TreeNode;
	typedef struct TreeNode* QueueType;
#endif
typedef struct SeqQueue{
	size_t tail;
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
int FindHead(SeqQueue *seq, QueueType *value);

// 销毁。
void DestoryQueue(SeqQueue *seq);
