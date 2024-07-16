
#include "test.h"
#include <../LLMToolkit/LLMToolkit.h>

using namespace ld;
using namespace std;
using llm::Spark::LLMSystem;

std::atomic_bool finish_bool(false);

struct inter
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

int xxxx()
{
	system("chcp 65001");
	instance<type_list<inter*, void*>> i(new inter(95), nullptr);
	cout << "value: " << *i.get_value_ptr<inter*>() << "\n";
	return 0;
}

int main()
{
	xxxx();
	instance<inter> i(new inter(1));
}
