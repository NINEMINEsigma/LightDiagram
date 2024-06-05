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

int main()
{
	ld_test();
	cout << typeid(function_traits_ex<decltype(&test::add)>).name() << "\n";
	cout << typeid(function_traits_ex<decltype(&test::add)>::call).name();
}
