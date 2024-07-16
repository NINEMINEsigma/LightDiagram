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
#pragma region instance_counter Property
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
#pragma endregion
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
		instance(instance & from) noexcept :instance_counter(from.instance_counter)
		{
			this->instance_counter++;
		}
		instance(instance && from) noexcept :instance_counter(from.instance_counter) {}
		virtual ~instance()
		{
			if (*this->instance_counter < 1)
			{
				delete this->instance_counter;
				return;
			}
			else
			{
				(*this->instance_counter)--;
			}
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
		void swap(instance<void>&from)
		{
			size_t* tempcat = this->instance_counter;
			this->set_counter(from.instance_counter);
			from.set_counter(tempcat);
		}
		void swap(instance<void> && from)
		{
			size_t* tempcat = this->instance_counter;
			this->set_counter(from.instance_counter);
			from.set_counter(tempcat);
		}
		instance<void>& operator=(instance<void>&from) noexcept
		{
			this->set_counter(from.instance_counter);
			return *this;
		}
		instance<void>& operator=(instance<void> && from) noexcept
		{
			this->set_counter(from.instance_counter);
			return  *this;
		}
		bool operator==(const instance<void>&from) const noexcept
		{
			return this->instance_counter == from.instance_counter;
		}
	};

	template<> _LF_C_API(Class) instance<nullptr_t> Symbol_Push _LF_Inherited(instance<void>)
	{
	public:
		instance() :instance<void>() {}
		instance(instance & from) noexcept :instance<void>(from) {}
		instance(instance && from) noexcept :instance<void>(std::move(from)) {}
		virtual ~instance() {}
		void* ref_ptr() noexcept
		{
			return nullptr;
		}
		nullptr_t ref_ins()
		{
			throw ld::LDException("bad function");
		}
		void swap(instance<nullptr_t>&from)noexcept
		{
			instance<void>::swap(from);
		}
		void swap(instance<nullptr_t> && from)noexcept
		{
			instance<void>::swap(std::move(from));
		}
		instance<nullptr_t>& operator=(instance<nullptr_t>&from) noexcept
		{
			instance<void>::operator=(from);
			return *this;
		}
		instance<nullptr_t>& operator=(instance<nullptr_t>&from) noexcept
		{
			instance<void>::operator=(std::move(from));
			return *this;
		}
		bool operator==(const instance<nullptr_t>&from) const noexcept
		{
			return instance<void>::operator==(from);
		}
	};

	template<typename Tag> _LF_C_API(TClass) instance Symbol_Push _LF_Inherited(instance<void>)
	{
		Tag* instance_ptr;
	protected:
		virtual void release_nocallback() override
		{
			delete this->instance_ptr;
		}
	public:
		instance(Tag * ptr) :instance_ptr(ptr), instance<void>() {}
		instance() :instance<Tag>(nullptr) {}
		instance(instance & from) noexcept :instance_ptr(from.instance_ptr), instance<void>(from) { }
		instance(instance && from) noexcept : instance_ptr(from.instance_ptr), instance<void>(std::move(from)) {}
		virtual ~instance() {}

		Tag* ref_ptr() noexcept
		{
			return instance_ptr;
		}
		Tag& ref_ins() noexcept
		{
			return *instance_ptr;
		}
		instance<Tag>& operator=(instance<Tag>&from) noexcept
		{
			instance<void>::operator=(from);
			return *this;
		}
		instance<Tag>& operator=(instance<Tag> && from) noexcept
		{
			instance<void>::operator=(std::move(from));
			return *this;
		}
		bool operator==(const instance<nullptr_t>&from) const noexcept
		{
			return instance<void>::operator==(from);
		}
	};

	template<size_t Max> _LF_C_API(Class) instance<ConstexprCount<Max>> Symbol_Push _LF_Inherited(instance<nullptr_t>)
	{
	private:
		void CheckStatus()const
		{
			if (this->ref_count() >= Max)
				throw ld::LDException("over count");
		}
	public:
		instance() :instance<void>() {}
		instance(instance && from)noexcept :instance<void>(std::move(from)) {}
		instance(instance & from) :instance<void>(from)
		{
			CheckStatus();
		}
		virtual ~instance()
		{

		}

	};

	template<typename Tag, size_t SlotID> instance<SlotMode<Tag, SlotID>> Symbol_Push _LF_Inherited(any_class)
	{
		static instance<Tag> single_instance;
	public:

	};
	template<typename Tag, size_t SlotID> instance<Tag> instance<SlotMode<Tag, SlotID>>::single_instance;
}

#endif // !__FILE_LF_RAII
