#include "Vector.h"
#include <iostream>
#include <string.h>

Vector::Vector(const Vector& v)
{
    if (v.first != v.finish)
    {
        first = new DataType[v.Size()];
        memcpy(first, v.first, v.Size()*sizeof(DataType));
        finish  = first + v.Size();
        endofstorage = first + v.Size();
    }
    else
    {
        first = finish = endofstorage = NULL;
    }
}

Vector::~Vector()
{
    delete[] first;
    first = finish = endofstorage = NULL;
}


Vector& Vector::operator=(const Vector& v)
{
    if (first == v.first)
    {
        return *this;
    }
    delete [] first;
    first  = new DataType[v.Size()];
    memcpy(first, v.first, v.Size()*sizeof(DataType));
    finish = first + v.Size();
    endofstorage = first + v.Size();
    return *this;
}

void Vector::Expands(size_t n)
{
    if (n > Capacity())
    {
        size_t len = Size();
        DataType* start = new DataType[n]; 
        memcpy(start, first, len*sizeof(DataType));
        delete [] first;
        first = start;
        finish = first + len;
        endofstorage = first + n;
    }
}

DataType* Vector::PushBack(DataType value)
{
    if (first == NULL)
    {
        first = new DataType[1];
        finish = first;
        endofstorage = first + 1;
    }
    if (Size() > Capacity())
    {
        Expands(Capacity()*2);
    }
    *finish = value;
    ++finish;
    return finish - 1;
}

void Vector::PopBack()
{
    if (Size() != 0)
    {
        --finish;
    }
}

void Vector::Insert(size_t pos, DataType value)
{
    if (pos > Size())
    {
        return;
    }
    for (size_t i = Size(); i > pos; --i)
    {
        *(first + i) = *(first + i - 1);
    }
    *(first + pos) = value;
    ++finish;
}

void Vector::Erase(size_t pos)
{
    if (pos > Size())
    {
        return;
    }
    for (size_t i = pos; i < Size(); ++i)
    {
        *(first + i) = *(first + i + 1);
    }
    --finish;
}

size_t Vector::Find(DataType value)
{
    for (size_t i = 0; i < Size(); i++)
    {
        if(*(first + i) == value)
        {
            return i;
        }
    }
    return (size_t)-1;
}

void Vector::Reserve(size_t n)
{
    Expands(n);
}

//////////////////////////////////////////
//测试代码
//////////////////////////////////////////

#define TESTHEAD printf("\n==============%s==============\n", __FUNCTION__)

#include <stdio.h>
void Vector::PrintVector()
{
    for (size_t i = 0; i < Size(); ++i)
    {
        printf("%d ", *(first+i));
    }
    printf("\n");
}

void TestPushBack()
{
    TESTHEAD;
    Vector v1;
    v1.PushBack(2);
    v1.PushBack(2);
    v1.PushBack(2);
    v1.PushBack(2);
    v1.PushBack(2);
    v1.PushBack(2);
    v1.PushBack(2);
    v1.PushBack(2);
    v1.PushBack(2);
    v1.PushBack(2);
    v1.PrintVector();
}

void Testfuzhi()
{
    TESTHEAD;
    Vector v1;
    v1.PushBack(1);
    v1.PushBack(2);
    v1.PushBack(3);
    v1.PushBack(4);
    v1.PushBack(5);
    v1.PushBack(6);
    v1.PushBack(7);
    v1.PushBack(8);
    Vector v2;
    v2 = v1;
    v2.PrintVector();
}

void TestCopy()
{
    TESTHEAD;
    Vector v1;
    v1.PushBack(1);
    v1.PushBack(2);
    v1.PushBack(3);
    Vector v2(v1);
    v2.PrintVector();
}

void TestPopBack()
{
    TESTHEAD;
    Vector v1;
    v1.PushBack(1);
    v1.PushBack(2);
    v1.PushBack(3);
    v1.PopBack();
    v1.PrintVector();
}

void TestInsert()
{
    TESTHEAD;
    Vector v1;
    v1.PushBack(1);
    v1.PushBack(2);
    v1.PushBack(3);
    v1.Insert(0, 4);
    v1.PrintVector();
}

void TestErase()
{
    TESTHEAD;
    Vector v1;
    v1.PushBack(1);
    v1.PushBack(2);
    v1.PushBack(3);
    v1.Erase(1);
    v1.PrintVector();
}

void TestFind()
{
    TESTHEAD;
    Vector v1;
    v1.PushBack(1);
    v1.PushBack(2);
    v1.PushBack(3);
    printf("%lu",v1.Find(3));
}

int main()
{
    TestPushBack();
    Testfuzhi();
    TestCopy();
    TestPopBack();
    TestInsert();
    TestErase();
    TestFind();
    return 0;
}

