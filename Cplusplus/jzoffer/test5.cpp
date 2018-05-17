/*
 * 请实现一个函数，把字符串中的每一个空格替换成  %20  
 * 例如 “We are happy.”
 * 输出为“We%20are%20happy.”
 *
 * */

#include <iostream>
#include <string.h>
using namespace std;
// 注意：
// 要有清楚的限定，在字符串扩充时候，
// 有两种想法
// 1）是当字符后面的空间有充裕的空间来存放扩容的字符
// 2）当字符串后面没有足够的空间，需要扩容，那么原有的
//    字符串在栈上还是在堆上。

// 1）是当字符后面的空间有充裕的空间来存放扩容的字符
void Repeat1(char* str)
{
    size_t count = 0;
    size_t len = 0;
    char* cur = str;
    while (*cur != '\0')
    {
        // 替换成%20
        if (*cur == ' ' || *cur == '#')
        {
            ++count;
        }
        ++len;
        ++cur;
    }
    size_t addlen = len+count*2;
    cur = str;
    for (int i = (int)len; i >= 0; --i)
    {
        if (*(cur+i) == ' ' || *(cur+i) == '#')
        {
            *(cur+addlen) = '0';
            --addlen;
            *(cur+addlen) = '2';
            --addlen;
            *(cur+addlen) = '%';
        }
        else
        {
            *(cur+addlen) = *(cur+i);
        }
        --addlen;
    }
}

// 将字符串中的“ ”，“#”替换成%加对应的十六位ASCII值
// 2）当字符串后面没有足够的空间，需要扩容，那么原有的
//    字符串在栈上还是在堆上。
// 引用传值注意
void Repeat2(char*& str)
{
    // count 用来计算字符串中‘ ’，‘#’的个数
    size_t count = 0;
    // 字符串长度
    size_t length = 0;
    char* cur = str;
    while (*cur)
    {
        if (*cur == ' ' || *cur == '#')
        {
            ++count;
        }
        // length不包含'\0'
        ++length;
        ++cur;
    }
    size_t amount = length + count*2 + 1;
    // 这里我们按照str在堆上开辟的，并且没有足够的空间，而且开空间不能多开辟。
    char* new_str = new char[amount];
    char* _str = new_str;
    cur = str;
    while (*cur)
    {
        if (*cur == ' ' || *cur == '#')
        {
            *_str++ = '%';
            *_str++ = '2';
            *_str++ = '0';
            ++cur;
        }
        else
        {
            *_str++ = *cur++;
        }
    }
    *_str = '\0';
    delete[] str;
    str = new_str;
}

void TestRepeat2()
{
    char* p = new char[20];
    strcpy(p, "ni hao a # en");
    cout<<p<<endl;
    Repeat2(p);
    cout<<p<<endl;
}

void TestRepeat1()
{
    char arr[] = "ni hao a # en";
    Repeat1(arr);
    cout<<arr<<endl;
}

int main()
{
    TestRepeat2();
    TestRepeat1();
    return 0;
}
