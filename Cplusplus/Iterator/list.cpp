
#include <iostream>
#include <Windows.h>
#include <assert.h>
#include <string.h>
#include <vector>

template<class T>
struct ListNode
{
	T data;
	ListNode<T>* next;
	ListNode<T>* prev;
	ListNode(const T& value) :data(value), next(NULL), prev(NULL){}
};

// Ref == T&
template<class T, class Ref, class Ptr> // 定义三个类型是为了解决const 的迭代器
struct ListIterator
{
	typedef ListIterator<T, T&, T*> Self;
	typedef ListNode<T> Node;


	ListIterator(Node* p = NULL) :_pNode(p)
	{}

	ListIterator(const Self& it)
	{
		_pNode = it._pNode;
	}

	Ref operator*()
	{
		return _pNode->data;
	}

	Ptr operator->()
	{
		return &(operator*());
		//return &(_pNode->data);
	}

	Self& operator++()
	{
		_pNode = _pNode->next;
		return *this;
	}

	Self operator++(int)
	{
		Self tmp(*this);
		++(*this);
		return tmp;
	}

	Self& operator--()
	{
		_pNode = _pNode->prev;
		return *this;
	}

	Self operator--(int)
	{
		Self tmp(*this);
		--(*this);
		return tmp;
	}

	bool operator==(const Self& it)
	{
		return _pNode == it._pNode;
	}
	bool operator!=(const Self& it)
	{
		return _pNode != it._pNode;
	}

	Node* _pNode;
};



template<class T>
class MyList
{
	typedef ListNode<T> Node;
	
public:
	typedef ListIterator<T, T&, T*> Iterator; // 迭代器
	typedef const ListIterator<T, T&, T*> ConIterator; // const迭代器

	MyList() : head(new Node(T()))
	{
		head->next = head;
		head->prev = head;
	}

	MyList(const MyList<T>& l) :head(new Node(T()))
	{
		Node* cur = l.head->next;
		while (cur != head)
		{
			Node* new_node = new Node(cur->data);
			new_node->prev = head->prev;
			new_node->prev->next = new_node;

			new_node->next = head;
			head->prev = new_node;
			cur = cur->next;
		}
	}

	MyList<T>& operator=(const MyList<T>& l)
	{
		if (this != &l)
		{
			Clear();
			Node* cur = l.head->next;
			while (cur != head)
			{
				Node* new_node = new Node(cur->data);
				new_node->prev = head->prev;
				new_node->prev->next = new_node;

				new_node->next = head;
				head->prev = new_node;
				cur = cur->next;
			}
		}
		return *this;
	}

	void PushBack(const T& value)
	{
		Node* new_node = new Node(value);
		Node* pre = head->prev;
		pre->next = new_node;
		new_node->prev = pre;

		head->prev = new_node;
		new_node->next = head;
	}

	void PopBack()
	{
		Erase(--End());
	}

	// 删除要返回原来的位置
	// 删除迭代器失效是删除后再++it会访问越界，因为已经释放

	// 插入返回插入后的节点位置，
	// 插入迭代器失效是跳过插入后面的那个元素
	Iterator Insert(Iterator pos, const T& value)
	{
		Node* new_node = new Node(value);

		Node* pre = pos._pNode->prev;
		pre->next = new_node;
		new_node->prev = pre;

		new_node->next = pos._pNode;
		pos._pNode->prev = new_node;
		return new_node;
	}

	Iterator Erase(Iterator pos)
	{
		assert(pos._pNode);
		Node* pre = pos._pNode->prev;
		Node* nex = pos._pNode->next;
		
		pre->next = nex;
		nex->prev = pre;

		delete pos._pNode;
		return nex;
	}


	~MyList()
	{
		Clear();
		delete head;
		head = NULL;
	}

	void Clear()
	{
		Node* cur = head->next;
		while (cur != head)
		{
			head->next = cur->next;
			cur->next->prev = head;
			delete cur;
		}
	}

	Iterator Begin()
	{
		return Iterator(head->next);
	}

	Iterator End()
	{
		return Iterator(head);
	}

private:
	Node* head;
};


int main()
{
	MyList<int> list;
	
	list.PushBack(1);
	MyList<int>::Iterator j = list.Begin();
	list.Insert(j, 0);
	MyList<int>::Iterator k = list.Begin();
	list.Erase(k);
	MyList<int>::Iterator i = list.Begin();
	
	while (i != list.End())
	{
		std::cout << *i << " ";
		++i;
	}


	// 一定要注意
	/*void Print()
	{
		Vector<int>::Iterator it = v.Begin();
		while (it != v.End())
		{
			if (*it == 0)
			{
				it = v.Erase(it);
			}
			else
			{
				++it;
			}
		}
	}*/
	system("pause");
	return 0;
}