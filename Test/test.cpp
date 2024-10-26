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

//try_solve_io_ques(ques_path);

class Solution 
{
public:
	double findMaxAverage(vector<int>& nums, int k) 
	{
		int result = 0;
		for (int i = 0, e = nums.size() - k; i < e; i++)
		{
			int sum = 0;
			for (int j = i, ej = i + k; j < ej; j++)
			{
				sum += nums[j];
			}
			result = max(sum, result);
		}
		return result / static_cast<double>(k);
	}
};