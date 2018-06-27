#define _CRT_SECURE_NO_WARNINGS 1 
#include<iostream>
using namespace std;
#include "FileCompress.h"
int main()
{
	FileCompress f;
	f.Compress("1.avi");
	f.Uncompress("1.avi.huffman");
	return 0;
}