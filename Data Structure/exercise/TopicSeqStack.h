#pragma once

#include<stdio.h>
#include<string.h>

#define MAXREPOSITORY 1000
#define PRINTSEQSTACKNAME printf("\n=============%s==========\n",__FUNCTION__)

typedef char SeqType;

// 栈的实现
typedef struct SeqStack{
	size_t size;
	SeqType data[MAXREPOSITORY];
}SeqStack;

// 实现共享栈
typedef struct Stack{
    size_t s1;
    size_t s2;
    SeqType data[MAXREPOSITORY];
}Stack;


// 两个栈实现一个队
typedef struct Queue{
	SeqStack stack1;
	SeqStack stack2;
	size_t size;
}Queue;

// 初始化。
void SeqStackInit(SeqStack *seq);

// 入栈。
void SeqStackPushStack(SeqStack *seq, SeqType value);

// 出栈。
void SeqStackPopStack(SeqStack *seq);

// 取栈顶元素。
int SeqStackFindTop(SeqStack *seq, SeqType *value);

// 销毁。
void SeqStackDestory(SeqStack *seq);

// 栈面试题。
// 实现一个栈，要求实现Push（出栈），Pop(入栈)，Min（返回最小值）的时间复杂度为O(1).
void PushStackMin(SeqStack *seq,SeqType value);

void PopStackMin(SeqStack *seq);

int TopStackMin(SeqStack *seq, SeqType *value);

// 两个栈实现一个队列

void InitQueue(Queue *q);

void UseTwoStackImitationQueuePush(Queue *q, SeqType value);

void UseTwoStackIQueuePop(Queue *q);

int UseTwoStackIQueueTop(Queue *q, SeqType *value);

////////////////////////////////
// 实现一个共享栈（一个数组两个栈）
void InitStackArray(Stack *stack);

// 前半部分
void PushStackArray1(Stack *stack, SeqType value);

void PopStackArray1(Stack *stack);

int FindTopStackArray1(Stack *stack, SeqType *elem);

void PushStackArray2(Stack *stack, SeqType value);

void PopStackArray2(Stack *stack);

int FindTopStackArray2(Stack *stack, SeqType *elem);

/////////////////////////
//判断字符串是否按照出栈顺序
/////////////////////////

int Stack_Order(char input[], size_t input_size, char output[], size_t output_size);

