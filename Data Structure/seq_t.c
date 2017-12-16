
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

void gei_yuansu_chazhao_xiabiao(seqlist *seq,TYPECHAR value) // 给元素查找下标subscript  value 为所给元素
{
	size_t i = 0;
	assert(seq);
	for(i=0; i<seq->size; i++)
	{
		if(seq->seq_t[i] == value)
		{
			printf("查找元素下标为：%d\n",i);
			break;
		}
	}
	if(i==seq->size)
	{
		printf("未查找到\n");	
	}
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


int main()
{
	initlist(&seq);
	//end_push_list(&seq,'a');
	//end_push_list(&seq,'b');
	//end_push_list(&seq,'c');
	//end_pop_list(&seq);
	//frist_push_list(&seq,'d');
	//frist_push_list(&seq,'e');
	//frist_pop_list(&seq);
	//read_element_of_anywhere_address(&seq,0);
	//update_element_of_anywhere_address(&seq,2,'q');
	//gei_yuansuh_shibie_xiabiao(&seq,'b');
	//insert_element_of_anywhere_address(&seq,0,'w');
	show(&seq);
	return 0;
}