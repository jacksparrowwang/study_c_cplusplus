#pragma once
#include<assert.h>
#define sequence_table_max_length 100
#define TYPECHAR char
#define SHOWTYPE "%c"

typedef struct seqlist
{
	size_t size ;
	TYPECHAR seq_t [sequence_table_max_length];
	
}seqlist;

seqlist seq ;

void show(seqlist *seq);
void initlist(seqlist *seq);
void end_push_list(seqlist *seq,TYPECHAR value);
void end_pop_list(seqlist *seq);
void frist_push_list(seqlist *seq,TYPECHAR value);
void frist_pop_list(seqlist *seq);
void read_element_of_anywhere_address(seqlist *seq,size_t address);
void update_element_of_anywhere_address(seqlist *seq,size_t address,TYPECHAR value);
void gei_yuansuh_shibie_xiabiao(seqlist *seq,TYPECHAR value);
void insert_element_of_anywhere_address(seqlist *seq,size_t address,TYPECHAR value);

