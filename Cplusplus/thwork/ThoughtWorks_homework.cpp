#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <string>

/* 条件编译，适合不同的平台, 本次编辑平台为Linux，本次测试平台是vs2013 和 centos 7 Linux */
#define Linux

#ifdef Linux 
#include <unistd.h> // Linux平台
#else 
#include <Windows.h> // windows平台
#include <io.h>
#endif

#define SIZE 512
#define BUFSIZE 1024

/* 用于保存第二行输入的坐标 */
struct Coord
{
	int src_x;
	int src_y;
	int dest_x;
	int dest_y;
};

/* 判断是否合法输入 */
bool IsTrue(char buf[], int *row, int *col)
{
	if (row == NULL || col == NULL){
		return false;
	}

    /* 判断格式是否正确 */
	if (buf[0] == ' '){
		std::cout << "Incorrect command format." << std::endl;
		return false;
	}
	if (buf[0] == '-'){
		std::cout << "Number out of range." << std::endl;
		return false;
	}
	std::string number1;
	std::string number2;
    /* 输入字符如果有正号也算为正确输入 */
	int i = 0;
	if (buf[0] == '+'){
		number1.push_back(buf[0]);
		++i;
	}
    /* 判断字符输入是否能转换成数字 */
	for (; i < SIZE; ++i){
		if (buf[i] == ' ' || buf[i] == '\n'){
			break;
		}
		if ( buf[i] >= '0' && buf[i] <= '9'){
			number1.push_back(buf[i]);
		}else{
			std::cout << "Invalid number format." << std::endl;
			return false;
		}
	}
    /* 输入数字过大，导致越界 */
	if (i == SIZE){
		std::cout << "Number out of range.";
		return false;
	}
    /* 输入第二个字符是否按照格式输入 */
	if (buf[i + 1] == ' '){
		std::cout << "Incorrect command format." << std::endl;
		return false;
	}
	if (buf[i + 1] == '-'){
		std::cout << "Number out of range."<< std::endl;
		return false;
	}
	++i;
	if (buf[i] == '+'){
		number2.push_back(buf[i]);
		++i;
	}
    /* 判断是否输入为数字 */
	for (; i < SIZE; ++i){
		if (buf[i] == ' ' || buf[i] == '\n'){
			break;
		}
		if (buf[i] >= '0' && buf[i] <= '9'){
			number2.push_back(buf[i]);
		}else{
			std::cout << "Invalid number format." << std::endl;
			return false;
		}
	}
    /* 判断两个字符串是否超过转换成数字的最大范围 */
	if (number1.size() > 9 || number2.size() > 9){
		std::cout << "Number out of range." << std::endl;
		return false;
	}
    /* 把字符串转化为数字 */
	*row = atoi(number1.c_str());
	*col = atoi(number2.c_str());
	return true;
}

/* 读取第二行内容 */
bool ReadBody(char buf[], std::vector<Coord>& v, int row, int col)
{
	if (buf == NULL){
		return false;
	}
    /* 按照格式读取，并判断是否合法 */
	Coord coor;
	for (int i = 0; i < (int)strlen(buf)-1; i+=8){
		if (buf[i] >= '0' && buf[i] <= '9'){
			coor.src_x = buf[i]-48;
			coor.src_y = buf[i + 2]-48;
			coor.dest_x = buf[i + 4]-48;
			coor.dest_y = buf[i + 6]-48;
            if (coor.src_x >= row || coor.dest_x >= row || coor.src_y >= col || coor.dest_y >= col)
            {
                std::cout <<"Number out of range."<<std::endl;
                return false;
            }
			v.push_back(coor);
		}else{
			std::cout << "Invalid number format." << std::endl;
			return false;
		}
	}
    /* 判断合法 */
	for (int i = 1; i < (int)strlen(buf); i += 8){
		if (buf[i] != ','){
			std::cout << "Incorrect command format." << std::endl;
			return false;
		}
		if (buf[i + 2] != ' '){
			std::cout << "Incorrect command format." << std::endl;
			return false;
		}
		if (buf[i + 4] != ','){
			std::cout << "Incorrect command format." << std::endl;
			return false;
		}
		if (buf[i + 6] != ';' && buf[i+6] != '\n')
		{
			std::cout << "Incorrect command format." << std::endl;
			return false;
		}
	}
	return true;
}

/* 判断是否满足两个相邻，正东南西北方向 */
bool IsLink(std::vector<Coord>& v)
{
	for (int i = 0; i < (int)v.size(); ++i)
	{
        /* 因为是相邻，必定x与y其中的某一个是相同的 */
        if (v[i].src_x == v[i].dest_x || v[i].src_y == v[i].dest_y)
		{
			if (v[i].src_x == v[i].dest_x && v[i].src_y == v[i].dest_y) // 自己连通能给自己
			{ 
				std::cout << "Maze format error."<< std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "Maze format error." << std::endl;
			return false;
		}
	}
	return true;
}

/* 连通第二行输入的坐标要求 */
void LinkCell(std::vector< std::vector<std::string> >& maze, std::vector<Coord>& v)
{
	for (int i = 0; i < (int)v.size(); ++i)
	{
		if (v[i].src_x + 1 == v[i].dest_x)
		{
			maze[v[i].src_x * 2 + 2][v[i].src_y * 2 + 1] = "[R]";
		}
		else if (v[i].src_x - 1 == v[i].dest_x)
		{
			maze[v[i].src_x * 2][v[i].src_y * 2 + 1] = "[R]";
		}
		else if (v[i].src_y + 1 == v[i].dest_y)
		{
			maze[v[i].src_x * 2+1][v[i].src_y * 2 + 2] = "[R]";
		}
		else if (v[i].src_y - 1 == v[i].dest_y)
		{
			maze[v[i].src_x * 2+1][v[i].src_y * 2] = "[R]";
		}
		else
		{
			std::cout << "183 error\n";
		}
	}
}

/* 将迷宫渲染成字符串 */
bool LinkTable(std::vector< std::vector<std::string> >& maze, std::vector<Coord>& v, int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
        for (int j = 0; j < col; ++j)
        {
            maze[i*2+1][j*2+1] = "[R]";
        }
	}
    /* 检查连通性 */
	bool ret = IsLink( v);
	if (ret == false)
	{
		return false;
	}
    /* 连通cell */
	LinkCell(maze, v);
	return true;
}

int main()
{
	int row = 0;
	int col = 0;
    char buf[SIZE] = {0};
/* 平台不一样函数接口不一 */
#ifdef Linux
	read(0, buf, SIZE-1);
#else
	size_t rd = _read(0, buf, SIZE-1);
#endif

	char buf1[BUFSIZE] = { 0 };
	std::vector<Coord> v;

#ifdef Linux
	read(0, buf1, BUFSIZE-1);
#else
	size_t rd = _read(0, BUFSIZE-1, size-1);
#endif

    /* 判断合法性 */
	bool ret = IsTrue(buf, &row, &col);
	if (ret == false){
		system("pause");
		return 1;
	}
    /* 读取第二行判断合法性 */
	ret = ReadBody(buf1, v, row, col);
	if (ret == false){
		system("pause");
		return 1;
	}
    /* 构建出迷宫 */
	std::vector< std::vector<std::string> > maze;
	maze.resize(row*2+1);
	for (int i = 0; i < row*2+1; ++i)
	{
		maze[i].resize(col*2+1, "[W]");
	}

	ret = LinkTable(maze, v, row, col);
	if (ret == false)
	{
		system("pause");
		return 1;
	}

    /* 打印迷宫 */
	for (int i = 0; i < row*2+1; ++i)
	{
		for (int j = 0; j < col*2+1; ++j)
		{
			std::cout << maze[i][j];
		}
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}
