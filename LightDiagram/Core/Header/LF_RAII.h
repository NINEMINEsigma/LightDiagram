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
	template<typename T> _LF_C_API(Class) instance;

	template<> _LF_C_API(Class) instance<void> Symbol_Push _LF_Inherited(any_class)
	{
	private:
		size_t* instance_counter;
	protected:
		size_t* get_counter()const
		{
			return this->instance_counter;
		}
		size_t* set_counter(size_t * incounter)
		{
			size_t* result = this->instance_counter;
			(*this->instance_counter)--;
			this->instance_counter = incounter;
			(*this->instance_counter)++;
			return result;
		}
		size_t* set_counter(nullptr_t)
		{
			size_t* result = this->instance_counter;
			(*this->instance_counter)--;
			this->instance_counter = nullptr;
			return result;
		}
		virtual void OnCounterEnter0_nologic() {}
		void OnCounterEnter0()
		{
			if (this->instance_counter == 0)
			{
				this->OnCounterEnter0_nologic();
			}
		}
		virtual void release_nocallback()
		{
			this->set_counter(nullptr);
		}
	public:
		instance() :instance_counter(new size_t(1)) {}
		instance(instance& from) noexcept:instance_counter(from.instance_counter)
		{
			this->instance_counter++;
		}
		instance(instance&& from) noexcept :instance_counter(from.instance_counter) {}
		virtual ~instance()
		{
			if (*this->instance_counter == 1)
			{
				delete this->instance_counter;
				return;
			}
			(*this->instance_counter)--;
		}
		size_t ref_count() const
		{
			return *this->instance_counter;
		}
		virtual void release()
		{
			this->release_nocallback();
			this->OnCounterEnter0();
		}
	};
}

#endif // !__FILE_LF_RAII
