#include"Khash_table.h"

size_t Func(KeyType key)
{
	return key % MAXHASHSIZE;
}

// 对开开散列哈希表初始化。// HashFunc是一个指针类型。
void HashTableInit(HashTable *ht, HashFunc func)
{
	if (ht == NULL || func == NULL)
	{
		return;
	}
	int i = 0;
	for (; i < MAXHASHSIZE; ++i)
	{
		ht->data[i] = NULL;
	}
	ht->size = 0;
	ht->hash_func = func;
}

// 进行创建哈希表中元素节点
HashElem *CreatHashElemNode(KeyType key,ValType value)
{
	HashElem *new_node = (HashElem *)malloc(sizeof(HashElem));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}


// 进行哈希表的插入。
int HashTableInsert(HashTable *ht, KeyType key, ValType value)
{
	if (ht == NULL)
	{
		return 0;
	}
	// 先用哈希函数求出偏移量。
	size_t offset = ht->hash_func(key);
	// 未查找到。
	HashElem *cur = ht->data[offset];
	while (cur != NULL)
	{
		if (cur->key == key)
		{
			return 0;
		}
		cur = cur->next;
	}
	// 链表为不带头单链表
	if (ht->data[offset] == NULL)
	{
		ht->data[offset] = CreatHashElemNode(key,value);
	}
	else
	{
		HashElem *new_node = CreatHashElemNode(key,value);

		// 插入方法1
		// 这里的插入是在头节点的第二个节点开始插入.
		//new_node->next = ht->data[offset]->next;
		//ht->data[offset]->next = new_node;

		// 插入方法2
		// 这里插入是在链表的头节点上插入。
		new_node->next = ht->data[offset];
		ht->data[offset] = new_node;
	}
	++ht->size;
	return 1;
}

// 进行key对应value值的查找。
int HashTableFind(HashTable *ht, KeyType key, ValType *value)
{
	if (ht == NULL || value == NULL)
	{
		return 0;
	}
	// 先找出key所对应数组的位置
	size_t offset = ht->hash_func(key);
	// 遍历链表进行查找。
	HashElem *cur = ht->data[offset];
	while (cur != NULL)
	{
		if (cur->key == key)
		{
			*value = cur->value;
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

// 对key的节点进行删除。
void HashTableRemove(HashTable *ht, KeyType key)
{
	if (ht == NULL)
	{
		return;
	}
	size_t offset = ht->hash_func(key);
	if (ht->data[offset] == NULL)
	{
		return;
	}
	if (ht->data[offset]->key == key)
	{
		HashElem *to_delete = ht->data[offset];
		ht->data[offset] = ht->data[offset]->next;
		free(to_delete);
	}
	else
	{
		HashElem *pre = ht->data[offset];
		HashElem *cur = ht->data[offset]->next;
		while (cur != NULL)
		{
			if(cur->key == key)
			{
				return;
			}
			pre = cur;
			cur = cur->next;
		}
		HashElem *to_delete = pre->next;
		pre->next = to_delete->next;
		free(to_delete);
	}
	--ht->size;
	return;
}

// 哈希表中元素的个数。
size_t HashTableSize(HashTable *ht)
{
	if (ht == NULL)
	{
		return 0;
	}
	return ht->size;
}

// 判断哈希表是否为空。
int HashTableEmpty(HashTable *ht)
{
	if (ht == NULL)
	{
		return 0;
	}
	if (ht->size == 0)
	{
		return 1;
	}
	return 0;
}

// 销毁哈希表。
void HashTableDestory(HashTable *ht)
{
	if (ht == NULL)
	{
		return;
	}
	int i = 0;
	for (; i < MAXHASHSIZE; ++i)
	{
		if  (ht->data[i] != NULL)
		{
			while (ht->data[i] != NULL)
			{
				// 采用头删。
				HashElem *to_delete = ht->data[i];
				ht->data[i] = ht->data[i]->next;
				free(to_delete);
			}
		}
	}
	ht->size = 0;
	ht->hash_func = NULL;
}
//////////////////////////////
//以下是测试代码
//////////////////////////////

#define TESTHEAD printf("\n==============%s==============\n",__FUNCTION__)

void PrintHashTable(HashTable *ht)
{
	if (ht == NULL)
	{
		return;
	}
	int i = 0;
	for (; i < MAXHASHSIZE; ++i)
	{
		if (ht->data[i] != NULL)
		{
			printf("[%d]",i);
			HashElem *cur = ht->data[i];
			while (cur != NULL)
			{
				printf("  [key %lu][value %d]  ",cur->key,cur->value);
				cur = cur->next;
			}
			printf("\n");
		}
	}
}

void TestHashTableInit()
{
	TESTHEAD;
	HashTable ht;
	HashTableInit(&ht, &Func);
	int i = 0;
	for (; i < MAXHASHSIZE; ++i)
	{
		if (ht.data[i] != NULL)
		{
			printf("error\n");
		}
	}
	printf("size except 0 actual %d\n",ht.size);
	printf("ht->hash_func except %p actual %p\n",&Func,ht.hash_func);
}

void TestHashTableInsert()
{
	TESTHEAD;
	HashTable ht;
	HashTableInit(&ht, &Func);
	HashTableInsert(&ht, 1, 100);
	HashTableInsert(&ht, 2, 300);
	HashTableInsert(&ht, 8, 900);
	HashTableInsert(&ht, 1001, 200);
	int ret = HashTableInsert(&ht, 1000001, 400);
	PrintHashTable(&ht);
	printf("ret except 1 actual %d",ret);
}
     
void TestHashTableFind()
{
	TESTHEAD;
	HashTable ht;
	HashTableInit(&ht, &Func);
	HashTableInsert(&ht, 1, 100);
	HashTableInsert(&ht, 2, 300);
	HashTableInsert(&ht, 1001, 200);
	HashTableInsert(&ht, 1000001, 400);
	ValType value;
	int ret = HashTableFind(&ht, 1001, &value);
	printf("ret except 1 actual %d\n [key 1001] [value %d]\n",ret,value);
	ret = HashTableFind(&ht, 1, &value);
	printf("ret except 1 actual %d\n [key 1] [value %d]\n",ret,value);
}

void TestHashTableRemove()
{
	TESTHEAD;
	HashTable ht;
	HashTableInit(&ht, &Func);
	HashTableInsert(&ht, 1, 100);
	HashTableInsert(&ht, 2, 300);
	HashTableInsert(&ht, 1001, 200);
	HashTableInsert(&ht, 1000001, 400);
	PrintHashTable(&ht);
	printf("\n");
	HashTableRemove(&ht, 1000001);
	PrintHashTable(&ht);
	printf("\n");
	HashTableRemove(&ht, 1001);
	PrintHashTable(&ht);
	printf("\n");
	HashTableRemove(&ht, 1);
	PrintHashTable(&ht);
}

void TestHashTableSED()
{
	TESTHEAD;
	HashTable ht;
	HashTableInit(&ht, &Func);
	HashTableInsert(&ht, 1, 100);
	HashTableInsert(&ht, 2, 300);
	HashTableInsert(&ht, 1001, 200);
	HashTableInsert(&ht, 1000001, 400);
	PrintHashTable(&ht);
	int ret = HashTableSize(&ht);
	printf("size except 4 actual %d\n",ret);
	// 空为1，不为空0
	int ret1 = HashTableEmpty(&ht);
	printf("empty except 0 actual %d\n",ret1);
	HashTableDestory(&ht);
	PrintHashTable(&ht);
}

int main()
{
	TestHashTableInit();
	TestHashTableInsert();
	TestHashTableFind();
	TestHashTableRemove();
	TestHashTableSED();
	return 0;
}
