#define _CRT_SECURE_NO_WARNINGS

#define is_monitor_the_constructor_of_anyclass false

#include<LightDiagram.h>

using namespace ld;
//using namespace ld::resources;
using namespace std;

sync_with_stdio_false(__auto__);


int main(int argc, char** argv)
{
	config_instance config(argc, argv);
	atomic_int index = 0;
	instance_limit_pool<std::thread> threads(
		[&index]()
		{
			return instance<std::thread>([&index]()
				{
					cout << index.fetch_add(1) << "\n";
				});
		},
		[](auto& from)
		{

		}, 5);
	Sleep(30);
}
