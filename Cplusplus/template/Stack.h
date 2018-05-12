#pragma once

template<class T, class Container >
class Stack
{
public:
    void Push(const T& value);
    void Pop();
    T& Top();
    bool Empty();
    void Print()
    {
        con.Print();
    }
protected:
    Container con;
};
