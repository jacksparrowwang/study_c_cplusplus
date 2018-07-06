#ifndef __GAME_H__
#define __GAME_H__
#define ROW 10
#define COL 10
#define ROWS ROW+2
#define COLS COL+2
#define EASY 10
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
enum option
{
	EXIT,
	PLAY
};
void init(char mine[ROWS][COLS],char set);
void display_mine(char mine[ROWS][COLS],int rows,int cols);
void display_check(char show[ROWS][COLS],int rows,int cols);
void set_mine(char mine[ROWS][COLS],int row,int col,int count);
int around_mine_amount(char mine[ROWS][COLS],int x,int y);
int sweep_mine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col,int count);
void repeat_frist_mine(char mine[ROWS][COLS],int x,int y);
void expand(char mine[ROWS][COLS],char show[ROWS][COLS],int x,int y);
void mark_mine(char show[ROWS][COLS],int x,int y);
void cancel_mark_mine(char show[ROWS][COLS],int x,int y);
#endif __GAME_H__
