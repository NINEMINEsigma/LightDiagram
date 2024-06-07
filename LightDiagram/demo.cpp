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
	auto finfo = function_info(&test::add, "add");
	cout << finfo.read_name() << "\n";
	cout << finfo.read_type().name();
}
