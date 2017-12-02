# cg19.github.com
测试
#include<stdio.h>
#include<assert.h>
#include<string.h>
char *my_strncpy(char *dest,const char *src,size_t count)
{
	int amount = 0;
	char *re = dest;
	assert(dest);
	assert(src);
	while(*dest = *src)
	{
		amount++;
		if(amount == count)
		{
			break;
		}
		dest++;
		src++;
	}
	return re;
}

char *my_strncat(char *dest,const char *src,size_t count)
{
	int amount = 0;
	char *re = dest;
	assert(dest);
	assert(src);
	while(*dest!='\0')
	{
		dest++;
	}
	while(*dest = *src)
	{
		amount++;
		if(amount == count)
		{
			break;
		}
		dest++;
		src++;
	}
	return re;
}

int my_strncmp(const char *string1,const char *string2,size_t count)
{
	int ret = 0;
	int amount = 0;
	assert(string1);
	assert(string2);
	while(!(ret = *(unsigned char*)string1 - *(unsigned char *)string2)&&*string2)
	{
		amount++;
		string1++;
		string2++;
		if(amount == count)
		{
			break;
		}
	}
	if(ret>0)
	{
		return 1;
	}
	else if(ret<0)
	{
		return -1;
	}
	return ret;
}
int main()
{
	char arr1[] = "124";
	char arr[6] = "123";
	//p =my_strncmp(arr,arr1,3);
	//my_strncpy(arr,arr1,2);
	//my_strncat(arr,arr1,3);
	return 0;
}
