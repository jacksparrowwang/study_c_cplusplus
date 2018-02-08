#include"LinkNode.h"


void TestInit()
{
	LinkNode *head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
}

void TestPushBackLinkNode()
{
	LinkNode *head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'d');
	LinkNodePrint(head);
}

void TestPopBackLinkNode() 
{
	LinkNode *head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	PopBackLinkNode(&head);
	PushBackLinkNode(&head,'a');
	PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'d');
	PopBackLinkNode(&head);
	PopBackLinkNode(&head);
	LinkNodePrint(head);
	PopBackLinkNode(&head);
	LinkNodePrint(head);
	PopBackLinkNode(&head);
	LinkNodePrint(head);
}

void TestPushFrontLinkNode() 
{
	LinkNode *head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	PushFrontLinkNode(&head, 'y');
	LinkNodePrint(head);
	PushBackLinkNode(&head, 'a');
	PushBackLinkNode(&head, 'b');
	PushBackLinkNode(&head, 'c');
	PushFrontLinkNode(&head, 'x');
	LinkNodePrint(head);
}

void TestPopFrontLinkNode() 
{
	LinkNode *head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	PopFrontLinkNode(&head);
	LinkNodePrint(head);
	PushBackLinkNode(&head, 'a');
	PushBackLinkNode(&head, 'b');
	PushBackLinkNode(&head, 'c');
	PopFrontLinkNode(&head);
	PopFrontLinkNode(&head);
	LinkNodePrint(head);
	PopFrontLinkNode(&head);
	LinkNodePrint(head);
}

void TestFindLinkNode()
{
	LinkNode* pos = NULL;
	LinkNode* temp = NULL;
	LinkNode* head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	PushBackLinkNode(&head,'a');
	pos = PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'d');
	temp = FindLinkNode(head,'b');
	printf("expect %p,actual %p\n",pos,temp);
}

//o(n)
void TestInsertFrontLinkNode()
{
	LinkNode* pos = NULL;
	LinkNode* temp = NULL;
	LinkNode* head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	temp = PushBackLinkNode(&head,'a');
	pos = PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'d');
	LinkNodePrint(head);
	InsertFrontLinkNode(&head,pos,'x');
	LinkNodePrint(head);
	InsertFrontLinkNode(&head,temp,'y');
	LinkNodePrint(head);
	InsertFrontLinkNode(&head,NULL,'8');
	LinkNodePrint(head);
}

void TestInsertFrontLinkNode1()
{
	LinkNode* pos = NULL;
	LinkNode* temp = NULL;
	LinkNode* head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	temp = PushBackLinkNode(&head,'a');
	pos = PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'d');
	LinkNodePrint(head);
	InsertFrontLinkNode1(&head,pos,'x');
	LinkNodePrint(head);
	InsertFrontLinkNode1(&head,temp,'y');
	LinkNodePrint(head);
	InsertFrontLinkNode1(&head,NULL,'8');
	LinkNodePrint(head);
}

void TestInsertAfterLinkNode()
{
	LinkNode* pos = NULL;
	LinkNode* temp = NULL;
	LinkNode* head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	temp = PushBackLinkNode(&head,'a');
	pos = PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'d');
	LinkNodePrint(head);
	InsertAfterLinkNode(head,pos,'x');
	LinkNodePrint(head);
	InsertAfterLinkNode(head,temp,'y');
	LinkNodePrint(head);
	InsertAfterLinkNode(head,NULL,'8');
	LinkNodePrint(head);
}

void TestEraseLinkNode()
{
	LinkNode* pos = NULL;
	LinkNode* temp = NULL;
	LinkNode* head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	temp = PushBackLinkNode(&head,'a');
	pos = PushBackLinkNode(&head,'b');
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'d');
	LinkNodePrint(head);
	EraseLinkNode(&head,pos);
	LinkNodePrint(head);
	EraseLinkNode(&head,temp);
	LinkNodePrint(head);
}

void TestEraseLinkNode1()  //采用换值不换位置的方法，所以pos的地址如果不正确，程序奔溃。
{
	LinkNode* pos = NULL;
	LinkNode* temp = NULL;
	LinkNode* head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	temp = PushBackLinkNode(&head,'a');
	pos = PushBackLinkNode(&head,'b');//在删除temp时候，pos已经被删除。
	PushBackLinkNode(&head,'c');
	PushBackLinkNode(&head,'d');
	EraseLinkNode1(head,temp);
	LinkNodePrint(head);
	EraseLinkNode1(head,temp);
	LinkNodePrint(head);
}

void TestRemoveLinkNode()
{
	int ret = 0;
	LinkNode *head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	PushBackLinkNode(&head, 'a');
	PushBackLinkNode(&head, 'b');
	PushBackLinkNode(&head, 'c');
	PushBackLinkNode(&head, 'd');
	LinkNodePrint(head);
	RemoveLinkNode(&head,'b');
	RemoveLinkNode(&head,'d');
	LinkNodePrint(head);
	RemoveLinkNode(&head,'a');
	LinkNodePrint(head);
}

void TestRemoveLinkNodeAll()
{

	LinkNode *head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	PushBackLinkNode(&head, 'd');
	PushBackLinkNode(&head, 'a');
	PushBackLinkNode(&head, 'd');
	PushBackLinkNode(&head, 'c');
	PushBackLinkNode(&head, 'd');
	PushBackLinkNode(&head, 'c');
	PushBackLinkNode(&head, 'd');
	PushBackLinkNode(&head, 'd');
	LinkNodePrint(head);
	RemoveLinkNodeAll(&head, 'd');
	LinkNodePrint(head);
}

void TestEmotyAndSzie()
{
	int ret = 0;
	size_t temp = 0;
	LinkNode *head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	ret = EmotyLinkNode(head);
	printf("except 1 actual %d\n",ret); //是空返回1，不是空返回0.
	PushBackLinkNode(&head, 'd');
	PushBackLinkNode(&head, 'a');
	PushBackLinkNode(&head, 'd');
	PushBackLinkNode(&head, 'c');
	PushBackLinkNode(&head, 'd');
	PushBackLinkNode(&head, 'c');
	PushBackLinkNode(&head, 'd');
	PushBackLinkNode(&head, 'd');
	temp = SizeLinkNode(head);
	printf("except 8 actual %d\n",temp);
}
void TestBackPrintLinkNode()
{
	LinkNode *head = NULL;
	DIV_LINE;
	InitLinkNode(&head);
	PushBackLinkNode(&head, 'a');
	PushBackLinkNode(&head, 'b');
	PushBackLinkNode(&head, 'c');
	PushBackLinkNode(&head, 'd');
	BackPrintLinkNode(head);
}

int main()
{
	TestInit();
	TestPushBackLinkNode();
	TestPopBackLinkNode();
	TestPushFrontLinkNode();
	TestPopFrontLinkNode();
	TestFindLinkNode();
	TestInsertFrontLinkNode();
	TestInsertFrontLinkNode1();
	TestInsertAfterLinkNode();
	TestEraseLinkNode();
	TestEraseLinkNode1();
	TestRemoveLinkNode();
	TestRemoveLinkNodeAll();
	TestEmotyAndSzie();
	TestBackPrintLinkNode();
	return 0;
}

