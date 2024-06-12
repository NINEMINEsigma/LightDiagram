#define _Source_Development
#include"LightDiagram.h"

#include<Windows.h>
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
	func_info a = make_function_info(test::test_inside, push);
	cout << a.invoke(nullptr);
}
