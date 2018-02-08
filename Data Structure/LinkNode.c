#include"LinkNode.h"

//打印
void LinkNodePrint(LinkNode *head)
{
	LinkNode* cur = NULL;
	printf("head:");
	if(head == NULL)
	{
		//空链表。
		return;
	}
	cur = head;
	
	while(cur != NULL)
	{
		printf("[%c:%p]-> ",cur->data,&cur->data);
		cur = cur->next;
	}
	printf("NULL\n\n");
}

//对单链表进行初始化
void InitLinkNode(LinkNode **head)
{
	if (head == NULL)
	{
		// 非法输入。
		return;
	}
	*head = NULL;
}

//创建节点
LinkNode *CreatNode(TypeChar value)
{
	LinkNode* new_node = (LinkNode *)malloc(sizeof(LinkNode));
	if(new_node == NULL)
	{
		//申请内存失败。
		return NULL;
	}
	new_node->next = NULL;
	new_node->data = value;
	return new_node;
}

//对单链表进行尾插;
LinkNode* PushBackLinkNode(LinkNode **head, TypeChar value)
{
	LinkNode *new_node = NULL;
	LinkNode *cur = NULL; 
	if(head == NULL)
	{
		//非法输入
		return NULL;
	}
	new_node = CreatNode(value);
	if(*head == NULL)
	{
		*head = new_node;
		return *head;
	}
	cur = *head;
	while(cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = new_node;
	return new_node;
}

//对单链表进行尾删
void PopBackLinkNode(LinkNode **head)
{
	LinkNode* to_delete = NULL;
	LinkNode* cur = *head;
	if (head == NULL)
	{
		//非法输入。
		return ;
	}
	if (*head == NULL)
	{
		//为空链表。
		return;
	}
	if ((*head)->next == NULL)
	{
		free(*head);
		*head = NULL;
		return;
	}
	while (cur->next->next != NULL)
	{
		cur = cur->next;
	}
	to_delete = cur->next;
	free(to_delete);
	cur->next = NULL;
	return;
}

//对单链表进行头插
void PushFrontLinkNode(LinkNode** head, TypeChar value)
{
	LinkNode* cur = NULL;
	if (head == NULL)
	{
		//非法输入。
		return;
	}
	cur = CreatNode(value);
	cur->next = *head;
	*head = cur;
}

//对单链表进行头删
void PopFrontLinkNode(LinkNode** head)
{
	LinkNode* cur = NULL;
	if (head ==NULL)
	{
		//非法输入。
		return;
	}
	if (*head == NULL)
	{
		//为空列表。
		return;
	}
	cur = (*head)->next;
	free(*head);
	*head = cur;
}

//对单链表进行值位置的查找，返回对应值的地址
LinkNode* FindLinkNode(LinkNode* head, TypeChar value)
{
	LinkNode* cur = NULL;
	if (head == NULL)
	{
		//空链表。
		return NULL;
	}
	cur = head;
	while (cur != NULL)
	{
		if (cur->data == value)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

//在链表的指定位置之前插入元素，普通放方法,时间复杂度O(n)
void InsertFrontLinkNode(LinkNode** head, LinkNode* pos, TypeChar value)
{
	LinkNode* new_node = NULL;
	LinkNode* cur = NULL;
	if (head == NULL || pos == NULL)
	{
		//非法输入。
		return;
	}
	if (*head == NULL)
	{
		//单链表为空。
		return;
	}
	cur = *head;
	if (cur == pos)   //对头节点进行判断，是否是pos.
	{
		PushFrontLinkNode(head, value);
		return;
	}
	while (cur->next != NULL)
	{
		if (cur->next == pos)
		{
			new_node = CreatNode(value);
			cur->next = new_node;
			new_node->next = pos;
			return;
		}
		cur = cur->next;
	}
	return;
}

//在链表的指定位置之前插入元素。（移花接木大法）时间复杂度为o(1).
void InsertFrontLinkNode1(LinkNode** head, LinkNode* pos, TypeChar value) //pos值必须要是合法节点
{
	LinkNode* new_node = NULL;
	if (head == NULL || pos == NULL)
	{
		//非法输入。
		return;
	}
	if (*head == NULL)
	{
		//链表为空。
		return;
	}
	new_node = CreatNode(pos->data);
	new_node->next = pos->next;
	pos->next = new_node;
	pos->data = value;
}

//在单链表指定位置之后插入元素。
void InsertAfterLinkNode(LinkNode* head, LinkNode* pos, TypeChar value)
{
	// 因为是在单链表之后插入元素，所以不会改变头指针，所以用* 而不用**
	LinkNode* new_node = NULL;
	if (head == NULL || pos == NULL)
	{
		//链表为空链表。
		return;
	}
	new_node = CreatNode(value);
	new_node->next = pos->next;
	pos->next = new_node;
	return;
}

//删除单链表中任意指定位置的节点。时间复杂度为o(n)
void EraseLinkNode(LinkNode** head, LinkNode* pos)
{
	LinkNode* cur = NULL;
	if (head == NULL || pos == NULL)
	{
		// 非法输入。
		return;
	}
	if (*head == NULL)
	{
		//链表为空。
		return;
	}
	if (*head == pos)
	{
		*head = (*head)->next;
		free(pos);
		return;
	}
	cur = *head;
	while (cur->next != NULL)
	{
		if (cur->next == pos)
		{
			cur->next = pos->next;
			pos->next = NULL;
			break;
		}
		cur = cur->next;
	}
	free(pos);
}

//删除单链表中指定位置的节点，（除过尾节点）时间复杂度为o(1).
void EraseLinkNode1(LinkNode* head, LinkNode* pos)
{
	LinkNode* temp = NULL;
	if (head == NULL || pos == NULL)
	{
		//链表为空，pos非法。
		return;
	}
	temp = pos->next;
	pos->data = temp->data;
	pos->next = temp->next;
	free(temp);
	return;
}

//删除指定值的节点，（在无头单链表中第一个出现的值的节点）
void RemoveLinkNode(LinkNode** head, TypeChar value)
{
	LinkNode* cur = NULL;
	LinkNode* temp = NULL;
	if (head == NULL)
	{
		//非法输入。
		return ;
	}
	if (*head == NULL)
	{
		//空链表。
		return ;
	}
	cur = *head;
	if (cur->data == value)  //头节点。
	{
		*head = (*head)->next;
		free(cur);
		return ;
	}
	while (cur->next != NULL)
	{
		if (cur->next->data == value)
		{
			temp = cur->next;        //赋值一定要注意保存原来指针指向的地址，以便于释放内存。
			cur->next = cur->next->next;//不明白画图。
			free(temp);
			break;
		}
		cur = cur->next;
	}
	
}

//删除指定值的所有元素。
void RemoveLinkNodeAll(LinkNode** head, TypeChar value)
{
	LinkNode* pos = NULL;
	int ret = 1;
	while (ret)
	{
		pos = FindLinkNode(*head, value);
		if (pos == NULL)
		{
			ret = 0;
		}
		EraseLinkNode(head, pos);
	}
	//LinkNode* cur = NULL;
	//LinkNode* temp = NULL;
	//LinkNode* keep = NULL;
	//LinkNode* sb = NULL;
	//if (head == NULL)
	//{
	//	// 非法输入。
	//	return;
	//}
	//if (*head == NULL)
	//{
	//	// 空链表。
	//	return;
	//}
	//temp = *head;
	//if ((*head)->data == value)
	//{
	//	*head = (*head)->next;
	//	free(temp);
	//}
	//keep = *head;
	//cur = (*head)->next;
	//while (cur->next != NULL)
	//{
	//	if (cur->data == value)
	//	{
	//		keep->next = cur->next;
	//		sb = cur;
	//	}
	//	else
	//	{
	//		keep = keep->next;
	//	}
	//	cur = cur->next;
	//	free(sb);
	//}
}

//判断链表是否为空
int EmotyLinkNode(LinkNode* head)
{
	if (head == NULL)
	{
		return 1;
	}
	return 0;
}

//求链表长度
size_t SizeLinkNode(LinkNode* head)
{
	size_t count = 0;
	LinkNode* cur = NULL;
	cur = head;
	while (cur != NULL)
	{
		++count;
		cur = cur->next;
	}
	return count;
}

//将链表逆序打印
void BackPrintLinkNode(LinkNode* head)
{
	if (head == NULL)
	{
		//为空链表。
		return;
	}
	BackPrintLinkNode(head->next);
	printf("[%c: %p]",head->data,head);
}