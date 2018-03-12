#pragma once

#include<stdio.h>

typedef char SearchTreeType;

typedef struct SearchTreeNode{
	SearchTreeType data;
	struct SearchTreeNode *lchild;
	struct SearchTreeNode *rchild;
}SearchTreeNode;

// 初始化树
void SearchTreeInit(SearchTreeNode **root);

// 二叉树的插入
void SearchTreeInsert(SearchTreeNode **root, SearchTreeType value);

// 查找树中的某个元素的位置
SearchTreeNode *SearchTreeFind(SearchTreeNode *root, SearchTreeType to_find);

// 删除树中某个元素
void SearchTreeRemove(SearchTreeNode **root, SearchTreeType value);