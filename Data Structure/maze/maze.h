#pragma once

#include<stdio.h>
#include"SeqStack.h"
#define MAZE_ROW 6
#define MAZE_COL 6

//typedef struct Point{
//	int row;
//	int col;
//}Point;

typedef struct Maze{
	int map[MAZE_ROW][MAZE_COL];
}Maze;

void InitMaze(Maze *maze);

// 找到一条路径
void _HasPath(Maze *maze, Point entry);

// 非递归的找到一条路劲
void HasPathByLoop(Maze* maze, Point entry);

// 在多条路径中找到一条最短路径
void GetShortPath(Maze *maze, Point entry);

// 多路径带环，找到一条最短路径
void GetShortPathWithCycle(Maze *maze, Point entry);
