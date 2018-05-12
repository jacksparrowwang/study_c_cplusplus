#include <iostream>
using namespace std;
#include <assert.h>
#include <string>
#include "Vector.h"


template<class T>
Vector<T>::Vector(const Vector<T>& v)
{
    size_t size = v.Size();    
    start = new T[size];
    for (size_t i = 0; i < size; ++i)
    {
        *(start+i) = *(v.start+i);
    }
    finish = start + size;
    endofstorage = start + size;
}

// *this = v
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
    if (this != &v)
    {
        if (Size() >= v.Size())
        {
            for (size_t i = 0; i < Size(); ++i)
            {
                *(start+i) = *(v.start+i);
            }
        }
        else
        {
            Vector<T>* tmp = new Vector<T>(v);
            start = tmp->start;
            finish = start + v.Size();
            endofstorage = start + v.Size();
        }
    }
    return *this;
}

template<class T>
void Vector<T>::Insert(size_t pos, const T& value)
{
    assert(pos <= Size());
    if (Size() >= Capacity())
    {
        Expand(Capacity()*2);
    }
    for (size_t i = Size(); i > pos; --i)
    {
        *(start + i) = *(start + i - 1);
    }
    *(start + pos) = value;
    ++finish;
}

template<class T>
void Vector<T>::Push(const T& value)
{
    Insert(Size(), value);
}

template<class T>
void Vector<T>::Pop()
{
    if (!IsEmpty())
    {
        --finish;
    }
}

template<class T>
size_t Vector<T>::Find(const T& to_find)
{
    for (size_t i = 0; i < Size(); ++i)
    {
        if (*(start+i) == to_find)
        {
            return i;
        }
    }
    return (size_t)-1;
}

template<class T>
T& Vector<T>::FindBack()
{
    return *(finish - 1);
}

#if 0
void TestPush()
{
    Vector<int> v;
    v.Push(1);
    v.Push(2);
    v.Push(3);
    v.Push(4);
    v.Print();

    Vector<string> v1;
    v1.Push("11111");
    v1.Push("22222");
    v1.Print();
}

void TestPop()
{
    Vector<int> v;
    v.Push(1);
    v.Push(2);
    v.Push(3);
    v.Push(4);
    v.Print();
    v.Pop();
    v.Print();

    Vector<string> v1;
    v1.Push("11111");
    v1.Push("22222");
    v1.Pop();
    v1.Print();
}

void TestCopy()
{
    Vector<int> v;
    v.Push(1);
    v.Push(2);
    v.Push(3);
    v.Print();
    Vector<int> v1(v);
    v1.Push(5);
    v1.Print();

    v = v1;
    v.Print();
}


int main()
{
    TestPush();
    TestPop();
    TestCopy();
    return 0;
}
#endif
