#pragma once

#include<stdio.h>
#include<stdint.h>
#include<malloc.h>
#include<string.h>

typedef struct BitMap{
	uint64_t *data;
	// bit位数最大为多少。
	size_t capacity;
}BitMap;

// 初始化，并且传入位图中最大的bit位数。
void BitMapInit(BitMap *bm, size_t capacity);

// 需要把第index位变为1.
void BitMapSet(BitMap *bm, size_t index);

// 需要把第index位变为0.
void BitMapUnset(BitMap *bm, size_t index);

// 测试第index位是1还是0，1返回1，0返回0.
int BitMapTestBit(BitMap *bm, size_t index);

// 让BitMap的bit全为1
void BitMapFill1(BitMap *bm);

// bit位全清0.
void BitMapClear(BitMap *bm);

// 销毁BitMap
void BitMapDestory(BitMap *bm);
