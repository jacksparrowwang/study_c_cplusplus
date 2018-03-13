#include"Bhash_table.h"

size_t Func(KeyType key)
{
	return key % MAXREPOSITORY;
}

// 初始化
void HashTableInit(HashTable *ht, HashFunc func)
{
	if (ht == NULL || func == NULL)
	{
		return;
	}
	int i = 0;
	for (; i < MAXREPOSITORY; ++i)
	{
		ht->data[i].sta = Empty;
	}
	ht->size = 0;
	ht->hash_func = func;
}


// 插入key
int HashTableInsert(HashTable *ht, KeyType key, ValueType value)
{
	if (ht == NULL)
	{
		return 0;
	}
	// 当插入一定到达负载因子，就需要扩充
	// 不然哈希冲突概率会比较大，效率下降。
	if (ht->size >= MAXREPOSITORY * 0.5)
	{
		return 0;
	}
	// 偏移量。
	size_t offset = ht->hash_func(key);
	while (1)
	{
		//if (ht->data[offset].key == key && ht->data[offset].sta == Valid)
		if (ht->data[offset].sta == Valid)
		{
			++offset; 
		}
		// 遇到空位置就是要插入的位置。
		else if (ht->data[offset].sta == Empty)
		{
			ht->data[offset].key = key;
			ht->data[offset].sta = Valid;
			ht->data[offset].value = value;
			++ht->size;
			return 1;
		}
		else
		{
			//++offset;
			if (offset >= MAXREPOSITORY)
			{
				offset -= MAXREPOSITORY;
			}
		}
	}
}

// 通过key来查找value
int HashTableFind(HashTable *ht, KeyType key, ValueType *value)
{
	if (ht == NULL || value == NULL)
	{
		return 0;
	}
	size_t offset = ht->hash_func(key);
	while (1)
	{
		if (ht->data[offset].key == key && ht->data[offset].sta == Valid)
		{
			*value = ht->data[offset].value;
			return 1;
		}
		else if (ht->data[offset].sta == Empty)
		{
			return 0;
		}
		else
		{
			++offset;
			if (offset >= MAXREPOSITORY)
			{
				offset -= MAXREPOSITORY;
			}
		}
	}
	return 0;
}

// 删除key所对应的节点 （将状态置为Invalid）
void HashTableRemove(HashTable *ht, KeyType key)
{
	if (ht == NULL)
	{
		return;
	}
	size_t offset = ht->hash_func(key);
	while (1)
	{
		if (ht->data[offset].key == key && ht->data[offset].sta == Valid)
		{
			// 这里不能置为Empty的原因，万一前面的元素哈希冲突到了此元素后面。
			ht->data[offset].sta =Invalid;
			--ht->size;
			return;
		}
		else if (ht->data[offset].sta == Empty)
		{
			return;
		}
		else
		{
			++offset;
			if (offset >= MAXREPOSITORY)
			{
				offset -= MAXREPOSITORY;
			}
		}
	}
}

// 判断是否为空
int HashTableEmpty(HashTable *ht)
{
	if (ht == NULL)
	{
		return -1;
	}
	if (ht->size == 0)
	{
		return 1;
	}
	return 0;
}

// 求hash长度
size_t HashTableSize(HashTable *ht)
{
	if (ht == NULL)
	{
		return 0;
	}
	return ht->size;
}

// 销毁hash
void HashTableDestroy(HashTable *ht)
{
	if (ht == NULL)
	{
		return;
	}
	int i = 0;
	for (; i < MAXREPOSITORY; ++i)
	{
		ht->data[i].sta = Empty;
	}
	ht->size = 0;
	ht->hash_func = NULL;
}


//////////////////////////
//以下为测试代码
//////////////////////////

#define TEST_HEAD printf("\n====================%s===================\n",__FUNCTION__)


void PrintHashTable(HashTable *ht)
{
	if (ht == NULL)
	{
		return;
	}
	int i = 0;
	for(; i < MAXREPOSITORY; ++i)
	{
		if (ht->data[i].sta == Valid)
		printf("数组下标[%d] key[%d] value[%d]\n",i,ht->data[i].key,ht->data[i].value);
	}
}

void TestHashTableInit()
{
	TEST_HEAD;
	HashTable ht;
	HashTableInit(&ht, Func);
	int i = 0;
	for (; i < MAXREPOSITORY; ++i)
	{
		if (ht.data[i].sta != Empty)
		{
			printf("%d ",i);
		}
	}
	printf("ht->size except 0,actual %d\n",ht.size);
}

void TestHashTableInsert()
{
	TEST_HEAD;
	HashTable ht;
	HashTableInit(&ht, Func);
	HashTableInsert(&ht, 1, 20);
	HashTableInsert(&ht, 2, 30);
	HashTableInsert(&ht, 101, 40);
	HashTableInsert(&ht, 1002, 50);
	HashTableInsert(&ht, 1001, 70);
	HashTableInsert(&ht, 999, 70);
	HashTableInsert(&ht, 1999, 80);
	PrintHashTable(&ht);
}

void TestHashTableFind()
{
	TEST_HEAD;
	HashTable ht;
	HashTableInit(&ht, Func);
	HashTableInsert(&ht, 1, 20);
	HashTableInsert(&ht, 2, 30);
	HashTableInsert(&ht, 101, 40);
	HashTableInsert(&ht, 1002, 50);
	HashTableInsert(&ht, 1001, 70);
	HashTableInsert(&ht, 999, 70);
	HashTableInsert(&ht, 1999, 80);
	PrintHashTable(&ht);
	ValueType ret;
	ValueType ret1;
	ValueType ret2;
	int bool0 = HashTableFind(&ht, 101, &ret);
	int bool1 = HashTableFind(&ht, 1001, &ret1);
	int bool2 = HashTableFind(&ht, 199, &ret2);
	printf("[1 : %d]key 101 value except 40,actual %d\n",bool0,ret);
	printf("[1 : %d]key 1001 value except 70,actual %d\n",bool1,ret1);
	printf("[0 : %d]key 199 value except   ,actual %d\n",bool2,ret2);
}

void TestHashTableRemove()
{
	TEST_HEAD;
	HashTable ht;
	HashTableInit(&ht, Func);
	HashTableInsert(&ht, 1, 20);
	HashTableInsert(&ht, 2, 30);
	HashTableInsert(&ht, 101, 40);
	HashTableInsert(&ht, 1002, 50);
	HashTableInsert(&ht, 1001, 70);
	HashTableInsert(&ht, 999, 70);
	HashTableInsert(&ht, 1999, 80);
	HashTableRemove(&ht, 101);
	PrintHashTable(&ht);
}

int main()
{
	TestHashTableInit();
	TestHashTableInsert();
	TestHashTableFind();
	TestHashTableRemove();
	return 0;
}
