#pragma once
#include <iostream>
#include <string.h>
class String
{
public:
    String();
    String(const char* str);
    String(const String& s);
    // 注意传引用
    String& operator=(const String& s);
    char& operator[](size_t pos);
    void CopyOnWrite();
    const char* C_str()
    {
        return _str;
    }
    ~String();
private:
    char* _str;
    int* _count;
};

class String1
{
public:
    String1();
    String1(const char* str);
    String1(const String1& s);
    // 注意传引用
    String1& operator=(const String1& s);
    char& operator[](size_t pos);
    void CopyOnWrite();
    int& GetCount();
    const char* C_str()
    {
        return _str;
    }
    ~String1();
private:
    // 计数放在_str的头部
    char* _str;
};
