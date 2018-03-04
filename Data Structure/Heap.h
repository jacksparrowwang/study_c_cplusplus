#pragma once
#include<stdio.h>

#define MAXREPOSITORY 1000

typedef int HeapType;

typedef int (*Compare)(HeapType, HeapType);

typedef struct Heap{
	HeapType data[MAXREPOSITORY];
	size_t size;
	Compare cmp;
}Heap;

// 初始化。
void HeapInit(Heap *heap, Compare compare);

// 入堆（在堆中插入元素）。
void HeapInsert(Heap *heap, HeapType value);

// 取堆顶元素。
int HeapFindRoot(Heap *heap, HeapType *value);

// 删除堆顶元素。
void HeapErase(Heap *heap);

// 判断堆是否为空。
int HeapEmpty(Heap *heap);

// 求堆中元素的个数。
size_t HeapSize(Heap *heap);

// 销毁堆。
void HeapDestroy(Heap *heap);

// 堆的排序。
void HeapSort(HeapType arr[], size_t size);
