#include"LightDiagram.h"

#include<Windows.h>
#include<iostream>

using namespace std;

class test
{
public:
	using integral_indicator = void;

	int b;
	int add(int a)
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

template<typename T>
using catr = const function_info<T>&;

int main()
{
	ld_test();
	func_info add_info = make_function_info(test, add);
	test test_instance;
	test_instance.b = 5;
	cout << add_info.invoke(nullptr, 2);
}
