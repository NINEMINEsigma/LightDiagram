#include<Core/LF_RAII.h>

using namespace std;

namespace ld
{
	static stack<size_indicator> size_indicators;
	static std::mutex size_indicator_locker;
	static size_t size_indicator_count = 0;
	size_indicator obtain_size_indicator()
	{
		lock_guard locker(size_indicator_locker);
		if (size_indicators.empty())
		{
			size_indicator_count = Max(size_indicators.size(), ++size_indicator_count);
			return new size_tag(1);
		}
		else
		{
			auto result = size_indicators.top();
			size_indicators.pop();
			return result;
		}
	}
	void free_size_indicator(_In_ size_indicator ptr)
	{
		lock_guard locker(size_indicator_locker);
		*ptr = 1;
		size_indicators.push(ptr);
	}
	size_t get_size_indicator_count()
	{
		return size_indicator_count;
	}

	namespace
	{
		class interval_any_binding_instance_image
		{
		public:
			void* ptr = nullptr;
			bool is_lost_root = false;
			vector<const void*> to;
			string code_str;
			void draw(
				ConsolePro& console,
				map<const void*, interval_any_binding_instance_image>& mapper,
				set<interval_any_binding_instance_image*>& blacktree,
				int layer = 0)
			{
				stringstream ss;
				for (int i = layer; i--;)
				{
					ss << "--";
				}
				ss << "|--" << ptr << string(Max(0, 60 - layer * 2), ' ') << code_str;
				if (blacktree.count(this) != 0)
				{
					console.MessageC = ConsoleColor::Yellow;
					console.LogMessage(next_line(ss));
					console.MessageC = ConsoleColor::None;
				}
				else
				{
					if (is_lost_root)
					{
						console.MessageC = ConsoleColor::Red;
						console.LogMessage(next_line(ss));
						console.MessageC = ConsoleColor::None;
					}
					else if (layer == 0)
					{
						console.MessageC = ConsoleColor::Green;
						console.LogMessage(next_line(ss));
						console.MessageC = ConsoleColor::None;
					}
					else
						console.LogMessage(next_line(ss));
					blacktree.insert(this);
					for (auto&& item : to)
					{
						mapper[item].draw(console, mapper, blacktree, layer + 1);
					}
					blacktree.erase(this);
				}
			}
		};
	}

	std::mutex any_binding_instance::any_binding_instance_locker;
	std::set<any_binding_instance*> any_binding_instance::any_binding_instances;
	void any_binding_instance::DrawMemory()
	{
		std::lock_guard<decltype(any_binding_instance_locker)> _locker(any_binding_instance_locker);
		ConsolePro console(::console);
		console.MessageC = ConsoleColor::None;
		if (any_binding_instances.empty())
		{
			console.LogWarning("\n----ld::any_binding_instance::DrawMemory<any_binding_instances is empty>----\n");
			return;
		}
		console.LogWarning("\n--------------------------------------------");
		console.LogWarning("----ld::any_binding_instance::DrawMemory----");
		std::map<const void*, int> header_counter;
		std::map<const void*, interval_any_binding_instance_image> mapper;
		std::map<const void*, bool> mapper_stats;
		stringstream ss;
		for (auto&& item : any_binding_instances)
		{
			auto* current = item->GetAnyAdr();
			string code_str = item->ToString();
			header_counter[current]++;
			ss << "binding " << current << " to " << item->__get_instance_ptr() << ", symbol="
				<< item->SymbolName() << ", \""
				<< code_str << "\"\n";
			if (code_str.length() > 25)
				mapper[current].code_str = code_str.substr(0, 20) + "...";
			else
				mapper[current].code_str = code_str;
			if (item->root_reachable())
			{
				console.LogMessage(next_line(ss));
			}
			else
			{
				console.LogError(next_line(ss));
				mapper[current].is_lost_root = true;
			}
			void* temp;
			if (item->__forward(&temp))
			{
				mapper[current].ptr = current;
				mapper_stats[current] = true;
			}
			else
			{
				mapper[current].ptr = current;
				mapper_stats[current] = false;
				mapper[temp].to.push_back(current);
			}
		}
		console.LogWarning("-------------pointer ref image--------------");
		for (auto&& item : header_counter)
		{
			ss << item.first << " ref times: " << item.second << "\n";
			console.LogMessage(next_line(ss));
		}
		console.LogWarning("--------------memory ref tree---------------");
		set<interval_any_binding_instance_image*> blacktree;
		for (auto&& [key,stats] : mapper_stats)
		{
			if (stats)
			{
				mapper[key].draw(console, mapper, blacktree);
			}
		}
		console.LogWarning("----ld::any_binding_instance::DrawMemory----");
		console.LogWarning("--------------------------------------------\n");
	}
	any_binding_instance::any_binding_instance(void* real_head_ptr) : instance_any_class, __init(real_head_ptr)
	{
		any_binding_instances.insert(this);
	}
	any_binding_instance::~any_binding_instance()
	{
		any_binding_instances.erase(this);
	}
	bool any_binding_instance::__tool_root_reachable(std::set<void*>& blacktree)
	{
		return false;
	}
	bool any_binding_instance::root_reachable()
	{
		return false;
	}
}

