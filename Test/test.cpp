#define _CRT_SECURE_NO_WARNINGS

#define is_monitor_the_constructor_of_anyclass false
#define binding_instance_manager
#define is_graph_ques false

constexpr const char* ques_path = "D:/CCSP/2019/subgraph/data/";

#include<LightDiagram.h>

using namespace ld;
using namespace ld::resources;
using namespace std;

sync_with_stdio_false(__auto__);


class env
{
public:
	int n, m;
	string nodes;
	map<int, int> edges;
	env() :
		n(next<int>(cin)),
		m(next<int>(cin)),
		nodes(next<string>(cin))
	{
		for (int i = 0; i < m; i++)
		{
			int index = next<int>(cin) - 1;
			cin >> edges[index];
		}
	}

	decltype(auto) check_path()
	{

	}

	int result = 0;
};

void solve(ifstream& anss)
{
	env __env__;
	__env__.check_path();
	check_ans(__env__.result);
}

//try_solve_io_ques(ques_path)

class layer : public any_class
{
	using _Forward = any_binding_instance;
	init_class_symbol(layer);
public:
	layer(int index) :__init(index) {}
	declare_binding_instance(layer, left);
	declare_binding_instance(layer, right);
	int index;
	void init_class(any_binding_instance* from)
	{
		left.init_forward(from);
		right.init_forward(from);
	}

	virtual string ToString() const override
	{
		return to_string(index);
	}
};

int main()
{
	//GlobalExceptionInit
		defined_global_binding_instance(layer, root, 0);
	auto& left = binding(root.get_ref().left, root, -5);
	binding(left.get_ref().left, left, -10);
	binding(left.get_ref().right, left, -1);
	auto& right = binding(root.get_ref().right, root, 5);
	binding(right.get_ref().left, right, 1);
	binding(right.get_ref().right, right, 10);
	defined_global_binding_instance(layer, root2, 0);
	binding(root2.get_ref().left, root2, left);
	binding(root2.get_ref().right, root2, right);
	any_binding_instance::DrawMemory();
	//GlobalExcpetionApply
}
