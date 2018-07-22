#pragma once

#include <iostream>

enum Color
{
    RED,
    BLACK
};

template<class K, class V>
struct RBTreeNode
{
    K key;
    V value;
    RBTreeNode<K, V>* left;
    RBTreeNode<K, V>* right;
    RBTreeNode<K, V>* parent;
    Color color;

    RBTreeNode(const K& _key, const V& _value)
        :key(_key),
        value(_value),
        left(NULL),
        right(NULL),
        parent(NULL),
        color(RED)
    {}
};

template<class K, class V>
class RBTree
{
    typedef RBTreeNode<K, V> Node;
public:
    RBTree():_root(NULL){}

    bool Insert(const K& key, const V& value)
    {
        if (_root == NULL)
        {
            _root = new Node(key, value);
            _root->color = BLACK;
            return true;
        }

        // 找到要插入的位置
        Node* cur = _root;
        Node* parent = NULL;
        while (cur != NULL)
        {
            if (cur->key > key)
            {
                parent = cur;
                cur = cur->left;
            }
            else if (cur->key < key)
            {
                parent = cur;
                cur = cur->right;
            }
            else
            {
                return false;
            }
        }

        // 插入
        cur = new Node(key, value);
        if (parent->key > key)
        {
            parent->left = cur;
            cur->parent = parent; // 插入的节点的parent指向上它的父节点
        }
        else
        {
            parent->right = cur;
            cur->parent = parent;
        }

        // 更新元素
		while (parent && parent->_colour == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				// 1.存在且为红
				// 2.不存在，存在且为黑
				if (uncle && uncle->_colour == RED)
				{
					parent->_colour = uncle->_colour = BLACK;
					grandfather->_colour = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if(parent->_right == cur)
					{
						RotateL(parent);

						swap(cur, parent);
					}

					RotateR(grandfather);
					parent->_colour = BLACK;
					grandfather->_colour = RED;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_colour == RED)
				{
					parent->_colour = BLACK;
					uncle->_colour = BLACK;
					grandfather->_colour = RED;

					// 继续往上更新
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 不存在 / 存在且为黑
				{
					if(cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}

					RotateL(grandfather);
					parent->_colour = BLACK;
					grandfather->_colour = RED;
				}
			}
		}

		_root->_colour = BLACK;

		return true;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (_root == parent)
		{
			_root =  subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_right == parent)
			{
				ppNode->_right = subL;
			}
			else
			{
				ppNode->_left = subL;
			}

			subL->_parent = ppNode;
		}
	}


	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;

		parent->_right = subRL;
		if(subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (parent == _root)
		{
			_root = subR;
			_root->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}

			subR->_parent = ppNode;
		}

	}
private:
    Node* _root;
};
