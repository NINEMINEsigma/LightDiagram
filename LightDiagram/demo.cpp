
#include"LightDiagram.h"

#include<iostream>

#include <cstdio>

using namespace std;
using namespace ld;

int main()
{
	ld_test();
	ConsolePro console;

	ld::LFContainter<int, int>::controller_type controller;
	ld::LFContainter<int,int> container(controller);

	getchar();
}