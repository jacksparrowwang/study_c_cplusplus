#include"LinkStack.h"


// 初始化。带头不带环单链表。
void LinkStackInit(LinkNode *head)
{
	if (head == NULL)
	{
		return;
	}
	head->next = NULL;
}

// 创建节点。
LinkNode *CreatNode(LinkType value)
{
	LinkNode *new_node = (LinkNode*)malloc(sizeof(LinkNode));
	if (new_node == NULL)
	{
		// 申请内存失败。
		return NULL;
	}
	new_node->data = value;
	new_node->next = NULL;
	return new_node;
}

// 入栈。
void LinkStackPushStack(LinkNode *head, LinkType value)
{
	if (head == NULL)
	{
		return;
	}
	LinkNode *new_node = CreatNode(value);
	if (new_node == NULL)
	{
		printf("内存申请失败。");
		// 返回值为NULL。
		return;
	}
	LinkNode *next = head->next;
	head->next = new_node;
	new_node->next = next;
}

// 出栈。
void LinkStackPopStack(LinkNode *head)
{
	if (head == NULL)
	{
		return;
	}
	if (head->next == NULL)
	{
		// 空栈。
		return;
	}
	LinkNode *delete = head->next;
	head->next = delete->next;
	free(delete);
}


// 取栈顶元素。
LinkType LinkStackFindTop(LinkNode *head)
{
	if (head == NULL)
	{
		printf("输入非法。");
		return 0;
	}
	if (head->next == NULL)
	{
		printf("栈为空。");
		return 0;
	}
	return head->next->data;
}

// 销毁。
void LinkStackDestory(LinkNode *head)
{
	if (head == NULL)
	{
		return;
	}
	LinkNode *cur = head->next;
	while (cur != NULL)
	{
		LinkNode *next = cur->next;
		head->next = next;
		free(cur);
		cur = next;
	}
}


/////////////
//测试代码 
/////////////

// 打印。
void PrintLinkStack(LinkNode *head)
{
	if (head == NULL)
	{
		return;
	}
	printf("(TOP)head->");
	LinkNode *cur = head->next;
	while (cur != NULL)
	{
		printf("[%c]->",cur->data);
		cur = cur->next;
	}
	printf("BOTTOM\n");
}

// 初始化。
void TestLinkStackInit()
{
	LINKSTACKNAME;
	LinkNode head;
	LinkStackInit(&head);
}

// 入栈。
void TestLinkStackPushStack()
{
	LINKSTACKNAME;
	LinkNode head;
	LinkStackInit(&head);
	LinkStackPushStack(&head,'a');
	LinkStackPushStack(&head,'b');
	LinkStackPushStack(&head,'c');
	LinkStackPushStack(&head,'d');
	PrintLinkStack(&head);
}

// 出栈。
void TestLinkStackPopStack()
{
	LINKSTACKNAME;
	LinkNode head;
	LinkStackInit(&head);
	LinkStackPushStack(&head,'a');
	LinkStackPushStack(&head,'b');
	LinkStackPushStack(&head,'c');
	LinkStackPushStack(&head,'d');
	PrintLinkStack(&head);
	LinkStackPopStack(&head);
	PrintLinkStack(&head);
	LinkStackPopStack(&head);
	LinkStackPopStack(&head);
	PrintLinkStack(&head);
	LinkStackPopStack(&head);
	PrintLinkStack(&head);
	LinkStackPopStack(&head);
	PrintLinkStack(&head);
}

// 销毁。
void TestLinkStackDestory()
{
	LINKSTACKNAME;
	LinkNode head;
	LinkStackInit(&head);
	LinkStackPushStack(&head,'a');
	LinkStackPushStack(&head,'b');
	LinkStackPushStack(&head,'c');
	LinkStackPushStack(&head,'d');
	PrintLinkStack(&head);
	LinkStackDestory(&head);
	PrintLinkStack(&head);
}

int main()
{
	TestLinkStackInit();
	TestLinkStackPushStack();
	TestLinkStackPopStack();
	TestLinkStackDestory();
	return 0;
}
