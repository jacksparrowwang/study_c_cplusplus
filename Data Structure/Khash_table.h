#pragma once

#include<stdio.h>
#include<stdlib.h>

#define MAXHASHSIZE 1000

typedef int KeyType; 
typedef int ValType; 

typedef size_t (*HashFunc)(KeyType);

typedef struct HashElem{ 
	KeyType key;
	ValType value;
	struct HashElem *next;
}HashElem;

typedef struct HashTable{
	HashElem *data[MAXHASHSIZE];
	size_t size;
	HashFunc hash_func;
}HashTable;

// 对开开散列哈希表初始化。
void HashTableInit(HashTable *ht, HashFunc func);

// 进行哈希表的插入。
int HashTableInsert(HashTable *ht, KeyType key, ValType value);

// 进行key对应value值的查找。
int HashTableFind(HashTable *ht, KeyType key, ValType *value);

// 对key的节点进行删除。
void HashTableRemove(HashTable *ht, KeyType key);

// 哈希表中元素的个数。
size_t HashTableSize(HashTable *ht);

// 判断哈希表是否为空。
int HashTableEmpty(HashTable *ht);

// 销毁哈希表。
void HashTableDestory(HashTable *ht);

