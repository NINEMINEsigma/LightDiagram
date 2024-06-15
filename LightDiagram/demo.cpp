//#define _Source_DLL_EXPORT

#include"LightDiagram.h"

#include<iostream>

#include <cstdio>

using namespace std;

int main()
{
	ld_test();
	cout << std::is_base_of_v<any_class, ld::IBase>;
	getchar();
}