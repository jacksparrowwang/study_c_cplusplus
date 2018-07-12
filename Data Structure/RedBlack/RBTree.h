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
    RBTree():root(NULL){}

    bool Insert(const K& key, const V& value)
    {
        if (root == NULL)
        {
            root = new Node(key, value);
            root->color = BLACK;
            return true;
        }

        // 找到要插入的位置
        Node* cur = root;
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

        // 更新颜色
    }
private:
    Node* root;
};
