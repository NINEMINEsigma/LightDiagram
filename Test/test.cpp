#define _CRT_SECURE_NO_WARNINGS

#include<LightDiagram.h>

using namespace std;
using namespace ld;
using namespace ld::resources;

static auto __auto__ = []()
	{
		cin.tie(0);
		cout.tie(0);
		ios::sync_with_stdio(false);
		return 0;
	};

class item
{
public:
	vector<int> component;
	vector<int> translateFrom;
	int cost = 0;

	int get_cost(vector<item>& items)
	{
		if (cost)
		{
			return cost;
		}
		else
		{
			int sum = 0;
			for (auto&& i : component)
			{
				sum += items[i].get_cost(items);
			}
			for (auto&& i : translateFrom)
			{
				sum = min(sum, items[i].get_cost(items));
			}
			return sum;
		}
	}
};

class package
{
public:
	set<int> items;
	int cost;
};

void init_result(item& result, int length)
{
	while (length--)
	{
		result.component.push_back(next<int>(cin));
	}
}

void init_costitems(vector<item>& items,int length)
{
	for (int i = 1; i <= length; i++)
	{
		auto& item = items[i];
		int temp = next<int>(cin);
		if (temp == 0)
		{
			item.cost = next<int>(cin);
		}
		else
		{
			while (temp--)
			{
				item.component.push_back(next<int>(cin));
			}
		}
	}
}

void init_translateFrom(vector<item>& items,int length)
{
	while (length--)
	{
		int from, to;
		cin >> from >> to;
		items[to].translateFrom.push_back(from);
	}
}

void init_pack(vector<package>& packages, int length)
{
	while (length--)
	{
		int count;
		cin >> count >> packages[length].cost;
		while (count--)
		{
			packages[length].items.insert(next<int>(cin));
		}
	}
}

void solve()
{
	int n, m, p, q;
	cin >> n >> m >> p >> q;
	vector<item> items(m + 1);
	item& result = items[0];
	vector<package> packages(q);
	init_result(result, n);
	init_costitems(items, m);
	init_translateFrom(items, p);
	init_pack(packages, q);
	cout << result.get_cost(items) << endl;
}

int main()
{
	string path = "D:/CCSP/2023/decorate/data/";
	for (int i = 1, e = 20; i <= e; i++)
	{
		cout << "QUES" << i << ":" << endl;
		string fileindex = to_string(i);
		string filein = path + fileindex + ".in";
		freopen(filein.c_str(), "r", stdin);
		solve();
		string fileout = path + fileindex + ".ans";
		cout << "ANS:" << endl;
		ifstream fs(fileout.c_str());
		char buffer[1024] = {};
		while (fs.eof() == false)
		{
			fs.getline(buffer, 1024);
			cout << buffer;
		}
		console.LogMessage("\n---------------------------------------");
	}
}
