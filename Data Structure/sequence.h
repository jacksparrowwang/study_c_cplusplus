#pragma once
#include<assert.h>
#define sequence_table_max_length 100
#define TYPECHAR char
#define SHOWTYPE "%c"

typedef int INT;

typedef struct seqlist
{
	size_t size ;
	TYPECHAR seq_t [sequence_table_max_length];
	
}seqlist;

seqlist seq ;

void show(seqlist *seq);
void initlist(seqlist *seq);

//尾部插入一个元素
void end_push_list(seqlist *seq,TYPECHAR value);

//尾部删除一个元素
void end_pop_list(seqlist *seq);

//首部插入一个元素
void frist_push_list(seqlist *seq,TYPECHAR value);

//在顺序表首部删除一个元素
void frist_pop_list(seqlist *seq);

//读取任意位置的元素。address为位置。
void read_element_of_anywhere_address(seqlist *seq,size_t address);

//修改指定位置的元素。address为修改的下标。value为修改成的值。
void update_element_of_anywhere_address(seqlist *seq,size_t address,TYPECHAR value);

// 给元素查找下标subscript  value 为所给元素
void gei_yuansuh_shibie_xiabiao(seqlist *seq,TYPECHAR value);

//在任意位置插入一个元素。address插入的位置。value要插入的值。
void insert_element_of_anywhere_address(seqlist *seq,size_t address,TYPECHAR value);

//删除指定位置的值
void seqListErase_address(seqlist *seq, size_t pos);

//按照指定值来删除，如果重复只删除第一个。
void SeqListRemove(seqlist* seq, TYPECHAR to_delete); 

//按照指定值来删除，表中所有要删除的值，时间复杂度为O（n）
void SeqListRemoveAll(seqlist* seq, TYPECHAR to_delete);

//获取顺序表中的元素
size_t SeqListSize(seqlist* seq);

//判断顺序表是否为空,为空返回1，不为空返回0。
int SeqListEmpty(seqlist* seq);

//冒泡排序
void SeqListBubbleSort(seqlist* seq); 

//回掉函数冒泡排序
void SeqListBubbleSortEx(seqlist* seq, INT (*cmp)(TYPECHAR , TYPECHAR));