/*
 * 找出数组中重复的数字
 * 在一个长度为n是数组里面的所有数字都在0~n-1的范围内。
 * 数组中某些数字是重复的，但不知到重复了几次，也不知道几个
 * 数组重复。
 * 只要求出一个重复的数字即可
 * 
 * 考虑时间复杂度和空间复杂度
 * 1. 用排序
 * 2. 哈希表
 * 3. 下标访问
 */
#include <iostream>

void InsertSort(size_t arr[], size_t size)
{
    size_t bound = 1;
    for (; bound < size; ++bound)
    {
        size_t i = bound;
        size_t key = arr[bound];
        for (; i > 0; --i)
        {
            if (arr[i-1] > key)
            {
                arr[i] = arr[i-1];
            }
            else
            {
                break;
            }
        }
        arr[i] = key;
    }
}

bool FindRepeat(size_t arr[], size_t size, size_t* number)
{
    if (number == NULL)
    {
        return false;
    }
    InsertSort(arr, size);
    // 防止数组越界
    for (size_t i = 0; i < size - 1; ++i)
    {
        if (arr[i] == arr[i+1])
        {
            *number = arr[i];
            return true;
        }
    }
    return false;
}

void Swap(size_t& a, size_t& b)
{
    size_t tmp = a;
    a = b;
    b = tmp;
}

bool FindRepeat2(size_t arr[], size_t size, size_t *number)
{
    if (size <= 1 || number == NULL)
    {
        return false;
    }
    // 判断是否合法
    for (size_t i = 0; i < size; ++i)
    {
        if (arr[i] > size - 1)
        {
            return false;
        }
    }
    // 用下标访问的方法，进行寻找
    for (size_t i = 0; i < size; ++i)
    {
        while (arr[i] != i)
        {
            size_t tmp = arr[i];
            if (tmp == arr[tmp])
            {
                *number = tmp;
                return true;
            }
            Swap(arr[i], arr[tmp]);
        }
    }
    return false;
}

int main()
{
    size_t arr[] = {2,3,1,1};
    size_t number = 0;
    int ret =  FindRepeat2(arr,sizeof(arr)/sizeof(arr[0]),&number);
    printf("%d,%lu\n",ret,number);
    
    return 0;
}

