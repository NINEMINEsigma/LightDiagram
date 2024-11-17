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

int main(int argc, char** argv)
{
	config_instance config(argc, argv);
	vector<instance<thread>> ths;
	for (int i = 0; i < sound_max; i++)
	{
		ths.push_back(instance<thread>(testing));
	}
	is_task = true;
	for (auto&& item : ths)
	{
		if (item.joinable())
			item.join();
	}
}
