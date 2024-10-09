#include<Core/LF_RAII.h>

using namespace std;

namespace ld
{
	std::mutex any_binding_instance::any_binding_instance_locker;
	std::set<any_binding_instance*> any_binding_instance::any_binding_instances;
	void any_binding_instance::DrawMemory()
	{
		std::lock_guard<decltype(any_binding_instance_locker)> _locker(any_binding_instance_locker);
		console.LogWarning("\n--------------------------------------------");
		console.LogWarning("----ld::any_binding_instance::DrawMemory----");
		std::map<void*, int> header_counter;
		for (auto&& item : any_binding_instances)
		{
			auto* current = dynamic_cast<any_class*>(item);
			header_counter[item->real_head_ptr]++;
			if (item->root_reachable())
			{
				std::cout << current->ToString() << "[" << item->real_head_ptr << "], any_class adr: " << current->GetAnyAdr() << "\n";
			}
			else
			{
				std::cout << ConsoleColor::RedIntensity
					<< current->ToString() << "[" << item->real_head_ptr << "], any_class adr: " << current->GetAnyAdr() << "\n";
			}
			std::cout << ConsoleColor::None;
		}
		console.LogWarning("---------------pointer image----------------");
		for (auto&& item : header_counter)
		{
			std::cout << item.first << " ref times: " << item.second << "\n";
		}
		console.LogWarning("----ld::any_binding_instance::DrawMemory----");
		console.LogWarning("--------------------------------------------\n");
	}
	any_binding_instance::any_binding_instance(void* real_head_ptr) : __init(real_head_ptr)
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

