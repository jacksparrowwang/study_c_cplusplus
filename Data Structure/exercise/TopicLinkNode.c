#include "TopicLinkNode.h"


// 打印
void PrintLinkNode(LinkNode* head)
{
	printf("head");
	LinkNode* cur = head;
	for (;cur != NULL; cur = cur->next)
	{
		printf("[%c:%p]-> ",cur->data,cur);
	}
	printf("NULL\n");
}

// 对链表进行初始化。
void InitLinkNode(LinkNode** head)
{
	if (head == NULL)
	{
		// 非法输入。
		return;
	}
	*head = NULL;
}

//创建一个节点
LinkNode* CreatNode(TypeChar value)
{
	LinkNode* new_node = (LinkNode*)malloc(sizeof(LinkNode));
	if (new_node == NULL)
	{
		//内存申请失败。
		return NULL;
	}
	new_node->data = value;
	new_node->next = NULL;
	return new_node;
}

//尾插一个元素
LinkNode* PushBackLinkNode(LinkNode** head, TypeChar value)
{
	if (head == NULL)
	{
		// 非法输入。
		return NULL;
	}
	LinkNode* new_node = CreatNode(value);
	if (*head == NULL)
	{
		*head = new_node;
		return *head;
	}
	LinkNode* cur = *head;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = new_node;
	return new_node;
}

// 从尾到头打印单链表。
void PrintBackLinkNode(LinkNode* head)
{
	if (head == NULL)
	{
		return;
	}
	PrintBackLinkNode(head->next);
	printf("[%c %p]  ",head->data,head);
}

// shanchu 一个无头单链表的非尾节点（不能遍历链表）
void EraseLinkNode(LinkNode* head, LinkNode* pos)
{
	if (head == NULL || pos == NULL)
	{
		// 为空链表或者pos不合法。
		return;
	}
	LinkNode* to_delete = pos->next;	
	pos->data = to_delete->data;
	pos->next = to_delete->next;
	free(to_delete);
	return;
}

// 单链表实现约瑟夫环。
LinkNode* JosephCycle(LinkNode* head, size_t food)
{
	if (head == NULL || food == 0)
	{
		// 空链表或者从0开始。
		return NULL;
	}
	while (head->next != head)
	{
		size_t i = 1;
		for (;i < food; i++)
		{
			head = head->next;
		}
		printf("%c",head->data);
		// 移花接木来删除元素。
		head->data = head->next->data;
		LinkNode* to_delete = head->next;
		head->next = to_delete->next;
		free(to_delete);
	}
	return head;

}

// 逆置单链表/反转单链表。
void ReverseLinkNode(LinkNode** head)
{
	if (head == NULL || *head == NULL)
	{
		// 不合法或者链表为空。
		return;
	}
	if ((*head)->next == NULL)
	{
		// 只有一个节点。
		return;
	}
	LinkNode* _head = *head;
	while ((*head)->next != NULL)
	{
		LinkNode* cur = (*head)->next;
		(*head)->next = cur->next;
		cur->next = _head;
		_head = cur;
	}
	*head = _head;
	return;
}

////////////////////// 单链表排序（冒泡）。
void BubbleSortLinkNode(LinkNode* head)
{
	if (head == NULL)
	{
		// 链表为空。
		return;
	}
	LinkNode* cur = head;
	LinkNode* tail = NULL; // 用tail来记录尾部。
	for (; cur != tail; cur = cur->next)
	{
		while (cur->next != tail)
		{
			if (cur->data > cur->next->data)
			{
				char tmp = cur->data;
				cur->data = cur->next->data;
				cur->next->data = tmp;
			}
			cur = cur->next;
		}
		tail = cur; // 更新tail，使其向前移动一位。
		cur = head; // cur重新赋值为头节点。
	}
}

// 合并两个有序列表，合并后任然有序。
LinkNode* MergeOrderLinkNode(LinkNode** head1, LinkNode** head2)
{
	if (head1 == NULL || head2 == NULL)
	{
		return NULL;
	}
	LinkNode* _head = NULL;
	LinkNode* tail = NULL;
	while ((*head1) != NULL && (*head2) != NULL)  // 循环条件必须是两个链表中至少一个链表循环到空。
	{
		// 1.第一次进入循环，要有新的头节点，还要有个tail来减少尾插的循环。
		if (_head == tail && tail == NULL)
		{
			// 比较两个头节点值的大小，来确定新头节点。
			if ((*head1)->data < (*head2)->data)
			{
				_head = tail = *head1;
				*head1 = (*head1)->next; //每次头节点后移。以此来保存后续节点。
			}
			else
			{
				_head = tail = *head2;
				*head2 = (*head2)->next;
			}
		}
		// 2.在新的链表中开始比较两个链表值进行尾插。
		if ((*head1)->data < (*head2)->data)
		{
			tail->next = *head1;
			*head1 = (*head1)->next;
		}
		else
		{
			tail->next = *head2;
			*head2 = (*head2)->next;
		}
			tail = tail->next;
	}
	// 3.两个链表已经比较完成，只需要将未插入完的链表一次插入新链表尾部。
	if (*head1 == NULL)
	{
		tail->next = *head2;
		*head2 = NULL;  // 防止野指针。
	}
	else
	{
		tail->next = *head1;	
		*head1 = NULL;
	}
	return _head;
}



// 查找单链表的中间节点，要求只能遍历一次链表。
LinkNode* FindMidNodeLinkNode(LinkNode* head)
{
	if (head == NULL)
	{
		// 空链表。
		return NULL;
	}
	// 利用快慢指针法求。
	LinkNode* fast = head;
	LinkNode* slow = head;
	while (fast->next->next != NULL && fast->next != NULL) // 必须满足两个条件。
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}


// 查找单链表的倒数第K个节点，要求只遍历一次链表。
LinkNode* FindBackKNodeLinkNode(LinkNode* head, size_t k)
{
	if (head == NULL)
	{
		// 空链表。
		return NULL;
	}
	LinkNode* front = head;
	LinkNode* last = head;
	while (front != NULL)
	{
		if (k > 0)
		{
			k--;
			// 先让前面的指针走K步。
			front = front->next;
		}
		else
		{
			// 同时让其进行遍历
			front = front->next;
			last = last->next;
		}
	}
	// 当跳出循环时，用K值判断是否查找成功。
	if (k == 0)
	{
		return last;
	}
	else
	{
		return NULL;
	}
}


// 删除链表倒数第K个节点。
void EraserBackKNodeLinkNode(LinkNode** head, size_t k)
{
	if (head == NULL || k == 0 || *head == NULL)
	{
		return;
	}
	LinkNode* cur = *head;
	size_t count = 0;
	// 求出节点的总个数。
	while (cur != NULL)
	{
		cur = cur->next;
		++count;
	}
	if (count < k)
	{
		// 要删除的节点不在链表上。
		return;
	}
	else if (count == k) // 要删除的倒数第K个节点是头节点。
	{
		cur = *head;
		*head = (*head)->next;
		free(cur);
	}
	else if (count > k) // 要删除的节点在链表上。
	{	
		LinkNode* previous = *head;
		LinkNode* later = *head;
		while (previous != NULL)
		{
			if (k+1 > 0)
			{
				k--;
				// 快指针先走k+1步。
				previous = previous->next;
			}
			else
			{
				previous = previous->next;
				later = later->next;
			}
		}
		// 删除第K个节点。
		LinkNode* to_delete = later->next;
		later->next = to_delete->next;
		free(to_delete);
	}
	return;
}


// 判断单链表是否带环？若带环，求环的长度？求环的入口点？并计算每个算法的时间复杂度。
int  DecideLoopLinkNode(LinkNode* head,int *length,LinkNode** enter)
{
	if (head == NULL)
	{
		// 空链表。
		return 0;
	}
	// 当只有一个节点时需要单独进行判断。
	if (head->next == head)
	{
		*length = 1;
		*enter = head;
		return 1;
	}
	LinkNode* front = head;
	LinkNode* later = head;
	while (front->next->next != NULL && front->next != NULL)
	{
		front = front->next->next; // 快指针一次跳两个节点。
		later = later->next; // 慢指针一次一个，如果带环它们一定会相遇。
		if (front == later)
		{
			// 求入口点。利用快慢指针，指针相交点到链表上从头到交点距离相等。
			LinkNode* _head = head;
			LinkNode* _front = front;
			while (_head != _front)
			{
				_head = _head->next;
				_front = _front->next;
			}
			*enter = _head;
//			printf("入口点：%p\n",_head);
			int count = 1;
			// 求环的长度。
			while (front->next != later)
			{
				++count;
				front = front->next;
			}
			*length = count;
//			printf("环的长度为：%d\n",count);
			return 1;
		}
	}
	return 0;
}

// 判断两个链表是否相交，若相交，求出交点。（假设链表不带环）
int DecideIntersectLinkNode(LinkNode* head1, LinkNode* head2,LinkNode** intersect)
{
	if (head1 == NULL || head2 == NULL)
	{
		// 两个中至少有一个为空链表。
		return 0;
	}
	LinkNode* _head1 = head1;
	int count1 = 0;
	// 计算head1的链表的长度。
	while (_head1 != NULL)
	{
		_head1 = _head1->next;
		++count1;
	}
	LinkNode* _head2 = head2;
	int count2 = 0;
	// 计算head2的链表的长度。
	while (_head2 != NULL)
	{
		_head2 = _head2->next;
		++count2;
	}
	int reduce = count1 - count2;
	// head1链表长度大于head2链表长度。
	if (reduce > 0)
	{
		// 让指针重新指向两个链表的头节点。
		_head1 = head1;
		_head2 = head2;
		while (_head1 != NULL)
		{
			if (reduce > 0) // 先让长链表走长出来的。
			{
				_head1 = _head1->next;
				--reduce;
			}
			else
			{
				if (_head1 == _head2)
				{
					*intersect = _head1;
	//				printf("交点为：actual %p\n",_head1);
					return 1;
				}
				_head1 = _head1->next;
				_head2 = _head2->next;
			}
		}
		return 0;
	}
	// head1链表长度小于或者等于head2链表长度。
	else
	{
		_head1 = head1;
		_head2 = head2;
		while (_head2 != NULL)
		{
			if (reduce < 0)
			{
				_head2 = _head2->next;
				++reduce;
			}
			else
			{
				if (_head1 == _head2)
				{
					*intersect = _head1;
					//printf("相交，交点为：actual %p\n",_head1);
					return 1;
				}
				_head1 = _head1->next;
				_head2 = _head2->next;
			}
		}
		return 0;
	}
}

// 对带环且没有在环上相交
LinkNode* _DecideIntersectLinkNode(LinkNode* head1, LinkNode* head2,LinkNode* loopinter)
{
	if (head1 == NULL || head2 == NULL)
	{
		// 两个中至少有一个为空链表。
		return NULL;
	}
	LinkNode* _head1 = head1;
	int count1 = 0;
	// 计算head1的链表的长度。
	while (_head1 != loopinter)
	{
		_head1 = _head1->next;
		++count1;
	}
	LinkNode* _head2 = head2;
	int count2 = 0;
	// 计算head2的链表的长度。
	while (_head2 != loopinter)
	{
		_head2 = _head2->next;
		++count2;
	}
	int reduce = count1 - count2;
	// head1链表长度大于head2链表长度。
	if (reduce > 0)
	{
		// 让指针重新指向两个链表的头节点。
		_head1 = head1;
		_head2 = head2;
		while (_head1 != loopinter)
		{
			if (reduce > 0) // 先让长链表走长出来的。
			{
				_head1 = _head1->next;
				--reduce;
			}
			else
			{
				if (_head1 == _head2)
				{
	//				printf("交点为：actual %p\n",_head1);
					return _head1;
				}
				_head1 = _head1->next;
				_head2 = _head2->next;
			}
		}
		return NULL;
	}
	// head1链表长度小于或者等于head2链表长度。
	else
	{
		_head1 = head1;
		_head2 = head2;
		while (_head2 != loopinter)
		{
			if (reduce < 0)
			{
				_head2 = _head2->next;
				++reduce;
			}
			else
			{
				if (_head1 == _head2)
				{
					//printf("相交，交点为：actual %p\n",_head1);
					return _head1;
				}
				_head1 = _head1->next;
				_head2 = _head2->next;
			}
		}
		return NULL;
	}
}

//判断两个链表是否相交，若相交，求出交点。（假设链表可能带环）
int DecideIntersectLinkNode1(LinkNode* head1, LinkNode* head2)
{
	if (head1 == NULL || head2 == NULL)
	{
		return 0;
	}
	// 先判断是否带环。
	LinkNode* intersect1 = NULL;
	LinkNode* intersect2 = NULL;
	int length1 = 0;
	int length2 = 0;
	int ret1 = DecideLoopLinkNode(head1,&length1,&intersect1);
	int ret2 = DecideLoopLinkNode(head2,&length2,&intersect2);
	// 若带环
	if (ret1 == ret2 && ret2 == 1)
	{
		if (intersect1 == intersect2)
		{
			// 两条链表相交在环以前。
			LinkNode* inter = _DecideIntersectLinkNode(head1,head2,intersect1->next);
			printf("交点为 %p\n",inter);
			return 1;
		}
		else
		{
			// 相交在环上，就有两个交点。
			printf("交点为 %p\n",intersect1);
			printf("交点为 %p\n",intersect2);
			return 1;
		}
	}
	// 到这里说明无交点。
	return 0;
}

// 复杂链表的复制。一个链表的每个节点，有一个指向next指针指向下一个节点，还有
// 一个random指针指向这个链表中的一个随机节点或者NULL，现在要求实现复制这条链
// 表，返回复制厚的新链表。
ComplexLinkNode *CreatComplexNode(TypeChar value)
{
    ComplexLinkNode* new_node = (ComplexLinkNode*)malloc(sizeof(ComplexLinkNode));
    if (new_node == NULL)
    {
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    new_node->random = NULL;
    return new_node;
}

size_t offp(ComplexLinkNode* head, ComplexLinkNode* random)
{
    ComplexLinkNode* cur = head;
    size_t count = 0;
    for (; cur != NULL; cur = cur->next)
    {
        if (cur == random)
        {
            return count;
        }
        ++count;
    }
    return (size_t)-1;
}

ComplexLinkNode* offs(ComplexLinkNode* new_head, size_t offset)
{
    ComplexLinkNode* cur = new_head;
    if (offset == (size_t)-1)
    {
        return NULL;
    }
    while (offset)
    {
        cur = cur->next;
        --offset;
    }
    return cur;
}

ComplexLinkNode *CypeComplexLinkNode(ComplexLinkNode *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    ComplexLinkNode* new_head = NULL;
    ComplexLinkNode* new_tail = NULL;
    ComplexLinkNode* cur = head;
    // 先复制新的链表，random指针指向空
    for (; cur != NULL; cur = cur->next)
    {
        ComplexLinkNode* new_node = CreatComplexNode(cur->data);
        if (new_head == new_tail && new_tail == NULL)
        {
            new_head = new_tail = new_node;
        }
        else
        {
            new_tail->next = new_node;
            new_tail = new_tail->next;
        }
    }

    // 开始让原来链表遍历并且把random指针相对于头节点的相对位移记录
    // 同时让两个链表前移
    ComplexLinkNode* new_cur = new_head;
    for (cur = head; new_cur != NULL&&cur != NULL; cur = cur->next, new_cur = new_cur->next)
    {
        // 求出原链表中当前节点的相对位置
        size_t setoff = offp(head, cur->random);
        // 用原来链表的相对位置，求出当前节点的random指针指向的位置
        new_cur->random = offs(new_head, setoff);
    }
    return new_head;
}

ComplexLinkNode *CypeComplexLinkNode2(ComplexLinkNode *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    ComplexLinkNode* cur = head;
    for (; cur != NULL; cur = cur->next->next)
    {
        ComplexLinkNode* new_node = CreatComplexNode(cur->data);
        new_node->next = cur->next;
        cur->next = new_node;
    }
    for (cur = head; cur != NULL; cur = cur->next->next)
    {
        if (cur->random == NULL)
        {
            cur->next->random = NULL;
            continue;
        }
        cur->next->random = cur->random->next;
    }
    ComplexLinkNode* new_head = NULL;
    ComplexLinkNode* new_tail = NULL;
    for (cur = head; cur != NULL; cur = cur->next)
    {
        ComplexLinkNode* new_delete = cur->next;
        cur->next = new_delete->next;
        if (new_head == new_tail && new_tail == NULL)
        {
            new_head = new_tail = new_delete;
        }
        else
        {
            new_tail->next = new_delete;
            new_tail = new_tail->next;
        }
    }
    return new_head;
}

// 求两个已排序单链表中相同的数据。
void UnionSet(LinkNode* l1, LinkNode* l2)
{
	if (l1 == NULL || l2 == NULL)
	{
		// 两个链表至少有一个为空链表。
		return;
	}
	LinkNode* head1 = l1;
	LinkNode* head2 = l2;
	while (head1 != NULL && head2 != NULL)
	{
		if (head1->data > head2->data)
		{
			head2 = head2->next;
		}
		else if (head1->data < head2->data)
		{
			head1 = head1->next;
		}
		else
		{
			printf("[%c %p]",head1->data,head1);
			head1 = head1->next;
			head2 = head2->next;
		}
	}
	return;
}

/////////////////////
// 我是分割线
/////////////////////

void TestComplexLinkNode2()
{
	DIVE_LINE;
    ComplexLinkNode* a = CreatComplexNode('a');
    ComplexLinkNode* b = CreatComplexNode('b');
    ComplexLinkNode* c = CreatComplexNode('c');
    ComplexLinkNode* d = CreatComplexNode('d');
    a->next = b;
    b->next = c;
    c->next = d;
    a->random = d;
    b->random = b;
    c->random = NULL;
    d->random = c;
    ComplexLinkNode* new_head = CypeComplexLinkNode(a);
    ComplexLinkNode*cur = new_head;
    while (cur != NULL)
    {
        printf("[%c[%p] %p]  ",cur->data,cur, cur->random);
        cur = cur->next;
    }
    printf("\n");
}

void TestUnionSet()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	LinkNode* head1 = NULL;
	InitLinkNode(&head);
	InitLinkNode(&head1);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'e');
	PushBackLinkNode(&head,'g');
	PushBackLinkNode(&head,'n');
	PrintLinkNode(head);
	PushBackLinkNode(&head1,'a');
	PushBackLinkNode(&head1,'c');
	PushBackLinkNode(&head1,'d');
	PushBackLinkNode(&head1,'f');
	PushBackLinkNode(&head1,'w');
	PushBackLinkNode(&head1,'y');
	PrintLinkNode(head1);
	UnionSet(head,head1);
}

void TestDecideIntersectLinkNode1()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	LinkNode* tmp = PushBackLinkNode(&head,'d');
	LinkNode* pos3 = PushBackLinkNode(&head,'e');
	PushBackLinkNode(&head,'f');
	LinkNode* pos1 = PushBackLinkNode(&head,'g');
	pos1->next = tmp;
	LinkNode* head1 = NULL;
	InitLinkNode(&head1);
	PushBackLinkNode(&head1,'a');
	PushBackLinkNode(&head1,'b');
	LinkNode* pos = PushBackLinkNode(&head1,'c');
	pos->next = pos3;
	int ret = DecideIntersectLinkNode1(head, head1);
	printf("%p\n",tmp);
	printf("%p\n",pos3);
	printf("except 1 actual %d\n",ret);
}

void TestDecideIntersectLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	LinkNode* tmp = PushBackLinkNode(&head,'d');
	PushBackLinkNode(&head,'e');
	PushBackLinkNode(&head,'f');
	PushBackLinkNode(&head,'g');
	LinkNode* head1 = NULL;
	InitLinkNode(&head1);
	PushBackLinkNode(&head1,'a');
	PushBackLinkNode(&head1,'b');
	LinkNode* pos = PushBackLinkNode(&head1,'c');
	pos->next = tmp;
	LinkNode* intersect = NULL;
	int ret = DecideIntersectLinkNode(head,head1,&intersect);
	printf("except 1 actual %d\n",ret);
	printf("except %p actual %p\n",tmp,intersect);
}

// 1为带环。
void TestDecideLoopLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	LinkNode* pos = PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'d');
	PushBackLinkNode(&head,'e');
	PushBackLinkNode(&head,'f');
	LinkNode* tmp = PushBackLinkNode(&head,'g');
	tmp->next = pos;
	int length = 0;
	LinkNode* enter = NULL;
	int ret = DecideLoopLinkNode(head,&length,&enter);
	printf("pos enter :%p %p\n",pos,enter);
	printf("except 5 actual %d\n",length);
	printf("except 1 actual %d",ret);
}


void TestEraserBackKNodeLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'g');
	PushBackLinkNode(&head,'f');
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PrintLinkNode(head);
	EraserBackKNodeLinkNode(&head,3);
	PrintLinkNode(head);
	EraserBackKNodeLinkNode(&head,1);
	PrintLinkNode(head);
	EraserBackKNodeLinkNode(&head,4);
	PrintLinkNode(head);
}
void TestFindBackKNodeLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	LinkNode* temp = PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'c');
	LinkNode* pos = PushBackLinkNode(&head,'g');
	PushBackLinkNode(&head,'f');
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PrintLinkNode(head);
	LinkNode* ret = NULL;
	LinkNode* ret1 = NULL;
	ret = FindBackKNodeLinkNode(head,9);
	ret1 = FindBackKNodeLinkNode(head,6);
	printf("except %p actual %p",pos,ret);
	printf("except %p actual %p",temp,ret1);
}

void TestFindMidNodeLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'c');
	LinkNode* pos = PushBackLinkNode(&head,'g');
	PushBackLinkNode(&head,'f');
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PrintLinkNode(head);
	LinkNode* ret = NULL;
	ret = FindMidNodeLinkNode(head);
	printf("except %p  actual %p",pos, ret);
}

void TestMergeOrderLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	LinkNode* head1 = NULL;
	InitLinkNode(&head);
	InitLinkNode(&head1);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'e');
	PushBackLinkNode(&head,'g');
	PushBackLinkNode(&head,'n');
	PrintLinkNode(head);
	PushBackLinkNode(&head1,'a');
	PushBackLinkNode(&head1,'c');
	PushBackLinkNode(&head1,'d');
	PushBackLinkNode(&head1,'f');
	PushBackLinkNode(&head1,'w');
	PushBackLinkNode(&head1,'y');
	PrintLinkNode(head1);
	LinkNode* ret = NULL;
	ret = MergeOrderLinkNode(&head,&head1);
	PrintLinkNode(ret);
}

void TestBubbleSortLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'g');
	PushBackLinkNode(&head,'f');
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PrintLinkNode(head);
	BubbleSortLinkNode(head);	
	PrintLinkNode(head);
}


void TestReverseLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'d');
	PushBackLinkNode(&head,'e');
	PushBackLinkNode(&head,'f');
	PrintLinkNode(head);
	ReverseLinkNode(&head);
	PrintLinkNode(head);
}
 
void TestJosephCycle()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	LinkNode* pos = PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'d');
	PushBackLinkNode(&head,'e');
	PushBackLinkNode(&head,'f');
	LinkNode* tmp = PushBackLinkNode(&head,'g');
	tmp->next = pos;
	LinkNode* ret = JosephCycle(head,5);
	printf("%c %p",ret->data,ret);
}

void TestEraseLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	LinkNode* pos = PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PrintLinkNode(head);
	EraseLinkNode(head,pos);
	PrintLinkNode(head);
}


void TestInitLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);

	PrintLinkNode(head);
}

void TestPushBackLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PrintLinkNode(head);
}

void TestPrintBackLinkNode()
{
	DIVE_LINE;
	LinkNode* head = NULL;
	InitLinkNode(&head);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PrintLinkNode(head);
	PrintBackLinkNode(head);
}

int main()
{
	TestInitLinkNode();
	TestPushBackLinkNode();
	TestPrintBackLinkNode();
	TestEraseLinkNode();
	TestJosephCycle();
	TestReverseLinkNode();	
	TestBubbleSortLinkNode();
	TestMergeOrderLinkNode();
	TestFindMidNodeLinkNode();
	TestFindBackKNodeLinkNode();
	TestEraserBackKNodeLinkNode();
	TestDecideLoopLinkNode();
	TestDecideIntersectLinkNode();
	TestDecideIntersectLinkNode1();
	TestUnionSet();
    TestComplexLinkNode2();
	return 0;
}


