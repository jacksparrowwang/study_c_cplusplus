#include"SeqQueue.h"


// 初始化。
void InitSeqQueue(SeqQueue *seq)
{
	if (seq == NULL)
	{
		return;
	}
	seq->size = 0;
	seq->count = 0;
	seq->tail = 0;
}


// 入队。
void PushQueue(SeqQueue *seq,QueueType value)
{
	if (seq == NULL)
	{
		return;
	}
	if (seq->count == MAXREPOSITORY)
	{
		// 队列满。
		return;
	}
	// 当循环顺序队循环完但队未满时，进行循环。
	if (seq->size > MAXREPOSITORY) 
	{
		seq->size = 0;
	}
	seq->data[seq->size] = value;
	++seq->size;
	++seq->count;
}

// 出队。
void PopQueue(SeqQueue *seq)
{
	if (seq == NULL)
	{
		return;
	}
	if (seq->count == 0)
	{
		// 空队列。
		return;
	}
	if (seq->tail > MAXREPOSITORY)
	{
		seq->tail = 0;	
	}
	++seq->tail;
	--seq->count;
}


// 取队首元素。
int FindHead(SeqQueue *seq, QueueType *value)
{
	if (seq == NULL)
	{
		return 0;
	}
	if (seq->count == 0)
	{
		return 0;
	}
	*value = seq->data[seq->tail];
	return 1;
}

// 销毁。
void DestoryQueue(SeqQueue *seq)
{
	if (seq == NULL)
	{
		return;
	}
	seq->size = 0;
	seq->count = 0;
	seq->tail = 0;
}

////////////////
//以下为测试代码
////////////////
#if 0

void PrintSeqQueue(SeqQueue *seq)
{
	if (seq == NULL)
	{
		return;
	}
	printf("[队尾]->");
	size_t count = 0;
	size_t size = seq->size;
	if (size != 0)
	{
		while (seq->count > count)
		{
			printf("[%c]->",seq->data[size-count-1]);
			count++;
		}
	}
	else
	{
		while (seq->count > count)
		{
			// 当循环到最大size但是队未满。
			if (size - count - 1 == 0)
			{
				printf("[%c]->",seq->data[size-count-1]);
				size = MAXREPOSITORY;
				count++;
			}
			else
			{
				printf("[%c]->",seq->data[size-count-1]);
				count++;
			}
		}
	}
	printf("[队头]\n");
}


// 顺序队的初始化。
void TestInitSeqQueue()
{
	TEAM_HEAD;
	SeqQueue seq;
	InitSeqQueue(&seq);
}

void TestPushQueue()
{
	TEAM_HEAD;
	SeqQueue seq;
	InitSeqQueue(&seq);
	PushQueue(&seq, 'a');
	PushQueue(&seq, 'b');
	PushQueue(&seq, 'c');
	PushQueue(&seq, 'd');
	PrintSeqQueue(&seq);
}

void TestPopQueue()
{
	TEAM_HEAD;
	SeqQueue seq;
	InitSeqQueue(&seq);
	PushQueue(&seq, 'a');
	PushQueue(&seq, 'b');
	PushQueue(&seq, 'c');
	PushQueue(&seq, 'd');
	PushQueue(&seq, 'e');
	PrintSeqQueue(&seq);
	PopQueue(&seq);
	PopQueue(&seq);
	PopQueue(&seq);
	PopQueue(&seq);
	PrintSeqQueue(&seq);
	PushQueue(&seq, 'f');
	PushQueue(&seq, 'g');
	PushQueue(&seq, 'h');
	PushQueue(&seq, 'i');
	PushQueue(&seq, 'j');
	PushQueue(&seq, 'k');
	PrintSeqQueue(&seq);
}

void TestFindHead()
{
	TEAM_HEAD;
	SeqQueue seq;
	InitSeqQueue(&seq);
	PushQueue(&seq, 'a');
	PushQueue(&seq, 'b');
	PushQueue(&seq, 'c');
	PushQueue(&seq, 'd');
	PushQueue(&seq, 'e');
	PrintSeqQueue(&seq);
	PopQueue(&seq);
	PopQueue(&seq);
	PopQueue(&seq);
	PopQueue(&seq);
	PrintSeqQueue(&seq);
	PushQueue(&seq, 'f');
	PushQueue(&seq, 'g');
	PushQueue(&seq, 'h');
	PushQueue(&seq, 'i');
	PushQueue(&seq, 'j');
	PushQueue(&seq, 'k');
	PrintSeqQueue(&seq);
	QueueType tmp;
	int ret = FindHead(&seq, &tmp);
	printf("except 1 actual %d\n",ret);
	printf("except e actual %c",tmp);
}

void TestDestoryQueue()
{
	TEAM_HEAD;
	SeqQueue seq;
	InitSeqQueue(&seq);
	PushQueue(&seq, 'a');
	PushQueue(&seq, 'b');
	PushQueue(&seq, 'c');
	PushQueue(&seq, 'd');
	PushQueue(&seq, 'e');
	PrintSeqQueue(&seq);
	DestoryQueue(&seq);
	PrintSeqQueue(&seq);
}

int main()
{
	TestInitSeqQueue();
	TestPushQueue();
	TestPopQueue();
	TestFindHead();
	TestDestoryQueue();
	return 0;
}
#endif
