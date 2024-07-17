
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

using test_type = meta_instance<type_list<ld_test>, type_list<int(void)>, type_list<int,int>>;
int __get(test_type* _this)
{
	return _this->_m_fields.get_value<0>();
	return 0;
}
int __get2(test_type* _this)
{
	return _this->_m_fields.get_value<0>() + 2024;
	return 0;
}

int main()
{
	system("chcp 65001");
	test_type testx(__get);
	testx.set_value<0>(95);
	cout << testx.invoke<0>() << "\n";
}
