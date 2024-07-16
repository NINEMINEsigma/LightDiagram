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

//*
//	On this page, each <set>function returns the old value before the change if it returns
//*

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
		size_t* set_counter(size_t * incounter)
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
		size_t* set_counter(nullptr_t)
		{
			size_t* result = this->instance_counter;
			if (this->instance_counter)
			{
				(*this->instance_counter)--;
			}
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
			}
			this->instance_counter = nullptr;
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
		instance(instance&& from) noexcept :instance_counter(from.instance_counter) 
		{
			from.instance_counter = nullptr;
		}
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
			this->instance_counter = from.instance_counter;
			from.instance_counter = tempcat;
		}
		void swap(instance<void>&& from)
		{
			size_t* cat = this->instance_counter;
			this->instance_counter = from.instance_counter;
			if (cat && *cat == 1)
			{
				delete cat;
			}
			from.instance_counter = nullptr;
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
			this->swap(std::move(from));
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
	// Base referance counter
	using instance_base = instance<void>;

	// Referance Counter(has function <get_ptr> and <get_ref>)
	template<> _LF_C_API(Class) instance<nullptr_t>: public instance<void>
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
	// Base referance counter(has some function)
	using instance_counter = instance<nullptr_t>;

	//main instance type to be a shared ptr
	template<typename Tag> _LF_C_API(TClass) instance : public instance<void>
	{
		Tag * instance_ptr;
	public:
		instance(Tag* ptr) :instance_ptr(ptr), instance<void>() {}
		instance(instance& from) noexcept:instance_ptr(from.instance_ptr), instance<void>(from) {}
		instance(instance&& from) noexcept:instance_ptr(from.instance_ptr), instance<void>(std::move(from))
		{
			from.instance_ptr = nullptr;
		}
		virtual ~instance()
		{
			if (this->get_count() <= 1)
			{
				delete instance_ptr;
			}
		}
		Tag* get_ptr() const noexcept
		{
			return instance_ptr;
		}
		void swap(instance<Tag>& from)noexcept
		{
			instance<void>::swap(from);
			Tag* cat = this->instance_ptr;
			this->instance_ptr = from.instance_ptr;
			from.instance_ptr = cat;
		}
		void swap(instance<Tag>&& from)noexcept
		{
			instance<void>::swap(std::move(from));
			this->instance_ptr = from.instance_ptr;
			from.instance_ptr = nullptr;
		}
		instance<Tag>& operator=(instance<Tag>& from) noexcept
		{
			if (this->get_count() <= 1)
			{
				delete this->instance_ptr;
			}
			instance<void>::operator=(from);
			this->instance_ptr = from.instance_ptr;
			return *this;
		}
		instance<Tag>& operator=(instance<Tag>&& from) noexcept
		{
			if (this->get_count() <= 1)
			{
				delete this->instance_ptr;
			}
			instance<void>::operator=(std::move(from));
			this->instance_ptr = from.instance_ptr;
			from.instance_ptr = nullptr;
			return *this;
		}
		instance<Tag>& operator=(Tag*&& from) noexcept
		{
			if (this->get_count() <= 1)
			{
				delete this->instance_ptr;
			}
			instance<void>::release();
			this->instance_ptr = from;
			return *this;
		}
		bool operator==(const instance<Tag>& from) const noexcept
		{
			return instance<void>::operator==(from);
		}
		bool operator==(nullptr_t) const noexcept
		{
			return this->instance_ptr == nullptr;
		}
	};

	template<typename... Args> using type_list_instance_baseclass = std::array<void*, sizeof...(Args)>;
	// long arguments package, and need all value is ptr
	template<typename... Args> _LF_C_API(TClass) instance<type_list<Args...>>  : public instance<type_list_instance_baseclass<Args...>>
	{
	public:
		using type_list_tag = type_list<Args...>;
		using baseclass_tag = type_list_instance_baseclass<Args...>;
		using my_type_tag = instance;
		using base_type_tag = instance<type_list_instance_baseclass<Args...>>;
		instance(void* args[sizeof...(Args)]) :base_type_tag(new baseclass_tag())
		{
			for (size_t i = 0; i < sizeof...(Args); i++)
			{
				this->get_ptr()->operator[](i) = args[i];
			}
		}
		template<size_t index>
		using result_of_type_list = 
			typename choose_type < std::is_same_v<void, typename type_decltype<type_list_tag, index>::tag>, bad_indicator, 
			typename type_decltype<type_list_tag, index>::tag>::tag;
		instance(result_of_type_list<0> arg0) :base_type_tag(new baseclass_tag())
		{
			this->get_ptr()->operator[](0) = arg0;
		}
		instance(result_of_type_list<0> arg0, result_of_type_list<1> arg1) :base_type_tag(new baseclass_tag())
		{
			this->get_ptr()->operator[](0) = arg0;
			this->get_ptr()->operator[](1) = arg1;
		}
		instance(result_of_type_list<0> arg0, result_of_type_list<1> arg1, result_of_type_list<2> arg2) :base_type_tag(new baseclass_tag())
		{
			this->get_ptr()->operator[](0) = arg0;
			this->get_ptr()->operator[](1) = arg1;
			this->get_ptr()->operator[](2) = arg2;
		}
		instance(result_of_type_list<0> arg0, result_of_type_list<1> arg1, result_of_type_list<2> arg2, result_of_type_list<3> arg3) :base_type_tag(new baseclass_tag())
		{
			this->get_ptr()->operator[](0) = arg0;
			this->get_ptr()->operator[](1) = arg1;
			this->get_ptr()->operator[](2) = arg2;
			this->get_ptr()->operator[](3) = arg3;
		}
		instance(instance& from)noexcept :base_type_tag(from) {}
		instance(instance&& from)noexcept :base_type_tag(std::move(from)) {}
	private:
		template<size_t delete_index> void delete_array_target()
		{
			if constexpr (delete_index < sizeof...(Args))
			{
				delete static_cast<result_of_type_list<delete_index>>(this->get_ptr()->operator[](delete_index));
				delete_array_target<delete_index + 1>();
			}
		}
	public:
		virtual ~instance()
		{
			if (this->get_count() <= 1)
			{
				delete_array_target<0>();
			}
		}

		template<typename TargetType> constexpr static int index_result_of_type_list = type_list_tag::is_type_list_contains<TargetType>(0);

		template<size_t index>
		result_of_type_list<index> get_value_ptr()
		{
			return static_cast<result_of_type_list<index>>(this->get_ptr()->operator[](index));
		}
		template<typename TargetType>
		auto get_value_ptr()
		{
			return get_value_ptr<index_result_of_type_list<TargetType>>();
		}
		template<size_t index>
		void set_value_ptr(const result_of_type_list<index>& ptr)
		{
			this->get_ptr()->operator[](index) = ptr;
		}
		template<typename TargetType>
		void get_value_ptr(const decltype(get_value_ptr<index_result_of_type_list<TargetType>>())& ptr)
		{
			set_value_ptr<index_result_of_type_list<TargetType>>(ptr);
		}


		void swap(my_type_tag& from)noexcept
		{
			base_type_tag::swap(from);
		}
		void swap(my_type_tag&& from)noexcept
		{
			if (this->get_count() <= 1)
			{
				for (size_t i = 0; i < sizeof...(Args); i++)
				{
					delete this->get_ptr()->operator[](i);
				}
			}
			base_type_tag::swap(std::move(from));
		}
		my_type_tag& operator=(my_type_tag& from) noexcept
		{
			if (this->get_count() <= 1)
			{
				for (size_t i = 0; i < sizeof...(Args); i++)
				{
					delete this->get_ptr()->operator[](i);
				}
			}
			base_type_tag::operator=(from);
			return *this;
		}
		my_type_tag& operator=(my_type_tag&& from) noexcept
		{
			if (this->get_count() <= 1)
			{
				for (size_t i = 0; i < sizeof...(Args); i++)
				{
					delete this->get_ptr()->operator[](i);
				}
			}
			base_type_tag::operator=(std::move(from));
			return *this;
		}
		bool operator==(const my_type_tag& from) const noexcept
		{
			return base_type_tag::operator==(from);
		}
	};
	// pseudo class, all argument type add pointer to ptr-type
	template<typename... Args> using instance_pseudo_class = instance<type_list<std::add_pointer_t<Args>...>>;
	// long arguments package, and need all value is ptr
	template<typename... Args> using instance_args_package = instance<type_list<Args...>>;

	// limited-ref-count shared ptr
	template<size_t Max> _LF_C_API(Class) instance<ConstexprCount<Max>> Symbol_Push _LF_Inherited(instance<nullptr_t>)
	{
	private:
		void CheckStatus() const
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
			CheckStatus();
			return *this;
		}
		instance<Tag>& operator=(instance<Tag> && from) noexcept
		{
			instance<nullptr_t>::operator=(std::move(from));
			return *this;
		}
		template<size_t OtherMax>
		constexpr bool operator==(const instance<ConstexprCount<OtherMax>>&from) const noexcept
		{
			return Max == OtherMax;
		}
	};
	// limited-ref-count shared ptr, throw bad when over count
	template<size_t Max> using instance_limit = instance<ConstexprCount<Max>>;
	
	// memeory alloc buffer, for temp or long time
	// bug warning, the delete-constructor is not triggered
	template<size_t BufferSize, size_t SlotID> _LF_C_API(Class) instance<long_tag_indicator<long_tag_indicator<void, BufferSize>, SlotID>>
	{
		static void* buffer_ptr;
		static void* lock_ptr;
	public:
		constexpr static size_t capacity = BufferSize;
		constexpr static size_t uid = SlotID;
		instance(void* source, size_t length)
		{
			static_assert(length <= instance::capacity, "The capacity is not sufficient to accommodate the target object");
			if (instance::lock_ptr == nullptr)
			{
				instance::buffer_ptr = malloc(instance::capacity);
			}
			else
			{
				::memset(instance::buffer_ptr, 0x00, instance::capacity);
			}
			instance::lock_ptr = this;
			::memmove(instance::buffer_ptr, source, length);
		}
		template<typename TargetType>
		instance(TargetType* source) :instance(source, sizeof(TargetType)) {}
		instance(nullptr_t)
		{
			if (instance::lock_ptr != nullptr)
			{
				delete instance::buffer_ptr;
				instance::buffer_ptr = nullptr;
			}
			instance::lock_ptr = this;
		}
		instance() {}
		virtual ~instance()
		{
			if (instance::lock_ptr == this)
			{
				delete instance::buffer_ptr;
				instance::buffer_ptr = nullptr;
				instance::lock_ptr = nullptr;
			}
		}

		static void* get_ptr();
		template<typename TargetType> TargetType& like()
		{
			if (instance::lock_ptr == this && instance::buffer_ptr == nullptr)
			{
				instance::buffer_ptr = malloc(instance::capacity);
				//new(buffer_ptr) TargetType();
			}
			return *static_cast<TargetType*>(instance::buffer_ptr);
		}
	};
	// memeory alloc buffer, for temp or long time
	template<size_t BufferSize, size_t SlotID> using instance_memory_buffer = instance<long_tag_indicator<long_tag_indicator<void, BufferSize>, SlotID>>;
	template<size_t BufferSize, size_t SlotID> void* instance<long_tag_indicator<long_tag_indicator<void, BufferSize>, SlotID>>::get_ptr()
	{
		return instance::buffer_ptr;
	}
	template<size_t BufferSize, size_t SlotID> void* instance<long_tag_indicator<long_tag_indicator<void, BufferSize>, SlotID>>::buffer_ptr = nullptr;
	template<size_t BufferSize, size_t SlotID> void* instance<long_tag_indicator<long_tag_indicator<void, BufferSize>, SlotID>>::lock_ptr = nullptr;

}

#endif // !__FILE_LF_RAII
