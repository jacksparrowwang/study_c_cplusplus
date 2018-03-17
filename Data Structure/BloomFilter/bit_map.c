#include"bit_map.h"


// 初始化，并且传入位图中最大的bit位数。
void BitMapInit(BitMap *bm, size_t capacity)
{
	if (bm == 0)
	{
		return;
	}
	bm->capacity = capacity;
	bm->data = (uint64_t *)malloc(capacity / (sizeof(uint64_t ) * 8) + 1);
	printf("bm->capacity %d\n", bm->capacity);
	printf("bm->data %p\n\n\n", bm->data);
}

// 找到index在第n个元素和n元素中offset bit位上。
size_t FindAddre(size_t *n, size_t index)
{
	*n = index / (sizeof(uint64_t) * 8);
	size_t offset = index % (sizeof(uint64_t) * 8);
	return offset;
}

// 需要把第index位变为1.
void BitMapSet(BitMap *bm, size_t index)
{
	if (bm == NULL)
	{
		return;
	}
	size_t n = 0;
	size_t offset = FindAddre(&n, index);
	bm->data[n] |= (1ul << offset);
	return;
}

// 需要把第index位变为0.
void BitMapUnset(BitMap *bm, size_t index)
{
	if (bm == NULL)
	{
		return;
	}
	size_t n = 0;
	size_t offset = FindAddre(&n, index);
	bm->data[n] &= ~(1ul << offset);
	return;
}

// 测试第index位是1还是0，1返回1，0返回0.
int BitMapTestBit(BitMap *bm, size_t index)
{
	if (bm == NULL)
	{
		return -1;
	}
	size_t n = 0;
	size_t offset = FindAddre(&n, index);
	if ((bm->data[n] | (1ul << offset)) == bm->data[n])
	{
		return 1;
	}
	return 0;
}

// 让BitMap的bit全为1
void BitMapFill1(BitMap *bm)
{
	if (bm == NULL)
	{
		return;
	}
	// 求出的是开辟了k个字节
	size_t k = bm->capacity / (sizeof(uint64_t) * 8) + 1;
	memset(bm->data, 0xff, sizeof(uint64_t) * k);
}

// bit位全清0.
void BitMapClear(BitMap *bm)
{
	if (bm == NULL)
	{
		return;
	}
	// 求出的是开辟了k个字节
	size_t k = bm->capacity / (sizeof(uint64_t) * 8) + 1;
	memset(bm->data, 0, sizeof(uint64_t) * k);
}

// 销毁BitMap
void BitMapDestory(BitMap *bm)
{
	if (bm == NULL)
	{
		return;
	}
	free(bm->data);
	bm->data = NULL;
	bm->capacity = 0;
}

////////////////////////////
//以下是测试函数
////////////////////////////

#if 0

#define TESTHEAD printf("\n============%s=========\n",__FUNCTION__)


void TestInit()
{
	TESTHEAD;
	BitMap bm;
	BitMapInit(&bm, 128);
}

void TestBitMapSet()
{
	TESTHEAD;
	BitMap bm;
	BitMapInit(&bm, 128);
	BitMapSet(&bm,1);
	BitMapSet(&bm,0);
	BitMapSet(&bm,64);
	BitMapSet(&bm,70);
	int i = 0;
	for (; i < bm.capacity / (sizeof(uint64_t) * 8) + 1; ++i)
	{
		printf("[下标 %d] [%x]   ",i,bm.data[i]);
	}
	//printf("except 2 actual %x",bm.data[0]);
}

void TestBitMapUnset()
{
	TESTHEAD;
	BitMap bm;
	BitMapInit(&bm, 63);
	BitMapSet(&bm,1);
	BitMapSet(&bm,0);
	BitMapSet(&bm,64);
	BitMapUnset(&bm,64);
	int i = 0;
	for (; i < bm.capacity / (sizeof(uint64_t) * 8) + 1; ++i)
	{
		printf("[下标 %d] [%x]   ",i,bm.data[i]);
	}
}

void TestBitMapTestBit()
{
	TESTHEAD;
	BitMap bm;
	BitMapInit(&bm, 63);
	BitMapSet(&bm,1);
	BitMapSet(&bm,0);
	BitMapSet(&bm,64);
	int ret = BitMapTestBit(&bm,1);
	printf("except 1 actual %d\n",ret);
	ret = BitMapTestBit(&bm,2);
	printf("except 0 actual %d\n",ret);
}

void TestBitMapFill()
{
	TESTHEAD;
	BitMap bm;
	BitMapInit(&bm, 63);
	BitMapSet(&bm,1);
	BitMapSet(&bm,0);
	BitMapSet(&bm,64);
	BitMapFill1(&bm);
	int i = 0;
	for (; i < bm.capacity / (sizeof(uint64_t) * 8) + 1; ++i)
	{
		printf("[下标 %d] [%x]   ",i,bm.data[i]);
	}
}

void TestBitMapClear()
{
	TESTHEAD;
	BitMap bm;
	BitMapInit(&bm, 63);
	BitMapSet(&bm,1);
	BitMapSet(&bm,0);
	BitMapSet(&bm,64);
	BitMapClear(&bm);
	int i = 0;
	for (; i < bm.capacity / (sizeof(uint64_t) * 8) + 1; ++i)
	{
		printf("[下标 %d] [%x]   ",i,bm.data[i]);
	}
}

void TestBitMapDestory()
{
	TESTHEAD;
	BitMap bm;
	BitMapInit(&bm, 63);
	BitMapSet(&bm,1);
	BitMapSet(&bm,0);
	BitMapSet(&bm,64);
	BitMapDestory(&bm);
}

int main()
{
	TestInit();
	TestBitMapSet();
	TestBitMapUnset();
	TestBitMapTestBit();
	TestBitMapFill();
	TestBitMapClear();
	TestBitMapDestory();
	return 0;
}
#endif 
