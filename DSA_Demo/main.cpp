#include "stdafx.h"
//main.cpp

//main.cpp
#include "Graph.h"
int main()
{
	cout << "邻阶矩阵遍历：" << endl;
	Graphmtx<char, int> instance1(30);
	cin >> instance1;
	cout << "DFS遍历：" << endl;
	char first1 = instance1.getValue(0);
	DFS(instance1, first1);
	cout << endl;
	cout << "BFS遍历：" << endl;
	BFS(instance1, first1);
	cout << endl;
	instance1.outMatrix();


	cout << "邻阶表遍历：" << endl;
	Graphlnk<char, int> instance2(30);
	cin >> instance2;
	cout << "DFS遍历：" << endl;
	char first2 = instance2.getValue(0);
	DFS(instance2, first2);
	cout << endl;
	cout << "BFS遍历：" << endl;
	BFS(instance2, first2);
	cout << endl;
	instance2.outTable();


	system("pause");
	return 0;
}
