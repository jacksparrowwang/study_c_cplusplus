#include"bloomfilter.h"



size_t Func1(const char *str)
{
	size_t hash = 0;
	size_t magic = 63689;
	size_t ch = 0;
	while (ch = (size_t)*str++)
	{
		hash = hash * magic + ch;
		magic *= 378551;
	}
	return hash;
}

size_t Func2(const char *str)
{
	size_t hash = 0;
	size_t ch;
	long  i = 0;
	for (; ch = (size_t) *str++; ++i)
	{
		if ((i & 1) == 0)
		{
			hash ^= (hash << 7 ^ ch ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
		}
	}
	return hash;
}


// 初始化，加入哈希函数
void BloomFilterInit(BloomFilter *bf)
{
	if (bf == NULL)
	{
		return;
	}
	BitMapInit(&bf->bitmap, BITMAPCAPACITY);
	bf->hash_func[0] = Func1;
	bf->hash_func[1] = Func2;
}

// 对字符串进行插入
void BloomFilterInsert(BloomFilter *bf, const char *str)
{
	if (bf == NULL || str == NULL)
	{
		return;
	}
	size_t i = 0;
	for(; i < HASHFUNCSIZE; ++i)
	{
		size_t index = bf->hash_func[i](str) % BITMAPCAPACITY;
		BitMapSet(&bf->bitmap, index);
	}
}

// 判断是否存在相同的字符串
int BloomFilterExist(BloomFilter *bf, const char *str)
{
	if (bf == NULL || str == NULL)
	{
		// 非法输入或者str指针为空。
		return -1;
	}
	int i = 0; 
	int tmp = 0;
	for (; i < HASHFUNCSIZE; ++i)
	{
		size_t index = bf->hash_func[i](str) % BITMAPCAPACITY;
		tmp = BitMapTestBit(&bf->bitmap, index);
		if (tmp == 0)
		{
			return 0;
		}
	}
	return 1;
}


// 对过滤器进行销毁
void BloomFilterDestory(BloomFilter *bf)
{
	if (bf == NULL)
	{
		return;
	}
	BitMapDestory(&bf);
	bf->hash_func[0] = NULL;
	bf->hash_func[1] = NULL;
}

/////////////////////////
#if 1

#define TESTHEAD printf("\n============%s=========\n",__FUNCTION__)
void TestInsert()
{
	TESTHEAD;
	BloomFilter bf;
	BloomFilterInit(&bf);
	BloomFilterInsert(&bf,"Hello");
	int i = 0;
	for (; i < BITMAPCAPACITY / (sizeof(uint64_t) * 8) + 1; ++i)
	{
		if (bf.bitmap.data[i] != 0)
		{
			printf("[下标 %d] [%x]   ",i,bf.bitmap.data[i]);
		}
	}
}

void TestExist()
{
	TESTHEAD;
	BloomFilter bf;
	BloomFilterInit(&bf);
	BloomFilterInsert(&bf,"Hello");
	int ret  = BloomFilterExist(&bf,"Hello");
	printf("except 1 actual %d\n",ret);
	ret = BloomFilterExist(&bf,"adf");
	printf("except 1 actual %d\n",ret);
}

int main()
{
	TestInsert();
	TestExist();
	return 0;
}
#endif
