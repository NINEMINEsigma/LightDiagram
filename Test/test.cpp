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

using namespace ld::graph;

int main()
{
	defined_global_binding_instance(linear_iter<int>, root, 0);

	push_back(root, 1);
	push_back(root, 2);
	push_front(root, -1);
	push_front(root, -2);
	any_binding_instance::DrawMemory();

	pop_back(root);
	pop_front(root);
	any_binding_instance::DrawMemory();

	pop_back(root);
	pop_front(root);
	any_binding_instance::DrawMemory();

	cout << get_size_indicator_count();
}
