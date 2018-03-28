#include"TopicSeqQueue.h"


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
int FindHeadQueue(SeqQueue *seq, QueueType *value)
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

////////////////////////
//两个队实现一个栈
////////////////////////

void InitSeqQueueUseStack(StackUseQueue *queue)
{
    if (queue == NULL)
    {
        return;
    }
    InitSeqQueue(&queue->q1);
    InitSeqQueue(&queue->q2);
    return;
}

void PushQueueUseStack(StackUseQueue *queue, QueueType value)
{
    if (queue == NULL)
    {
        return;
    }
    QueueType elem;
    while (FindHeadQueue(&queue->q2, &elem))
    {
        PopQueue(&queue->q2);
        PushQueue(&queue->q1, elem);
    }
    if (queue->q1.size == MAXREPOSITORY)
    {
        // 队列已经满了。
        return;
    }
    PushQueue(&queue->q1, value);
    return;
}

void PopQueueUseStack(StackUseQueue *queue)
{
    if (queue == NULL)
    {
        return;
    }
    QueueType elem;
    QueueType final_elem;
    while (FindHeadQueue(&queue->q1, &elem))
    {
        PopQueue(&queue->q1);
        if (!FindHeadQueue(&queue->q1, &final_elem))
        {
            break;
        }
        PushQueue(&queue->q2, elem);
    }
    return;
}

int FindHeadQueueUseStack(StackUseQueue *queue, QueueType *value)
{
    if (queue == NULL)
    {
        return 0;
    }
    QueueType elem;
    QueueType final_elem;
    while (FindHeadQueue(&queue->q1, &elem))
    {
        PopQueue(&queue->q1);
        if (!FindHeadQueue(&queue->q1, &final_elem))
        {
            break;
        }
        PushQueue(&queue->q2, elem);
    }
    *value = elem;
    return 1;
}
////////////////
//以下为测试代码
////////////////

void PrintSeqQueue(SeqQueue *seq);

void TestFindHead()
{
	TEAM_HEAD;
    StackUseQueue queue;
    InitSeqQueueUseStack(&queue);
    PushQueueUseStack(&queue, 'a');
    PushQueueUseStack(&queue, 'b');
    PrintSeqQueue(&queue.q1);
    QueueType value;
    int ret = FindHeadQueueUseStack(&queue, &value);
    printf("except b actual %c \n", value);
    printf("except 1 actual %d \n", ret);
}

void TestPopQueue()
{
	TEAM_HEAD;
    StackUseQueue queue;
    InitSeqQueueUseStack(&queue);
    PushQueueUseStack(&queue, 'a');
    PushQueueUseStack(&queue, 'b');
    PushQueueUseStack(&queue, 'c');
    PushQueueUseStack(&queue, 'd');
    PrintSeqQueue(&queue.q1);
    PopQueueUseStack(&queue);
    PrintSeqQueue(&queue.q2);
}

void TestPushQueue()
{
	TEAM_HEAD;
    StackUseQueue queue;
    InitSeqQueueUseStack(&queue);
    PushQueueUseStack(&queue, 'a');
    PushQueueUseStack(&queue, 'b');
    PushQueueUseStack(&queue, 'c');
    PushQueueUseStack(&queue, 'd');
    PrintSeqQueue(&queue.q1);
}

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

int main()
{
    TestPushQueue();
    TestPopQueue();
    TestFindHead();
    return 0;
}


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
	int ret = FindHeadQueue(&seq, &tmp);
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
