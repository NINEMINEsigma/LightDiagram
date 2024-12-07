#include "LF_RAII.h"

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
			size_indicator_count = ld::Max(size_indicators.size(), ++size_indicator_count);
			return new size_tag(1);
		}
		else
		{
			auto result = size_indicators.top();
			size_indicators.pop();
			return result;
		}
	}
	void free_size_indicator(_In_ size_indicator& ptr)
	{
		lock_guard locker(size_indicator_locker);
		*ptr = 1;
		size_indicators.push(ptr);
		ptr = nullptr;
	}
	size_t get_size_indicator_count()
	{
		return size_indicator_count;
	}

	function<void* (size_t)> alloc_instance_inside_ptr_handler = [](size_t _Bytes)->void*
		{
			return ::malloc(_Bytes);
		};
	function<void(void*)> free_instance_inside_ptr_handler = [](void* ptr)->void
		{
			::free(ptr);
		};

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
				ss << "|--" << ptr;
				if (code_str == "nullptr")
				{
					console.MessageC = ConsoleColor::Cyan;
					console.LogMessage(next_line(ss));
					console.MessageC = ConsoleColor::None;
				}
				else
				{
					ss << "  " << string(Max(0, 60 - layer * 2), ' ') << code_str;
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
			auto* current = item->any_head_ptr->GetAnyAdr();
			string code_str = item->any_head_ptr->ToString();
			auto* inst_ptr = item->__get_instance_ptr();
			if (inst_ptr)
				header_counter[inst_ptr]++;
			if (inst_ptr)
			{
				ss << "binding " << current << " to " <<  inst_ptr
					<< ", symbol=" << item->any_head_ptr->SymbolName()
					<< ", \"" << code_str << "\"\n";
			}
			else
			{
				ss << "binding " << current << " to nullptr"
					<< ", symbol=" << item->any_head_ptr->SymbolName() << "\n";
			}
			if (code_str.length() > 50)
				mapper[current].code_str = code_str.substr(0, 45) + "...";
			else
				mapper[current].code_str = code_str;
			if (item->is_init() == false)
			{
				console.LogWarning(next_line(ss));
				mapper[current].is_lost_root = true;
			}
			else if (item->root_reachable())
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
	any_binding_instance::any_binding_instance(void* real_head_ptr, any_class* any_head_ptr) : __init(real_head_ptr), __init(any_head_ptr)
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

	instance<new_indicator>::instance(std::new_handler handler) :handler(ld::set_new_bad_catch(handler))
	{

	}
	instance<new_indicator>::~instance()
	{
		ld::set_new_bad_catch(handler);
	}

	void any_binding_instance::gc()
	{
		lock_guard<decltype(any_binding_instance_locker)> _locker(any_binding_instance_locker);
		set<any_binding_instance*> mapper;
		for (auto&& item : any_binding_instances)
		{
			if (item->is_init() && item->root_reachable() == false)
			{
				mapper.insert(item);
			}
		}
		for (auto&& item : mapper)
		{
			any_binding_instances.erase(item);
			static_cast<instance<void>*>(item->real_head_ptr)->release();
		}
	}

}

namespace std
{
	std::string to_string(const ld::tool_file& file)
	{
		return file.get_ref().string();
	}
}

namespace ld
{
	void instance<std::thread>::destruct_and_free_instance_ptr()
	{
		is_instance_safe_env;
		if (instance_ptr == nullptr)
			return;
		if (instance_ptr->joinable() && is_need_join_when_destructor)
			instance_ptr->join();
		__tool_destruct_and_free_instance_ptr(this->instance_ptr, free_instance_inside_ptr_handler);
		//instance_ptr->~tag();
		//free_instance_inside_ptr_handler(instance_ptr);
		//instance_ptr = nullptr;
	}
	instance<std::thread>::instance() :
		instance_ptr(new(alloc_instance_inside_ptr_handler(sizeof(tag))) tag()),
		instance<void>(){}
	instance<std::thread>::instance(const std::function<void()>& data) :
		instance_ptr(new(alloc_instance_inside_ptr_handler(sizeof(tag))) tag(data)), instance<void>() {}
	instance<std::thread>::instance(instance& from) noexcept : instance_ptr(from.instance_ptr),  instance<void>(from) {}
	instance<std::thread>::instance(instance&& from) noexcept : instance_ptr(from.instance_ptr),  instance<void>(std::move(from)) {}
	instance<std::thread>::instance(const instance& from) noexcept : instance_ptr(from.instance_ptr),  instance<void>(from) {}
	instance<std::thread>::~instance()
	{
		if (this->countable() != -1 && this->get_count() <= 1)
		{
			destruct_and_free_instance_ptr();
		}
	}

	void instance<std::thread>::swap(instance& from)noexcept
	{
		instance<void>::swap(from);
		std::swap(this->instance_ptr, from.instance_ptr);
	}
	void instance<std::thread>::swap(instance&& from)noexcept
	{
		instance<void>::swap(std::move(from));
		this->instance_ptr = std::move(from.instance_ptr);
	}

	instance<std::thread>& instance<std::thread>::operator=(instance& from) noexcept
	{
		if (this->get_count() <= 1)
		{
			destruct_and_free_instance_ptr();
		}
		instance<void>::operator=(from);
		this->instance_ptr = from.instance_ptr;
		return *this;
	}
	instance<std::thread>& instance<std::thread>::operator=(instance&& from) noexcept
	{
		if (this->get_count() <= 1)
		{
			destruct_and_free_instance_ptr();
		}
		instance<void>::operator=(std::move(from));
		this->instance_ptr = std::move(from.instance_ptr);
		return *this;
	}
	instance<std::thread>& instance<std::thread>::operator=(const function<void()>& from) noexcept
	{
		if (this->get_count() <= 1)
		{
			destruct_and_free_instance_ptr();
		}
		else
		{
			if (instance_ptr->joinable() && is_need_join_when_destructor)
				instance_ptr->join();
		}
		if (this->instance_ptr)
		{
			*this->instance_ptr = std::move(tag(from));
		}
		else
		{
			instance::operator=(instance(from));
		}
		return *this;
	}
	instance<std::thread>& instance<std::thread>::operator=(const instance& from) noexcept
	{
		if (this->get_count() <= 1)
		{
			destruct_and_free_instance_ptr();
		}
		instance<void>::operator=(from);
		this->instance_ptr = from.instance_ptr;
		return *this;
	}
	bool instance<std::thread>::operator==(const instance& from) const noexcept
	{
		return instance<void>::operator==(from);
	}
	bool instance<std::thread>::equals(const instance& from) const noexcept
	{
		return instance<void>::operator==(from);
	}

#ifdef _MSC_VER
	_NODISCARD instance<std::thread>::tag::native_handle_type instance<std::thread>::native_handle() noexcept
	{
		if (this->instance_ptr)
			return this->instance_ptr->native_handle();
		else
			return {};
	}
#endif
	_NODISCARD instance<std::thread>::tag::id instance<std::thread>::get_id() const noexcept
	{
		if (this->instance_ptr)
			return this->instance_ptr->get_id();
		else
			return {};
	}
	void instance<std::thread>::detach() noexcept
	{
		if (this->instance_ptr)
			this->instance_ptr->detach();
	}
	void instance<std::thread>::join() noexcept
	{
		if (this->instance_ptr && this->joinable())
		{
			this->instance_ptr->join();
		}
	}
	_NODISCARD bool instance<std::thread>::joinable() const noexcept
	{
		if (this->instance_ptr)
			return this->instance_ptr->joinable();
		else
			return false;
	}
}
