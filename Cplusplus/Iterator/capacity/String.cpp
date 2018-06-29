#include "String.h"

String::String()
{
    _str = new char[1];
    _str[0] = '\0';
    _size = 0;
    _capactiy = _size;
}

String::String(const char* str)
{
    int len = strlen(str);
    _str = new char[len + 1];
    strcpy(_str, str);
    _size = len;
    _capactiy = _size;
}

// 传统写法
// 第一种
/* String::String(const String& s) */
/* { */
/*     _str = new char[strlen(s._str)+1]; */
/*     strcpy(_str, s._str); */
/*     _size = strlen(s._str); */
/*     _capactiy = _size; */
/* } */

// 简单写法
String::String(const String& s)
{
    // 必须先把_str置为空
    _str = NULL;
    // 注意这里是调用了构造函数，必须穿字符串
    String tmp(s._str);
    swap(_str,tmp._str);
    _size = s._size;
    _capactiy = s._capactiy;
}

String::~String()
{
    if (_str)
    {
        delete []_str;
        _size = 0;
        _capactiy = 0;
    }
}

///////////////////////////////////////
// 赋值运算符重载
///////////////////////////////////////
// 写法一
/* String& String::operator=(const String& s) */
/* { */
/*     if (this == &s) */
/*     { */
/*         return *this; */
/*     } */
/*     delete[] _str; */
/*     _str = new char[strlen(s._str)+1]; */

/*     strcpy(_str, s._str); */
/*     _size = s._size; */
/*     _capactiy = s._capactiy; */
/*     return *this; */
/* } */

// 写法二
String& String::operator=(const String& s)
{
    if (this == &s)
    {
        return *this;
    }
    // 这里是调用拷贝构造
    String tmp(s);
    // 库函数里面用的是引用
    // 交换为内置类型
    swap(_str, tmp._str);
    swap(_size, tmp._size);
    swap(_capactiy, tmp._capactiy);
    return *this;
}

////////////////////////////////////
//对字符串的操作
////////////////////////////////////
// 注意扩展空间需要释放原来的空间
void String::Expand(size_t n)
{
    if (n > _capactiy)
    {
        // 开辟空间需要多开一个用来保存\0
        char* newchar = new char[n+1]; 
        strcpy(newchar, _str);
        // 一定要先释放原有内存
        delete []_str;
        _str = newchar;
        _capactiy = n;
    }
}

void String::PushBack(char ch)
{
    if (_size >= _capactiy)
    {
        Expand(_capactiy*2);
    }
    // 这里size已经++
   _str[_size++] = ch;
   _str[_size] = '\0';
}

void String::PushBack(const char* str)
{
    size_t len = strlen(str);
    if (_size + len > _capactiy)
    {
        Expand(_capactiy + len);
    }
    // 把指针挪到_str的\0处
    strcpy(_str+_size, str);
    _size += len;
}

void String::PopBack()
{
    if (_size == 0)
    {
        return;
    }
    _str[_size] = '\0';
    --_size;
}

void String::Insert(size_t pos, char ch)
{
    assert(pos < _size);
    if (_size >= _capactiy)
    {
        Expand(_capactiy*2);
    }
    for (int i = _size; i >= (int)pos; --i)
    {
        _str[i+1] = _str[i];
    }
    _str[pos] = ch;
    ++_size;
}

void String::Insert(size_t pos, const char* str)
{
    assert(pos < _size);
    size_t len = strlen(str);
    if (_size + len >= _capactiy)
    {
        Expand(_size+len);
    }
    for (int i = _size+len; i > (int)pos; --i)
    {
        _str[i] = _str[i-len];
    }
    strncpy(_str+pos, str, len);
    _size += len;
}

void String::Erase(size_t pos, size_t len)
{
    assert(pos < _size);
    // 1.先判断是否删除的大于最大长度,包含是否删除整个字符串
    if (pos + len >= _size)
    {
        _str[pos] = '\0';
        _size = pos;
    }
    else
    {
        // 必须等于, 需要把\0拷贝进去
        for (int i = pos + len; i <= (int)_size; ++i)
        {
            _str[i-len] = _str[i];
        }
        _size -= len;
    }
}

void String::Replace(char ch1, char ch2)
{
    assert(ch1 != '\0'|| ch2 != '\0');
    char* tmp = _str;
    while (*tmp)
    {
        if (*tmp == ch1)
        {
            *tmp = ch2;
        }
        ++tmp;
    }
}

void String::Replace(const char* str1, const char* str2)
{
    assert(str1 != nullptr || str2 != nullptr);
    // 1.判断字符串是否相等，相等不用替换，退出
    if (strcmp(str1, str2) == 0)
    {
        return;
    }
    // 2.判断在要替换的字符串中是否存在子串str1，
    char* p_str = strstr(_str, str1);
    if (p_str != NULL)
    {
        //   a) 存在，进行计算str1和str2的长度，长度相减，得出是增长还是缩短
        //      从后向前进行搬运。
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        if (len1 - len2 > 0)
        {
            // p_str 是查找到字符串在原来字符串中的地址
            strncpy(p_str, str2, len2);
            // 将空位补全
            while (*(p_str + len1))
            {
                *(p_str + len2) = *(p_str + len1);
                p_str = p_str + 1;
            }
            // 处理最后一个\0;
            *(p_str + len2) = '\0';
        }
        else if (len1 - len2 < 0)
        {
            if (_size + (len2 - len1) >= _capactiy)
            {
                Expand(_size + (len2 - len1));
            }
            p_str = NULL;
            // 因为内存扩张将原有指针指向的地方给释放
            // 并且重新开辟了一段，所以原来指针会有野指针的可能。
            char *p = strstr(_str, str1);
            int tmp = strlen((p+len1)) + 1;
            /* cout<<_str<<endl; */
            /* cout<<tmp<<endl; */
            /* cout<<str2<<endl; */
            /* cout<<str1<<endl; */
            /* cout<<p<<endl; */
            memmove(p+len2, p+len1, tmp);
            /* while (p_str+len2 + tmp != p_str+len2) */
            /* { */
            /*     *(p_str+len2+tmp) = *(p_str+len1+tmp); */
            /*     tmp--; */
            /* } */
            strncpy(p, str2, len2);
        }
        else
        {
            strncpy(p_str, str2, len2);
        }
    }
    return;
    //   b) 不存在直接返回
}

//////////////////////////////////////////////
//加的重载,注意返回值不能用引用
//////////////////////////////////////////////
// 加上一个字符
String String::operator+(char ch)
{
    String tmp(*this);
    tmp.PushBack(ch);
    return tmp;
}

// 加上常量字符串
String String::operator+(const char* str)
{
    // 这个调用构造函数
    String tmp(this->_str);

    tmp.PushBack(str);

    return tmp;
}

// 对象的加
String String::operator+(const String& s)
{
    // 这里是拷贝构造
    String tmp(*this);
    tmp.PushBack(s._str);
    return tmp;
}

////////////////////////////
// +=重载
////////////////////////////
String& String::operator+=(char ch)
{
    this->PushBack(ch);
    return *this;
}

String& String::operator+=(const char* str)
{
    this->PushBack(str);
    return *this;
}

String& String::operator+=(const String& s)
{
    this->PushBack(s._str);
    return *this;
}

//////////////////////////////
// bool型运算符重载
//////////////////////////////
int My_strcmp(const char* str1, const char* str2)
{
    int ret = 0;
    // *str2是用来跳出循环的
    while (!(ret = (unsigned int)*str1++ - (unsigned int)*str2++) && *str2);
    if (ret > 0)
    {
        return 1;
    }
    else if (ret < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

bool String::operator==(const String& s)
{
    int a = My_strcmp(this->_str, s._str);
    if (a == 0)
    {
        return true;
    }
    return false;
}

bool String::operator<(const String& s)
{
    int tmp = My_strcmp(this->_str, s._str);
    if (tmp == -1)
    {
        return true;
    }
    return false;
}

bool String::operator>(const String& s)
{
    if (!(*this <= s))
    {
        return true;
    }
    return false;
}

bool String::operator<=(const String& s)
{
    if (*this < s && *this == s)
    {
        return true;
    }
    return false;
}

bool String::operator>=(const String& s)
{
    if (!(*this < s))
    {
        return true;
    }
    return false;
}

bool String::operator!=(const String& s)
{
    if (!(*this == s))
    {
        return true;
    }
    return false;
}

///////////////////////////////////
int main()
{
    // 无参
    /* String s1; */
    /* cout<< s1.c_str()<<endl; */

    // 有参数
    /* String s2("nihao"); */
    /* cout<<s2.c_str()<<endl; */

    // 插入一个字符
    /* s2.PushBack('a'); */
    /* cout<<s2.c_str()<<endl; */

    // 赋值
    /* s1 = s2; */
    /* cout<< s1.c_str()<<endl; */

    // 尾插字符串
    /* String s3; */
    /* s3.PushBack("wohenhao!"); */
    /* cout<< s3.c_str()<<endl; */

    /* // 加字符串 */
    /* String s4("abcd"); */
    /* cout<< (s4+"woyehenhao").c_str()<<endl; */
    /* cout<< (s4+'e').c_str()<<endl; */

    /* // 加等字符，字符串 */
    /* String s5("nihao!"); */
    /* s5 += "wohenhao"; */
    /* cout<< s5.c_str()<<endl; */
    /* s5 += '?'; */
    /* cout<< s5.c_str()<<endl; */

    /* cout<<(s4 += s5).c_str()<<endl; */

    String s6("nihaowoqueshihenhao");
    String s7("nihao!");
    cout<< (s6 == s7)<<endl;

    /* s6.Insert(2,"bianzihaokan"); */
    /* cout<< s6.c_str()<<endl; */

    /* s6.Erase(2,12); */
    /* cout<< s6.c_str()<<endl; */

    /* s6.Replace('o', 'e'); */
    /* cout<<s6.c_str()<<endl; */

    /* s6.Replace("ni", "wo"); */
    s6.Replace("ni", "wohen");
    cout<<s6.c_str()<<endl;
    return 0;
}
