
#include<stdio.h>
#include"sequence.h"


void show(seqlist *seq)  //打印列表
{
	size_t i = 0;
	for(i=0; i <(seq->size); i++)
	{
		printf("%c",seq->seq_t[i]);
	}
	printf("\n");
}


void initlist(seqlist *seq)  //初始化列表
{
	seq->size = 0;
	assert(seq);
	seq->seq_t[seq->size] = 0;
}

void end_push_list(seqlist *seq,TYPECHAR value)  //尾部插入一个元素
{
	assert(seq);
	if(seq->size > sequence_table_max_length)
	{
		fprintf(stderr,"顺序表长度不足\n");
		return ;
	}
	seq->seq_t[seq->size] = value;
	seq->size++;

}


void end_pop_list(seqlist *seq)  //尾部删除一个元素
{
	assert(seq);
	if(seq->size <= 0)
	{
		fprintf(stderr,"已经到达最首部\n");
		return;
	}
	seq->size--;
}



void frist_push_list(seqlist *seq,TYPECHAR value)  //首部插入一个元素
{
	size_t i = 0;
	assert(seq);
	seq->size++;
	if(seq->size > sequence_table_max_length)
	{
		fprintf(stderr,"顺序表长度不足\n");
	}
	for(i=seq->size; i>0; i--)
	{
		seq->seq_t[i] = seq->seq_t[i-1];
	}
	seq->seq_t[i] = value;//下标为0

}

void frist_pop_list(seqlist *seq)  //在顺序表首部删除一个元素
{
	size_t i = 0;
	assert(seq);
	seq->size--;
	for(i=0; i < seq->size; i++)
	{
		seq->seq_t[i] = seq->seq_t[i+1];
	}
	
}

//读取任意位置的元素。address为位置。
void read_element_of_anywhere_address(seqlist *seq,size_t address)
{
	assert(seq);
	if(address > seq->size)
	{
		fprintf(stderr,"访问越界\n");
	}
	printf(SHOWTYPE,seq->seq_t[address]);
}

//修改指定位置的元素。address为修改的下标。value为修改成的值。
void update_element_of_anywhere_address(seqlist *seq,size_t address,TYPECHAR value) 
{
	assert(seq);
	if(address > seq->size)
	{
		fprintf(stderr,"修改越界\n");
	}
	seq->seq_t[address] = value;
}

size_t gei_yuansu_chazhao_xiabiao(seqlist *seq,TYPECHAR value) // 给元素查找下标subscript  value 为所给元素
{
	size_t i = 0;
	assert(seq);
	for(i=0; i<seq->size; i++)
	{
		if(seq->seq_t[i] == value)
		{
			printf("查找元素下标为：%d\n",i);
			return i;
		}
	}
	if(i==seq->size)
	{
		printf("未查找到\n");	
	}
	return -1;
}


//在任意位置插入一个元素。address插入的位置。value要插入的值。
void insert_element_of_anywhere_address(seqlist *seq,size_t address,TYPECHAR value)
{	
	size_t i = 0;
	assert(seq);
	seq->size++;
	if(seq->size > sequence_table_max_length)
	{
		fprintf(stderr,"顺序表长度不足\n");
	}
	for(i = seq->size; i>address; i--)
	{
		seq->seq_t[i] = seq->seq_t[i-1];
	}
	seq->seq_t[i] = value;
}

//删除指定位置的元素
void seqListErase_address(seqlist* seq, size_t pos)
{
	size_t i = 0;
	assert(seq);
	if(pos > seq->size)
	{
		printf("未查找到\n");
		return ;
	}
	for(i=pos; i < seq->size; i++)
	{
		seq->seq_t[i] = seq->seq_t[i+1];
	}
	(seq->size)--;
	return ;
}

//按照指定的值来删除,如果重复只删除第一个。时间复杂度为O（n）
void SeqListRemove(seqlist *seq, TYPECHAR to_delete)
{	
	size_t i = 0;
	assert(seq);
	i = gei_yuansu_chazhao_xiabiao(seq,to_delete);
	seqListErase_address(seq,i);
	return ;
}

//按照指定值来删除，表中所有要删除的值，时间复杂度为O（n）
void SeqListRemoveAll(seqlist* seq, TYPECHAR to_delete)
{
	size_t count = 0;
	size_t i = 0;
	assert(seq);
	for(i = 0; i < seq->size; i++)
	{
		if(seq->seq_t[i] != to_delete)
		{
			seq->seq_t[i-count] = seq->seq_t[i];
		}
		else
		{
			count++;
		}
	}
	seq->size-=count;
	return ;
}


//获取顺序表中元素的个数
size_t SeqListSize(seqlist* seq)
{
	assert(seq);
	return seq->size;
}

//判断顺序表是否为空,为空返回1，不为空返回0。
int SeqListEmpty(seqlist* seq)
{
	assert(seq);
	if (seq->size == 0)
	{
		return 1;
	}
		return 0;
}


//交换
void swap(char *p, char *q)
{
	char temp = *p;
	*p = *q;
	*q = temp;
}

//冒泡排序
void SeqListBubbleSort(seqlist* seq)
{
	size_t i = 0;
	size_t j = 0;
	assert(seq);
	for(i = 0; i < seq->size-1; i++)
	{
		for(j = 0; j < seq->size-i-1; j++)
		{
			if(seq->seq_t[j] > seq->seq_t[j+1])
			{
				swap(&(seq->seq_t[j]),&(seq->seq_t[j+1]));
			}
		}
	}
}

//回掉函数
int cmp(TYPECHAR value1,TYPECHAR value2)
{
	return value1 - value2 ;
}

//回掉函数冒泡排序
void SeqListBubbleSortEx(seqlist* seq, INT (*cmp)(TYPECHAR , TYPECHAR))
{
	size_t i = 0;
	size_t j = 0;
	assert(seq);
	for (i = 0; i < seq->size-1; i++)
	{
		for (j = 0; j < seq->size-i-1; j++)
		{
			if (cmp(seq->seq_t[j],seq->seq_t[j+1]) >0)
				swap(&(seq->seq_t[j]),&(seq->seq_t[j+1]));
		}
	}
}


int main()
{
	initlist(&seq);
	end_push_list(&seq,'a');
	end_push_list(&seq,'b');
	end_push_list(&seq,'c');
	end_push_list(&seq,'b');
	//end_pop_list(&seq);
	//frist_push_list(&seq,'d');
	//frist_push_list(&seq,'e');
	//frist_pop_list(&seq);
	//read_element_of_anywhere_address(&seq,0);//查找下表的元素
	//update_element_of_anywhere_address(&seq,2,'q');//修改指定位置的元素
	//gei_yuansuh_shibie_xiabiao(&seq,'b');//给出元素查找出元素的下表
	//insert_element_of_anywhere_address(&seq,0,'w');//在任意位置插入元素
	//seqListErase_address(&seq,4);//删除指定位置的元素
	//SeqListRemove(&seq,'b');//删除所给值的顺序表中的第一个元素
	//SeqListRemoveAll(&seq,'c');//删除所给指定值的所有元素
	//printf("%lu",SeqListSize(&seq));//计算顺序表中的个数
	//printf("%d",SeqListEmpty(&seq));//判断空顺序表
	//SeqListBubbleSort(&seq);//冒泡排序
	//SeqListBubbleSortEx(&seq, cmp);//回掉函数冒泡排序的测试
	show(&seq);
	return 0;
}