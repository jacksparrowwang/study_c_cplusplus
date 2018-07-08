#pragma once

#include <queue>
#include <vector>

template<class T>
struct HuffmanTreeNode
{
	T data;
	HuffmanTreeNode<T>* left;
	HuffmanTreeNode<T>* right;

	HuffmanTreeNode(const T& data) // 节点的构造函数
		:data(data), left(NULL), right(NULL)
	{}
};

template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> TreeNode; // 给节点重新命名

	struct CompareTreeNode // 提供一个内部类来实现一个仿函数，用来给优先级队列提供比较
	{
		bool operator()(TreeNode* l, TreeNode* r)
		{
			return l->data > r->data;
		}
	};

public:

	HuffmanTree(){};

	HuffmanTree(T* arr, size_t size, const T& invalid)// 这里的arr是一个数组的hash表
	{
		std::priority_queue<TreeNode*, std::vector<TreeNode*>, CompareTreeNode> minheap; //默认为大堆 小于号
		for (size_t i = 0; i < size; ++i)
		{
			if (arr[i] != invalid)
			minheap.push(new TreeNode(arr[i])); // 先建立一个小堆
		}
		while (minheap.size() > 1) // 注意 
		{
			// 这里怎么才能把抛回去的父结点与新取出的最小节点区分开
			// 用节点的指针
			TreeNode* top1 = minheap.top(); 
			minheap.pop();
			TreeNode* top2 = minheap.top();
			minheap.pop();
			TreeNode* parent = new TreeNode(top2->data + top1->data);
			parent->left = top1;
			parent->right = top2;
			minheap.push(parent); //最后永远会剩余一个
		}
		root = minheap.top();
	}

	TreeNode* GetRoot() // 外部提供访问root
	{
		return root;
	}

	~HuffmanTree()
	{
		Destory(root);
		root = NULL;
	}

	void Destory(TreeNode* root) //析构时候的递归函数
	{
		if (root == NULL)
		{
			return;
		}
		Destory(root->left);
		Destory(root->right);
		delete root;
	}


private:
	HuffmanTree(const HuffmanTree<T>& h);
	HuffmanTree<T> operator=(const HuffmanTree<T>& h);

protected:
	TreeNode* root;
};

//void TestHuffmanTree()
//{
//	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	HuffmanTree<int> hm(a, sizeof(a) / sizeof(int), 0);
//}
