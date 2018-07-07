#include "AVLTree.h"
int main()
{
	AVLTree<int, int> a;
	
	// 第一组测试用例
	a.Insert(16, 8);
	a.Insert(3, 9);
	a.Insert(7, 13);
	a.Insert(11, 14);
	a.Insert(9, 16);
	a.Insert(26, 19);
	a.Insert(18, 1);
	a.Insert(14, 1);
	a.Insert(15, 1);
	// 测试用例
	// 4 2 6 1 3 5 15 7 16 14 
}
