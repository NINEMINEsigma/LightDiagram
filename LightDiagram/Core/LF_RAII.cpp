#include<Core/LF_RAII.h>

using namespace std;

namespace ld
{
	namespace
	{
		class interval_any_binding_instance_image
		{
		public:
			void* ptr = nullptr;
			vector<const void*> to;
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
				ss << "|--" << ptr;
				if (blacktree.count(this) != 0)
				{
					console.MessageC = ConsoleColor::Yellow;
					console.LogMessage(next_line(ss));
					console.MessageC = ConsoleColor::None;
				}
				else
				{
					if (layer == 0)
					{
						console.MessageC = ConsoleColor::Green;
						console.LogMessage(next_line(ss));
						console.MessageC = ConsoleColor::None;
					}
					else
						console.LogMessage(next_line(ss) + string(to.size() == 0 ? "*" : ""));
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
		console.LogWarning("\n--------------------------------------------");
		console.LogWarning("----ld::any_binding_instance::DrawMemory----");
		std::map<const void*, int> header_counter;
		std::map<const void*, interval_any_binding_instance_image> mapper;
		std::map<const void*, bool> mapper_stats;
		stringstream ss;
		for (auto&& item : any_binding_instances)
		{
			auto* current = item->GetAnyAdr();
			header_counter[current]++;
			ss << "binding " << current << " to " << item->__get_instance_ptr() << ", symbol="
				<< item->SymbolName() << ", \""
				<< item->ToString() << "\"\n";
			if (item->root_reachable())
			{
				console.LogMessage(next_line(ss));
			}
			else
			{
				console.LogError(next_line(ss));
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

