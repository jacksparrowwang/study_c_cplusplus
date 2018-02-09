#include "DLinkNode.h"

void DLinkNodePrint(DLinkNode *head)
{
	if (head == NULL)
	{
		return;
	}
	DLinkNode *cur = head->next;
	printf("head->");
	for (;cur != head;cur = cur->next)
	{
		printf("[%c %p]->",cur->data,cur);
	}
	printf("head\n");
}

// 初始化链表。
void DLinkNodeInit(DLinkNode *head)
{
	if (head == NULL)
	{
		// 非法输入
		return;
	}
	head->next = head;
	head->prev = head;
}

// 创建节点
DLinkNode *CreatNode(LinkType value)
{
	DLinkNode *node = (DLinkNode*)malloc(sizeof(DLinkNode));
	if (node == NULL)
	{
		// 开辟空间失败。
		return;
	}
	node->data = value;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

// 尾插一个元素。
DLinkNode *DLinkNodePushBack(DLinkNode *head, LinkType value)
{
	if (head == NULL)
	{
		// 非法输入。
		return NULL;
	}
	DLinkNode *new_node = CreatNode(value);
	DLinkNode *pre = head->prev;
	pre->next = new_node;
	new_node->prev = pre;

	new_node->next = head;
	head->prev = new_node;
	return new_node;
}

// 尾删一个元素。
void DLinkNodePopBack(DLinkNode *head)
{
	if (head == NULL)
{
		// 非法输入。
		return;
	}
	if (head->next == head)
	{
		// 空链表。
		return;
	}
	DLinkNode *delete = head->prev;
	DLinkNode *pre = delete->prev;
	pre->next = head;
	head->prev = pre;
	free(delete);
}

// 头插入一个元素。
void DLinkNodePushFront(DLinkNode *head, LinkType value)
{
	if (head == NULL)
	{
		return;
	}
	DLinkNode *new_node = CreatNode(value);
	DLinkNode *next = head->next;
	head->next = new_node;
	new_node->prev = head;
	
	next->prev = new_node;
	new_node->next = next;
}

// 头删一个元素。
void DLinkNodePopFront(DLinkNode *head)
{
	if (head == NULL)
	{
		// 非法输入。
		return;
	}
	if (head->next == head)
	{
		// 链表为空。
		return;
	}
	DLinkNode *delete = head->next;
	DLinkNode *next = delete->next;
	head->next = next;
	next->prev = head;
	free(delete);
}

// 查找指定元素。
DLinkNode* DLinkNodeFind(DLinkNode *head, LinkType find)
{
	if (head == NULL || head->next == head)
	{
		// 链表为空或者非法输入。
		return NULL;
	}
	DLinkNode *cur = head->next;
	while (cur != head)
	{
		if (cur->data == find)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

// 在指定位置之前插入一个元素。
void DLinkNodeInsertFront(DLinkNode *pos, LinkType value)
{
	if (pos == NULL)
	{
		// 非法输入。
		return;
	}
	DLinkNode *new_node = CreatNode(value);
	DLinkNode *prev = pos->prev;
	prev->next = new_node;
	new_node->prev = prev;

	new_node->next = pos;
	pos->prev = new_node;
}


// 在指定元素之后插入一个元素。
void DLinkNodeInsertBack(DLinkNode *pos, LinkType value)
{
	if (pos == NULL)
	{
		// 非法输入。
		return;
	}
	DLinkNode *new_node = CreatNode(value);
	DLinkNode *next = pos->next;
	pos->next = new_node;
	new_node->prev = pos;

	new_node->next = next;
	next->prev = new_node;
}

// 删除指定位置的节点。
void DLinkNodeErase(DLinkNode *head,DLinkNode *pos)
{
	if (pos == NULL)
	{
		// 非法输入。
		return;
	}
	DLinkNode *cur = head->next;
	while (cur != head)
	{
		if (cur == pos)
		{
			DLinkNode *prev = pos->prev;
			DLinkNode *next = pos->next;
			prev->next = next;
			next->prev = prev;
			free(pos);
			return;
		}
		cur = cur->next;
	}
	printf("pos位置有误\n");
	return;
}


// 删除指定元素的第一个节点。
void DLinkNodeRemove(DLinkNode *head, LinkType value)
{
	if (head  == NULL)
	{
		// 非法输入。
		return;
	}
	DLinkNode *cur = head->next;
	while (cur != head)
	{
		if (cur->data == value)
		{
			DLinkNode *prev = cur->prev;
			DLinkNode *next = cur->next;
			prev->next = next;
			next->prev = prev;
		}
		cur = cur->next;
	}
}

// 删除指定元素的所有节点。
void DLinkNodeRemoveAll(DLinkNode *head, LinkType value)
{
	if (head == NULL)
	{
		return;
	}
	DLinkNode *pos;// = DLinkNodeFind(head,value);
	while (pos != NULL)
	{
		pos = DLinkNodeFind(head,value);
		DLinkNodeErase(head,pos);
	}
	return;
}


// 求链表的长度
size_t DLinkNodeSize(DLinkNode *head)
{
	if (head == NULL)
	{
		return (size_t)-1;
	}
	DLinkNode *cur = head->next;
	size_t count = 0;
	while (cur != head)
	{
		++count;
		cur = cur->next;
	}
	return count;
}

// 判读链表是否为空。
int DLinkNodeEmpty(DLinkNode *head)
{
	if (head == NULL)
	{
		return (size_t)-1;
	}
	if (head->next = head)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

///////////////////
//以下是测试代码
///////////////////

// 初始化。
void TestDLinkNodeInit()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
}

// 尾插。
void TestDLinkNodePushBack()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
	DLinkNodePushBack(&head,'a');
	DLinkNodePushBack(&head,'b');
	DLinkNodePushBack(&head,'c');
	DLinkNodePushBack(&head,'d');
	DLinkNodePrint(&head);
}

// 尾删。
void TestDLinkNodePopBack()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
	DLinkNodePushBack(&head,'a');
	DLinkNodePushBack(&head,'b');
	DLinkNodePushBack(&head,'c');
	DLinkNodePushBack(&head,'d');
	DLinkNodePrint(&head);
	DLinkNodePopBack(&head);
	DLinkNodePopBack(&head);
	DLinkNodePopBack(&head);
	DLinkNodePrint(&head);
	DLinkNodePopBack(&head);
	DLinkNodePopBack(&head);
	DLinkNodePrint(&head);
}

// 头插。
void TestDLinknodePushFront()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
	DLinkNodePushFront(&head,'a');
	DLinkNodePushFront(&head,'b');
	DLinkNodePrint(&head);
	DLinkNodePushFront(&head,'d');
	DLinkNodePrint(&head);
}

// 头删。
void TestDLinkNodePopFront()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
	DLinkNodePushFront(&head,'a');
	DLinkNodePushFront(&head,'b');
	DLinkNodePushFront(&head,'d');
	DLinkNodePrint(&head);
	DLinkNodePopFront(&head);
	DLinkNodePrint(&head);
	DLinkNodePopFront(&head);
	DLinkNodePopFront(&head);
	DLinkNodePrint(&head);
	DLinkNodePopFront(&head);
	DLinkNodePrint(&head);
}

// 按元素查找的位置。
void TestDLinkNodeFind()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
	DLinkNodePushFront(&head,'a');
	DLinkNode *pos = DLinkNodePushBack(&head,'b');
	DLinkNodePushFront(&head,'c');
	DLinkNodePushFront(&head,'d');
	DLinkNodePushFront(&head,'e');
	DLinkNodePrint(&head);
	DLinkNode *ret = DLinkNodeFind(&head, 'b');
	printf("except %p actual %p \n",pos, ret);
}

// 指定位置之前插入一个元素。
void TestDLinkNodeInsertFront()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
	DLinkNode *pos1 = DLinkNodePushBack(&head,'a');
	DLinkNode *pos = DLinkNodePushBack(&head,'b');
	DLinkNodePushBack(&head,'c');
	DLinkNodePushBack(&head,'d');
	DLinkNodePushBack(&head,'e');
	DLinkNodePrint(&head);
	DLinkNodeInsertFront(pos,'f');
	DLinkNodePrint(&head);
	DLinkNodeInsertFront(pos1,'g');
	DLinkNodePrint(&head);
}

// 指定位置之后插入一个元素。
void TestDLinkNodeInsertBack()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
	DLinkNode *pos1 = DLinkNodePushBack(&head,'a');
	DLinkNodePushBack(&head,'b');
	DLinkNodePushBack(&head,'c');
	DLinkNodePushBack(&head,'d');
	DLinkNode *pos = DLinkNodePushBack(&head,'e');
	DLinkNodePrint(&head);
	DLinkNodeInsertBack(pos1,'f');
	DLinkNodeInsertBack(pos,'g');
	DLinkNodePrint(&head);
}

// 删除指定位置节点。
void TestDLinkNodeErase()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
	DLinkNode *pos1 = DLinkNodePushBack(&head,'a');
	DLinkNodePushBack(&head,'b');
	DLinkNodePushBack(&head,'c');
	DLinkNodePushBack(&head,'d');
	DLinkNode *pos = DLinkNodePushBack(&head,'e');
	DLinkNodePrint(&head);
	DLinkNodeErase(&head,pos1);
	DLinkNodePrint(&head);
	DLinkNodeErase(&head,pos);
	DLinkNodePrint(&head);
}

// 删除指定元素的第一个节点。
void TestDLinkNodeRemove()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
	DLinkNode *pos1 = DLinkNodePushBack(&head,'a');
	DLinkNodePushBack(&head,'b');
	DLinkNodePushBack(&head,'c');
	DLinkNodePushBack(&head,'d');
	DLinkNode *pos = DLinkNodePushBack(&head,'e');
	DLinkNodePrint(&head);
	DLinkNodeRemove(&head,'b');
	DLinkNodePrint(&head);
	DLinkNodeRemove(&head,'a');
	DLinkNodePrint(&head);
}

// 删除指定元素的所有节点。
void TestDLinkNodeRemoveAll()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
	DLinkNode *pos1 = DLinkNodePushBack(&head,'a');
	DLinkNodePushBack(&head,'b');
	DLinkNodePushBack(&head,'c');
	DLinkNodePushBack(&head,'d');
	DLinkNode *pos = DLinkNodePushBack(&head,'c');
	DLinkNodePrint(&head);
	DLinkNodeRemoveAll(&head,'a');
	DLinkNodePrint(&head);
	DLinkNodeRemoveAll(&head,'c');
	DLinkNodePrint(&head);
}

// 判断链表是否为空，不为空求出链表的长度。
void TestDLinkNodeSize()
{
	FUNCTIONNAME;
	DLinkNode head;
	DLinkNodeInit(&head);
	int ret = DLinkNodeEmpty(&head);
	DLinkNode *pos1 = DLinkNodePushBack(&head,'a');
	DLinkNodePushBack(&head,'b');
	DLinkNodePushBack(&head,'c');
	DLinkNodePushBack(&head,'d');
	DLinkNode *pos = DLinkNodePushBack(&head,'c');
	DLinkNodePrint(&head);
	size_t size = DLinkNodeSize(&head);
	printf("except 1 actual %d\n",ret);
	printf("except 5 actual %d\n",size);
}

int main()
{
	TestDLinkNodeInit();
	TestDLinkNodePushBack();
	TestDLinkNodePopBack();
	TestDLinknodePushFront();
	TestDLinkNodePopFront();
	TestDLinkNodeFind();
	TestDLinkNodeInsertFront();
	TestDLinkNodeInsertBack();
	TestDLinkNodeErase();
	TestDLinkNodeRemove();
	TestDLinkNodeRemoveAll();
	TestDLinkNodeSize();
	return 0;
}
