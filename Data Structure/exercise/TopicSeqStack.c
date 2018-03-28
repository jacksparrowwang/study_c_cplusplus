#include "TopicSeqStack.h"


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
		printf("seq非法输入。");
		return 0;
	}
	if (seq->size == 0)
	{
		// 空栈。
		return 0;
	}
	*value = seq->data[seq->size-1];
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

// 栈面试题。
// 实现一个栈，要求实现Push（出栈），Pop(入栈)，Min（返回最小值）的时间复杂度为O(1).
void PushStackMin(SeqStack *seq,SeqType value)
{
	if (seq == NULL)
	{
		return;
	}
	if (seq->size == 0)
	{
		// 第一次入栈把相同的元素压入两次
		seq->data[seq->size] = value;
		++seq->size;
		seq->data[seq->size] = value;
		++seq->size;
	}
	else
	{
		// 再次入栈，先入正常值
		seq->data[seq->size] = value;
		++seq->size;
		// 再比较新入的值与上一次栈中栈顶的值比较。
		// 如果小就把这个值再入一次，如果大就把上次栈顶入栈
		if (seq->data[seq->size-1] > seq->data[seq->size-2])
		{
			seq->data[seq->size] = seq->data[seq->size-2];
			++seq->size;
		}
		else
		{
			seq->data[seq->size] = seq->data[seq->size-1];
			++seq->size;
		}
	}
}

void PopStackMin(SeqStack *seq)
{
	if (seq == NULL)
	{
		return;
	}
	if (seq->size == 0)
	{
		return;
	}
	seq->size = seq->size-2;
}

int TopStackMin(SeqStack *seq, SeqType *value)
{
	if (seq == NULL)
	{
		return 0;
	}
	if (seq->size == 0)
	{
		// 空栈
		return 0;
	}
	*value = seq->data[seq->size-1];
	return 1;
}

///////////////////////////////////////////////////
// 两个栈实现一个队
void InitQueue(Queue *q)
{
	if (q == NULL)
	{
		return;
	}
	// 初始化两个栈
	SeqStackInit(&q->stack1);
	SeqStackInit(&q->stack2);
}

// 入队
void UseTwoStackImitationQueuePush(Queue *q, SeqType value)
{
	if (q == NULL)
	{
		return;
	}
	// 先要让2里面的元素全转移到1里面
	// 前提是要有一个栈为空才可以
	SeqType cur;
	while (SeqStackFindTop(&q->stack2, &cur))
	{
		SeqStackPopStack(&q->stack2);
		SeqStackPushStack(&q->stack1, cur);
	}
	if (q->size == MAXREPOSITORY)
	{
		// 队已经满
		return;
	}
	SeqStackPushStack(&q->stack1, value);
	++q->size;
}

// 出队
void UseTwoStackIQueuePop(Queue *q)
{
	if (q == NULL)
	{
		return;
	}
	// 先要将1里面的元素转移到2里面
	SeqType cur;
	while (SeqStackFindTop(&q->stack1, &cur))
	{
		SeqStackPopStack(&q->stack1);
		SeqStackPushStack(&q->stack2, cur);
	}
	if (q->size == 0)
	{
		// 为空队
		return;
	}
	SeqStackPopStack(&q->stack2);
	--q->size;
	return;
}

// 取队首元素
int UseTwoStackIQueueTop(Queue *q, SeqType *value)
{
	if (q == NULL)
	{
		return -1;
	}
	SeqType cur;
	while (SeqStackFindTop(&q->stack1, &cur))
	{
		SeqStackPopStack(&q->stack1);
		SeqStackPushStack(&q->stack2, cur);
	}
	if (q->size == 0)
	{
		return 0;
	}
	*value = q->stack2.data[q->stack2.size-1];
	return 1;
}

void InitStackArray(Stack *stack)
{
    if (stack == NULL)
    {
        return;
    }
    stack->s1 = 0;
    stack->s2 = MAXREPOSITORY - 1;
    return;
}

void PushStackArray1(Stack *stack, SeqType value)
{
    if (stack == NULL)
    {
        return;
    }
    if (stack->s1 > stack->s2)
    {
        return;
    }
    stack->data[stack->s1] = value;
    ++stack->s1;
    return;
}

void PopStackArray1(Stack *stack)
{
    if (stack == NULL)
    {
        return;
    }
    if (stack->s1 == 0)
    {
        return;
    }
    --stack->s1;
    return;
}

int FindTopStackArray1(Stack *stack, SeqType *elem)
{
    if (stack == NULL)
    {
        return -1;
    }
    if (stack->s1 == 0)
    {
        return 0;
    }
    *elem = stack->data[stack->s1 - 1];
    return 1;
}

void PushStackArray2(Stack *stack, SeqType value)
{
    if (stack == NULL)
    {
        return;
    }
    if (stack->s1 > stack->s2)
    {
        return;
    }
    stack->data[stack->s2] = value;
    --stack->s2;
    return;
}

void PopStackArray2(Stack *stack)
{
    if (stack == NULL)
    {
        return;
    }
    if (stack->s2 == MAXREPOSITORY-1)
    {
        return;
    }
    ++stack->s2;
    return;
}

int FindTopStackArray2(Stack *stack, SeqType *elem)
{
    if  (stack == NULL)
    {
        return -1;
    }
    if (stack->s2 == MAXREPOSITORY-1)
    {
        return 0;
    }
    *elem = stack->data[stack->s2 + 1];
    return 1;
}

///////////////////////////////////////
//判断字符串是是否按照出栈顺序
///////////////////////////////////////
int Stack_Order(char input[], size_t input_size, char output[], size_t output_size)
{
    SeqStack stack;
    SeqStackInit(&stack);
    char value;
    size_t index = 0;
    size_t i = 0;
    for (; i < input_size; ++i)
    {
        SeqStackPushStack(&stack, input[i]);
        while (SeqStackFindTop(&stack, &value))
        {
            if (output[index] == value)
            {
                ++index;
                SeqStackPopStack(&stack);
            }
            else
            {
                break;
            }
        }
    }
    if (index >= output_size && stack.size == 0)
    {
        return 1;
    }
    return 0;
}


/////////////////////
//测试代码
/////////////////////

void TestStack_Order()
{
	PRINTSEQSTACKNAME;
    char input[] = "abcd";
    char output[] = "bacd";
    int ret = Stack_Order(input, strlen(input), output, strlen(output));
    printf("except 1 actual %d\n", ret);
}

void PrintSeqStackArray2(Stack *seq)
{
	if (seq == NULL)
	{
		return;
	}
	printf("栈底->");
	size_t i = MAXREPOSITORY - 1;
	for (; i>seq->s2; --i)
	{
		printf("[%c]->",seq->data[i]);
	}
	printf("栈顶\n");
}
void PrintSeqStackArray1(Stack *seq)
{
	if (seq == NULL)
	{
		return;
	}
	printf("栈底->");
	size_t i = 0;
	for (; i<seq->s1; ++i)
	{
		printf("[%c]->",seq->data[i]);
	}
	printf("栈顶\n");
}

void TestArrayStack()
{
	PRINTSEQSTACKNAME;
    Stack s;
    InitStackArray(&s);
    PushStackArray1(&s, 'a');
    PushStackArray1(&s, 'b');
    PushStackArray1(&s, 'c');
	PrintSeqStackArray1(&s);
    PopStackArray1(&s);
	PrintSeqStackArray1(&s);
    SeqType elem;
    int ret = FindTopStackArray1(&s, &elem);
    printf("except b actual %c\n", elem);
    printf("except 1 actual %d\n", ret);
    
    PushStackArray2(&s, 'd');
    PushStackArray2(&s, 'e');
    PushStackArray2(&s, 'f');
	PrintSeqStackArray2(&s);
    PopStackArray2(&s);
	PrintSeqStackArray2(&s);
    ret = FindTopStackArray2(&s, &elem);
    printf("except e actual %c\n", elem);
    printf("except 1 actual %d\n", ret);
}

void TestTwoStackIQueueTop()
{
	PRINTSEQSTACKNAME;
	Queue q;
	InitQueue(&q);
	UseTwoStackImitationQueuePush(&q, 'a');
	UseTwoStackImitationQueuePush(&q, 'b');
	UseTwoStackImitationQueuePush(&q, 'c');
	UseTwoStackImitationQueuePush(&q, 'd');
	PrintSeqStack(&q.stack1);
	UseTwoStackIQueuePop(&q);
	UseTwoStackIQueuePop(&q);
	PrintSeqStack(&q.stack2);
	SeqType value;
	int ret = UseTwoStackIQueueTop(&q, &value);
	printf("except c actual %c\n", value);
	printf("except 1 actual %d\n", ret);
}

void TestTwoStackIQueuePop()
{
	PRINTSEQSTACKNAME;
	Queue q;
	InitQueue(&q);
	UseTwoStackImitationQueuePush(&q, 'a');
	UseTwoStackImitationQueuePush(&q, 'b');
	UseTwoStackImitationQueuePush(&q, 'c');
	UseTwoStackImitationQueuePush(&q, 'd');
	PrintSeqStack(&q.stack1);
	UseTwoStackIQueuePop(&q);
	UseTwoStackIQueuePop(&q);
	PrintSeqStack(&q.stack2);
}

void TestTwoStackIQueuePush()
{
	PRINTSEQSTACKNAME;
	Queue q;
	InitQueue(&q);
	UseTwoStackImitationQueuePush(&q, 'a');
	UseTwoStackImitationQueuePush(&q, 'b');
	UseTwoStackImitationQueuePush(&q, 'c');
	UseTwoStackImitationQueuePush(&q, 'd');
	PrintSeqStack(&q.stack1);
}

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

// 最小入栈。
void TestPushStackMin()
{
	PRINTSEQSTACKNAME;
	SeqStack seq;
	SeqStackInit(&seq);
	PushStackMin(&seq,'b');
	PrintSeqStack(&seq);
	PushStackMin(&seq,'g');
	PushStackMin(&seq,'d');
	PrintSeqStack(&seq);
	SeqType value;
	int ret = SeqStackFindTop(&seq, &value);
	printf("except d actual %d\n",ret);
}

// 最小出栈。
void TestPopStackMin()
{
	PRINTSEQSTACKNAME;
	SeqStack seq;
	SeqStackInit(&seq);
	PushStackMin(&seq,'b');
	PushStackMin(&seq,'g');
	PushStackMin(&seq,'d');
	PrintSeqStack(&seq);
	PopStackMin(&seq);
	PrintSeqStack(&seq);
	PopStackMin(&seq);
	PopStackMin(&seq);
	PrintSeqStack(&seq);
	PopStackMin(&seq);
	PrintSeqStack(&seq);
}

int main()
{
	TestSeqStackInit();
	TestSeqStackPushStack();
	TestSeqStackPopStack();
	TestSeqStackFindTop();
	TestPushStackMin();
	TestPopStackMin();
	TestTwoStackIQueuePush();
	TestTwoStackIQueuePop();
	TestTwoStackIQueueTop();
    TestArrayStack();
    TestStack_Order();
	return 0;
}
