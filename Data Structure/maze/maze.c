#include"maze.h"


void InitMaze(Maze *maze)
{
	if (maze == NULL)
	{
		return;
	}
	int map[MAZE_ROW][MAZE_COL] = {
		{0, 1, 0, 0, 0, 0},
		{0, 1, 1, 1, 0, 0},
		{0, 1, 0, 1, 1, 0},
		{0, 1, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
	};
	size_t i = 0;
	for (; i < MAZE_ROW; ++i)
	{
		size_t j = 0;
		for (; j < MAZE_COL; ++j)
		{
			maze->map[i][j] = map[i][j];
		}
	}
}

int CanStay(Maze *maze, Point cur)
{
	// 判断点是否在地图上
	if (cur.row < 0 || cur.col >= MAZE_COL || cur.col < 0 || cur.row >= MAZE_ROW)
	{
		return 0;
	}
	if (maze->map[cur.row][cur.col] == 1)
	{
		return 1;
	}
	return 0;
}


// 标记走过的路径
void Mark(Maze *maze, Point cur)
{
	if (maze == NULL)
	{
		return;
	}
	maze->map[cur.row][cur.col] = 2;
}

// 判断是否可以退出
int IsExit(Point cur, Point entry)
{
	// 判断是否在边缘
	if (cur.row == 0 || cur.col == 0 || cur.row == MAZE_COL-1 || cur.col == MAZE_ROW-1)
	{
		// 判断是否是入口点
		if (cur.row == entry.row && cur.col == entry.col)
		{
			return 0;
		}
		return 1;
	}
	return 0;
}


//是否存在路径，开时cur为入口点
void HasPath(Maze *maze, Point cur, Point entry)
{
	// 1，判断入口点是否合法(点在地图上，并且值为1)
	if (!CanStay(maze, cur))
	{
		return;
	}
	// 2，标记当前走过的点
	Mark(maze, cur);
	// 3，判断当前点是否是出口（落在边缘上并且不是入口）
	if (IsExit(cur, entry))
	{
		printf("1\n");
		return;
	}
	// 4，按照顺时钟向周围探测（用递归）
	Point up = cur;
	up.row -= 1;
	HasPath(maze, up, entry);
	
	Point right = cur;
	right.col += 1;
	HasPath(maze, right, entry);

	Point down = cur;
	down.row += 1;
	HasPath(maze, down, entry);

	Point left = cur;
	left.col -= 1;
	HasPath(maze, left, entry);
	// 5，如果四个方向都探测到了就返回。
	return;
}

// 递归版寻找迷宫路径
void _HasPath(Maze *maze, Point entry)
{
	if (maze == NULL)
	{
		return;
	}
	HasPath(maze, entry, entry);
}



void HasPathByLoop(Maze* maze, Point entry)
{
	if (maze == NULL)
	{
		return;
	}
	// 判断入口点是否正确
	if (!CanStay(maze, entry))
	{
		return;
	}
	// 标记入口点走过
	Mark(maze, entry);
	SeqStack stack;
	SeqStackInit(&stack);
    // 从入口点进行压栈
	SeqStackPushStack(&stack, entry);
	Point cur;
	while (SeqStackFindTop(&stack, &cur))
	{
		if (IsExit(cur, entry))
		{
			printf("找到了出口\n");
			return;
		}
		Point up = cur;
		up.row -= 1;
		if (CanStay(maze, up))
		{
			Mark(maze, up);
			SeqStackPushStack(&stack, up);
			continue;
		}
		Point right = cur;
		right.col += 1;
		if (CanStay(maze, right))
		{
			Mark(maze, right);
			SeqStackPushStack(&stack, right);
			continue;
		}
		Point down = cur;
		down.row += 1;
		if (CanStay(maze, down))
		{
			Mark(maze, down);
			SeqStackPushStack(&stack, down);
			continue;
		}
		Point left = cur;
		left.col -= 1;
		if (CanStay(maze, left))
		{
			Mark(maze, left);
			SeqStackPushStack(&stack, left);
			continue;
		}
		SeqStackPopStack(&stack);
	}
	return;
}

////////////////////////////////////
//多出路迷宫，找到一条最短路径
////////////////////////////////////
// 采用打擂台的方法，每次找到一条路径，就进行比较
void _GetShortPath(Maze *maze, Point cur, Point entry, SeqStack *cur_path, SeqStack *short_path)
{
	// 判断是否能落脚
	if (!CanStay(maze, cur))
	{
		return;
	}
    // 标记当前点为走过的点
	Mark(maze, cur);
	SeqStackPushStack(cur_path, cur);
	if (IsExit(cur, entry))
	{
		if (SeqStackSize(cur_path) < SeqStackSize(short_path) || SeqStackSize(short_path) == 0)
		{
			SeqStackAssign(cur_path, short_path);
		}
		SeqStackPopStack(cur_path);
		printf("找到了\n");
		return;
	}
	Point up = cur;
	up.row -= 1;
	_GetShortPath(maze, up, entry, cur_path, short_path);
	Point right = cur;
	right.col += 1;
	_GetShortPath(maze, right, entry, cur_path, short_path);
	Point down = cur;
	down.row += 1;
	_GetShortPath(maze, down, entry, cur_path, short_path);
	Point left = cur;
	left.col -= 1;
	_GetShortPath(maze, left, entry, cur_path, short_path);
}

// 递归的进行查找最短路径
void GetShortPath(Maze *maze, Point entry)
{
	SeqStack short_path;
	SeqStack cur_path;
	SeqStackInit(&short_path);
	SeqStackInit(&cur_path);
	_GetShortPath(maze, entry, entry, &cur_path, &short_path);
}

//////////////////////////////
//多出口带环迷宫求最短路径
//////////////////////////////

int CanStayWithCycle(Maze *maze, Point cur, Point pre)
{
    if (pre.row < 0)
    {
        if (cur.row < 0 || cur.row >= MAZE_ROW || cur.col < 0 || cur.col >= MAZE_COL)
        {
            return 0;
        }
        int cur_value = maze->map[cur.row][cur.col];
        if (cur_value == 1)
        {
            return 1;
        }
        return 0;
    }
    if (cur.row < 0 || cur.row >= MAZE_ROW || cur.col < 0 || cur.col >= MAZE_COL)
    {
        return 0;
    }
    int cur_value = maze->map[cur.row][cur.col];
    if (cur_value == 1)
    {
        return 1;
    }
    // 判断当前点的值和前一个值的大小，满足cur_value-1 > pre_path 时才能落脚
    int pre_value = maze->map[pre.row][pre.col];
    if (cur_value - 1 > pre_value)
    {
        return 1;
    }
    return 0;
}

void MarkWithCycle(Maze *maze, Point cur, Point pre)
{
    if (pre.row < 0 || pre.row >= MAZE_ROW || pre.col < 0 || pre.col >= MAZE_COL)
    {
        maze->map[cur.row][cur.col] = 2;
        return;
    }
    int pre_value = maze->map[pre.row][pre.col];
    maze->map[cur.row][cur.col] = pre_value + 1;
}

void _GetShortPathWithCycle(Maze *maze, Point cur, Point entry,Point pre, SeqStack *cur_path, SeqStack *short_path)
{
    // 1. 判断当前是否可以落脚，判断方法为cur-1 > pre 
    if (!CanStayWithCycle(maze, cur, pre))
    {
        return;
    }
    // 2. 如果可以落脚就标记当前点,并且把当前点入栈
    MarkWithCycle(maze, cur, pre);
    SeqStackPushStack(cur_path, cur);
    // 3. 判断是否为出口。
    if (IsExit(cur, entry))
    {
        //    判断cur_path 和 shor_path的大小
        printf("找到\n");
        if (SeqStackSize(cur_path ) < SeqStackSize(short_path) || SeqStackSize(short_path) == 0)
        {
        //    如果cur_path比较小，就替换short_path
            SeqStackAssign(cur_path, short_path);
        }
        //    出栈，回溯
        SeqStackPopStack(cur_path);
        return;
    }
    // 4.如果不是出口，就以当前点为基准，进行四个方向的探测，并递归调用调用该函数
    Point up = cur;
    up.row -= 1;
    _GetShortPathWithCycle(maze, up, cur, entry, cur_path, short_path);

    Point right = cur;
    right.col += 1;
    _GetShortPathWithCycle(maze, right, cur, entry, cur_path, short_path);

    Point down = cur;
    down.row += 1;
    _GetShortPathWithCycle(maze, down, cur, entry, cur_path, short_path);
    
    Point left = cur;
    left.col -= 1;
    _GetShortPathWithCycle(maze, left, cur, entry, cur_path, short_path);
    SeqStackPopStack(cur_path);
    return;
}

// 如果cur 10 pre 9 这时没必要走
// 采用顺序标记的方法，比较出cur - 1 > pre 时，继续查找路径
void GetShortPathWithCycle(Maze *maze, Point entry)
{
	SeqStack short_path;
	SeqStack cur_path;
	SeqStackInit(&short_path);
	SeqStackInit(&cur_path);
    Point pre = {-1, -1};
	_GetShortPathWithCycle(maze, entry, entry, pre, &cur_path, &short_path);
}


//////////////////////////////
//以下为测试代码
//////////////////////////////

#define TEST_HEAD printf("\n===================%s=====================\n",__FUNCTION__)



void PrintMaze(Maze *maze)
{
	if (maze == NULL)
	{
		return;
	}
	size_t i = 0;
	for (; i < MAZE_ROW; ++i)
	{
		size_t j = 0;
		for (; j < MAZE_COL; ++j)
		{
			printf("%d   ",maze->map[i][j]); 
		}
		printf("\n");
	}
}

void TestHasPathByLoop()
{
	TEST_HEAD;
	Maze m;
	InitMaze(&m);
	Point p = {0,1};
	_HasPath(&m,p);
	PrintMaze(&m);
}

void TestHasPath()
{
	TEST_HEAD;
	Maze m;
	InitMaze(&m);
	Point p = {0,1};
	_HasPath(&m,p);
	PrintMaze(&m);
}

void TestInit()
{
	TEST_HEAD;
	Maze m;
	InitMaze(&m);
	PrintMaze(&m);
}

int main()
{
	TestInit();
	TestHasPath();
	TestHasPathByLoop();
	return 0;
}
