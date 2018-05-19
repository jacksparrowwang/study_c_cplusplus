#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SeqStack.h"


void Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

////////////////////////////
// 正向冒泡排序
void BubbleSortI(int arr[], int size)
{
	int i = 0;
	for (; i < size - 1; ++i)
	{
		int flag = 0;
		int j = 0;
		for (; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j],&arr[j + 1]);
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
}

// 反向冒泡排序,时间复杂度为O(n^2)
void BubbleSortB(int arr[], int size)
{
	int bound = 1;
	for (; bound < size; ++bound)
	{
		int flag = 0;
		int j = size - 1;
		for (; j >= bound; --j)
		{
			if (arr[j] < arr[j - 1])
			{
				Swap(&arr[j],&arr[j-1]);
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
}


////////////////////////////
// 选择排序 时间复杂度为O(n ^ 2)
void SelectSort(int arr[], int size)
{
	int i = 0;
	for (; i < size - 1; ++i)
	{
		int j = 0;
		for (j = i + 1; j < size; ++j)
		{
			if (arr[i] > arr[j])
			{
				Swap(&arr[i],&arr[j]);
			}
		}
	}
	return;
}

////////////////////////////
// 下沉。事先知道或者计算出父节点N，然后通过N*2+1计算出孩子节点
// 左孩子与右孩子进行比较
//	1)如果要建立大堆就要把较大值的孩子与父节点进行比较，父节点小进行
//	交换，大就不需要交换。
//	2)如果要建立小堆就要把较小值的孩子与父节点进行比较，父节点大进行
//	交换，小就不需要交换。
// 然后父节点+1。
// 当右孩子等于size时候跳出循环

void AdjustDown(int arr[], size_t size, size_t index)
{
	size_t child = index * 2 + 1;
	while (child  < size)
	{
		// 必须要判断child + 1 < size
		if ((child + 1 < size) && arr[child] > arr[child + 1])
		{
			child = child + 1;
		}
		if (arr[child] < arr[index])
		{
			Swap(&arr[child], &arr[index]);
		}
		else
		{
			break;
		}
		// 更新下标
		index = child;
		child = index * 2 + 1;
	}
}

// 堆排序,时间复杂度为O(N * logN)
void HeapSort(int arr[], size_t size)
{
	if (size <= 1)
	{
		return;
	}
	// 最后的父节点
	size_t star = (size - 1 - 1) / 2;
	for (; star > 0; --star)
	{
		AdjustDown(arr, size, star);
	}
	AdjustDown(arr, size, 0);
	size_t heap_size = size;
	while (heap_size)
	{
		Swap(&arr[0], &arr[heap_size-1]);
		--heap_size;
		// 必须传入更新后的新元素个数
		AdjustDown(arr,heap_size,0);
	}
}

////////////////////////////
// 插入排序1
void InsertSort(int arr[], int size)
{
	int i = 1;
	for (; i < size; ++i)
	{
		int value = arr[i];
		int j = i - 1;
		for (; j >= 0; --j)
		{
			if (arr[j] > value)
			{
				arr[j + 1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j + 1] = value;
	}
}

//插入排序2,时间复杂度为O(n^2)
void InsertSort2(int arr[], size_t size)
{
	size_t bound = 1;
	for (; bound < size; ++bound)
	{
		int value = arr[bound];
		size_t i = bound;
		for (; i > 0; --i)
		{
			if (arr[i - 1] > value)
			{
				arr[i] = arr[i - 1];
			}
			else
			{
				break;
			}
		}
		arr[i] = value;
	}
}

////////////////////////////
// 如果序列已经基本有序，那么插排的速度快
// 如果元素个数比较少，插入排序速度快
// 希尔排序
// 时间复杂度O（N ^ 2）最差情况
void ShellSort(int arr[], size_t size)
{
	if (size <= 1)
	{
		return;
	}
	// 第一次先分为两个组。插排完
	// 第二次分为四组
	// ...
	// N / 2  N / 4  N / 8 ... 1;希尔序列k
	size_t group = size / 2;
	for (; group > 0; group /= 2)
	{
		size_t bound = group;
		for (; bound < size; ++bound)
		{
			// 先是bound对第一组元素的第一个元素插入到
			// 第零组元素中。当bound++就对第一组的第二个元素
			// 插入到第零组元素中...
			int value = arr[bound];
			size_t i = bound;
			for (; i >= group; i -= group)
			{
				if (arr[i-group] > value)
				{
					arr[i] = arr[i - group];
				}
				else
				{
					break;
				}
			}
			arr[i] = value;
		}
	}
	return;
}

////////////////////////////
// 归并排序
// [beg,mid)
// [mid,end)
// 采用前闭后开
void _MergeArray(int arr[], size_t beg, size_t mid, size_t end, int *tmp)
{
    // 每次函数出栈都会调用这个函数。
    // 最开始从两个元素开始
    // 一个元素情况是非递归进行
	size_t cur1 = beg;
	size_t cur2 = mid;
	size_t index = 0;
	while (cur1 < mid && cur2 < end)
	{
		if (arr[cur1] < arr[cur2])
		{
			tmp[index] = arr[cur1];
			++index;
			++cur1;
		}
		else
		{
			tmp[index] = arr[cur2];
			++index;
			++cur2;
		}
	}
	while (cur1 < mid)
	{
		tmp[index++] = arr[cur1++];
	}
	while (cur2 < end)
	{
		tmp[index++] = arr[cur2++];
	}
	memcpy(arr + beg, tmp, sizeof(int)*(end - beg));
}

// 递归体
void _MergeSort(int arr[], size_t beg, size_t end, int *tmp)
{
	if (end - beg <= 1)
	{
		return;
	}
	size_t mid = beg + (end - beg)/2;
    // [)
    // 当递归到最底部的时候就剩下两个元素的时候
    // 仔去判断下一次递归失败所以就剩下两个元素。
    // 从两个元素开始调元_MergeArray函数，进行从
    // 最右边进行函数出栈。
	_MergeSort(arr, beg, mid, tmp);
	_MergeSort(arr, mid, end, tmp);
	_MergeArray(arr, beg, mid, end, tmp);
}

// 归并排序(递归排序)，时间复杂度为O(n * logn)
// 空间复杂读为O(n)
// 可以进行外部排序
void MergeSort(int arr[], size_t size)
{
	if (size <= 1)
	{
		return;
	}
	// 采用空间换时间
	int *tmp = (int *)malloc(sizeof(int) * size);
	// [0,size)
	_MergeSort(arr, 0, size, tmp);
	free(tmp);
}

// 非递归归并排序
// 直接按照间隔为1的划分。这样就可以不用递归划分区域
// 非递归和递归都采用了，以空间换时间的做法。
void MergeSortByLoop(int arr[], size_t size)
{
	if (size <= 1)
	{
		return;
	}
	int *tmp = (int *)malloc(sizeof(int) * size);
	// 起初定义的间隔为1,下标相减为1
	size_t gap = 1;
	// 每次已2倍增长,这个是归并组的间隔，是每次归并时，有几个元素
	for (; gap < size; gap *= 2)
	{
		size_t i = 0;
		// 每次比较的是相邻的两组元素
		for (; i < size; i += 2 * gap)
		{
			size_t beg = i;
			size_t mid = i + gap;
			size_t end = i + 2 * gap;
			// 防止在处理最后几个元素
			// 数组访问越界
			if (mid > size)
			{
				mid = size;
			}
			if (end > size)
			{
				end = size;
			}
			_MergeArray(arr, beg, mid ,end, tmp);
		}
	}
	free(tmp);
}


//////////////////////////// 

// 交换法(主要)
size_t Partion1(int arr[], size_t beg, size_t end)
{
	size_t left = beg;
	// 因为这里是前闭后开区间。
	size_t right = end-1;
	// 选取基准值。
	int key = arr[right];
	while (left < right)
	{
		if (arr[left] <= key)
		{
			++left;
		}
		else if (arr[right] >= key)
		{
			--right;
		}
		else
		{
			Swap(&arr[left],&arr[right]);
		}
	}
	// 程序到这里说明 left 和 right 已经指向同一个位置
	// 所以用下标left和right是一样的
	// 因而返回left和right是一样的。
    // ******这里
    // ******一定
    // ******不能是key
    // *****因为是对数组操作，key就改变了数组的原有数据。
	Swap(&arr[right],&arr[end-1]);
	return right;
}

// 挖坑法
size_t Partion2(int arr[], size_t beg, size_t end)
{
	size_t left = beg;
	size_t right = end-1;
	int key = arr[right];
	while (left < right)
	{
		while (left < right && arr[left] <= key)
		{
			++left;
		}
		if (left < right)
		{
			arr[right] = arr[left];
			--right;
		}
		while (left < right && arr[right] >= key)
		{
			--right;
		}
		if (left < right)
		{
			arr[left] = arr[right];
			++left;
		}
	}
	arr[left] = key;
	return left;
}

// 双指针法
size_t Partion3(int arr[], size_t beg, size_t end)
{
	size_t cur = beg;
	size_t pre = beg-1;
	int key = arr[end-1];
	while (cur < end)
	{
		if (arr[cur] < key && ++pre != cur)
		{
			Swap(&arr[cur], &arr[pre]);
		}
		++cur;
	}
	if (++pre != end)
	{
		Swap(&arr[pre], &arr[end-1]);
	}
	return pre;
}

// 快排递归体
void _QuickSort(int arr[], size_t beg, size_t end)
{
	// 前闭后开
	if (end - beg <= 1)
	{
		return;
	}
	// 找到基准值的下标，以基准值下标把数组分为开。
	// 依次划分。
	size_t mid = Partion1(arr, beg, end);
	_QuickSort(arr, beg, mid);
	_QuickSort(arr, mid+1, end);
}

//////////////
// 快速排序改进
// 1.三值取中值
// 2.当区间比较小的时候可以采用插入排序，直接对这个区间进行排序
//   从而减少递归次数
// 3.当递归深度到达一定程度时，使用堆排序对待排序区间进行排序。
/////////////
// 快速排序(递归版)
// 时间复杂度最坏是O(n^2),序列是逆序
// 平均时间复杂度为O(n * logn)
void QuickSort(int arr[], size_t size)
{
	if (size <= 1)
	{
		return;
	}
	_QuickSort(arr, 0, size);
}

////////////////////////
// 快速排序(非递归版)
void QuickSortByLoop(int arr[], size_t size)
{
	SeqStack stack;
	SeqStackInit(&stack);
	size_t beg = 0;
	size_t end = size;
	SeqStackPushStack(&stack, beg);
	SeqStackPushStack(&stack, end);
	while (stack.size > 0)
	{
		SeqStackFindTop(&stack, &end);
		SeqStackPopStack(&stack);
		SeqStackFindTop(&stack, &beg);
		SeqStackPopStack(&stack);
		if (end - beg <= 1)
		{
			continue;
		}
		size_t mid = Partion1(arr, beg, end);
		SeqStackPushStack(&stack, beg);
		SeqStackPushStack(&stack, mid);
		SeqStackPushStack(&stack, mid + 1);
		SeqStackPushStack(&stack, end);
	}
}

void CountSort(int arr[], int size)
{
    // 求出最大和最小的数
    int mindata = arr[0];
    int maxdata = arr[0];
    int i = 0;
    for (; i < size; ++i)
    {
        if (mindata > arr[i])
        {
            mindata = arr[i];
        }
        if (maxdata < arr[i])
        {
            maxdata = arr[i];
        }
    }

    int range = maxdata - mindata + 1;
    int *pcount = (int*)malloc(sizeof(int)*range);
    if (pcount == NULL)
    {
        printf("error\n");
    }
    memset(pcount, 0, sizeof(int)*range);
    
    for (i = 0; i < size; ++i)
    {
        pcount[arr[i]-mindata]++;
    }

    size_t index = 0;
    for (i = 0;  i < range; ++i)
    {
        while (pcount[i]--)
        {
            arr[index++] = i + mindata;
        }
    }
    free(pcount);
}

////////////////////////
//以下为测试代码
////////////////////////

#define HEAD printf("\n=============%s==============\n",__FUNCTION__)


void TestQuickSortByLoop()
{
	HEAD;
	int arr[] = {23,45,6,23,2345,-1,-563,-5453,837458,453456,234,45567,748,7,64,34,56,23,6,2,634,3245,4,73,8};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	QuickSortByLoop(arr,size);
	size_t i = 0;
	for (; i < size; ++i)
	{
		printf("[%d] ", arr[i]);
	}
	printf("\n\n\n");
}


void TestQuickSort()
{
	HEAD;
	//int arr[] = {23,45,6,23,2345,453456,234,45567,748,7,64,34,56,23,6,2,634,3245,4,73,8};
    int arr[] = {11,3,6,4,6,4,5,3,7,5,97,23};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	QuickSort(arr,size);
	size_t i = 0;
	for (; i < size; ++i)
	{
		printf("[%d] ", arr[i]);
	}
	printf("\n\n\n");
}


void TestMergeSortByLoop()
{
	HEAD;
	int arr[] = {23,45,6,23634,3245,4,73,8};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	MergeSortByLoop(arr,size);
	size_t i = 0;
	for (; i < size; ++i)
	{
		printf("[%d] ", arr[i]);
	}
	printf("\n\n\n");
}


void TestMergeSort()
{
	HEAD;
	int arr[] = {23,45,6,23634,3245,4,73,8};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	MergeSort(arr,size);
	size_t i = 0;
	for (; i < size; ++i)
	{
		printf("[%d] ", arr[i]);
	}
	printf("\n\n\n");
}


void TestShelltSort()
{
	HEAD;
	int arr[] = {23,45,6,23634,3245,4,73,8};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	ShellSort(arr,size);
	size_t i = 0;
	for (; i < size; ++i)
	{
		printf("[%d] ", arr[i]);
	}
	printf("\n\n\n");
}

void TestInsertSort()
{
	HEAD;
	int arr[] = {23,45,6,23634,3245,4,73,8};
	int size = sizeof(arr)/sizeof(arr[0]);
	InsertSort2(arr,size);
	int i = 0;
	for (; i < size; ++i)
	{
		printf("[%d] ", arr[i]);
	}
	printf("\n\n\n");
}

// 反向
void TestBubbleSortB()
{
	HEAD;
	int arr[] = {23,45,6,23634,3245,4,73,8};
	int size = sizeof(arr)/sizeof(arr[0]);
	BubbleSortB(arr,size);
	int i = 0;
	for (; i < size; ++i)
	{
		printf("[%d] ", arr[i]);
	}
	printf("\n\n\n");
}


// 正向
void TestBubbleSortI()
{
	HEAD;
	int arr[] = {23,45,6,23634,3245,4,73,8};
	int size = sizeof(arr)/sizeof(arr[0]);
	BubbleSortI(arr,size);
	int i = 0;
	for (; i < size; ++i)
	{
		printf("[%d] ", arr[i]);
	}
	printf("\n\n\n");
}

// 选择排序
void TestSelectSort()
{
	HEAD;
	int arr[] = {23,45,6,23634,3245,4,73,8};
	int size = sizeof(arr)/sizeof(arr[0]);
	SelectSort(arr,size);
	int i = 0;
	for (; i < size; ++i)
	{
		printf("[%d] ", arr[i]);
	}
	printf("\n\n\n");
}

// 堆排序
void TestHeapSort()
{
	HEAD;
	int arr[] = {23,45,6,23634,3245,4,73,8};
	int size = sizeof(arr)/sizeof(arr[0]);
	HeapSort(arr,size);
	int i = 0;
	for (; i < size; ++i)
	{
		printf("[%d] ", arr[i]);
	}
	printf("\n\n\n");
}

void TestCountSort()
{
	HEAD;
	int arr[] = {23,45,6,24,35,4,7,8};
	int size = sizeof(arr)/sizeof(arr[0]);
	CountSort(arr,size);
	int i = 0;
	for (; i < size; ++i)
	{
		printf("[%d] ", arr[i]);
	}
	printf("\n\n\n");
}

int main()
{
	TestBubbleSortI();
	TestBubbleSortB();
	TestSelectSort();
	TestHeapSort();
	TestInsertSort();
	TestShelltSort();
	TestMergeSort();
	TestMergeSortByLoop();
	TestQuickSort();
	TestQuickSortByLoop();
    TestCountSort();
	return 0;
}
