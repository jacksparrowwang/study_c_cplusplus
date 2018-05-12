#include <iostream>
using namespace std;
#include "Queue.h"
#include "List.h"
#include "List.cpp"

template<class T, template<class> class Conteinar>
/* template<class T, class Conteinar> */
void Queue<T,Conteinar>::Push(const T& value)
{
    con.PushBack(value);
}

template<class T, template<class> class Conteinar>
/* template<class T, class Conteinar> */
void Queue<T,Conteinar>::Pop()
{
    con.PopFront();
}

template<class T, template<class> class Conteinar>
/* template<class T, class Conteinar> */
T& Queue<T,Conteinar>::FindHead()
{
    con.FindHead();
}

int main()
{
    Queue<int, List > q;
    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Push(4);
    q.Print();
    q.Pop();
    q.Print();
    cout<<q.FindHead()<<endl;
    return 0;
}
