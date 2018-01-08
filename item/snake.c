#include "snake.h"
#include<windows.h>



//欢迎界面
void welcome()
{
	SetPos(20,10);
	printf("welcome to snake game\n");
	SetPos(18,16);
	printf("↑ ↓ ← → 控制方向\n");
	system("pause");
	system("cls");
}

//移动光标位置
void SetPos(int x,int y)
{

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//用来调整光标位置
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle,pos);
}


//创建地图
void CreatMap()
{
	int i = 0;
	for (i=0; i <= 56; i+=2)
	{
		SetPos(i,0);
		printf(FOOD);
		SetPos(i,26);
		printf(FOOD);
	}
	for(i=1; i <= 25; i++)
	{
		SetPos(0,i);
		printf(FOOD);
		SetPos(56,i);
		printf(FOOD);
	}
}

//初始化蛇
void InitSnake(snake *ps)
{
	int i = 0;
	
	node *cur = NULL;
	if(ps == NULL)
	{
		printf("node is NULL");
		return;
	}
	cur = (node*)malloc(sizeof(node));//创建蛇的尾节点
	cur->next = NULL;
	cur->x = INIT_X;
	cur->y = INIT_Y;
	for(i=1; i<=4; i++)//用头差方法进行创建单链表
	{
		ps->head = (node*)malloc(sizeof(node));
		ps->head->next = cur;
		ps->head->x = INIT_X + i*2;
		ps->head->y = INIT_Y;
		cur = ps->head;
	}
	ps->sta = OK;
	ps->dir = RIGHT;
	ps->speed = 300;
	while(cur != NULL)
	{
		SetPos(cur->x,cur->y);
		printf(SNAKE_FOOD);
		cur = cur->next;
	}
	printf("\n");

}

//初始化食物
void InitFood(snake *ps)
{
	node *cur = ps->head;
	if (ps == NULL)
	{
		return;
	}
	ps->food = (node*)malloc(sizeof(node));//创建失误
	ps->food->next = NULL;
agine :
	do
	{
		ps->food->x = rand() % 53 + 2;
	}while(ps->food->x%2 != 0);//产生失误不是在奇数的位置上
	ps->food->y = rand() % 25 + 1;
	while(cur != NULL)
	{
		if(cur->x == ps->food->x && cur->y == ps->food->y)
		{
			goto agine;
		}
		cur = cur->next;
	}
	SetPos(ps->food->x,ps->food->y);
	printf(SNAKE_FOOD);
	
}

//吃食物情况
void EatFood(snake *ps,node *snf)
{
	//将创建节点mov节点插入到头部，更新头指针
	node *cur = NULL;
	snf->next = ps->head;
	ps->head = snf;
	cur = ps->head;
	while(cur != NULL)//重新打印，不用删除最后一个节点
	{
		SetPos(cur->x,cur->y);
		printf(SNAKE_FOOD);
		cur = cur->next;
	}
	InitFood(ps);
}

//没有食物情况
void NoFood(node **sn,node *mov)
{
	//将创建节点mov节点插入到头部，更新头指针
	node *cur = NULL;
	mov->next = *sn;
	*sn = mov;
	cur = *sn;
	while(cur->next->next != NULL)//更新打印
	{
		SetPos(cur->x,cur->y);
		printf(SNAKE_FOOD);
		cur = cur->next;
	}
	SetPos(cur->next->x,cur->next->y);//将最后的一个节点变为空格，并且销毁其节点
	printf("  ");
	free(cur->next);
	cur->next = NULL;
}

//蛇移动
void SnakeMove(snake *ps)
{
	node *cur = (node *)malloc(sizeof(node));//创建节点为没吃到食物时候移动
	cur->x = ps->head->x;
	cur->y = ps->head->y;

	//方向控制转向
	switch(ps->dir)
	{
	case UP:
		cur->y -= 1;
		break;
	case DOWN:
		cur->y += 1;
		break;
	case LEFT:
		cur->x -= 2;
		break;
	case RIGHT:
		cur->x += 2;
		break;
	default:
		break;
	}
	if(ps->food->x == ps->head->x && ps->food->y == ps->head->y)//判断是否遇到失误
	{
		EatFood(ps,ps->food);
	}
	else
	{
		NoFood(&ps->head,cur);
	}
}

//被墙撞死
void KillByWall(snake *ps)
{
	//判断边界
	if(ps->head->x == 0 || ps->head->x == 56 || ps->head->y == 0 || ps->head->y == 26)
	{
		ps->sta = KILL_BY_WALL;
	}
}

//吃到自己
void KillByOwn(snake *ps)
{
	node *cur = ps->head->next->next;//头节点的后后一个节点，第二节点不用判断，因为头吃不到第二个
	while(cur != NULL)
	{
		if(ps->head->x ==cur->x  && ps->head->y == cur->y)//遍历自己与头节点的x,y
		{
			ps->sta = KILL_BY_OWN;
			break;
		}
		cur = cur->next;
	}
}

//游戏结束提示
void EndGame(snake *ps)
{
	SetPos(22,13);
	switch(ps->sta)
	{
	case  KILL_BY_OWN:
		printf("你自己把自己吃掉了\n");
		break;
	case KILL_BY_WALL:
		printf("你被墙撞死了\n");
		break;
	default:
		break;;
	}
}

//游戏控制
void SnakeControl(snake *ps)
{
	do
	{
		//虚拟键盘调整方向
		if (GetAsyncKeyState(VK_UP) && ps->dir != DOWN)
		{
			ps->dir = UP;
		}
		else if (GetAsyncKeyState(VK_DOWN) && ps->dir != UP)
		{
			ps->dir = DOWN;
		}
		else if (GetAsyncKeyState(VK_LEFT) && ps->dir != RIGHT)
		{
			ps->dir = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && ps->dir != LEFT)
		{
			ps->dir = RIGHT;
		}
		Sleep(ps->speed);//蛇的速度
		SnakeMove(ps);
		KillByWall(ps);
		KillByOwn(ps);
		
	}while(ps->sta == OK);
	EndGame(ps);
}

void GameRun()
{
	snake s;
	welcome();
	srand((int)time(NULL));
	CreatMap();
	InitSnake(&s);
	InitFood(&s);
	SnakeControl(&s);
	
}

int main()
{
	GameRun();
	return 0;
}