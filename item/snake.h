#pragma once

#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

#define FOOD "□"
#define SNAKE_FOOD "●"
#define INIT_X 24
#define INIT_Y 10

//蛇的身体
typedef struct node
{
	int x;
	int y;
	struct node *next;
}node;

//状态
enum status
{
	OK,
	KILL_BY_WALL,
	KILL_BY_OWN
};

//方向
enum direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//蛇
typedef struct snake
{
	node *head;
	node *food;
	enum status sta;
	enum direction dir;
	int speed;
}snake;

//欢迎界面
void welcome();

//光标位置
void SetPos(int x,int y);

//创建地图
void CreatMap();

//初始化蛇
void InitSnake(snake *ps);

//初始化食物
void InitFood(snake *ps);

//蛇移动
void SnakeMove(snake *ps);

//吃食物情况
void EatFood(snake *ps,node *snf);

//没有食物情况
void NoFood(node **sn,node *mov);