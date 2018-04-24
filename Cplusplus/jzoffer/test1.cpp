/*
 *  给如下类型CMyString的声明，请为该类型添加赋值运算符函数 
 *
 *  class CMyString
 *  {
 *  public:
 *      CMyString(char* pData = nullptr);
 *      CMyString(const CMyString& str);
 *      ~CMyString(void);
 *  private:
 *      char* m_pData;
 *  };
 */
#include <iostream>
#include <string.h>
using namespace std;

class CMyString
{
public:
    CMyString(char* pData = nullptr);
    CMyString(const CMyString& str);
    CMyString& operator=(const CMyString& str);
    void Print();
    ~CMyString(void);
private:
    char* m_pData;
};

// pData 是构造函数传过来需要初始化的值
CMyString::CMyString(char* pData)
{
    // 如果传入值非法
    if (pData == nullptr)
    {
        m_pData = new char[1];
        m_pData[0] = '\0';
    }
    else
    {
        // 加一是要存放'\0'
        m_pData = new char[strlen(pData) + 1];
        strcpy(m_pData, pData);
    }
}

// 拷贝构造
CMyString::CMyString(const CMyString& str)
{
    m_pData = NULL;
    // 注意不要用原来的str去交换注意注意注意
    CMyString tmp(str.m_pData);
    swap(tmp.m_pData, m_pData);

    // 第二种写法
    /* m_pData = new char[strlen(str.m_pData) + 1]; */
    /* strcpy(m_pData, str.m_pData); */
}

// 赋值运算符重载
// 第一种写法
/* CMyString& CMyString::operator=(const CMyString& str) */
/* { */
/*     // 赋值前先判断是否是自己本身 */
/*     if (this == &str) */
/*     { */
/*         return *this; */
/*     } */

/*     // 在赋值前需要把原来的空间给释放。 */
/*     delete [] m_pData; */
/*     m_pData = nullptr; */

/*     // 开辟新的空间 */
/*     m_pData = new char[strlen(str.m_pData) + 1]; */
/*     strcpy(m_pData, str.m_pData); */
    
/*     return *this; */    
/* } */

// 第二种写法
CMyString& CMyString::operator=(const CMyString& str)
{
    if (this != &str)
    {
        CMyString tmp(str);
        swap(m_pData, tmp.m_pData);
    }
    return *this;
}

void CMyString::Print()
{
    cout<<m_pData<<endl;
}

CMyString::~CMyString()
{
    delete[] m_pData;
}

int main()
{
    char p[] = "abcd";
    CMyString c1(p);
    c1.Print();

    // 拷贝构造
    CMyString c3(c1);
    c3.Print();

    // 判断空指针
    char *p1 = nullptr;
    CMyString c2(p1);
    c2.Print();
    return 0;
}
