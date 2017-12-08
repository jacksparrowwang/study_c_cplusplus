#include"game.h"
void menu()
{
	printf("**********************\n");
	printf("****1.play  0.exit****\n");
	printf("**********************\n");
	printf("请选择--》\n");
}
void test()
{
	int ret = 0;
	char mine[ROWS][COLS] = {0};
	char show[ROWS][COLS] = {0};
	srand((unsigned int)time(NULL));

	init(mine,'0');//初始化雷盘
	//display_mine(mine,ROWS,COLS);
	set_mine(mine,ROW,COL,EASY);//设置雷
	//display_mine(mine,ROWS,COLS);
	init(show,'*');//初始化棋盘
	display_check(show,ROWS,COLS);//打印棋盘
	ret = sweep_mine(mine,show,ROW,COL,EASY);//扫雷
	if(ret == 1)
	{
		printf("很遗憾你被炸死了  @  \n");
	}
	else 
	{
		printf("恭喜你，胜利了\n");
	}
	display_check(show,ROWS,COLS);
	
	printf("*****雷的分布 1 *****\n");
	
	display_mine(mine,ROWS,COLS);
}

int main()
{
	int input = 0;	
	do
	{
		menu();
		scanf("%d",&input);
		switch(input)
		{
		case PLAY:
			printf("游戏开始\n");
				 test();
			printf("游戏结束\n");
			break;
		case EXIT:
			break;
		default:
			printf("输入错误\n");
			break;
		}
	}
	while(input);//如果在游戏结束输入非数字，会无限循环，怎么解决？
	return 0;
}