#pragma once

#include <iostream>
#include <assert.h>

template<class K, class V>
struct TreeNode
{
	int _bf; // 平衡因子
	K _key;
	V _value;// 数据
	TreeNode<K,V>* _left;
	TreeNode<K,V>* _right;
	TreeNode<K,V>* _parent;

	TreeNode(const K& key, const V& value)
		: _bf(0)
		, _key(key)
		, _value(value)
		, _right(NULL)
		, _left(NULL)
		, _parent(NULL)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef TreeNode<K,V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		// 查找
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false; // key值重复
			}
		}

		// 插入
		Node* new_node = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_right = new_node;
			++parent->_bf;
		}
		else
		{
			parent->_left = new_node;
			--parent->_bf;
		}
		new_node->_parent = parent; //节点_parent指向parent

		// 更新平衡因子
		while (parent)
		{
			if (parent->_bf == 0)
			{
				return true;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				Node* ppNode = parent->_parent;
				if (ppNode != NULL)
				{
					if (ppNode->_left == parent)
					{
						--ppNode->_bf;
					}
					else
					{
						++ppNode->_bf;
					}
				}
				parent = ppNode;
			}
			else if (parent->_bf == 2 || parent->_bf == -2) /// ********
			{
				// 旋转
				if (parent->_bf == 2)
				{
					if (parent->_right->_bf == -1)
					{
						TreeRL(parent); //右左旋
						//parent->_right->_bf = 0;
					}
					else
					{
						TreeL(parent); // 左旋
						//parent->_left->_bf = 0;
					}
				}
				else
				{
					if (parent->_left->_bf == 1)
					{
						TreeLR(parent); // 左右旋
						//parent->_left->_bf = 0;
					}
					else
					{
						TreeR(parent); // 右旋
						//parent->_right->_bf = 0;
					}
				}
				parent->_bf = 0;
			}
			else
			{
				assert(false); // 树已经错误
			}
		}
		return false;
	}


protected:
	void TreeR(Node* parent) // 右旋
	{
		Node* pparent = parent->_parent;
		Node* parL = parent->_left;
		Node* parLuR = parL->_right;

		// 降parent链接parL的右子树
		parent->_left = parLuR;
		if (parLuR)
			parLuR->_parent = parent;

		// parent变成par的右子树
		parL->_right = parent;
		parent->_parent = parL;

		if (pparent == NULL)
		{
			_root = parL;
			parL->_parent = NULL; // 注意
			return;
		}
		
		// 旋转后根结点位置要链接到上面的子树
		parL->_parent = pparent; // 上接

		if (pparent->_left == parent) // 下接
			pparent->_left = parL;
		else
			pparent->_right = parL;
		//*****
	}

	void TreeL(Node* parent) // 左旋
	{
		Node* pparent = parent->_parent;
		Node* parR = parent->_right;
		Node* parRuL = parR->_left;

		parent->_right = parRuL;
		if (parRuL)
			parRuL->_parent = parent;

		parent->_parent = parR;
		parR->_left = parent;

		if (pparent == NULL)
		{
			_root = parR;
			parR->_parent = NULL;
			return;
		}

		parR->_parent = pparent;
		if (pparent->_right == parent)
		{
			pparent->_right = parR;
		}
		else
		{
			pparent->_left = parR;
		}
	}

	void TreeRL(Node* parent) // 右左旋
	{
		TreeR(parent->_right);
		TreeL(parent);
	}

	void TreeLR(Node* parent) // 左右旋
	{
		TreeL(parent->_left);
		TreeR(parent);
	}

private:
	Node* _root;
};

