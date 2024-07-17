
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
	instance_memory_buffer<sizeof(inter)*2, 0> temp;
	cout << temp.get_address_like_array<inter>(0)->value << "\n";
	cout << temp.get_address_like_array<inter>(1)->value << "\n";
}

int main()
{
	system("chcp 65001");
	instance_memory_buffer<sizeof(inter)*2, 0> temp(nullptr);
	new(temp.get_address_like_array<inter>(0)) inter(1);
	new(temp.get_address_like_array<inter>(1)) inter(2);
	xxxx();
	temp.release_target<inter>(0);
	temp.release_target<inter>(1);
}
