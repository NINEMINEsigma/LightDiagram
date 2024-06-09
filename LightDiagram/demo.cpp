#include"LightDiagram.h"

#include<Windows.h>
#include<iostream>

using namespace std;

class test
{
public:
	using integral_indicator = void;

	int b = 0;
	int add(int a)
	{
		return b = a + b;
	}
};

using test_type = int******;

int main()
{
	ld_test();
	fvar_info field = make_field_info(test, b);
	fvar_base fiebase = make_field_info(test, b);
	func_info func = make_function_info(test, add);
	test a;
	func.invoke(&a, 500);
	cout << *((int*)fiebase.get(&a)) << "\n";
}
