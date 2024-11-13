#define _CRT_SECURE_NO_WARNINGS

#define is_monitor_the_constructor_of_anyclass false

#include<LightDiagram.h>

using namespace ld;
//using namespace ld::resources;
using namespace std;

sync_with_stdio_false(__auto__);

void notepad_open()
{
	instance<process_kit> process("notepad", 0);
	cout << "stats: " << process->get_stats() << endl;
}

int main(int argc, char** argv)
{
	config_instance config(argc, argv);
	do
	{
		instance<thread> th(notepad_open);
		int i;
		cin >> i;
	} while (false);
}
