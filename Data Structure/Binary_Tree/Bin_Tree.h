#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#include"SeqQueue.h"

#include"SeqStack.h"

typedef char TreeType;

typedef struct TreeNode{
	TreeType data;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
}TreeNode;

// 二叉树的初始化。
void TreeInit(TreeNode **root);

// 先序遍历。
void PreOrder(TreeNode *root);

// 中序遍历。
void InOrder(TreeNode *root);

// 后序遍历。
void PostOrder(TreeNode *root);

// 层序遍历。
//void LevelOrder(TreeNode *root);

// 创建一颗树。
TreeNode *CreatTree(TreeType arr[], size_t size, TreeType null_node);

// 销毁树。
void TreeDestory(TreeNode **root);

// 树的深拷贝。
TreeNode *TreeClone(TreeNode *root);

// 树节点的个数。
size_t TreeSize(TreeNode *root);

// 树的叶子节点。
size_t TreeLevelSize(TreeNode *root);

// 树的高度。
size_t TreeHeight(TreeNode *root);

// 给定值查找对应节点的位置
TreeNode *TreeFind(TreeNode *root, TreeType to_find);

// 求给定节点的左孩子节点位置
TreeNode *LChild(TreeNode *node);

// 求取给定节点的右孩子节点的位置
TreeNode *RChild(TreeNode *node);

// 给出节点求出该节点的父节点。
TreeNode *Parent(TreeNode *root,TreeNode *node);

// 先序遍历（非递归）采用的是根右左入栈
void PreOrderByLoop(TreeNode *root);

// 中序遍历（非递归）采用的是根到左再右入栈
void InOrderByLoop(TreeNode *root);

// 后序遍历（非递归）采用的是根左右边入栈
void PostOrderByLoop(TreeNode *root);

// 镜像树
void TreeMirror(TreeNode *root);

// 是否是完全树
void IsCompleteTree(TreeNode *root);

// 给出先序遍历和中序遍历还原二叉树
TreeNode *ReBuildTree(TreeType per_order[], size_t pre_order_size, TreeType in_order[], size_t in_order_size);
