#include<test.h>

using namespace ld::algorithm;

#include<vector>
#include<set>
#include<iostream>

using namespace std;

auto ___auto___ = []()
	{
		cin.tie(nullptr)->sync_with_stdio(false), cout.tie(nullptr);
		return 0;
	};

using namespace std;

class node
{
	set<int> subj;
	int weight = 0;
	int self_weight = 0;
	map<int, set<node*>> delay_opter;
public:
	set<node*> childs;
	int index;
	void set_weight(int w)
	{
		this->self_weight = w;
	}
	int get_weight() const
	{
		return this->weight;
	}
	int all_weight = 0;
	int update_weight()
	{
		this->weight = this->self_weight;
		this->all_weight = this->is_enable ? this->self_weight : 0;
		for (auto& child : childs)
		{
			if (child->is_enable)
			{
				this->weight += child->update_weight();
				this->all_weight += child->all_weight;
			}
		}
		return this->weight;
	}
	void push_child(const int& parent, node* child)
	{
		this->subj.insert(child->index);
		if (this->index == parent)
			this->childs.insert(child);
		else
		{
			bool stats = false;
			for (auto& child_parent : this->childs)
			{
				if (child_parent->index == parent || child_parent->subj.count(parent))
				{
					child_parent->push_child(parent, child);
					stats = true;
					break;
				}
			}
			if (stats == false)
			{
				delay_opter[parent].insert(child);
			}
		}
		if (delay_opter.count(child->index))
		{
			for (auto&& delay : delay_opter[child->index])
			{
				this->push_child(child->index, delay);
			}
			delay_opter.erase(child->index);
		}
	}
	int ask_weight = 0;
	bool is_enable = true;
	node* update_ask_weight(const int& top_value, bool is_root = true)
	{
		node* result = this;
		for (auto child : childs)
		{
			child->ask_weight = abs(child->weight * 2 - top_value);
		}
		for (auto child : childs)
		{
			if (is_root == false && child->is_enable == false)continue;
			node* reget = child->update_ask_weight(top_value, false);
			if (result->is_enable == false && reget->is_enable)
				result = reget;
			else if (
				reget->is_enable &&
				(result->ask_weight > reget->ask_weight) ||
				(result->ask_weight == reget->ask_weight && result->index > reget->index))
				result = reget;
		}
		return result;
	}
	bool ask(const int& target)
	{
		return index == target || subj.count(target);
	}
};

int main()
{
	//init
	int n, m;
	cin >> n >> m;
	vector<node> mapper(n + 1);
	for (int i = 1; i <= n; i++)
	{
		int a;
		cin >> a;
		mapper[i].set_weight(a);
		mapper[i].index = i;
	}
	for (int i = 2; i <= n; i++)
	{
		int a;
		cin >> a;
		mapper[1].push_child(a, &mapper[i]);
	}
	//result
	vector<vector<int>> results;
	for (int i = 0; i < m; i++)
	{
		results.push_back({});
		for (auto& i : mapper)
			i.is_enable = true;
		int ask;
		cin >> ask;
		auto& result = *results.rbegin();
		node* current;
		int unable = 0;
		do
		{
			mapper[1].update_weight();
			mapper[1].ask_weight = mapper[1].get_weight();
			current = mapper[1].update_ask_weight(mapper[1].all_weight);
			result.push_back(current->index);
			if (current->ask(ask))
			{
				for (auto& item : mapper)
				{
					if (item.is_enable&&current != &item && current->childs.count(&item) == false)
					{
						item.is_enable = false;
						unable++;
					}
				}
			}
			else
			{
				for (auto& item : mapper)
				{
					if (item.is_enable && current->childs.count(&item))
					{
						item.is_enable = false;
						unable++;
					}
				}
				current->is_enable = false;
				unable++;
			}
		} while (unable < n);
	}
	for (auto&& result : results)
	{
		for (auto&& index : result)
		{
			cout << index << " ";
		}
		cout << "\n";
	}
}
