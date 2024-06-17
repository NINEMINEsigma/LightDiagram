//#define _Source_DLL_EXPORT

#include"LightDiagram.h"

#include<iostream>

#include <cstdio>

using namespace std;
using namespace ld;

int main()
{
	ld_test();
	ConsolePro console;

	console.LogMessage("Test Message");
	console.LogWarning("Test Warning");
	console.LogError("Test Error");

	getchar();
}