#include"Bin_Tree.h"


// 二叉树的初始化。
void TreeInit(TreeNode **root)
{
	if (root == NULL)
	{
		return;
	}
	*root == NULL;
}

// 先序遍历。
void PreOrder(TreeNode *root)
{
	if (root == NULL)
	{
		// 空树。
		return;
	}
	printf("%c ",root->data);
	PreOrder(root->lchild);
	PreOrder(root->rchild);
}

// 中序遍历。
void InOrder(TreeNode *root)
{
	if (root == NULL)
	{
		// 空树。
		return;
	}
	InOrder(root->lchild);
	printf("%c ",root->data);
	InOrder(root->rchild);
}

// 后序遍历。
void PostOrder(TreeNode *root)
{
	if (root == NULL)
	{
		// 空树。
		return;
	}
	PostOrder(root->lchild);
	PostOrder(root->rchild);
	printf("%c ",root->data);
}

#if 0
// 层序遍历。
void LevelOrder(TreeNode *root)
{
	if (root == NULL)
	{
		return;
	}	
	SeqQueue seq;
	InitSeqQueue(&seq);
	TreeNode *tmp = NULL;
	PushQueue(&seq, root);
	while (FindHead(&seq, &tmp))
	{
		printf("%c",tmp->data);
		PopQueue(&seq);
		if (tmp->lchild != NULL)
		{
			PushQueue(&seq, tmp->lchild);
		}
		if (tmp->rchild != NULL)
		{
			PushQueue(&seq, tmp->rchild);
		}
	}
	printf("\n");
}
#endif

// 递归创建树。
TreeNode *_CreatTree(TreeType arr[], size_t size, size_t *index, TreeType null_node)
{
	// 如果*index 大于 size时候，说明创建树的计数个数已经超出size
	if (arr == NULL || *index > size)
	{
		return NULL;
	}
	if (arr[*index] == null_node)
	{
		return NULL;
	}
	// 先序遍历创建树。
	TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
	// 根节点。
	root->data = arr[*index];
	++(*index);
	// 左子树递归
	root->lchild = _CreatTree(arr, size, index, null_node);
	++(*index);
	// 右子树递归
	root->rchild = _CreatTree(arr, size, index, null_node);
	return root;
}

// 创建一颗树。
TreeNode *CreatTree(TreeType arr[], size_t size, TreeType null_node)
{
	// 数组个数size为0，空数组
	if (arr == NULL || size < 1)
	{
		return NULL;
	}
	// 用来计数当前节点。
	size_t index = 0;
	TreeNode *root = _CreatTree(arr, size,&index, null_node);
	return root;
}

// 创建节点
TreeNode *CreatTreeNode(TreeType value)
{
	TreeNode *new_node = (TreeNode*)malloc(sizeof(TreeNode));
	new_node->data = value;
	new_node->lchild = NULL;
	new_node->rchild = NULL;
	return new_node;
}

// 销毁树。
void TreeDestory(TreeNode **root)
{
	if (root == NULL || *root == NULL)
	{
		return;
	}
	// 先用指针变量来把根结点保存起来。
	// 因为在递归过程中可以不断刷新根节点。
	TreeNode *to_delete = *root;
	TreeDestory(&to_delete->lchild);
	TreeDestory(&to_delete->rchild);
	free(to_delete);
	*root = NULL;
}

// 树的深拷贝。
TreeNode *TreeClone(TreeNode *root)
{
	if (root == NULL)
	{
		return NULL;
	}
	TreeNode *new_node = CreatTreeNode(root->data);
	new_node->lchild = TreeClone(root->lchild);
	new_node->rchild = TreeClone(root->rchild);
	return new_node;
}

// 树节点的个数。
size_t TreeSize(TreeNode *root)
{
	if (root == NULL)
	{
		return 0;
	}
	return 1 + TreeSize(root->lchild) + TreeSize(root->rchild);
}


// 树的叶子节点。
size_t TreeLevelSize(TreeNode *root)
{
	if (root == NULL)
	{
		return 0;
	}
	// 只要是节点的左右孩子都为NULL，那么这个节点就是叶子节点。
	if (root->lchild == NULL && root->rchild == NULL)
	{
		return 1;
	}
	// 根节点的左右子树分别递归求取叶子节点。
	return TreeLevelSize(root->lchild) + TreeLevelSize(root->rchild);
}


// 树的高度。
size_t TreeHeight(TreeNode *root)
{
	if (root == NULL)
	{
		return 0;
	}
	size_t i = TreeHeight(root->lchild);
	size_t j = TreeHeight(root->rchild);
	return 1 + (i > j ? i : j);
}

// 给定值查找对应节点的位置
TreeNode *TreeFind(TreeNode *root, TreeType to_find)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->data == to_find)
	{
		return root;
	}
	TreeNode *lchild = TreeFind(root->lchild, to_find);
	TreeNode *rchild = TreeFind(root->rchild, to_find);
	return lchild != NULL ? lchild : rchild;
}

// 求给定节点的左孩子节点位置
TreeNode *LChild(TreeNode *node)
{
	if (node == NULL)
	{
		return NULL;
	}
	return node->lchild;
}

// 求取给定节点的右孩子节点的位置
TreeNode *RChild(TreeNode *node)
{
	if (node == NULL)
	{
		return NULL;
	}
	return node->rchild;
}

// 给出节点求出该节点的父节点。
TreeNode *Parent(TreeNode *root,TreeNode *node)
{
	if (node == NULL || root == NULL)
	{
		return NULL;
	}
	if (root == node)
	{
		return NULL;
	}
	if (root->lchild == node || root->rchild == node)
	{
		return root;
	}
	TreeNode *lpar = Parent(root->lchild, node);
	TreeNode *rpar = Parent(root->rchild, node);
	return lpar != NULL ? lpar : rpar;
}

// 先序遍历（非递归）采用的是根右左入栈
void PreOrderByLoop(TreeNode *root)
{
	if (root == NULL)
	{
		return;
	}
	SeqStack seq;
	SeqStackInit(&seq);
	// 先让根结点入栈
	SeqStackPushStack(&seq,root);
	while (1)
	{
		// 取栈顶元素
		TreeNode *top = NULL;
		SeqStackFindTop(&seq,&top);
		if (top == NULL)
		{
			// 取栈顶元为空
			// 说明栈为空
			break;
		}
		// 访问栈顶元素
		printf("%c ",top->data);
		// 出栈
		SeqStackPopStack(&seq);
		// 入栈顺序要先入右子树后入左子树
		if (top->rchild != NULL)
		{
			SeqStackPushStack(&seq,top->rchild);
		}
		if (top->lchild != NULL)
		{
			SeqStackPushStack(&seq,top->lchild);
		}
	}
	printf("\n");
}

// 中序遍历（非递归）采用的是根到左再右入栈
void InOrderByLoop(TreeNode *root)
{
	if (root == NULL)
	{
		return;
	}
	SeqStack stack;
	SeqStackInit(&stack);
	TreeNode *cur = root;
	while (1)
	{
		// 先找到树的最左节点，在找最左节点时将节点依次入栈。
		while (cur != NULL)
		{
			SeqStackPushStack(&stack,cur);
			cur = cur->lchild;
		}
		// 取出栈顶元素。
		TreeNode *top = NULL;
		SeqStackFindTop(&stack,&top);
		if (top == NULL)
		{
			// 判断是否结束
			// 栈顶元素为空时，说明已经遍历完成。
			break;
		}
		printf("%c ",top->data);
		// 将栈顶元素出栈
		SeqStackPopStack(&stack);
		// 让cur指向栈顶元素的右节点。是深度遍历 。
		cur = top->rchild;
	}
	printf("\n");
}

// 后序遍历（非递归）采用的是根左右边入栈
void PostOrderByLoop(TreeNode *root)
{
	if (root == NULL)
	{
		return;
	}
	SeqStack stack;
	SeqStackInit(&stack);
	TreeNode *cur = root;
	TreeNode *pre = NULL;
	while (1)
	{
		// 先找到树的最左节点，在找最左节点时将节点依次入栈。
		while (cur != NULL)
		{
			SeqStackPushStack(&stack,cur);
			cur = cur->lchild;
		}
		// 取栈顶元素
		TreeNode *top = NULL;
		SeqStackFindTop(&stack,&top);
		if (top == NULL)
		{
			break;
		}
		// 出栈操作必须满足以下两个条件
		// 1.栈顶元素的右子树必须为空
		// 2.访问的右子树已经被访问过
		if (top->rchild == NULL || top->rchild == pre)
		{
			printf("%c ",top->data);
			SeqStackPopStack(&stack);
			// 来分辨是否已经访问过右子树
			pre = top;
		}
		// 如果右子树没有被访问过必须循环处理。
		else
		{
			cur = top->rchild;
		}
	}
	printf("\n");
}

// 镜像树
void TreeMirror(TreeNode *root)
{
	if (root == NULL)
	{
		return;
	}
	TreeNode * tmp = root->lchild;
	root->lchild = root->rchild;
	root->rchild = tmp;
	TreeMirror(root->lchild);
	TreeMirror(root->rchild);
}

// 这个是查找根结点在中序里的位置
size_t Find(TreeType arr[], size_t left, size_t right, TreeType to_find)
{
	size_t i = left;
	for (; i < right; ++i)
	{
		if (arr[i] == to_find)
		{
			return i;
		}
	}
	return (size_t)-1;
}

// 递归的去构建树
TreeNode *_ReBuildTree(TreeType pre_order[], size_t pre_order_size, size_t *index,
		        TreeType in_order[], size_t in_order_left, size_t in_order_right)
{
	if (in_order_left >= in_order_right)	
	{
		// 说明当前中序遍历为空。
		return NULL;
	}
	if (index != NULL && *index >= pre_order_size)
	{
		// 先序遍历结束,树还原完成。
		return NULL;
	}
	// 先创建根结点
	TreeNode *new_node = CreatTreeNode(pre_order[*index]);
	// 在中序中查找根结点的位置。
	size_t cur_root_in_order_index = Find(in_order, in_order_left, in_order_right, pre_order[*index]);
	// 创建完成后记录节点的index就需要++
	++(*index);
	assert(cur_root_in_order_index != (size_t)-1);
	// 接下来递归的去构建左子树和右子树
	new_node->lchild = _ReBuildTree(pre_order,pre_order_size,index,in_order, 
			                           in_order_left, cur_root_in_order_index);
	new_node->rchild = _ReBuildTree(pre_order,pre_order_size,index,in_order, 
			                          cur_root_in_order_index + 1, in_order_right);
	return new_node;
}

// 给出先序遍历和中序遍历还原二叉树
TreeNode *ReBuildTree(TreeType pre_order[], size_t pre_order_size, TreeType in_order[], size_t in_order_size)
{
	size_t index = 0;
	TreeNode *root = _ReBuildTree(pre_order, pre_order_size, &index, in_order, 0, in_order_size);
	return root;
}


//////////////////////
//以下是测试代码
//////////////////////

#define TEST_HEAD printf("\n============%s===========\n",__FUNCTION__)

void TestTreeInit()
{
	TEST_HEAD;
	TreeNode *root = NULL;
	TreeInit(&root);
}

void TestPreOrder()
{
	TEST_HEAD;
	TreeNode *root = NULL;
	TreeInit(&root);
	TreeNode *a = CreatTreeNode('a');
	TreeNode *b = CreatTreeNode('b');
	TreeNode *c = CreatTreeNode('c');
	TreeNode *d = CreatTreeNode('d');
	TreeNode *e = CreatTreeNode('e');
	TreeNode *f = CreatTreeNode('f');
	TreeNode *g = CreatTreeNode('g');
	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	e->lchild = g;
	c->rchild = f;
	root = a;
	printf("先序遍历");
	PreOrder(root);
}

void TestInOrder()
{
	TEST_HEAD;
	TreeNode *root = NULL;
	TreeInit(&root);
	TreeNode *a = CreatTreeNode('a');
	TreeNode *b = CreatTreeNode('b');
	TreeNode *c = CreatTreeNode('c');
	TreeNode *d = CreatTreeNode('d');
	TreeNode *e = CreatTreeNode('e');
	TreeNode *f = CreatTreeNode('f');
	TreeNode *g = CreatTreeNode('g');
	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	e->lchild = g;
	c->rchild = f;
	root = a;
	printf("中序遍历");
	InOrder(root);
}

void TestPostOrder()
{
	TEST_HEAD;
	TreeNode *root = NULL;
	TreeInit(&root);
	TreeNode *a = CreatTreeNode('a');
	TreeNode *b = CreatTreeNode('b');
	TreeNode *c = CreatTreeNode('c');
	TreeNode *d = CreatTreeNode('d');
	TreeNode *e = CreatTreeNode('e');
	TreeNode *f = CreatTreeNode('f');
	TreeNode *g = CreatTreeNode('g');
	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	e->lchild = g;
	c->rchild = f;
	root = a;
	printf("后序遍历");
	PostOrder(root);
}

#if 0
void TestLevelOrder()
{
	TEST_HEAD;
	TreeNode *root = NULL;
	TreeInit(&root);
	TreeNode *a = CreatTreeNode('a');
	TreeNode *b = CreatTreeNode('b');
	TreeNode *c = CreatTreeNode('c');
	TreeNode *d = CreatTreeNode('d');
	TreeNode *e = CreatTreeNode('e');
	TreeNode *f = CreatTreeNode('f');
	TreeNode *g = CreatTreeNode('g');
	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	e->lchild = g;
	c->rchild = f;
	root = a;
	
	printf("层序遍历");
	LevelOrder(root);
}
#endif

void TestCreatTree()
{
	TEST_HEAD;
	TreeType arr[] = "abd##eg###c#f##";
	TreeNode *root = CreatTree(arr, strlen(arr), '#');
	printf("先序遍历");
	PreOrder(root);
	printf("\n");
	printf("中序遍历");
	InOrder(root);
	printf("\n");
	printf("后序遍历");
	PostOrder(root);
	printf("\n");
}

void TestTreeDestory()
{
	TEST_HEAD;
	TreeNode *root = NULL;
	TreeInit(&root);
	TreeNode *a = CreatTreeNode('a');
	TreeNode *b = CreatTreeNode('b');
	TreeNode *c = CreatTreeNode('c');
	TreeNode *d = CreatTreeNode('d');
	TreeNode *e = CreatTreeNode('e');
	TreeNode *f = CreatTreeNode('f');
	TreeNode *g = CreatTreeNode('g');
	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	e->lchild = g;
	c->rchild = f;
	root = a;
	TreeDestory(&root);
	printf("except NULL actual %p",root);
}

void TestTreeClone()
{
	TEST_HEAD;
	TreeNode *root = NULL;
	TreeInit(&root);
	TreeNode *a = CreatTreeNode('a');
	TreeNode *b = CreatTreeNode('b');
	TreeNode *c = CreatTreeNode('c');
	TreeNode *d = CreatTreeNode('d');
	TreeNode *e = CreatTreeNode('e');
	TreeNode *f = CreatTreeNode('f');
	TreeNode *g = CreatTreeNode('g');
	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	e->lchild = g;
	c->rchild = f;
	root = a;
	TreeNode *ret = TreeClone(root);
	printf("[root %p] [ret %p]",root,ret);
	printf("\n");
	PreOrder(root);
	printf("\n");
	PreOrder(ret);
}

void TestTreeSize()
{
	TEST_HEAD;
	TreeNode *root = NULL;
	TreeInit(&root);
	TreeNode *a = CreatTreeNode('a');
	TreeNode *b = CreatTreeNode('b');
	TreeNode *c = CreatTreeNode('c');
	TreeNode *d = CreatTreeNode('d');
	TreeNode *e = CreatTreeNode('e');
	TreeNode *f = CreatTreeNode('f');
	TreeNode *g = CreatTreeNode('g');
	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	e->lchild = g;
	c->rchild = f;
	root = a;
	size_t ret = TreeSize(root);
	printf("except 7 actual %d\n",ret);
}

void TestTreeLevelSize()
{
	TEST_HEAD;
	TreeNode *root = NULL;
	TreeInit(&root);
	TreeNode *a = CreatTreeNode('a');
	TreeNode *b = CreatTreeNode('b');
	TreeNode *c = CreatTreeNode('c');
	TreeNode *d = CreatTreeNode('d');
	TreeNode *e = CreatTreeNode('e');
	TreeNode *f = CreatTreeNode('f');
	TreeNode *g = CreatTreeNode('g');
	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	c->lchild = f;
	c->rchild = g;
	root = a;
	size_t ret = TreeLevelSize(root);
	printf("except 4 actual %d",ret);
}

void TestTreeHeight()
{
	TEST_HEAD;
	TreeNode *root = NULL;
	TreeInit(&root);
	TreeNode *a = CreatTreeNode('a');
	TreeNode *b = CreatTreeNode('b');
	TreeNode *c = CreatTreeNode('c');
	TreeNode *d = CreatTreeNode('d');
	TreeNode *e = CreatTreeNode('e');
	TreeNode *f = CreatTreeNode('f');
	TreeNode *g = CreatTreeNode('g');
	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	c->lchild = f;
	c->rchild = g;
	// 这是一个四层二叉树。第一层从1开始。
	//a->lchild = b;
	//a->rchild = c;
	//b->lchild = d;
	//b->rchild = e;
	//e->lchild = g;
	//c->rchild = f;
	root = a;
	size_t ret = TreeHeight(root);
	printf("except 3 actual %d\n",ret);
}

void TestTreeFind()
{
	TEST_HEAD;
	TreeType arr[] = "abd##eg###c#f##";
	TreeNode *root = CreatTree(arr, strlen(arr), '#');
	TreeNode *ret = TreeFind(root,'c');
	printf("except %p actual %p \n",root->rchild,ret);
}

void TestParent()
{
	TEST_HEAD;
	TreeType arr[] = "abd##eg###c#f##";
	TreeNode *root = CreatTree(arr, strlen(arr), '#');
	TreeNode *ret = Parent(root,root->rchild);
	printf("except %p actual %p \n",root, ret);
	TreeNode *ret1 = Parent(root,root->lchild->rchild);
	printf("except %p actual %p \n",root->lchild, ret1);
}

void TestPreOrderByLoop()
{
	TEST_HEAD;
	TreeType arr[] = "abd##eg###c#f##";
	TreeNode *root = CreatTree(arr, strlen(arr), '#');
	PreOrderByLoop(root);
}

void TestInOrderByLoop()
{
	TEST_HEAD;
	TreeType arr[] = "abd##eg###c#f##";
	TreeNode *root = CreatTree(arr, strlen(arr), '#');
	InOrderByLoop(root);
}

void TestPostOrderByLoop()
{
	TEST_HEAD;
	TreeType arr[] = "abd##eg###c#f##";
	TreeNode *root = CreatTree(arr, strlen(arr), '#');
	PostOrderByLoop(root);
}

void TestReBuild()
{
	TEST_HEAD;
	TreeType pre_order[] = "abdegcf";
	TreeType in_order[] = "dbgeacf";
	TreeNode *root = ReBuildTree(pre_order, strlen(pre_order), in_order, strlen(in_order));
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
}

int main()
{
	TestTreeInit();
	TestPreOrder();
	TestInOrder();
	TestPostOrder();
	TestCreatTree();
	//TestLevelOrder();
	TestTreeDestory();
	TestTreeClone();
	TestTreeSize();
	TestTreeLevelSize();
	TestTreeHeight();
	TestTreeFind();
	TestParent();
	TestPreOrderByLoop();
	TestInOrderByLoop();
	TestPostOrderByLoop();
	TestReBuild();
	return 0;
}
