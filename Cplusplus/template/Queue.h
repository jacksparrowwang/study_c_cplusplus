#pragma once

/* template<class T, class Conteinar> */
template<class T, template<class> class Conteinar>
class Queue
{
public:
    void Push(const T& value);

    void Pop();

    T& FindHead();

    bool IsEmpty();

    void Print()
    {
        con.Print();
    }
protected:
    Conteinar<T> con;

};
