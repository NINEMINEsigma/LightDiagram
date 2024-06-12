

#include"LightDiagram.h"

#include<iostream>

using namespace std;

class test
{
public:
	using integral_indicator = void;

	class test_inside
	{
	public:
		void push()
		{
			cout << "ok";
		}
	};

	int b = 0;
	int add(int a)
	{
		return b = a + b;
	}
};

int add(int b)
{
	return b;
}

using test_type = int******;

int main()
{
	ld_test();
	test a;
	func_info t = make_function_info(test, add);
	t.invoke(&a, 50);
	fvar_info f = make_field_info(test, b);
	cout << f.get(&a);
}
