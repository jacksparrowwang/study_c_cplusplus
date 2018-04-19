#pragma once
#include <iostream>
typedef int DataType;

class Vector
{
public:
    Vector():first(NULL),finish(NULL),endofstorage(NULL){}
    Vector(const Vector& v);
    ~Vector();
    Vector& operator=(const Vector& v);

    size_t Size() const
    {
        return finish - first;
    }

    size_t Capacity() const
    {
        return endofstorage - first;
    }

    void PrintVector();
    void Expands(size_t n);
    DataType* PushBack(DataType value); 
    void PopBack();
    void Insert(size_t pos, DataType value);
    void Erase(size_t pos);
    size_t Find(DataType value);
    void Reserve(size_t n);
private:
    DataType* first;
    DataType* finish;
    DataType* endofstorage;
};
