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

	// Referance Counter
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
		size_t* set_counter(size_t *& incounter)
		{
			size_t* result = this->instance_counter;
			if (result)
			{
				(*this->instance_counter)--;
			}
			this->instance_counter = incounter;
			(*this->instance_counter)++;
			return result;
		}
		size_t* set_counter(size_t*&& incounter)
		{
			size_t* result = this->instance_counter;
			if (result)
			{
				(*this->instance_counter)--;
			}
			this->instance_counter = incounter;
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
		virtual void release_nocallback()
		{
			(*this->instance_counter)--;
			if (*this->instance_counter == 0)
			{
				delete this->instance_counter;
				this->instance_counter = nullptr;
			}
		}
	public:
		void release()
		{
			release_nocallback();
			this->set_counter(new size_t(1));
		}
		instance() :instance_counter(new size_t(1)) {}
		instance(instance & from) noexcept :instance_counter(from.instance_counter)
		{
			(*this->instance_counter)++;
		}
		instance(instance&& from) noexcept :instance_counter(from.instance_counter) { from.instance_counter = nullptr; }
		virtual ~instance()
		{
			if (this->instance_counter)
				release_nocallback();
		}
		size_t get_count() const noexcept
		{
			return this->instance_counter ? *this->instance_counter : 0;
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
			size_t* cat = this->set_counter(from.instance_counter);
			if (cat && *cat == 0)
			{
				delete cat;
			}
			return *this;
		}
		instance<void>& operator=(instance<void>&& from) noexcept
		{
			size_t* cat = this->set_counter(std::move(from.instance_counter));
			if (cat && *cat == 0)
			{
				delete cat;
			}
			from.instance_counter = nullptr;
			return  *this;
		}
		bool operator==(const instance<void>&from) const noexcept
		{
			return *this->instance_counter == *from.instance_counter;
		}
		bool is_same(const instance<void>& from) const noexcept
		{
			return this->instance_counter == from.instance_counter;
		}
	};

	using instance_base = instance<void>;

	// Referance Counter(has function <get_ptr> and <get_ref>)
	template<> _LF_C_API(Class) instance<nullptr_t> Symbol_Push _LF_Inherited(instance<void>)
	{
	public:
		using tag = nullptr_t;
		instance() :instance<void>() {}
		instance(void* anyptr) :instance<void>() {}
		instance(instance & from) noexcept :instance<void>(from) {}
		instance(instance && from) noexcept :instance<void>(std::move(from)) {}
		virtual ~instance() {}
		void* get_ptr() const noexcept
		{
			return nullptr;
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
		instance<nullptr_t>& operator=(instance<nullptr_t>&&from) noexcept
		{
			instance<void>::operator=(std::move(from));
			return *this;
		}
		bool operator==(const instance<nullptr_t>&from) const noexcept
		{
			return instance<void>::operator==(from);
		}
	};

	using instance_counter = instance<nullptr_t>;

	//main instance type to be a shared ptr
	template<typename Tag> _LF_C_API(TClass) instance final: public instance<void>
	{
		Tag* instance_ptr;
	protected:
#pragma region instance_ptr Property
		Tag* get_ptr()const
		{
			return this->instance_ptr;
		}
		Tag* set_ptr(Tag * inptr)
		{
			Tag* result = this->instance_ptr;
			this->instance_ptr = inptr;
			return result;
		}
#pragma endregion
	public:
		instance(Tag * ptr) :instance_ptr(ptr), instance<void>() {}
		//instance() :instance<Tag>(nullptr) {}
		instance(instance & from) noexcept :instance_ptr(from.instance_ptr), instance<void>(from) { }
		instance(instance && from) noexcept : instance_ptr(from.instance_ptr), instance<void>(std::move(from)) {}
		virtual ~instance()
		{
			if (this->get_count() <= 1)
			{
				delete this->instance_ptr;
			}
		}

		Tag* get_ptr() noexcept
		{
			return instance_ptr;
		}
		instance<Tag>& operator=(instance<Tag>&from) noexcept
		{
			if (this->get_count() <= 1) 
			{
				delete this->instance_ptr;
				this->instance_ptr = nullptr;
			}
			this->set_ptr(from.instance_ptr);
			instance<void>::operator=(from);
			return *this;
		}
		instance<Tag>& operator=(instance<Tag> && from) noexcept
		{
			if (this->get_count() <= 1)
			{
				delete this->instance_ptr;
				this->instance_ptr = nullptr;
			}
			this->set_ptr(std::move(from.instance_ptr));
			from.set_ptr(nullptr);
			instance<void>::operator=(std::move(from));
			return *this;
		}
		bool operator==(const instance<Tag>& from) const noexcept
		{
			return instance<void>::operator==(from);
		}
		void swap(instance<Tag>& from)noexcept
		{
			instance<void>::swap(from);
			Tag* tempptr = this->instance_ptr;
			this->set_ptr(from.instance_ptr);
			from.set_ptr(tempptr);
		}
		void swap(instance<Tag>&& from)noexcept
		{
			this->set_ptr(std::move(from.instance_ptr));
			from.instance_ptr = nullptr;
			instance<void>::swap(std::move(from));
		}
	};

	//limited-ref-count shared ptr
	template<size_t Max> _LF_C_API(Class) instance<ConstexprCount<Max>> Symbol_Push _LF_Inherited(instance<nullptr_t>)
	{
	private:
		void CheckStatus() const throw(LDException)
		{
			if (this->get_count() >= Max)
				throw ld::LDException("over count");
		}
		using Tag = ConstexprCount<Max>;
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
		instance<Tag>& operator=(instance<Tag>&from) noexcept
		{
			instance<nullptr_t>::operator=(from);
			return *this;
		}
		instance<Tag>& operator=(instance<Tag> && from) noexcept
		{
			instance<nullptr_t>::operator=(std::move(from));
			return *this;
		}
		bool operator==(const instance<ConstexprCount<Max>>&from) const noexcept
		{
			return instance<nullptr_t>::operator==(from);
		}
	};

	template<size_t Max> using instance_limit = instance<ConstexprCount<Max>>;
	/*
	template<typename Tag, size_t SlotID> _LF_C_API(Class) instance<SlotMode<Tag, SlotID>> Symbol_Push _LF_Inherited(any_class)
	{
		static instance* hoster;
		static Tag* single_ptr;
	public:
		instance(Tag * ptr)
		{
			delete instance::single_ptr;
			instance::single_ptr = ptr;
			instance::hoster = this;
		}
		instance() {}
		instance(instance && from) noexcept
		{
			if (instance::hoster == &from)
				instance::hoster = this;
		}
		virtual ~instance()
		{
			if (this == instance::hoster)
				delete instance::single_ptr;
		}

		Tag* ref_ptr() noexcept
		{
			return instance::single_ptr;
		}
		Tag& ref_ins() noexcept
		{
			return *instance::single_ptr;
		}
		instance<Tag>& operator=(instance<Tag> && from)  noexcept
		{
			if (instance::hoster == &from)
				instance::hoster = this;
			return *this;
		}
		template<typename AnyTag, size_t AnyID>
		constexpr bool operator==(const instance<SlotMode<AnyTag, AnyID>>&from) const noexcept
		{
			return std:; is_same_v<AnyTag, Tag>&& AnyID == SlotID;
		}
	};

	template<typename Tag, size_t SlotID> Tag* instance<SlotMode<Tag, SlotID>>::single_ptr = nullptr;
	template<typename Tag, size_t SlotID> instance<SlotMode<Tag, SlotID>>* instance<SlotMode<Tag, SlotID>>::hoster = nullptr;
	template<typename Tag, size_t SlotID>  using instance_static = instance<SlotMode<Tag, SlotID>>;*/
}

#endif // !__FILE_LF_RAII
