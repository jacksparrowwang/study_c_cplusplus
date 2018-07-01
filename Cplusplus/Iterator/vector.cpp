#include <iostream>
#include <Windows.h>
#include <assert.h>
#include <vector>

template<class T>
class MyVector
{
public:
	typedef T* Iterator;
	typedef const T* ConIterator;

	// 构造
	MyVector() :start(NULL), finish(NULL), endofstorage(NULL)
	{}

	// 析构
	~MyVector()
	{
		delete[] start;
		start = finish = endofstorage = NULL;
	}
	
	// 拷贝构造
	MyVector(const MyVector<T>& v)
	{
		start = new T[v.Size()];
		for (int i = 0; i < (int)v.Size(); ++i)
		{
			*(start + i) = *(v.start + i);
		}
		finish = start + v.Size();
		endofstorage = start + v.Capacity();
	}

	// this = v ，赋值运算符重载
	MyVector<int>& operator=(const MyVector<int>& v)
	{
		if (&v != this)
		{
			delete[] start;
			start = new T[v.Size()];
			for (int i = 0; i < (int)v.Size(); ++i)
			{
				*(start + i) = *(v.start + i);
			}
			finish = start + v.Size();
			endofstorage = finish;

		}
		return *this;
	}

	/////////////////////////////
	// vector 相关接口
	/////////////////////////////
	void PushBack(const T& value)
	{
		if (finish == endofstorage)
		{
			if (endofstorage == NULL)
			{
				start = new T[3];
				finish = start; // 这里为初始的位置
				endofstorage = start + 3; // 注意这里的endofstorage要是最后的边界
			}
			else
			{
				Expand(Capacity() * 2);
			}
		}
		*finish = value;
		++finish;
	}

	void PopBack()
	{
		if (finish == start)
		{
			return;
		}
		--finish;
	}

	Iterator Erase(ConIterator position) //返回值防止迭代器失效
	{
		assert(position < End() && position >= Begin());
		size_t i = position - Begin();
		for (; i < Size(); ++i)
		{
			*(start + i) = *(start + i + 1);
		}
		--finish;
		return (Iterator)position; // 注意迭代器失效问题
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

	Iterator Insert(Iterator position, const T& value)
	{

		assert(position < End() && position >= Begin());
		size_t off = position - start;
		if (finish == endofstorage)
		{
			Expand(Capacity() * 2);
		}

		position = off + start; // 注意跌掉器失效
		for (Iterator i = End(); i != position; --i)
		{
			*i = *(i - 1);
		}
		*position = value;
		++finish;
		return position;
	}

	void Resize(size_t n, T x = T())
	{
		if (n <= Size())
		{
			finish = start + n;
		}
		if (n > Capacity())
		{
			Expand(n);
		}
		int i = 0;
		while (finish + i != endofstorage)
		{
			*(finish + i) = x;
			++i;
		}
		finish = endofstorage;
	}

	void Reserve(size_t n)
	{
		if (n > Capacity())
		{
			Expand(n);
		}
	}

	void Assign(size_t n, const T &val = T())
	{
		if (n>Size())
		{
			if (n>Capacity())
			{
				Expand(n);
			}
			_finish = _start + n;
		}
		size_t i = 0;
		for (i = 0; i<n; ++i)
		{
			_start[i] = val;
		}
	}

	T& operator[](size_t position)
	{
		assert(position < Size());
		return start[position];
	}

	const T& operator[](size_t position) const
	{
		assert(position < Size());
		return start[position];
	}


	///////////////////////////////
	// 迭代器
	///////////////////////////////
	// ++i
	Iterator& operator++()
	{
		return *(this += 1);
	}

	Iterator operator++(int) //后置
	{
		Iterator tmp = this;
		this += 1;
		return *tmp;
	}

	Iterator& operator--()
	{
		return *(this-=1)
	}

	Iterator operator--(int)
	{
		Iterator tmp = this;
		this -= 1;
		return *tmp;
	}

	Iterator& operator->()
	{
		return this;
	}

	Iterator& operator*()
	{
		return *this;
	}

	Iterator Begin()
	{
		return start;
	}

	// 后面的const是为防止const对象能调动Begin函数
	// 前面的const是为了防止返回值，通过返回值来修改const修饰的对象
	/*const Iterator Begin() const 
	{
		return start;
	}*/
	// 库中有两个迭代器 一个为const_iterator,另一个是iterator
	ConIterator Begin() const
	{
		return start;
	}

	Iterator End()
	{
		return finish;
	}

	ConIterator End() const
	{
		return finish;
	}

	const size_t Size() const
	{
		return finish - start;
	}

	const size_t Capacity() const
	{
		return endofstorage - start;
	}

protected:
	Iterator start;
	Iterator finish;
	Iterator endofstorage;

	// 不给外部进行访问
	void Expand(size_t n)
	{
		if (n > Capacity())
		{
			Iterator tmp = new T[n];
			size_t size = Size();
			for (size_t i = 0; i < size; ++i)
			{
				*(tmp + i) = *(start + i);
			}
			delete[] start;
			start = tmp;
			finish = start + size;
			endofstorage = start + n;
		}
	}
};


////////////////////////////////////////////////
// 以下是测试代码
////////////////////////////////////////////////

#define HEAD printf("\n=========================%s====================\n",__FUNCTION__)

void Print(const MyVector<int>& v1)
{
	MyVector<int>::ConIterator it = v1.Begin();
	for (; it != v1.End(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void InitCopyOperatorTest()
{
	HEAD;
	MyVector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	Print(v1);
	MyVector<int> v2;
	v2 = v1;
	Print(v2);
	MyVector<int> v3 = v2;
	Print(v3);

}

void PushTest()
{
	HEAD;
	MyVector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);
	Print(v1);
}

void PopTest()
{
	HEAD;
	MyVector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PopBack();
	Print(v1);
	v1.PopBack();
	v1.PopBack();
	v1.PopBack();
	Print(v1);
}

void EraseInsertTest()
{
	HEAD;
	MyVector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);
	Print(v1);
	v1.Insert(v1.Begin()+1, 10);
	Print(v1);
	v1.Erase(v1.Begin() + 4);
	Print(v1);
}

void ResizeReseveTest()
{
	HEAD;
	MyVector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);
	Print(v1);
	v1.Resize(10, 8);
	Print(v1);
	v1.Reserve(15);
	std::cout << v1.Size() << std::endl;
	std::cout << v1.Capacity() << std::endl;
}


void Print1(const std::vector<int>& v1)
{
	std::vector<int>::const_iterator it = v1.begin();
	for (; it != v1.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void Test1()
{
	std::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	Print1(v1);
}
//int main()
//{
//	InitCopyOperatorTest();
//	PushTest();
//	PopTest();
//	EraseInsertTest();
//	ResizeReseveTest();
//	Test1();
//	system("pause");
//	return 0;
//}