#pragma once
// 布隆过滤器

#include<stdio.h>
#include<stdint.h>
#include"bit_map.h"

#define HASHFUNCSIZE 2
#define BITMAPCAPACITY 1024

typedef size_t (*HashFunc)(const char *);

typedef struct BloomFilter{
	BitMap bitmap;
	HashFunc hash_func[HASHFUNCSIZE];
}BloomFilter;

// 初始化，加入哈希函数
void BloomFilterInit(BloomFilter *bf);

// 对字符串进行插入
void BloomFilterInsert(BloomFilter *bf, const char *str);

// 判断是否存在相同的字符串
int BloomFilterExist(BloomFilter *bf, const char *str);

// 对过滤器进行销毁
void BloomFilterDestory(BloomFilter *bf);
