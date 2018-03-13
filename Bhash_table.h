#pragma once


#include<stdio.h>

#define MAXREPOSITORY 1000

typedef enum Status{

	Empty,   // 表示空
	Valid,   // 表示有效元素
	Invalid // 用状态表示被删除的元素
}Status;

typedef int KeyType;
typedef int ValueType;

// 用来记录每个节点的具体信息
typedef struct HashElem{
	KeyType key;      // 需要记录的值
	ValueType value;  // 记录值的个数
	Status sta;		  // 这个值是否有效
}HashElem;

typedef size_t(*HashFunc)(KeyType);

typedef struct HashTable{
	HashElem data[MAXREPOSITORY];
	size_t size;  // 用来判断是否达到负载因子
	HashFunc hash_func;
}HashTable;

// 初始化
void HashTableInit(HashTable *ht, HashFunc func);

// 插入key
int HashTableInsert(HashTable *ht, KeyType key, ValueType value);

// 通过key来查找value
int HashTableFind(HashTable *ht, KeyType key, ValueType *value);

// 删除key所对应的节点 （将状态置为Invalid）
void HashTableRemove(HashTable *ht, KeyType key);

// 判断是否为空
int HashTableEmpty(HashTable *ht);

// 求hash长度
size_t HashTableSize(HashTable *ht);

// 销毁hash
void HashTableDestroy(HashTable *ht);
