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
	--seq->count;
}


// 取队尾元素。
QueueType FindButtom(SeqQueue *seq)
{
	if (seq == NULL)
	{
		printf("输入错误\n");
		return 0;
	}
	if (seq->count == 0)
	{
		printf("队为空\n");
		return 0;
	}
	return seq->data[seq->size-1];
}


// 取队首元素。
QueueType FindHead(SeqQueue *seq)
{
	if (seq == NULL)
	{
		printf("输入错误\n");
		return 0;
	}
	if (seq->count == 0)
	{
		printf("队为空\n");
		return 0;
	}
	if (seq->size >= seq->count)
	{
		return seq->data[seq->size - seq->count];
	}
	else 
	{
		size_t tmp = seq->count-seq->size;
		size_t size = MAXREPOSITORY;
		return seq->data[size-tmp];
	}
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
}

////////////////
//以下为测试代码
////////////////

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
//		for (; count < seq->count; ++count)
//		{
//			printf("[%c]<-",seq->data[count]);
//		}
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
//		for(; count < seq->count; ++count)
//		{
//			if (size-count == 0)
//			{
//				size = MAXREPOSITORY;
//			}
//			printf("[%c]<-",seq->data[size-count]);
//		}
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

void TestFindButtom()
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
	QueueType ret = FindButtom(&seq);
	printf("except e actual %c",ret);
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
	QueueType ret = FindHead(&seq);
	printf("except e actual %c",ret);
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
	TestFindButtom();
	TestFindHead();
	TestDestoryQueue();
	return 0;
}
