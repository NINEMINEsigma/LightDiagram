#define _CRT_SECURE_NO_WARNINGS

#define is_monitor_the_constructor_of_anyclass false

#include<LightDiagram.h>

using namespace ld;
//using namespace ld::resources;
using namespace std;

sync_with_stdio_false(__auto__);

struct test
{
	test()
	{
		cout << "start\n";
	}
	test(test& from)
	{
		cout << "move-l\n";
	}
	test(test&& from)
	{
		cout << "move-r\n";
	}
	~test()
	{
		cout << "end\n";
	}
};

int main(int argc, char** argv)
{
	config_instance config(argc, argv);
	atomic_int index = 0;
	instance<int> a(1);
	//instance<int> b{ std::move(a) };
	//instance<int> b = std::move(a);
	instance<int> b{ std::move(a)};
}
