/*斐波那契数列 */
/*
大家都知道斐波那契数列，现在要求输入一个整数n，
请你输出斐波那契数列的第n项。
n<=39
*/
// 1，1，2，3，5，8...
 int Fibonacci(int n) {
        if (n <= 0)
        {
            return 0;
        }
        if (n <= 2) // 如果小于等于2说明为1
        {
            return 1;
        }
        int front = 1;
        int mid = 1;
        int cur = 0;
        while (n > 2) // 是赋值关系是后面被前面的赋值就可以
        {
            cur = front + mid;
            front = mid;
            mid = cur;
            --n;
        }
        return cur;
    }
	
// 斐波那契变形
/*
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
*/	
// 1,2,3,5,8,13...
    int jumpFloor(int number) {
        if (number <=0)
        {
            return 0;
        }
        if (number <= 3) 
        {
            return number;
        }
        int front = 1;
        int mid = 2;
        int cur = 0;
        while (number > 2)
        {
            cur = front + mid;
            front = mid;
            mid = cur;
            --number;
        }
        return cur;
    }
	
/*
一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
*/

//2F(N)
// 1, 2, 4, 8, 16, 32...
    int jumpFloorII(int number) {
        if (number <= 0)
        {
            return 0;
        }
        if (number <= 2)
        {
            return number;
        }
        int front = 2;
        int cur = 0;
        while (number > 2)
        {
            cur = 2*front;
            front = cur;
            --number;
        }
        return cur;
    }