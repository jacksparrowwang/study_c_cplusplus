/*
在一个字符串(1<=字符串长度<=10000，
全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置
*/

#include <iostream>
#include <string>

  int FirstNotRepeatingChar(string str) {
        if (str.size()<1)
        {
            return -1;
        }
        // 利用数组的随机访问造出哈希表
        int hash[256] = {0};
        for (int i = 0; i < str.size(); ++i)
        {
            // 字符的asii码为下标， 出现的次数为数组的数值
            hash[str[i]]++;
        }
        for (int i = 0; i < str.size(); ++i)
        {
            // 再把字符串从头访问，找出第一次出现的字符
            if (hash[str[i]] == 1)
            {
                return i;
            }
        }
        return -1;
    }