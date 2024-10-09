#define _CRT_SECURE_NO_WARNINGS

#define is_monitor_the_constructor_of_anyclass true

#include<LightDiagram.h>

using namespace ld;
using namespace ld::resources;
using namespace std;

sync_with_stdio_false(__auto__);

template<typename T>
struct Ts final: public any_class
{
	using tag = remove_cv_t<T>;
	tag value;
	Ts(const tag& value) :value(value)
	{
		stringstream ss;
		ss << typeid(Ts).name() << "[" << this->GetAnyAdr() << "] is in constructor" << endl;
		console.LogError(next_line(ss) + "\n");
	}
	Ts(const Ts& value) :value(value.value)
	{
		stringstream ss;
		ss << typeid(Ts).name() << "[" << this->GetAnyAdr() << "] is in constructor(move)" << endl;
		console.LogError(next_line(ss) + "\n");
	}
	~Ts()
	{
		stringstream ss;
		ss << "Ts{" << value << "} is de-opt" << endl;
		console.LogError(next_line(ss) + "\n");
	}
	operator tag& ()
	{
		return value;
	}

	virtual std::string SymbolName() const override
	{
		return typeid(*this).name();
	}
};

template<typename _Forward = global_indicator>
class bitest final: public any_class
{
	init_class_symbol(bitest);
public:
	declare_binding_instance(Ts<int>, index);
	declare_binding_instance(Ts<string>, name);
	declare_binding_instance(bitest<any_binding_instance>, next);
	bitest(int index, string name) :__init(index), __init(name)
	{
		stringstream ss;
		ss << "bitest[" << this->GetAnyAdr() << "] is in constructor" << endl;
		console.LogWarning(next_line(ss) + "\n");
	}
	virtual ~bitest()
	{
		stringstream ss;
		ss << "bitest{" << index << "," << name << "} is de-opt" << endl;
		console.LogWarning(next_line(ss) + "\n");
	}

	void init_class(__class__& that)
	{
		index.init_forward(that);
		name.init_forward(that);
		next.init_forward(that);
	}

	virtual const char* ToString() const
	{
		return static_cast<string&>(name.get_ref()).c_str();
	}
	operator int() const
	{
		return static_cast<int&>(index.get_ref());
	}

	virtual std::string SymbolName() const override
	{
		return typeid(*this).name();
	}
};

int main()
{
	auto that = make_binding_instance_g<bitest<>>(1, string("test"));
	console.LogMessage(string((const char*)(bitest<>&)that) + "\n");
	console.LogMessage(to_string((int)(bitest<>&)that) + "\n");
	console.LogMessage("Create next instance\n");
	auto& next_that = that.get_ref().next = make_binding_instance<decltype(that.get_ref().next)>(that, 99, string("next test"));
	console.LogMessage(string(next_that.get_ref().ToString()) + "\n");
	console.LogMessage(to_string((int)next_that.get_ref()) + "\n");
	any_binding_instance::DrawMemory();
}
