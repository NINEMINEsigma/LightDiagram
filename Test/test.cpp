#define _CRT_SECURE_NO_WARNINGS

#include<LightDiagram.h>

using namespace ld;
//using namespace ld::resources;
using namespace std;

sync_with_stdio_false(__auto__);

atomic_int index = 0;
mutex _mutex;
constexpr int sound_max = 10;
bool is_task = false;

void testing()
{
	while (is_task == false) {}
	lock_guard lg(_mutex);
	int mysound = index.fetch_add(1);
	cout << mysound << endl;
}

void line1()
{
	instance_limit_pool<thread> ths(sound_max);
	for (int i = 0; i < sound_max; i++)
	{
		ths.current() = testing;
		ths.next();
	}
	for (auto&& item : ths)
	{
		item.join();
	}
}

void line2()
{
	is_task = true;
}

int main(int argc, char** argv)
{
	config_instance config(argc, argv);
	instance<thread> th1(line1);
	int a;
	cin >> a;
	line2();
}
