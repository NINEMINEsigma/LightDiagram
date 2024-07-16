
#include "test.h"
#include <../LLMToolkit/LLMToolkit.h>

using namespace ld;
using namespace std;
using llm::Spark::LLMSystem;

std::atomic_bool finish_bool(false);

struct inter :_LF_Inherited(any_class)
{
	inter(int v) :value(v)
	{
		cout << ld::ConsoleColor::Green << value << endl << ld::ConsoleColor::None;
	}
	~inter()
	{
		cout << ld::ConsoleColor::Red << value << endl << ld::ConsoleColor::None;
	}
	int value;
	operator int()
	{
		return value;
	}
};

void tlog(instance<inter> i)
{
	cout << "count: " << i.get_count() << " address: " << &i << " ptr: " << i.get_ptr() << " value: " << *i.get_ptr() << "\n";
}

void xxxx()
{
	instance_memory_buffer<sizeof(inter), 0> temp;
	cout << temp.like<inter>().value << "\n";
	temp.like<inter>().value = 1999;
}

int main()
{
	system("chcp 65001");
	instance_memory_buffer<sizeof(inter), 0> temp(nullptr);
	temp.like<inter>().value = 95;
	fvar_info finfo = make_field_info(inter, value);
	cout << temp.like<inter>().value << "\n";
	finfo.set_rv(&temp.like<inter>(), 2024);
	cout << temp.like<inter>().value << "\n";
	xxxx();
	cout << temp.like<inter>().value << "\n";
}
