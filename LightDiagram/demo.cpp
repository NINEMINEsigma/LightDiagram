#include"LightDiagram.h"

#include<Windows.h>
#include<iostream>

using namespace std;

if_member_exist_def(tagx);

class test
{
public:
	using tagx = void;
	int add(int a,int b)
	{
		return a + b;
	}
};

int _stdcall sub(int a, double b)
{
	return a - b;
}

int main()
{
	ld_test();
	cout << if_member_exist(add)<test> << "\n";
	cout << "awake success\n";
	for (int i = 0, e = 100; i <= e; i++)
	{
		cout << "\r";
		int t = i * 100 / e;
		for (int j = 0; j < t / 10; j++)
		{
			cout << "X";
		}
		for (int j = t / 10; j < e / 10; j++)
		{
			cout << " ";
		}
		cout << " " << t << "%";
		Sleep(100 * i / e);
	}
}
