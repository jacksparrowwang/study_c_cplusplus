/*
 * 在一个二位数组中，每一行都按照从左到右递增的顺序.
 * 每一列都按照从上到下递增的顺序排序。
 * 当输入这样的一个数组和一个整数，判断数字中是否含有该整数。
 * 
 * 1  2  8  9
 * 2  4  9  12
 * 4  7  10 13
 * 6  8  11 15
 *
 */

#include <iostream>
#include <assert.h>
using namespace std;
#define COL 4
#define ROW 4

// 我们以左上角为基准,进行比较。
bool ExistNumber(int arr[][COL], int number)
{
    assert(arr);
    int i = 0;
    int j = COL-1;
    while (i >= 0 && i < ROW && j < COL && j >= 0)
    {
        if (arr[i][j] > number)
        {
            --j;
        }
        else if (arr[i][j] < number)
        {
            ++i;
        }
        else
        {
            return true;
        }
    }
    return false;
}

int main()
{
    int arr[ROW][COL] = {
        {1 , 2 , 8 , 9 },
        {2 , 4 , 9 , 12},
        {4 , 7 , 10, 13},
        {6 , 8 , 11, 15}
    };
    bool ret = ExistNumber(arr, 12);
    cout<<ret<<endl;
    return 0;
}
