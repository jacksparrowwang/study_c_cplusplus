/*
 * 不修改数组找出重复的数字
 * 在一个长度为n+1的数组里的所有数字都在1~n的范围内，所以数组中
 * 至少有一个数字是重复的
 * 找出任意一个重复的数字，但是不能改变原有数字。
 */
#include <iostream>

size_t GetNumber(const size_t* arr,size_t size, size_t beg, size_t end)
{
    size_t count = 0;
    for (size_t i = 0; i < size; ++i)
    {
        // 这里计算个数，必须计算自己。因为它要与数组的二分的个数相比
        if (arr[i] <= end && arr[i] >= beg)
        {
            ++count;
        }
    }
    return count;
}

bool FindRepeat(const size_t* arr, size_t size, size_t* number)
{
    if (number == NULL || size <= 1)
    {
        return false;
    }
    // 判断非法情况
    for (size_t i = 0; i < size; ++i)
    {
        if (arr[i] > size -1)
        {
            return false;
        }
    }
    // 题目是1~n的数字，n+1又为数组的个数，所以用类似与二分法的思想进行划分
    // 时间复杂度O（nlogn）
    size_t count = 0;
    size_t beg = 0;
    // 
    size_t end = size-1;
    while (end > beg)
    {
        size_t mid = beg + (end - beg) / 2;
        count = GetNumber(arr, size, beg, mid);
        // 这里加一是因为个数相减后要包含最开始的那个数。
        // 比如 2 ~ 5 之间有3个数，但是要包含2，所以有四个数
        if (count > mid - beg + 1)
        {
            // 这里是找到了前把那部分里面一定会有重复，
            // 所以就不用判断后面半部分
            end = mid;
        }
        else
        {
            beg = mid + 1;
        }
    }
    // 相等的时候就说明已经不能再分，而count还大于1，说明这个数字一定是重复的
    if (end == beg && count > 1)
    {
        *number = beg;
        return true;
    }
    return false;
}

int main()
{
    size_t arr[] = {3,3,4,3,3};
    size_t number = 0;
    int ret =  FindRepeat(arr,sizeof(arr)/sizeof(arr[0]),&number);
    printf("%d,%lu\n",ret,number);
    return 0;
}
