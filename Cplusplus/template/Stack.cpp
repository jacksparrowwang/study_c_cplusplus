#include <iostream>
using namespace std;
#include "Vector.h"
#include "Vector.cpp"
#include "Stack.h"

template<class T, class Container>
void Stack<T,Container>::Push(const T& value)
{
    con.Push(value); 
}

template<class T, class Container>
void Stack<T, Container>::Pop()
{
    con.Pop();
}

// 这里判断如果取栈顶元素失败返回什么？

template<class T, class Container>
T& Stack<T, Container>::Top()
{
    /* if (con.IsEmpty()) */
    /* { */
    /*     return ?; */
    /* } */
    return con.FindBack();
}

int main()
{
    Stack< int,Vector<int> > s;
    s.Push(1);
    s.Push(4);
    s.Print();    
    s.Pop();
    s.Print();    
    cout<<s.Top()<<endl;
    /* s.Pop(); */
    /* s.Print(); */    
    /* cout<<s.Top()<<endl; */
    return 0;
}
