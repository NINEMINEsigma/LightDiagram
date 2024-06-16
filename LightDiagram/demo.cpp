//#define _Source_DLL_EXPORT

#include"LightDiagram.h"

#include<iostream>

#include <cstdio>

using namespace std;
using namespace ld;

int main()
{
	ld_test();

	for (int i = 0, e = 308; i <= e; i++)
	{
		ld::EaseProgressBar(i/(double)e, 40, ConsoleBackgroundColor::Blue);
		Sleep(50);
	}

	getchar();
}