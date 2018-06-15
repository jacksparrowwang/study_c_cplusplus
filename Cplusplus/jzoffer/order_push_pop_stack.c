/*
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。
假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4，5,3,2,1是
该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
（注意：这两个序列的长度是相等的）
*/

// 思路：
// 先用栈的数据结构
// 再定义两个int变量，用来记录如栈到vector上哪个值上和比较pop上哪个值上
// 再循环的去比较，结束条件为
// 如果跳出循环就是vector中的数据比较完成
// 如果是j > pushV.size()说明比较已经出项超出范围，就不匹配

class Solution {
public:
bool IsPopOrder(vector<int> pushV,vector<int> popV) {
    std::stack<int> s;
    int i = 0;
    int j = 0;
    while (i != popV.size())
    {
        // 刚开始栈为NULL的时候，或者是出栈后为空
        if (s.empty() == true)
        {
            s.push(pushV[j]);
            ++j;
        }
        // 每次出栈或者入栈都要比较与弹栈顺序是否相同
        if (s.top() == popV[i])
        {
            // 是就出栈
            s.pop();
            ++i;
        }
        else
        {
            // 这里是为了处理，当访问到最后一个元素的时候，
            // j++ 后如果访问pushV[j]实际已经越界
            if (j ==  pushV.size())
            {
                ++j;
            }
            else
            {
                // 如果不是就入下一个
                s.push(pushV[j]);
                ++j;
            }
        }
        // 这里是如果走到原有顺序后，就不成立
        // 这里不能是>=，因为在走到=的时候还需要再判断一次
        // 把最后一个元素入栈后，j就等于pushV.size()，如果不出栈
        if (j > pushV.size()) 
        {
            return false;
        }
    }
    return true;
}
};
