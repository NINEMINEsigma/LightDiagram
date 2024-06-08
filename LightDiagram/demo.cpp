#include"LightDiagram.h"

#include<Windows.h>
#include<iostream>

using namespace std;

class test
{
public:
	using integral_indicator = void;

	int add(int a, int b)
	{
		return a + b;
	}
};

int add(int a, int b)
{
	return a + b;
}

namespace kkk
{
	int add(int a, int b)
	{
		return a + b;
	}
}

int main()
{
	ld_test();
	auto finfo = kit::traits::function::make_function_info(&::add, "add");
	cout << finfo.read_name() << "\n";
	cout << finfo.read_func_name() << "\n";
	cout << finfo.read_type().name();
}
