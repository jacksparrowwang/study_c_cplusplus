#ifndef __ADDRESSBOOK_H__
#define __ADDRESSBOOK_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

#define NAME_MAX 200
#define GENDER_MAX 100
#define ADDRESS_MAX 200
#define NUMBER_MAX 200
#define SEQLIST_MAX 1000
#define FILE_PATH "address_book.txt"

typedef struct person_inf
{	
	char name[NAME_MAX];
	char gender[GENDER_MAX];
	char number[NUMBER_MAX];
	char address[ADDRESS_MAX];
}person_inf;

typedef struct address_book
{
	size_t size;
	person_inf data[SEQLIST_MAX];
}address_book;

//初始化通讯录
void address_book_init(address_book *book);

//添加信息
void address_book_add(address_book *book);

//显示信息
void address_book_display(address_book *book);

//删除所有信息
void address_book_delete_all(address_book *book);

//保存信息
void address_book_save(address_book *book);

//加载信息
void address_book_load(address_book *book);

//修改信息
void address_book_update(address_book *book);

//删除信息
void address_book_delete(address_book *book);

//查找信息
void address_book_find(address_book *book);

//销毁通讯录
void adderss_book_destory(address_book *book);

#endif