#define _CRT_SECURE_NO_WARNINGS 1 
#include<iostream>
using namespace std;
#include "FileCompress.h"
int main()
{
	FileCompress f;
	f.Compress("input.txt");
	f.Uncompress("input.txt.huffman");
	return 0;
}