#ifndef __FILE_LF_RAII
#define __FILE_LF_RAII

#include <Core/Header/LF_Config.h>
#include <Core/Header/anyclass.h>
#include <Core/Header/static_traits.h>
#include <Core/Header/static_indicator.h>
#include <Core/Header/static_exist.h>
#include <Core/Header/LF_Exception.h>

if_type_exist_def(pointer_indicator);
if_type_exist_def(owner_indicator);
if_type_exist_def(counter_indicator);
if_type_exist_def(counter_num_indicator);

namespace ld
{
	_LF_C_API(OClass) instance_base : _LF_Inherited(any_class)
	{
	private:
		void* my_shared_ptr;
		size_t* my_counter;
		void* operator new(size_t t) = delete;
		void operator delete(void* ptr) = delete;
		void try_destroy()
		{
			if (*my_counter == 0)
			{
				delete my_counter;
				delete my_shared_ptr;
			}
		}
		void sub_counter()
		{
			(*my_counter)--;
		}
		void add_counter()
		{
			(*my_counter)++;
		}
	protected:
		void set_ptr(void* ptr,size_t* ctr)
		{
			this->my_shared_ptr = ptr;
			sub_counter();
			this->my_counter = ctr;
			add_counter();
		}
		void* get_ptr() const
		{
			return this->my_shared_ptr;
		}
	public:
		instance_base(void * &ptr) :my_shared_ptr(ptr), my_counter(new size_t(1)) { ptr = nullptr; }
		instance_base(void * &&ptr) :my_shared_ptr(std::move(ptr)), my_counter(new size_t(1)) { ptr = nullptr; }
		instance_base(instance_base& from)noexcept :my_shared_ptr(from.my_shared_ptr), my_counter(from.my_counter) { (*my_counter)++; }
		instance_base(instance_base&& from)noexcept :my_shared_ptr(from.my_shared_ptr) { from.my_shared_ptr = nullptr; }
		virtual ~instance_base()
		{
			sub_counter();
			try_destroy();
		}
	};


	static std::unordered_set <instance_base*> all_instance_base_set;

	template<typename T>
	_LF_C_API(TClass) instance : _LF_Inherited(instance_base)
	{
	private:
		T* my_shared_ptr;
		size_t* my_counter;
		void* operator new(size_t t) = delete;
		void operator delete(void* ptr) = delete;

	public:
		instance(T * &ptr) :my_shared_ptr(ptr), my_counter(new size_t(1)) { ptr = nullptr; }
		instance(T * &&ptr) :my_shared_ptr(std::move(ptr)), my_counter(new size_t(1)) { ptr = nullptr; }
		instance(instance & from)noexcept :my_shared_ptr(from.my_shared_ptr), my_counter(from.my_counter) { (*my_counter)++; }
		instance(instance && from)noexcept :my_shared_ptr(from.my_shared_ptr) { from.my_shared_ptr = nullptr; }
		virtual ~instance()
		{
			(*my_counter)--;
			if (*my_counter == 0)
			{
				delete my_counter;
				delete my_shared_ptr;
			}
		}
	};
}

#endif // !__FILE_LF_RAII
