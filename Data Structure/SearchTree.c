#include"SearchTree.h"
#include<windows.h>

void DestroyTreeNode(SearchTreeNode *delete)
{
	if (delete == NULL)
	{
		return;
	}
	free(delete);
}

// 初始化
void SearchTreeInit(SearchTreeNode **root)
{
	if (root == NULL)
	{
		return;
	}
	*root = NULL;
}

// 创建树节点
SearchTreeNode *CreatSearchTree(SearchTreeType value)
{
	SearchTreeNode *new_node = (SearchTreeNode *)malloc(sizeof(SearchTreeNode));
	new_node->data = value;
	new_node->lchild = NULL;
	new_node->rchild = NULL;
	return new_node;
}

#if 1
// 二叉搜索树的插入（非递归）
void SearchTreeInsert1(SearchTreeNode **root, SearchTreeType value)
{
	if (root == NULL)
	{
		return;
	}
	//当树为空树。
	if (*root == NULL)
	{
		*root = CreatSearchTree(value);
		return;
	}
	SearchTreeNode *parent = NULL;
	SearchTreeNode *cur = *root;
	// 先找到要插入的位置。并且需要记录当前节点的父节点。
	while (cur != NULL)
	{
		if (cur->data > value)
		{
			parent = cur;
			cur = cur->lchild;
		}
		else if (cur->data < value)
		{
			parent = cur;
			cur = cur->rchild;
		}
		else
		{
			return;
		}
	}
	// 判断在当前节点的父节点的左孩子还是右孩子插入。
	if (parent->data > value)
	{
		parent->lchild = CreatSearchTree(value);
	}
	else
	{
		parent->rchild = CreatSearchTree(value);
	}
}


// 查找树中的某个元素的位置(二叉搜索树)（非递归）
SearchTreeNode *SearchTreeFind1(SearchTreeNode *root, SearchTreeType to_find)
{
	if (root == NULL)
	{
		return NULL;
	}
	SearchTreeNode *cur = root;
	while (cur != NULL)
	{
		if (cur->data > to_find)
		{
			cur = cur->lchild;
		}
		else if (cur->data < to_find)
		{
			cur = cur->rchild;
		}
		else
		{
			return cur;
		}
	}
	return NULL;
}

// 删除树中某个元素（非递归）
void SearchTreeRemove1(SearchTreeNode **root, SearchTreeType value)
{
	if (root == NULL)
	{
		return;
	}
	if (*root == NULL)
	{
		return;
	}
	SearchTreeNode *to_delete = *root;
	SearchTreeNode *parent = NULL;
	// 1.循环找到对应元素的位置。
	while (to_delete != NULL)
	{
		if (to_delete->data > value)
		{
			parent = to_delete;
			to_delete = to_delete->lchild;
		}
		else if (to_delete->data < value)
		{
			parent = to_delete;
			to_delete = to_delete->rchild;
		}
		else
		{
			break;
		}
	}
	if (to_delete != NULL)
	{
		// 2.如果有多个节点
		
		if (to_delete->lchild == NULL && to_delete->rchild == NULL)
		{
			//  只有一个根节点。
			if ((*root)->data == value)
			{
				DestroyTreeNode(to_delete);
				*root = NULL;
				return;
			}
			// 是树的叶子节点。
			// 这个时候parent->data一定不会等于value
			if (parent->data > value)
			{
				parent->lchild = NULL;
				DestroyTreeNode(to_delete);
			}
			else
			{
				parent->rchild = NULL;
				DestroyTreeNode(to_delete);
			}
		}
		else if (to_delete->lchild != NULL && to_delete->rchild == NULL)
		{
			//   只有左子树.
			if (parent->lchild == to_delete)
			{
				parent->lchild = to_delete->lchild;
				DestroyTreeNode(to_delete);
			}
			else
			{
				parent->rchild = to_delete->lchild;
				DestroyTreeNode(to_delete);
			}
		}
		else if (to_delete->lchild == NULL && to_delete->rchild != NULL)
		{
			//   只有右子树
			if (parent->lchild == to_delete)
			{
				parent->lchild = to_delete->rchild;
				DestroyTreeNode(to_delete);
			}
			else
			{
				parent->rchild = to_delete->rchild;
				DestroyTreeNode(to_delete);
			}
		}
		else
		{
			//   左右子树都有
			SearchTreeNode *cur = to_delete->rchild;
			parent = to_delete;
			while (cur->lchild != NULL)
			{
				parent = cur;
				cur = cur->lchild;
			}
			to_delete->data = cur->data;
			if (parent->rchild == cur)
			{
				parent->rchild = cur->rchild;
				DestroyTreeNode(cur);
			}
			else
			{
				parent->lchild = NULL;
				DestroyTreeNode(cur);
			}
		}
	}
	return;
}
#endif


// 二叉树的插入递归插入
void SearchTreeInsert(SearchTreeNode **root, SearchTreeType value)
{
	if (root == NULL)
	{
		return;
	}
	if (*root == NULL)
	{
		*root = CreatSearchTree(value);
		return;
	}
	if ((*root)->data > value)
	{
		SearchTreeInsert(&(*root)->lchild, value);
	}
	else
	{
		SearchTreeInsert(&(*root)->rchild, value);
	}
	return;
}

// 查找树中的某个元素的位置(递归查找)
SearchTreeNode *SearchTreeFind(SearchTreeNode *root, SearchTreeType to_find)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->data == to_find)
	{
		return root;
	}
	SearchTreeNode *lchild = SearchTreeFind(root->lchild,to_find);
	SearchTreeNode *rchild = SearchTreeFind(root->rchild, to_find);
	if (lchild != NULL)
	{
		return lchild;
	}
	if (rchild != NULL)
	{
		return rchild;
	}
	return NULL;
}

// 删除树中某个元素
void SearchTreeRemove(SearchTreeNode **root, SearchTreeType value)
{
	if (root == NULL || *root == NULL)
	{
		return;
	}
	// 1.先查找出要删除的元素
	if (value < (*root)->data)
	{
		SearchTreeRemove(&(*root)->lchild, value);
	}
	else if (value >(*root)->data)
	{
		SearchTreeRemove(&(*root)->rchild, value);
	}
	else
	{
		// 2.删除分为4个步骤
		SearchTreeNode *remove = *root;
		// a）只有一个节点或者叶子节点
		if (remove->lchild == NULL && remove->rchild == NULL)
		{
			*root = NULL;
			free(remove);
			return;
		}
		// b）只有左子树
		else if (remove->lchild != NULL && remove->rchild == NULL)
		{
			*root = remove->lchild;
			free(remove);
			return;
		}
		// c）只有右子树
		else if (remove->lchild == NULL && remove->rchild != NULL)
		{
			*root = remove->rchild;
			free(remove);
			return;
		}
		// d）左右子树都有
		else
		{
			SearchTreeNode *min = remove->rchild;
			while (min->lchild != NULL)
			{
				min = min->lchild;
			}
			remove->data = min->data;
			SearchTreeRemove(&remove->rchild, min->data);
			return;
		}
	}
}

////////////////////////
#if 1
void PreOrder(SearchTreeNode *root)
{
	if (root == NULL)
	{
		return;
	}
	printf("%c", root->data);
	PreOrder(root->lchild);
	PreOrder(root->rchild);
}

void InOrder(SearchTreeNode *root)
{
	if (root == NULL)
	{
		return;
	}
	InOrder(root->lchild);
	printf("%c", root->data);
	InOrder(root->rchild);
}

void TestSearchTreeInsert()
{
	SearchTreeNode *root = NULL;
	SearchTreeInit(&root);
	SearchTreeInsert(&root,'b');
	SearchTreeInsert(&root,'a');
	SearchTreeInsert(&root,'c');
	SearchTreeInsert(&root,'d');
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
}

void TestSearchTreeFind()
{
	SearchTreeNode *root = NULL;
	SearchTreeInit(&root);
	SearchTreeInsert(&root, 'b');
	SearchTreeInsert(&root, 'a');
	SearchTreeInsert(&root, 'c');
	SearchTreeInsert(&root, 'd');
	SearchTreeNode *ret = SearchTreeFind(root, 'c');
	SearchTreeNode *ret1 = SearchTreeFind(root, 'g');
	printf("%p %c  %p\n", ret,ret->data, ret1);
}

void TestSearchTreeRemove()
{
	SearchTreeNode *root = NULL;
	SearchTreeInit(&root);
	SearchTreeInsert(&root, 'b');
	SearchTreeInsert(&root, 'a');
	SearchTreeInsert(&root, 'f');
	SearchTreeInsert(&root, 'd');
	SearchTreeInsert(&root, 'g');
	SearchTreeInsert(&root, 'h');
	SearchTreeInsert(&root, 'e');
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	SearchTreeRemove(&root,'d');
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	SearchTreeRemove(&root, 'a');
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
}

int main()
{
	TestSearchTreeInsert();
	printf("\n");
	printf("\n");
	TestSearchTreeFind();
	printf("\n");
	printf("\n");
	TestSearchTreeRemove();
	system("pause");
	return 0;
}
#endif