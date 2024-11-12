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
	cout << ld::constexpr_kit::Max(10, 9, 5, 1, 2) << "\n" << ld::constexpr_kit::Min(9, 5, 1, 0, 2);
}