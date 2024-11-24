#define _CRT_SECURE_NO_WARNINGS

/*
#include<LightDiagram.h>

using namespace ld;
using namespace ld::resources;
using namespace std;

int main(int argc, char** argv)
{
	config_instance __config__(argc, argv);
}
*/

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

template<typename T,typename Q>
decltype(auto) Max(T&& first, Q&& second)
{
	return first > second ? first : second;
}
template<typename T,typename Q>
decltype(auto) Min(T&& first, Q&& second)
{
	return first < second ? first : second;
}
template<typename T, typename ...Args>
decltype(auto) Max(T&& first, T&& second, Args&&... args)
{
	return Max(Max(std::forward<T>(first), std::forward<T>(second)), std::forward<Args>(args)...);
}
template<typename T, typename ...Args>
decltype(auto) Min(T&& first, T&& second, Args&&... args)
{
	return Min(Min(std::forward<T>(first), std::forward<T>(second)), std::forward<Args>(args)...);
}

/*

struct node
{
	int cost;
	int ah;

	bool operator>(const node& right) const
	{
		return cost > right.cost;
	}
	bool operator<(const node& right) const
	{
		return cost < right.cost;
	}
};

vector<node> nodes;

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	priority_queue<node> pq;
	for (int i = 0; i < n; i++)
	{
		int cost, ah;
		cin >> cost >> ah;
		pq.push({ cost, ah });
	}
	while (!pq.empty() && m - pq.top().ah > 0 && pq.top().cost > k)
	{
		node top = pq.top();
		pq.pop();
		m -= top.ah;
		top.cost -= 1;
		pq.push(top);
	}
	if (pq.empty())
		cout << k << endl;
	else
		cout << Max(k, pq.top().cost) << endl;
	return 0;
}
*/

int k;

class node
{
public:
	vector<int> costs;
	node() :costs(k) {}
};

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<node> nodes(n);
	for(auto& i:nodes)
	{
		for (auto& item : i.costs)
		{
			cin >> item;
		}
	}
	return 0;
}