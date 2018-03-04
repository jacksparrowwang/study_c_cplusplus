#include"Heap.h"
 // 1. 堆是一个完全二叉树 
 // 2. 堆有两种, 一种叫小堆(小根堆, 最小堆), 
 // 一种叫大堆(大根堆, 最大堆). 
 // 3. 以小堆为例, 这个树的根节点是这个树中的最小的元素 
 // 对于任意一个子树来说, 子树的根节点, 小于左右孩子节点的值. 
 // 4. 以大堆为例, 这个树的根节点是这个树种的最大元素 
 // 对于任意一个子树来说, 子树的根节点, 大于左右孩子节点的值. 


int Less(HeapType a, HeapType b)
{
	return a < b ? 1:0;
}

// 初始化。
void HeapInit(Heap *heap, Compare compare)
{
	if (heap == NULL || compare == NULL)
	{
		return;
	}
	heap->size = 0;
	heap->cmp = compare;
}

// 交换。
void Swap(HeapType *a, HeapType *b)
{
	HeapType tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}

// 上浮
void AdjustUp(Heap *heap,size_t size, size_t index)
{
	if (heap == NULL)
	{
		return;
	}
	size_t child = index;
	size_t parent = (size - 1 - 1) / 2;
	while (child > 0)
	{
		if (heap->cmp(heap->data[child], heap->data[parent]))
		//if (heap->data[child] < heap->data[parent])
		{
			Swap(&heap->data[child], &heap->data[parent]);
		}
		// 因为是尾部插入然后上移，当上移到parent < child时候，
		// 就需要停止，不然会继续向上判断。
		else 
		{
			break;
		}
		child = parent; 
		parent = (child-1) / 2; 
	}
//	if (heap->cmp(heap->data[child], heap->data[0]))
//	//if (heap->data[child] < heap->data[0])
//	{
//		Swap(&heap->data[child], &heap->data[0]);
//	}
}

// 入堆（在堆中插入元素）。
void HeapInsert(Heap *heap, HeapType value)
{
	if (heap == NULL)
	{
		return;
	}
	if (heap->size > MAXREPOSITORY)
	{
		return;
	}
	heap->data[heap->size] = value;
	++heap->size;
	size_t index = heap->size-1 ;
	AdjustUp(heap, heap->size, index);
}

// 取堆顶元素。
int HeapFindRoot(Heap *heap, HeapType *value)
{
	if (heap == NULL || value == NULL)
	{
		return 0;
	}
	*value = heap->data[0];
	return 1;
}

// 下沉
void AdjustDown(Heap *heap,size_t size, size_t index)
{
	if (heap == NULL)
	{
		return;
	}
	/*
	 * 方法1，但代码很繁琐
	size_t parent = index;
	size_t lchild = parent * 2 + 1;
	size_t rchild = parent * 2 + 2;
	while (rchild < size && lchild < size)
	{
		if (heap->cmp(heap->data[lchild], heap->data[rchild]))
		{
			if (heap->cmp(heap->data[lchild], heap->data[parent]))	
			{
				Swap(&heap->data[lchild], &heap->data[parent]);
				parent = lchild;
				lchild = parent * 2 + 1;
				rchild = parent * 2 + 2;
			}
			else
			{
				break;
			}
		}
		else
		{
			if (heap->cmp(heap->data[rchild], heap->data[parent]))	
			{
				Swap(&heap->data[rchild], &heap->data[parent]);
				parent = rchild;
				lchild = parent * 2 + 1;
				rchild = parent * 2 + 2;
			}
			else
			{
				break;
			}
		}
	}*/
	// 方法2 代码的优化。
	size_t lchild = index * 2 + 1;
	while ((lchild + 1) < size)
	{
		// 如果是右孩子小于左孩子，那么把下标为右孩子赋给左孩子下标。
		if (heap->cmp(heap->data[lchild + 1], heap->data[lchild]))
		{
			lchild = lchild + 1;
		}
		// 把孩子中小的一个与父节点值比较，如果父值大，子小，那么交换。否则跳出循环。
		if (heap->cmp(heap->data[lchild], heap->data[index]))
		{
			Swap(&heap->data[lchild], &heap->data[index]);
		}
		else
		{
			break;
		}
		// 更新index和孩子节点下标。
		index = lchild;
		lchild = index * 2 + 1;
	}
}



// 删除堆顶元素。
void HeapErase(Heap *heap)
{
	if (heap == NULL)
	{
		return;
	}
	Swap(&heap->data[0], &heap->data[heap->size-1]);
	--heap->size;
	size_t index = 0;
	AdjustDown(heap, heap->size, index);
}

// 判断堆是否为空。
int HeapEmpty(Heap *heap)
{
	if (heap == NULL)
	{
		return -1;
	}
	if (heap->size == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// 求堆中元素的个数。
size_t HeapSize(Heap *heap)
{
	if (heap == NULL)
	{
		return (size_t)-1;
	}
	return heap->size;
}

// 销毁堆。
void HeapDestroy(Heap *heap)
{
	if (heap == NULL)
	{
		return;
	}
	heap->size = 0;
}

 // 在我们不想开辟额外的空间, 或者消耗额外的时间的前提下, 
 // 如果我们想进行从小到大排序, 就需要一个大堆 
 // 如果我们想进行从大到小排序, 就需要一个小堆 

// 堆的排序。
void HeapSort(HeapType arr[], size_t size)
{
	if (arr == NULL || size < 1)
	{
		return;
	}
	Heap heap;
	HeapInit(&heap, Less);
	int i = 0;
	for (; i < size; ++i)
	{
		HeapInsert(&heap,arr[i]);
	}
	size_t count = size;
	while (size)
	{
		HeapErase(&heap);
		--size;
	}
	int j = 0;
	for (; j < count; ++j)
	{
		printf("%d  ",heap.data[j]);
	}
}

//////////////////////////
//以下为测试代码
//////////////////////////

#define HEAP_HEAD printf("\n==============%s============\n",__FUNCTION__)

void PrintHeap(Heap *heap)
{
	if (heap == NULL)
	{
		return;
	}
	int i = 0;
	for (; i < heap->size; ++i)
	{
		printf("[%d : %d]  ",i,heap->data[i]);
	}
	printf("\n");
}

void TestHeapInit()
{
	HEAP_HEAD;
	Heap heap;
	HeapInit(&heap, &Less);
}

void TestHeapInsert()
{
	HEAP_HEAD;
	Heap heap;
	HeapInit(&heap, &Less);
	HeapInsert(&heap, 12);
	HeapInsert(&heap, 6);
	HeapInsert(&heap, 8);
	HeapInsert(&heap, 1);
	HeapInsert(&heap, 2);
	HeapInsert(&heap, 18);
	PrintHeap(&heap);
}

void TestHeapFindRoot()
{
	HEAP_HEAD;
	Heap heap;
	HeapInit(&heap, &Less);
	HeapInsert(&heap, 12);
	HeapInsert(&heap, 6);
	HeapInsert(&heap, 8);
	HeapInsert(&heap, 1);
	HeapInsert(&heap, 2);
	HeapInsert(&heap, 18);
	PrintHeap(&heap);
	HeapType value;
	int i = HeapFindRoot(&heap, &value);
	printf("except value 1 actual %d\n",value);
	printf("except 1 actual %d\n",i);
}


void TestHeapErase()
{
	HEAP_HEAD;
	Heap heap;
	HeapInit(&heap, &Less);
	HeapInsert(&heap, 12);
	HeapInsert(&heap, 6);
	HeapInsert(&heap, 8);
	HeapInsert(&heap, 1);
	HeapInsert(&heap, 2);
	HeapInsert(&heap, 18);
	PrintHeap(&heap);
	HeapErase(&heap);
	PrintHeap(&heap);
}

void TestEmptySizeDestroy()
{
	HEAP_HEAD;
	Heap heap;
	HeapInit(&heap, &Less);
	HeapInsert(&heap, 12);
	HeapInsert(&heap, 6);
	HeapInsert(&heap, 8);
	HeapInsert(&heap, 1);
	HeapInsert(&heap, 2);
	HeapInsert(&heap, 18);
	PrintHeap(&heap);
	int e = HeapEmpty(&heap);
	printf("except 0 actul %d\n",e);
	size_t s = HeapSize(&heap);
	printf("except 6 actul %d\n",s);
	HeapDestroy(&heap);
	PrintHeap(&heap);
}

void TestHeapSort()
{
	HEAP_HEAD;
	int arr[] = {12,6,8,1,2,18};
	HeapSort(arr,6);
}

int main()
{
	TestHeapInit();
	TestHeapInsert();
	TestHeapFindRoot();
	TestHeapErase();
	TestEmptySizeDestroy();
	TestHeapSort();
	return 0;
}
