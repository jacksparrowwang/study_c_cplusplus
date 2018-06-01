/*

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，
超过数组长度的一半，因此输出2。如果不存在则输出0。

*/



    // 利用快排思想
    int Partition(vector<int> numbers, int beg, int endd)
    {
        int value = numbers[endd-1];
        int end = endd-1;
        while (beg < end)
        {
            if (numbers[beg] <= value)
            {
                ++beg;
            }
            else if (numbers[end] >= value)
            {
                --end;
            }
            else
            {
                swap(numbers[beg], numbers[end]);
            }
        }
        swap(numbers[beg], numbers[end]);
        return beg;
    }
    // 还是在找出中位数
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if (numbers.size() < 1)
        {
            return 0;
        }
		// 数组的中间的位置
        int mid =  numbers.size()>>1;
        int beg = 0;
        int end = numbers.size()-1;
		// 找到对应的中间位置的数
        int index = Partition(numbers, beg, end);
        while (index != mid)
        {
			// 如果中间数大于中间位置
            if (index > mid)
            {
				// 走到前半部分
                end = index - 1;
                index = Partition(numbers, beg, end);
            }
            else
            {
				// 走后半部分
                beg = index + 1;
                index = Partition(numbers, beg, end);
            }
        }
		// 找到了
        int result = numbers[mid];
        
        // 这是在判断找到的中位数，是不是超过数组的一半
        int count = 0;
        for (int i = 0; i < numbers.size(); ++i)
        {
            if (numbers[i] == result)
            {
                ++count;
            }
        }
		// 找到的数没有超过一半，2倍就会小于它的长度
        if (count*2 <= numbers.size())
        {
            return 0;
        }
        return result;
    }