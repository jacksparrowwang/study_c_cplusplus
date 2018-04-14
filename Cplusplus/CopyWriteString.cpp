#include "CopyWriteString.h"

String::String()
{
    _str = new char[1];
    _str[0] = '\0';
    _count = new int(1);
}

String::String(const char* str):
    _str(new char[strlen(str)+1]),
    _count(new int(1))
{
    strcpy(_str, str);
}

String::~String()
{
    // 需要先判断是否引用计数为1
    if (--(*_count) == 0)
    {
        delete[] _str;
        delete _count;
        _str = NULL;
        _count = NULL;
    }
}

String::String(const String& s)
{
    // 引用计数
    _str = s._str;
    _count = s._count;
    ++(*_count);
}

String& String::operator=(const String& s)
{
    if (this == &s)
    {
        return *this;
    }
    // 首先要判断自己的空间是有其他成员在用
    --(*_count);
    // 如果在减完后等于0，说明已经是最后一个一个元素
    if (*_count == 0)
    {
        delete []_str;
        delete _count;
    }
    _str = s._str;
    _count = s._count;
    // 指针指向字符串，引用计数加1
    ++(*_count);
    return *this;
}

void String::CopyOnWrite()
{
    // 先判断有几个对象在使用
    if (--(*_count) != 0)
    {
        char* tmp = new char[strlen(_str)+1];
        strcpy(tmp, _str);
        _str = tmp;
        _count = new int(1);
    }
    else
    {
        ++(*_count);
    }
}

char& String::operator[](size_t pos)
{
    CopyOnWrite();
    return _str[pos];   
}

/////////////////////////////

int& String1::GetCount()
{
    return *((int*)(_str-4));
}

String1::String1()
{
    // 创建好空间让指针指向向前四个字节的位置
    _str = new char[5];
    *(_str+=4) = '\0';
    GetCount() = 1;
}

String1::String1(const char* str)
    :_str(new char[strlen(str)+5])
{
    _str+=4;
    strcpy(_str, str);
    GetCount() = 1;
}

String1::~String1()
{
    --GetCount();
    if (GetCount() == 0)
    {
        // 释放要减去4个字节，与构造函数相对应
        delete[] (_str-4);
    }
}

String1::String1(const String1& s)
{
    // 拷贝构造，只需要加引用计数。
    ++GetCount();
    // 让不同对象的字符指针指向同一地址
    _str = s._str;
}

String1& String1::operator=(const String1& s)
{
    if (_str == s._str)
    {
        return *this;
    }
    // 先让原来的对象的引用计数减1
    --GetCount();
    // 判断是否是老哥一个，是就直接释放
    if (GetCount() == 0)
    {
        delete [] (_str-4);
        _str = NULL;
    }
    // 赋值到新的对象，加引用计数，并且让指针指向新对象字符串的地址
    _str = s._str;
    ++GetCount();
    return *this;
}

void String1::CopyOnWrite()
{
    --GetCount();
    if (GetCount() != 0)
    {
        char* tmp = new char[strlen(_str)+5];
        // 开辟好空间需要将指针移动四个字节
        tmp += 4;
        strcpy(tmp, _str);
        _str = tmp;
        GetCount() = 1;
    }
    else
    {
        ++GetCount();
    }
}

char& String1::operator[](size_t pos)
{
    CopyOnWrite();
    return _str[pos];
}

/////////////////////////////////////
//测试代码
/////////////////////////////////////

void TestString()
{
    String s1("hello");
    String s2(s1);
    /* printf("%p  %p\n", s1.C_str(), s2.C_str()); */
    String s3("nihao");
    s2 = s3;
    printf("%p  %p\n", s1.C_str(), s2.C_str());
    printf("%p  %p\n", s3.C_str(), s2.C_str());
    s3[1] = 'a'; 
    printf("%p  %p\n", s1.C_str(), s2.C_str());
    printf("%p %s  %p %s", s3.C_str(),s3.C_str(),s2.C_str(), s2.C_str());
}

void TestString1()
{
    String1 s1;
    String1 s2("nihao");
    printf("%s %d\n", s2.C_str(), s2.GetCount());
    s1 = s2;
    printf("%s %p %p %d\n", s1.C_str(), s1.C_str(), s1.C_str(), s1.GetCount());
    s1[2] = 'a';
    printf("%s %p %p %d\n", s1.C_str(), s1.C_str(), s2.C_str(), s1.GetCount());
}

int main()
{
    //TestString();
    
    TestString1();
    
    return 0;
}
