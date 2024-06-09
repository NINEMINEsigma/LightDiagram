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

using test_type = int******;

int main()
{
	ld_test();
	func_info add_info = make_function_info(test, add);
	test test_instance;
	test_instance.b = 5;
	cout << add_info.invoke(&test_instance, 2) << "\n\n";
	cout << typeid(test_type).name() << "\n";
	cout << typeid(std::remove_pointer<test_type>::type).name() << "\n";
	cout << typeid(remove_full_ptr<test_type>::tag).name();
}
