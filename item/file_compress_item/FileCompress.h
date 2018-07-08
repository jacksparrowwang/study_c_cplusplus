#pragma once

#include <stdio.h>
#include <string>
#include <assert.h>
#include "HuffmanTree.h"

#define LEN 256

typedef long long LongType;

struct charInfo
{
	unsigned char ch;
	std::string code;
	LongType count;

	charInfo() :ch(0), code(""), count(0)
	{}

	charInfo operator+(const charInfo& info)
	{
		charInfo ret;
		ret.count = count + info.count;
		return ret;
	}

	// w1 > w2
	bool operator>(const charInfo& info)
	{
		return count > info.count;
	}

	bool operator!=(const charInfo& info)
	{
		return count != info.count;
	}
};

class FileCompress
{
	typedef HuffmanTreeNode<charInfo> TreeNode;

	struct TmpInfo //用来写入和读出在压缩文件中，以此来构建huffman树
	{
		char cha;
		LongType count;
	};

public:

	FileCompress()
	{
		for (size_t i = 0; i < LEN; ++i)
		{
			hashtableInfo[i].ch = i;
			hashtableInfo[i].count = 0;
		}
	}

	// 压
	void Compress(const char* file)
	{
		// 打开原来的文件
		FILE* fd = fopen(file, "rb");
		if (fd == NULL)
		{
			perror("fopen error\n");
			return;
		}

		// 统计数组
		char c = fgetc(fd);
		//c = fgetc(fd);
		//bi:
		while (!feof(fd))
		{
			hashtableInfo[(unsigned char)c].count++;
			c = fgetc(fd);
		}
		/*if ((c = fgetc(fd)) != EOF)
		{
			goto bi;
		}*/

		// 创建huffman树
		charInfo invalid;
		invalid.count = 0;
		HuffmanTree<charInfo> huffman(hashtableInfo, 256, invalid);

		// 获得字节的编码
		std::string code;
		GetCode(huffman.GetRoot(), code);

		// 创建并且打开新的文件按
		std::string compressfile = file;
		compressfile += ".huffman";
		FILE* fin = fopen(compressfile.c_str(), "wb");
		assert(fin);

		// 在压缩文件中写入构建huffman的ch和count
		for (size_t i = 0; i < 256; ++i)
		{

			if (hashtableInfo[i].count > 0)
			{
				TmpInfo tmp;
				tmp.cha = hashtableInfo[i].ch;
				tmp.count = hashtableInfo[i].count;
				fwrite(&tmp, sizeof(TmpInfo), 1, fin);
			}
		}

		TmpInfo tmp;
		tmp.count = -1;
		fwrite(&tmp, sizeof(TmpInfo), 1, fin);


		// 压缩
		fseek(fd, 0, SEEK_SET); // 把原来文件指针移到开头
		c = fgetc(fd);
		char value = 0;
		size_t pos = 0;
		while (!feof(fd))
		{
			// 先拿出hash中对应字符的编码,并且按照比特位写入文件
			std::string& code = hashtableInfo[(unsigned char)c].code;
			for (size_t i = 0; i < code.size(); ++i)
			{
				if (code[i] == '1')
				{
					value |= (1 << pos);
				}
				else if (code[i] == '0')
				{
					value &= (~(1 << pos));
				}
				else
				{
					assert(false);
				}
				++pos;
				if (pos == 8)
				{
					fputc(value, fin);
					value = 0;
					pos = 0;
				}
			}
			c = fgetc(fd);
		}
		if (pos > 0)
		{
			fputc(value, fin);
		}

		fclose(fd);
		fclose(fin);
	}

	// 获取字符表示的二进制码
	void GetCode(TreeNode* root, std::string code)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->left == NULL && root->right == NULL)
		{
			hashtableInfo[(unsigned char)root->data.ch].code = code;
			return;
		}
		GetCode(root->left, code + '0');
		GetCode(root->right, code + '1');
	}

	//////////////////////////////////////////
	//////////////////////////////////////////
	// 解压
	void Uncompress(const char* file)
	{
		// 还原文件名字
		std::string uncompress = file;
		size_t pos = uncompress.rfind(".");
		if (pos == std::string::npos)
		{
			assert(false);
		}
		uncompress.erase(pos); //从pos删到尾，默认是string::npos

		// 打开要解压后,需要写入的文件
		FILE* fout = fopen(uncompress.c_str(), "wb");
		assert(fout);

		// 打开压缩文件
		FILE* fd = fopen(file, "rb");
		assert(fd);
		TmpInfo tmp;
		fread(&tmp, sizeof(TmpInfo), 1, fd);
		while (tmp.count != -1)
		{
			hashtableInfo[(unsigned char)tmp.cha].ch = tmp.cha;
			hashtableInfo[(unsigned char)tmp.cha].count = tmp.count;
			fread(&tmp, sizeof(TmpInfo), 1, fd);
		}
		// 重建huffman树
		charInfo invalid;
		invalid.count = 0;
		HuffmanTree<charInfo> tree(hashtableInfo, 256, invalid);
		TreeNode* root = tree.GetRoot();
		LongType n = root->data.count;

		TreeNode* cur = root;
		char c = 0;
		c = fgetc(fd);
		while (1)
		{
			
			for (size_t i = 0; i < 8; ++i)
			{
	
				if ((c & (1 << i))) // 因为与完后是0，才是与的那一位为0，其它值都为1，因为就会转成int值
				{
					cur = cur->right;
				}
				else
				{
					cur = cur->left;
				}

				if (cur->left == NULL && cur->right == NULL)
				{
					putc(cur->data.ch, fout); // 写到文件中去
					cur = root;
					if (--n == 0) // 处理最后几个比特位
					{
						fclose(fd);
						fclose(fout);
						return;
					}
				}
			}
			c = fgetc(fd);
		/*char value = fgetc(fd);
		pos = 0; 
			for (;;){
				if (value & (1 << pos))
					cur = cur->right;
				else
					cur = cur->left;
				++pos;

				if (NULL == cur->left && NULL == cur->right){
					fputc(cur->data.ch, fout);
					cur = root;
					if (--n == 0)
						break;
				}
				if (pos > 7){
					value = fgetc(fd);
					pos = 0;
				}
			}*/

		}
		fclose(fd);
		fclose(fout);
	}


protected:
	charInfo hashtableInfo[LEN];
};
