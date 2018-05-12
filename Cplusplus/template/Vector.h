#pragma once
/* const 写在函数后面修饰的是this指针 */

template<class T>
class Vector
{
public:
    Vector():start(NULL), finish(NULL),endofstorage(NULL){}

    Vector(const Vector<T>& v);

    Vector<T>& operator=(const Vector<T>& v);

    void Push(const T& value);
    
    void Pop();

    void Insert(size_t pos, const T& value);

    size_t Find(const T& to_find);

    T& FindBack();

    void Expand(size_t n)
    {
        // 判断太恶心
        if (n >= Capacity())
        {
            if (start == NULL && finish == NULL)
            {
                start = new T[3];
                finish = start;
                endofstorage = start + 3;;
            }
            else
            {
                size_t size = Size();
                T* new_start = new T[n];
                for (size_t i = 0; i < size; ++i)
                {
                    // 这里采用对象赋值，调用的是赋值重载.
                    *(new_start + i) = *(start + i);
                }
                delete [] start;
                start = new_start;
                finish = size + start;
                endofstorage = start + n;
            }
        }
    }

    const size_t Size() const
    {
        return finish - start;
    }

    size_t Capacity() const
    {
        return endofstorage - start;
    }

    bool IsEmpty() const
    {
        return start == finish;
    }

    ~Vector()
    {
        delete[] start;
        start = finish = endofstorage = NULL;
    }

    bool Clear() const
    {
        return start = finish;
    }

    void Print()
    {
        for (int i = 0; i < Size(); ++i)
        {
            cout<<*(start+i)<<" ";
        }
        cout<<endl;
    }

protected:
    T* start;
    T* finish;
    T* endofstorage;
};
