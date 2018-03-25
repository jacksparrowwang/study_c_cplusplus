#include "SeqStack.h"


// 初始化。
void SeqStackInit(SeqStack *seq)
{
	if (seq == NULL)
	{
		// 非法输入。
		return;
	}
	seq->size = 0;
}

// 入栈。
void SeqStackPushStack(SeqStack *seq, SeqType value)
{
	if (seq == NULL)
	{
		return;
	}
	if (seq->size > MAXREPOSITORY)
	{
		return;
	}
	seq->data[seq->size] = value;
	++seq->size;
}

// 打印栈。
void PrintSeqStack(SeqStack *seq)
{
	if (seq == NULL)
	{
		return;
	}
	printf("栈底->");
	size_t i = 0;
	for (; i<seq->size; ++i)
	{
		printf("[%c]->",seq->data[i]);
	}
	printf("栈顶\n");
}

// 出栈。
void SeqStackPopStack(SeqStack *seq)
{
	if (seq == NULL)
	{
		// 非法输入。
		return;
	}
	if (seq->size == 0)
	{
		// 空顺序表。
		return;
	}
	--seq->size;
}

// 取栈顶元素。
int SeqStackFindTop(SeqStack *seq, SeqType *value)
{
	if (seq == NULL)
	{
		return 0;
	}
	if (seq->size == 0)
	{
		printf("栈为空栈。");
		// 空栈。
		return 0;
	}
	*value =  seq->data[seq->size-1];
	return 1;
}


// 销毁。
void SeqStackDestory(SeqStack *seq)
{
	if (seq == NULL)
	{
		return;
	}
	seq->size = 0;
}

/////////////////////
//测试代码
/////////////////////

#if 0
// 初始化
void TestSeqStackInit()
{
	PRINTSEQSTACKNAME;
	SeqStack seq;
	SeqStackInit(&seq);
}

// 入栈。
void TestSeqStackPushStack()
{
	PRINTSEQSTACKNAME;
	SeqStack seq;
	SeqStackInit(&seq);
	SeqStackPushStack(&seq, 'a');
	SeqStackPushStack(&seq, 'b');
	SeqStackPushStack(&seq, 'c');
	SeqStackPushStack(&seq, 'd');
	PrintSeqStack(&seq);
}

// 出栈。
void TestSeqStackPopStack()
{
	PRINTSEQSTACKNAME;
	SeqStack seq;
	SeqStackInit(&seq);
	SeqStackPushStack(&seq, 'a');
	SeqStackPushStack(&seq, 'b');
	SeqStackPushStack(&seq, 'c');
	SeqStackPushStack(&seq, 'd');
	PrintSeqStack(&seq);
	SeqStackPopStack(&seq);
	PrintSeqStack(&seq);
	SeqStackPopStack(&seq);
	SeqStackPopStack(&seq);
	SeqStackPopStack(&seq);
	PrintSeqStack(&seq);
	SeqStackPopStack(&seq);
	PrintSeqStack(&seq);
}

// 取栈顶元素。
void TestSeqStackFindTop()
{
	PRINTSEQSTACKNAME;
	SeqStack seq;
	SeqStackInit(&seq);
	SeqStackPushStack(&seq, 'a');
	SeqStackPushStack(&seq, 'b');
	SeqStackPushStack(&seq, 'c');
	SeqStackPushStack(&seq, 'd');
	PrintSeqStack(&seq);
	SeqType value;
	int ret = SeqStackFindTop(&seq, &value);
	printf("except d actual %d\n",ret);
}

int main()
{
	TestSeqStackInit();
	TestSeqStackPushStack();
	TestSeqStackPopStack();
	TestSeqStackFindTop();
	return 0;
}
#endif
