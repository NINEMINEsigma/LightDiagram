#define _CRT_SECURE_NO_WARNINGS

#define is_monitor_the_constructor_of_anyclass true
#define binding_instance_manager

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
		console.LogError(next_line(ss));
	}
	Ts(const Ts& value) :value(value.value)
	{
		stringstream ss;
		ss << typeid(Ts).name() << "[" << this->GetAnyAdr() << "] is in constructor(move)" << endl;
		console.LogError(next_line(ss));
	}
	~Ts()
	{
		stringstream ss;
		ss << "Ts{" << value << "} is de-opt" << endl;
		console.LogError(next_line(ss));
	}
	operator tag& ()
	{
		return value;
	}

	virtual std::string SymbolName() const override
	{
		return typeid(*this).name();
	}
	virtual string ToString() const override
	{
		if constexpr (enable_to_string<tag> && std::is_same_v < tag, void > == false)
			return to_string(value);
		else
			return GetType().name();
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
		console.LogWarning(next_line(ss));
	}
	virtual ~bitest()
	{
		stringstream ss;
		ss << "bitest{" << index.ToString() << "," << name.ToString() << "} is de-opt" << endl;
		console.LogWarning(next_line(ss));
	}

	void init_class(any_binding_instance& that)
	{
		index.init_forward(that);
		name.init_forward(that);
		next.init_forward(that);
	}

	virtual string ToString() const
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
	console.LogMessage(static_cast<bitest<>&>(that).ToString());
	console.LogMessage(to_string((int)(bitest<>&)that));
	console.LogMessage("Create next instance");
	binding_member(that.get_ref().next, that, 99, string("next test"));
	auto& next_that = that.get_ref().next;
	//next_that.get_ref().init_class(next_that);
	console.LogMessage(next_that.get_ref().ToString());
	console.LogMessage(to_string((int)next_that.get_ref()));
	any_binding_instance::DrawMemory();
}
