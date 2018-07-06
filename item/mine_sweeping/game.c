#include"game.h"
void init(char mine[ROWS][COLS],char set)//初始化  雷盘  棋盘
{
	int i, j;
	for(i=0; i<ROWS; i++)
	{
		for(j=0; j<COLS; j++)
		{
			mine[i][j] = set;
		}
	}
}
void display_mine(char mine[ROWS][COLS],int rows,int cols)//打印雷
{
	int i, j;
	
	//printf("游戏开始\n");
	//printf("");
	for(i=1; i<=ROW; i++)
	{
		printf("%4d",i);
	}
	printf("\n");
	for(i=1; i<=ROW; i++)
	{
		printf("%2d ",i);
		for(j=1; j<=COL; j++)
		{
			printf("%c   ",mine[i][j]);
		}
		printf("\n");
	}
}
void display_check(char show[ROWS][COLS],int rows,int cols)//打印棋盘
{
	int i, j;
	system("cls");
	printf("游戏开始\n");
	
	for(i=1; i<=ROW; i++)
	{
		printf("%4d",i);
	}
	printf("\n");
	for(i=1; i<=ROW; i++)
	{
		printf("%2d ",i);
		for(j=1; j<=COL; j++)
		{
			printf("%c   ",show[i][j]);
		}
		printf("\n");
	}
}
void set_mine(char mine[ROWS][COLS],int row,int col,int count)//布雷
{
	int x = 0,y = 0;
	while(count>0)
	{
		x = rand()%row+1;
		y = rand()%col+1;
		if(mine[x][y] != '1')
		{
			mine[x][y] = '1';
			count--;
		}
		
	}
}
int sweep_mine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col,int count)//扫雷
{
	int x = 0,y = 0,c = 0,n = 1,select = 0,num = 0;
	while(ROW*COL-count >= n&&num<=count)//判玩家赢
	{
		
		printf("1 排雷  2 标记雷  3 取消标记\n");
		printf("---------------------------\n");
		printf("请选择--》\n");
		scanf("%d",&select);//选择扫雷  标记雷  取消标记
		if(select == 1)
		{
			printf("请输入行 列--》\n");
			scanf("%d%d",&x,&y);
			if(x>0&&x<=row&&y>0&&y<=col)//判断传入值是否合法
			{

				if(n==1 && mine[x][y] == '1')
				{
					mine[x][y] = '0';
					repeat_frist_mine(mine,x,y);//把第一个雷给移走
				}
				//show[x][y] = mine[x][y];
				if(mine[x][y] == '1')//踩雷了
				{
					show[x][y] = '@';
					return 1;
				}
				else
				{
					expand(mine,show,x,y);//不是雷扩展
				}
				display_check(show,ROWS,COLS);
			}
			else
			{
				printf("输入错误,请重新输入\n");
			}
			n++;
		}
		else if(select == 2)
		{
			printf("请输入要标记的行 列\n");
			scanf("%d%d",&x,&y);
			mark_mine(show,x,y);
			num++;
			
		}
		else if(select == 3)
		{
			printf("请输入要取消标记的行 列\n");
			scanf("%d%d",&x,&y);
			cancel_mark_mine(show,x,y);
			num--;
			
		}
		else
		{
			printf("输入错误代号\n");
		}
	}
	return 0;
}
int around_mine_amount(char mine[ROWS][COLS],int x,int y)//是否用static?  计算周围雷
{
	int amount = 0;
	amount = (mine[x-1][y]+mine[x-1][y-1]+mine[x][y-1]+mine[x+1][y-1]+mine[x+1][y]+mine[x+1][y+1]+mine[x][y+1]+mine[x-1][y+1])-'0'*8;
	return amount;
}
void repeat_frist_mine(char mine[ROWS][COLS],int x,int y)//重新设置第一个雷
{
	int i = 0;
	int j = 0;

	do
	{
		i = rand()%10+1;
		j = rand()%10+1;
		if(mine[i][j] != '1'&& i != x && j != y)
		{
			mine[i][j] = '1';
			break;
		}
	}
	while(1);
}


void expand(char mine[ROWS][COLS],char show[ROWS][COLS],int x,int y)//扩展
{
	if(x>0 && x<=ROW && y>0 && y<=COL)
	{
		if(around_mine_amount(mine,x,y) == 0)
		{
			show[x][y] = '0';
			if(mine[x-1][y] == '0' && show[x-1][y] == '*')//1
			{
				expand(mine,show,x-1,y);
			}
			else
			{
				show[x-1][y] = around_mine_amount(mine,x-1,y) + '0';
			}
			if(mine[x-1][y+1] == '0'&& show[x-1][y+1] == '*')//2
			{
				expand(mine,show,x-1,y+1);
			}
			else
			{
				show[x-1][y+1] = around_mine_amount(mine,x-1,y+1) + '0';
			}
			if(mine[x][y+1] == '0'&& show[x][y+1] == '*')//3
			{
				expand(mine,show,x,y+1);
			}
			else
			{
				show[x][y+1] = around_mine_amount(mine,x,y+1) + '0';
			}
			if(mine[x+1][y+1] == '0'&& show[x+1][y+1] == '*')//4
			{
				expand(mine,show,x+1,y+1);
			}
			else
			{
				show[x+1][y+1] = around_mine_amount(mine,x+1,y+1) + '0';
			}
			if(mine[x+1][y] == '0'&& show[x+1][y] == '*' )//5
			{
				expand(mine,show,x+1,y);
			}
			else
			{
				show[x+1][y] = around_mine_amount(mine,x+1,y) + '0';
			}
			if(mine[x+1][y-1] == '0'&& show[x+1][y-1] == '*')//6
			{
				expand(mine,show,x+1,y-1);
			}
			else
			{
				show[x+1][y-1] = around_mine_amount(mine,x+1,y-1) + '0';
			}
			if(mine[x][y-1] == '0'&& show[x][y-1] == '*')//7
			{
				expand(mine,show,x,y-1);
			}
			else
			{
				show[x][y-1] = around_mine_amount(mine,x,y-1) + '0';
			}
			if(mine[x-1][y-1] == '0'&& show[x-1][y-1] == '*')//8
			{
				expand(mine,show,x-1,y-1);
			}
			else
			{
				show[x-1][y-1] = around_mine_amount(mine,x-1,y-1) + '0';
			}
		}
		else
		{
			show[x][y] = around_mine_amount(mine,x,y) + '0';
		}
	}
}
void mark_mine(char show[ROWS][COLS],int x,int y)//标记雷
{
	if(show[x][y] == '*')
	{
		show[x][y] = '$' ;
		display_check(show,ROWS,COLS);
	}
	else
	{
		printf("标记位置错误\n");
	}
}


void cancel_mark_mine(char show[ROWS][COLS],int x,int y)//取消标记
{
	if(show[x][y] == '$')
	{
		show[x][y] = '*' ;
		display_check(show,ROWS,COLS);
	}
	else
	{
		printf("取消标记位置错误\n");
	}
}