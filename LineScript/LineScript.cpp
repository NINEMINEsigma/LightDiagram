#define _CRT_SECURE_NO_WARNINGS

#define is_monitor_the_constructor_of_anyclass false
#define binding_instance_manager

#include<Lang.h>

sync_with_stdio_false(__auto__);

using namespace std;
using namespace ld;

int main(int argc,char** argv)
{
	config_instance config(argc, argv);
	console.LogMessage("ok");
}