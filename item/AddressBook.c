
#define _CRT_SECURE_NO_WARNINGS

#include "AddressBook.h"

//初始化通讯录
void address_book_init(address_book *book)
{
	if(book == NULL)
	{
		return ;
	}
	book->size = 0;
}

//添加信息
void address_book_add(address_book *book)
{
	size_t cur = 0;
	if(book == NULL)
	{
		printf("book is NULL\n");
		return ;
	}
	cur = book->size;
	++book->size;
	printf("添加信息\n");
	printf("请输入要添加的姓名\n");
	scanf("%s",book->data[cur].name);
	printf("请输入要添加的性别\n");
	scanf("%s",book->data[cur].gender);
	printf("请输入要添加的电话\n");
	scanf("%s",book->data[cur].number);
	printf("请输入要添加的地址\n");
	scanf("%s",book->data[cur].address);
	printf("添加成功\n");
	return;
}

//显示信息
void address_book_display(address_book *book)
{
	size_t j = 0;
	if(book == NULL)
	{
		return ;
	}
	printf("序号\t\t姓名\t\t性别\t\t电话\t\t地址\n");
	for(j=0; j< book->size; j++)
	{
		printf("%u\t\t%s\t\t%s\t\t%s\t\t%s\n",j,book->data[j].name,
		book->data[j].gender,book->data[j].number,
		book->data[j].address);
	}
}

//保存信息
void address_book_save(address_book *book)
{
	size_t i = 0;
	FILE *fp = fopen(FILE_PATH,"w");
	if(book == NULL)
	{
		return ;
	}
	if(fp == NULL)
	{
		printf("打开文件失败\n");
		return ;
	}
	//fprintf(fp,"序号\t\t姓名\t\t性别\t\t电话\t\t地址\n");
	for(i=0; i< book->size; i++)
	{
		fprintf(fp,"%u\t\t%s\t\t%s\t\t%s\t\t%s\n",i,book->data[i].name,
		book->data[i].gender,book->data[i].number,
		book->data[i].address);
	}
	fclose(fp);
}

//加载信息
void address_book_load(address_book *book)
{
	size_t len = 0;
	size_t i = 0;
	FILE *fp = fopen(FILE_PATH,"r");

	if(book == NULL)
	{
		return ;
	}
	if(fp == NULL)
	{
		printf("打开文件失败\n");
		return ;
	}
	fseek(fp,0,SEEK_END);
	len = ftell(fp);
	if(len == 0)
	{
		printf("通讯录为空\n\n");
		return ;
	}
	rewind(fp);
	while(!feof(fp))
	{
		fscanf(fp,"%u\t\t%s\t\t%s\t\t%s\t\t%s\n",&i,book->data[book->size].name,//name是数组，在调用数组名时候降级为指针
			book->data[i].gender,book->data[book->size].number,
			book->data[book->size].address);
		i++;
		++book->size;
	}
	fclose(fp);
}


//修改信息
void address_book_update(address_book *book)
{
	size_t i = 0;
	if(book == NULL)
	{
		return ;
	}
	printf("请输入要修改的编号\n");
	scanf("%u",&i);
	if(i > book->size || i < 0)
	{
		printf("输入为非法值\n");
		return ;
	}
	printf("修改信息\n");
	printf("姓名修改为\n");
	scanf("%s",book->data[i].name);
	printf("性别修改为\n");
	scanf("%s",book->data[i].gender);
	printf("修改电话为\n");
	scanf("%s",book->data[i].number);
	printf("地址修改为\n");
	scanf("%s",book->data[i].address);
	printf("修改成功\n");
	return ;
}


//删除信息
void address_book_delete(address_book *book)
{
	size_t i = 0;
	if(book == NULL)
	{
		return ;
	}
	printf("请输入要删除的编号\n");
	scanf("%u",&i);
	if(i > book->size)
	{
		printf("输入为非法值\n");
		return ;
	}
	while(i < book->size)
	{
		book->data[i] = book->data[i+1];
		i++;
	}
	book->size--;
	printf("删除成功\n");
	return;
}

//删除所有信息
void address_book_delete_all(address_book *book)
{
	if(book == NULL)
	{
		return ;
	}
	book->size = 0;
}

//查找信息
void address_book_find(address_book *book)
{
	int flag = 0;
	size_t i = 0;
	int choice = 0;
	char f_name[50];
	char f_number[50];
	if(book == NULL)
	{
		//book为空指针；
		return ;
	}
	printf("请输入要查找的方式\n");
	printf("************************\n");
	printf("*1.姓名查找 2.电话号查找\n");
	printf("************************\n");
	scanf("%d",&choice);
	if (choice == 1)
	{
		//姓名查找
		printf("请输入查找的姓名或者关键字\n");
		scanf("%s",f_name);
		printf("序号\t\t姓名\t\t性别\t\t电话\t\t地址\n");
		while(i < book->size)
		{
			if(strstr(book->data[i].name,f_name)) //用strstr函数来查关键字
			{
				flag = 1;
				printf("%u\t\t%s\t\t%s\t\t%s\t\t%s\n",i,book->data[i].name,
				book->data[i].gender,book->data[i].number,
				book->data[i].address);
			}
			i++;
		}
		if(flag == 0)
		printf("未查找到\n");
	}
	else if (choice == 2)
	{
		//电话号码查找
		printf("请输入查找的电话号或者关键号码\n");
		scanf("%s",f_number);
		printf("序号\t\t姓名\t\t性别\t\t电话\t\t地址\n");
		while(i < book->size)
		{
			if(strstr(book->data[i].number,f_number))
			{
				flag = 1;
				printf("%u\t\t%s\t\t%s\t\t%s\t\t%s\n",i,book->data[i].name,
				book->data[i].gender,book->data[i].number,
				book->data[i].address);
			}
			i++;
		}
		if(flag == 0)
		{
			printf("未查找到\n");
		}
	}
	else
	{
		printf("选择错误\n");
	}
}

/*fseek(fp,100L,0);把文件内部指针移动到离文件开头100字节处；
fseek(fp,100L,1);把文件内部指针移动到离文件当前位置100字节处；
fseek(fp,-100L,2);把文件内部指针退回到离文件结尾100字节处。

ftell(fp);利用函数 ftell() 也能方便地知道一个文件的长。
如以下语句序列： fseek(fp, 0L,SEEK_END); len =ftell(fp)+1; 
首先将文件的当前位置移到文件的末尾，然后调用函数ftell()获得当前
位置相对于文件首的位移，该位移值等于文件所含字节数。
*/

//销毁通讯录
void adderss_book_destory(address_book *book)
{
	FILE *fp = fopen(FILE_PATH,"w");
	if(book == NULL)
	{
		return ;
	}
	if(fp == NULL)
	{
		printf("打开文件失败\n");
		return ;
	}
	fseek(fp,0,SEEK_SET);
	rewind(fp);
	fclose(fp);
	printf("销毁成功\n");
}


enum
{
	EXIT,
	DISPLAY,
	ADD,
	UPDATE,
	Y_DELETE,
	FIND,
	DESTORY
};

//菜单
void menu()
{
	int choice = 0;
	address_book book;
	address_book_init(&book);
	address_book_load(&book);
	while(1)
	{
		printf("===============================\n");
		printf("1.显示通讯录\n");
		printf("2.添加\n");
		printf("3.修改\n");
		printf("4.删除\n");
		printf("5.查找\n");
		printf("6.销毁\n");
		printf("0.退出\n");
		printf("===============================\n");
		scanf("%d",&choice);
		system("cls");
		switch (choice)
		{
			case DISPLAY:
				address_book_display(&book);
				break;
			case ADD:
				address_book_add(&book);
				address_book_save(&book);
				break;
			case UPDATE:
				address_book_update(&book);
				address_book_save(&book);
				break;
			case Y_DELETE:
				address_book_delete(&book);
				address_book_save(&book);
				break;
			case FIND:
				address_book_find(&book);
				break;
			case DESTORY:
				adderss_book_destory(&book);
				address_book_delete_all(&book);
				break;
			case EXIT:
				return ;
				break;
			default:
				printf("输入值非法\n");
				break;
		}
	}

}

int main()
{
	menu();
	return 0;
}