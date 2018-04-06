#pragma once
#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

class String
{
public:
        String();

        String(const char* str);

        String(const String& s);

        ~String();

        String& operator=(const String& s);

        // 用来打印
        const char* c_str()
        {
            return _str;
        }
        // 增容
        void Expand(size_t n);
        void PushBack(const char ch);
        void PushBack(const char* str);
        void PopBack();
        void Insert(size_t pos, char ch);
        void Insert(size_t pos, const char* str);
        void Erase(size_t pos, size_t len = 1);
        void Replace(char ch1, char ch2);
        void Replace(const char* str1, const char* str2);

        String operator+(const char ch);
        String operator+(const char* str);
        String operator+(const String& s);

        String& operator+=(const char ch);
        String& operator+=(const char* str);
        String& operator+=(const String& s);

        bool operator==(const String& s);
        bool operator<(const String& s);
        bool operator>(const String& s);
        bool operator>=(const String& s);
        bool operator<=(const String& s);
        bool operator!=(const String& s);
        

private:
        char* _str;
        size_t _size;
        size_t _capactiy;
};

