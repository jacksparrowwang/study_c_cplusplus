#include"thread_tree.h"

ThreadNode *CreatThreadNode(ThreadType value)
{
	ThreadNode *root = (ThreadNode *)malloc(sizeof(ThreadNode));
	if (root == NULL)
	{
		return NULL;
	}
	root->data = value;
	root->left = NULL;
	root->right = NULL;
	root->lflag = CHILD;
	root->rflag = CHILD;
	return root;
}

ThreadNode *_ThreadTreeCreat(ThreadType arr[], size_t size, size_t *index, ThreadType nullnode)
{
	if (*index >= size || index == NULL)
	{
		return NULL;
	}
	if (arr[*index] == nullnode)
	{
		return NULL;
	}
	ThreadNode *root = CreatTreadNode(arr[*index]);
	++(*index);
	root->left = _ThreadTreeCreat(arr, size, index, nullnode);
	++(*index);
	root->right = _ThreadTreeCreat(arr, size, index, nullnode);
	return root;
}

// 创建树,用二叉树先序结果带空指针域创建 nullnode 表示NULL
ThreadNode *ThreadTreeCreat(ThreadType arr[], size_t size, ThreadType nullnode)
{
	size_t index = 0;
	return _ThreadTreeCreat(arr, size, &index, nullnode);
}

// 先序线索化
void _PreThreading(ThreadNode *root, ThreadNode **prev)
{
	if (root == NULL || prev == NULL)
	{
		return;
	}
	// 1 如果当前根结点左子树为空，就把left指针指向前驱
	if (root->left == NULL)
	{
		root->left = *prev;
		root->lflag = THREAD;
	}
	// 2 如果当前根结点的前驱的右子树为空，就把前驱的right指针指向当前根结点
	if ((*prev)->right == NULL)
	{
		(*prev)->right = root;
		(*prev)->right = THREAD;
	}
	// 更新prev，让prev把上一个记录下来
	*prev = root;
	if (root->lflag == CHILD)
	{
		// 处理左子树
		_PreThreading(root->left, prev);
	}
	if (root->rflag == CHILD)
	{
		// 处理右子树
		_PreThreading(root->right, prev);
	}
}

// 先序线索化
void PreThreading(ThreadNode *root)
{
	ThreadNode *prev = NULL;
	_PreThreading(root, &prev);
}

// 先序线索化遍历。(相当于链表)
void PreOrderByThreading(ThreadNode *root)
{
	if (root == NULL)
	{
		return;
	}
	ThreadNode *cur = root;
	while (cur != NULL)
	{
		// cur的lflag等于CHILD，不是线索，打印。
		while (cur->lflag == CHILD)
		{
			printf("%c ", cur->data);
			cur = cur->left;
		}
		printf("%c ", cur->data);
		// cur的right指针指向后继还是右子树都可以
		cur = cur->right;
	}
}

// 中序线索化
void _InThreading(ThreadNode *root, ThreadNode **prev)
{
	if (root == NULL || prev == NULL)
	{
		return;
	}
	// 先递归找到左子树中最左侧的节点
	if (root->lflag == CHILD)
	{
		_InThreading(root->left, prev);
	}
	if (root->left == NULL)
	{
		root->left = (*prev);
		root->lflag = THREAD;
	}
	// 这里的*prev刚开始是NULL,所以要加以判断
	if (*prev != NULL && (*prev)->right == NULL)
	{
		(*prev)->right = root;
		(*prev)->rflag = THREAD;
	}
	*prev = root;
	if (root->rflag == CHIDL)
	{
		_InThreading(root->right, prev);
	}
	
}

// 中序线索化
void InThreading(ThreadNode *root)
{
	ThreadNode *prev = NULL;
	_InThreading(root, &prev);
}

// 中序线索化遍历。(相当于链表)
void InOrderByThreading(ThreadNode *root)
{
	if (root == NULL)
	{
		return;
	}
	ThreadNode *cur = root;
	// 先遍历到最左节点。并且不能访问
	while (cur != NULL && cur->lflag == CHILD)
	{
		cur = cur->left;
	}
	while (cur != NULL)
	{
		// 先打印最左节点
		printf("%c ", cur->data);
		if (cur->rflag == THREAD)
		{
			cur = cur->right;
		}
		else 
		{
			// cur的right是子树
			cur = cur->right;
			while (cur != NULL && cur->lflag == CHILD)
			{
				cur = cur->left;
			}
		}
	}
	return;
}

void _PostThreading(ThreadNode *root, ThreadNode **prev)
{
	if (root == NULL || prev == NULL)
	{
		return;
	}
	// 先递归找到左子树中最左侧的节点
	if (root->lflag == CHILD)
	{
		_PostThreading(root->left, prev);
	}
	if (root->rflag == CHIDL)
	{
		_PostThreading(root->right, prev);
	}
	
	if (root->left == NULL)
	{
		root->left = (*prev);
		root->lflag = THREAD;
	}
	// 这里的*prev刚开始是NULL,所以要加以判断
	if (*prev != NULL && (*prev)->right == NULL)
	{
		(*prev)->right = root;
		(*prev)->rflag = THREAD;
	}
	*prev = root;
}

// 后序线索化
void PostThreading(ThreadNode *root)
{
	ThreadNode *prev = NULL;
	_PostThreading(root);
}


//////////////////////////
//以下为测试代码
//////////////////////////


int main()
{
	return 0;
}
