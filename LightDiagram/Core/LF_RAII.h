#ifndef __FILE_LF_RAII
#define __FILE_LF_RAII

#include <Core/LF_Config.h>
#include <Core/anyclass.h>
#include <Core/static_traits.h>
#include <Core/static_indicator.h>
#include <Core/static_exist.h>
#include <Core/LF_Exception.h>

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
		instance(instance && from) noexcept :instance_counter(from.instance_counter)
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
		void swap(instance<void> && from)
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
		instance<void>& operator=(instance<void> && from) noexcept
		{
			this->swap(std::move(from));
			return  *this;
		}
		bool operator==(const instance<void>&from) const noexcept
		{
			return *this->instance_counter == *from.instance_counter;
		}
		bool is_same(const instance<void>&from) const noexcept
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
		instance(instance& from) noexcept :instance<void>(from) {}
		instance(instance&& from) noexcept :instance<void>(std::move(from)) {}
		virtual ~instance() {}
		void* get_ptr() const noexcept
		{
			return nullptr;
		}
		void swap(instance<nullptr_t>& from)noexcept
		{
			instance<void>::swap(from);
		}
		void swap(instance<nullptr_t>&& from)noexcept
		{
			instance<void>::swap(std::move(from));
		}
		instance<nullptr_t>& operator=(instance<nullptr_t>& from) noexcept
		{
			instance<void>::operator=(from);
			return *this;
		}
		instance<nullptr_t>& operator=(instance<nullptr_t>&& from) noexcept
		{
			instance<void>::operator=(std::move(from));
			return *this;
		}
		bool operator==(const instance<nullptr_t>& from) const noexcept
		{
			return instance<void>::operator==(from);
		}
	};
	// Base referance counter(has some function)
	using instance_counter = instance<nullptr_t>;


	//main instance template type to be a shared ptr
	template<typename Tag> _LF_C_API(TClass) instance : public instance<void>
	{
		Tag * instance_ptr;
	public:
		instance(Tag* ptr) :instance_ptr(ptr), instance<void>() {}
		instance(instance& from) noexcept :instance_ptr(from.instance_ptr), instance<void>(from) {}
		instance(instance&& from) noexcept :instance_ptr(from.instance_ptr), instance<void>(std::move(from))
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
		Tag& get_ref() const
		{
			return *instance_ptr;
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
		instance<Tag>& operator=(Tag* from) noexcept
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
		bool equals(const instance<Tag>& from) const noexcept
		{
			return instance<void>::operator==(from);
		}
		bool equals(nullptr_t) const noexcept
		{
			return this->instance_ptr == nullptr;
		}
		bool equals(Tag* from) const noexcept
		{
			return this->instance_ptr == from;
		}
		bool equals(const Tag& from) const noexcept
		{
			return *this->instance_ptr == from;
		}

		//reboxing operator
		//warning: delete-constructor may not be called correctly
		template<typename OtherTag>
		bool reboxing(instance<OtherTag>& from)
		{
			if constexpr (std::is_base_of_v<Tag, OtherTag>)
			{
				if (this->get_count() <= 1)
				{
					delete this->instance_ptr;
				}
				instance<void>::operator=(from);
				this->instance_ptr = from.get_ptr();
				return true;
			}
			else if constexpr (std::is_base_of_v<OtherTag, Tag>)
			{
				if (dynamic_cast<OtherTag*>(from.get_ptr()) == nullptr)return false;
				if (this->get_count() <= 1)
				{
					delete this->instance_ptr;
				}
				instance<void>::operator=(from);
				this->instance_ptr = dynamic_cast<OtherTag*>(from.get_ptr());
				return true;
			}
			else return false;
		}
		//reboxing operator
		//warning: delete-constructor may not be called correctly
		template<typename OtherTag>
		bool reboxing(instance<OtherTag>&& from)
		{
			if constexpr (std::is_base_of_v<Tag, OtherTag>)
			{
				if (this->get_count() <= 1)
				{
					delete this->instance_ptr;
				}
				instance<void>::operator=(std::move(from));
				this->instance_ptr = from.get_ptr();
				return true;
			}
			else if constexpr (std::is_base_of_v<OtherTag, Tag>)
			{
				if (dynamic_cast<OtherTag*>(from.get_ptr()) == nullptr)return false;
				if (this->get_count() <= 1)
				{
					delete this->instance_ptr;
				}
				instance<void>::operator=(std::move(from));
				this->instance_ptr = dynamic_cast<OtherTag*>(from.get_ptr());
				return true;
			}
			else return false;
		}
		//reboxing operator
		//warning: delete-constructor may not be called correctly
		//return from
		template<typename OtherTag>
		instance<OtherTag>& operator<<(instance<OtherTag>& from)
		{
			this->reboxing(from);
			return from;
		}
		//reboxing operator
		//warning: delete-constructor may not be called correctly
		//return itself
		template<typename OtherTag>
		instance& operator<<(instance<OtherTag>&& from)
		{
			this->reboxing(std::move(from));
			return *this;
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
	template<size_t Max> _LF_C_API(TClass) instance<ConstexprCount<Max>> Symbol_Push _LF_Inherited(instance<nullptr_t>)
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
	// bug warning, the delete-constructor is not triggered on this type's delete-constructor
	// and buffer capacity is BufferSize+1 !!!
	template<size_t BufferSize, size_t SlotID> _LF_C_API(TClass) instance<long_tag_indicator<long_tag_indicator<void_indicator, BufferSize>, SlotID>> Symbol_Endl
	{
		static void* buffer_ptr;
		static void* lock_ptr;
	public:
		constexpr static size_t capacity = BufferSize + 1;
		constexpr static size_t uid = SlotID;
		using args_package_indicator = long_tag_indicator<long_tag_indicator<void_indicator, BufferSize>, SlotID>;
		//generate buffer, it will alloc memory or clear old buffer
		bool create()
		{
			if (instance::lock_ptr == nullptr)
			{
				instance::buffer_ptr = malloc(instance::capacity);
				instance::lock_ptr = this;
			}
			else if (instance::lock_ptr == this)
			{
				::memset(instance::buffer_ptr, 0x00, instance::capacity);
			}
			else return false;
			return true;
		}
		//generate buffer and copy from source
		instance(void_indicator, void* source, size_t length)
		{
			if (length <= instance::capacity)
			{
				if (create() && source)
					::memmove(&static_cast<char*>(instance::buffer_ptr)[1], source, length + 1);
			}
			else
			{
				throw ld::LDException("The capacity is not sufficient to accommodate the target object");
			}
		}
		//generate buffer but not create instance of target
		instance(nullptr_t)
		{
			if (instance::lock_ptr != nullptr) instance::lock_ptr = this;
			create();
		}
		//able to refer memory buffer
		instance() {}
		//release buffer, it will free memory
		bool release() const
		{
			if (instance::lock_ptr == this)
			{
				::free(instance::buffer_ptr);
				instance::buffer_ptr = nullptr;
				instance::lock_ptr = nullptr;
				return true;
			}
			return false;
		}
		virtual ~instance()
		{
			release();
		}

		void* get_buffer() const
		{
			return &static_cast<char*>(instance::buffer_ptr)[1];
		}
		void* get_address_with_offset(size_t offset)
		{
			return &static_cast<char*>(instance::buffer_ptr)[1 + offset];
		}
		template<typename TargetType>
		TargetType* get_address_like_array(size_t offset)
		{
			return reinterpret_cast<TargetType*>(&static_cast<char*>(instance::buffer_ptr)[1 + sizeof(TargetType) * offset]);
		}
		//generate buffer then move target data bitset or create instance of target
		template<typename TargetType, typename... Args> instance(TargetType* source, const Args&... args) :instance(void_indicator{}, source, sizeof(TargetType))
		{
			static_assert(sizeof(TargetType) <= instance::capacity, "The capacity is not sufficient to accommodate the target object");
			if (source == nullptr)
			{
				new(get_buffer()) TargetType(args...);
			}
		}
		static void* get_ptr();
		template<typename TargetType> TargetType& like()
		{
			return *static_cast<TargetType*>(this->get_buffer());
		}

		//create target and lock on single buffer
		template<typename TargetType,typename... Args> TargetType& create_target(const Args&... args)
		{
			if (instance::lock_ptr == this)
			{
				create();
				return *new(this->get_buffer()) TargetType(args...);
			}
			else throw ld::LDException("muti-source buffer use create");
		}
		//release target and lock on single buffer
		template<class TargetType> void release_target(size_t offset = 0)
		{
			if (instance::lock_ptr == this)
			{
				if (instance::buffer_ptr != nullptr)
				{
					this->get_address_like_array<TargetType>(offset)->~TargetType();
				}
			}
			else throw ld::LDException("muti-source buffer use release");
		}
	};
	// memeory alloc buffer, for temp or long time
	// bug warning, the delete-constructor is not triggered on this type's delete-constructor
	// and buffer capacity is BufferSize+1 !!!
	template<size_t BufferSize, size_t SlotID> using instance_memory_buffer = instance<long_tag_indicator<long_tag_indicator<void_indicator, BufferSize>, SlotID>>;
	template<size_t BufferSize, size_t SlotID> void* instance<long_tag_indicator<long_tag_indicator<void_indicator, BufferSize>, SlotID>>::get_ptr()
	{
		return instance::buffer_ptr;
	}
	template<size_t BufferSize, size_t SlotID> void* instance<long_tag_indicator<long_tag_indicator<void_indicator, BufferSize>, SlotID>>::buffer_ptr = nullptr;
	template<size_t BufferSize, size_t SlotID> void* instance<long_tag_indicator<long_tag_indicator<void_indicator, BufferSize>, SlotID>>::lock_ptr = nullptr;

	// file stream by instance impt
	template<typename... Args> _LF_C_API(TClass) instance<type_list<io_tag_indicator, Args...>>  Symbol_Push _LF_Inherited(instance<void>)
	{
	public:
		//TODO
	};
	// file (a)stream by instance impt
	template<typename... Args> using instance_astream = instance<type_list<io_tag_indicator, string_indicator, Args...>>;
	// file wstream by instance impt
	template<typename... Args> using instance_wstream = instance<type_list<io_tag_indicator, wstring_indicator, Args...>>;
	// file stream by instance impt
	template<typename... Args> using instance_stream_t = instance < type_list < io_tag_indicator, Args... >>;


	template<typename... Modules, typename... Functions, typename... Fields> _LF_C_API(TClass)
		instance<type_list<class_indicator, type_list<Modules...>, type_list<Functions...>, type_list<Fields...>>> Symbol_Endl
	{
	public:
		using base_tag = type_list<type_list<type_list<Modules...>, type_list<Functions...>, type_list<Fields...>>>;
		using module_list = type_list<Modules...>;
		using func_list = type_list<Functions...>;
		using field_list = type_list<Fields...>;
	public:
		using func_container = class_component_indicatior<std::function<typename extension_func_traits<type_list<instance*, Functions>>::tag>...>;
		using field_container = class_component_indicatior<Fields...>;
	public:
		func_container _m_funcs;
		field_container _m_fields;
		instance(std::function<typename extension_func_traits<type_list<instance*, Functions>>::tag>... _funcs_args) : _m_funcs(_funcs_args...), _m_fields() {}
		instance(instance&) = delete;
		instance(instance&&) = delete;
		instance operator=(instance&) = delete;
		instance operator=(instance&&) = delete;
		virtual ~instance() {}

		template<size_t index, typename... Args>// decltype(std::declval<instance>()._m_funcs.get_value<index>()(nullptr)) 
		auto&& invoke(Args&&... args)
		{
			if constexpr (std::is_same_v<void, decltype(this->_m_funcs.get_value<index>().operator()(this, args...))>)
				this->_m_funcs.get_value<index>().operator()(this, args...);
			else
				return this->_m_funcs.get_value<index>().operator()(this, args...);
		}
		template<size_t index>
		auto& get_value()
		{
			return this->_m_fields.get_value<index>();
		}
		template<size_t index,typename _T>
		void set_value(_T&& right)
		{
			 this->_m_fields.set_value<index>(std::forward<_T>(right));
		}
	};
	template<typename ModulesList, typename FunctionsList, typename FieldsList > using meta_instance = instance<type_list<class_indicator, ModulesList, FunctionsList, FieldsList>>;

	//array memory buffer
	template<typename VoidContainerType> _LF_C_API(TClass)
		instance<type_list<container_indicator, void_indicator, VoidContainerType>> Symbol_Push _LF_Inherited(instance<VoidContainerType>)
	{
		instance(void* head, void* tail, size_t unit_size) :instance<VoidContainerType>(new VoidContainerType(head, tail, unit_size)) {}
	public:
		instance(void* head, size_t length, size_t unit_size) :instance(head, (void*)((size_t)head + length * unit_size), unit_size) {}
		instance(size_t length, size_t unit_size) :instance(::malloc(sizeof(char) * length * unit_size), length, unit_size) {}
		virtual ~instance()
		{
			::free(this->get_ptr()->get_head());
		}
	};
	//array target type buffer
	template<typename AccTy, class AccContainerType> _LF_C_API(TClass)
		instance<type_list<container_indicator, AccTy, AccContainerType>> Symbol_Push _LF_Inherited(instance<AccContainerType>)
	{
	public:
		constexpr static size_t unit_size = sizeof(AccTy);
	private:
		instance(AccTy * head, AccTy * tail) :instance<AccContainerType>(new AccContainerType(head, tail)) {}
	public:
		instance(void* head, size_t length) :instance((AccTy*)head, (AccTy*)((size_t)head + length * unit_size)) {}
		instance(size_t length) :instance(::malloc(sizeof(char) * length * unit_size), length) {}
		virtual ~instance()
		{
			::free(this->get_ptr()->get_head());
		}
	};
	template<typename VoidContainerType> using void_container_instance = instance<type_list<container_indicator, void_indicator, VoidContainerType>>;
	template<typename AccTy, typename AccContainerType> using accu_container_instance = instance<type_list<container_indicator, AccTy, AccContainerType>>;

	//file reader of setup split char
	template<typename _CharTy, size_t splitChar, size_t splitLineChar>
	_LF_C_API(TClass) instance<type_list<io_tag_indicator, long_tag_indicator<_CharTy, splitChar>, long_tag_indicator<_CharTy, splitLineChar>>>
		Symbol_Push _LF_Inherited(instance<std::vector<std::vector<std::basic_string<_CharTy>>>>) Symbol_Endl
	{
	public:
		using string = std::basic_string<_CharTy>;
		using first_layer = std::vector<std::vector<std::basic_string<_CharTy>>>;
		using second_layer = std::vector<std::basic_string<_CharTy>>;
		using inside_layer = std::basic_string<_CharTy>;
		using inside_char = _CharTy;

		void read(std::ifstream & in_file)
		{
			_CharTy val;
			string current_str;
			auto& container = *this->get_ptr();
			container.push_back(second_layer());
			size_t row_count = 0;
			while (in_file.read(reinterpret_cast<char*>(&val), sizeof(_CharTy)))
			{
				if ((size_t)val == (size_t)splitChar)
				{
					container[row_count].push_back(current_str);
					current_str.clear();
				}
				else if ((size_t)val == (size_t)splitLineChar)
				{
#if defined(_WINDOW_)||true
					if (current_str.empty() == false && (size_t)'\r' == (size_t)*current_str.rbegin())
						current_str.erase(--current_str.end());
#endif // _WINDOW_
					if (current_str.empty() == false)
					{
						container[row_count].push_back(current_str);

						current_str.clear();
					}
					row_count++;
					container.push_back(second_layer());
				}
				else
				{
					current_str.push_back(val);
				}
				if (in_file.eof())break;
			}
			if (current_str.empty() == false)
			{
				container[row_count].push_back(current_str);
				current_str.clear();
			}
		}
		void read(const string_indicator::tag& path)
		{
			//open file, in|binary
			std::ifstream in_file(path, std::ios::in | std::ios::binary);
			read(in_file);
			in_file.close();
		}

		instance() :instance<first_layer>(new first_layer()) {}
		instance(std::ifstream& in_file) :instance<first_layer>(new first_layer())
		{
			read(in_file);
		}
		instance(const string_indicator::tag & path) :instance<first_layer>(new first_layer())
		{
			read(path);
		}
		instance(instance && from) noexcept :instance<first_layer>(std::move(from)) {}
		instance& operator=(instance&& from) noexcept
		{
			instance<first_layer>::operator=(std::move(from));
			return *this;
		}
		instance(instance & from) noexcept : instance<first_layer>(from) {}
		instance& operator=(instance& from) noexcept
		{
			instance<first_layer>::operator=(from);
			return *this;
		}
		~instance() {}

		inline auto begin() const noexcept
		{
			return this->get_ptr()->begin();
		}
		inline auto end() const noexcept
		{
			return this->get_ptr()->end();
		}
		inline auto rbegin() const noexcept
		{
			return this->get_ptr()->rbegin();
		}
		inline auto rend() const noexcept
		{
			return this->get_ptr()->rend();
		}
		inline auto cbegin() const noexcept
		{
			return this->get_ptr()->cbegin();
		}
		inline auto cend() const noexcept
		{
			return this->get_ptr()->cend();
		}

		second_layer& row(size_t index) const
		{
			return (*this->get_ptr())[index];
		}
		size_t row_count() const
		{
			return this->get_ptr()->size();
		}
		inside_layer& cell(size_t row_index, size_t col_index) const
		{
			return this->row(row_index)[col_index];
		}

		template<typename _ReTy>
		auto get_cell_value(size_t row_index, size_t col_index) const
		{
			inside_layer& str = cell(row_index, col_index);

			if constexpr (std::is_floating_point_v<_ReTy>)
				return std::atof(str.c_str());
			else if constexpr (std::is_integral_v<_ReTy>)
				return std::atoi(str.c_str());
			else if constexpr (std::is_same_v<const char*, _ReTy>)
				return str.c_str();
			else if constexpr (std::is_same_v<inside_layer, _ReTy>)
				return str;
			else
			{
				static_assert(std::is_same_v<decltype(std::declval<instance>().get_cell_value(0, 0)), void > == false, "not support for this type");
				return;
			}
		}

		void set_cell_value(size_t row_index, size_t col_index, const inside_layer& str)
		{
			this->row(row_index)[col_index] = str;
		}

		template<typename _Index>
		first_layer sub_ignore_pr(const std::vector<_Index>& ignore_rows, const std::vector<_Index>& ignore_cols)
		{
			auto& from = *this->get_ptr();
			first_layer result;
			for (size_t i = 0, row_ignore_count = 0, e = from.size(); i + row_ignore_count < e; i++)
			{
				if (std::find(ignore_rows.begin(), ignore_rows.end(), i) != ignore_rows.end())
				{
					row_ignore_count++;
					continue;
				}
				result.push_back(second_layer());
				for (size_t j = 0, col_ignore_count = 0, ej = from[i].size(); j < ej; j++)
				{
					if (std::find(ignore_cols.begin(), ignore_cols.end(), j) != ignore_cols.end())
					{
						continue;
					}
					result[i - row_ignore_count].push_back(from[i][j]);
				}
			}
			return result;
		}

		template<typename _Index>
		first_layer sub_pr(const std::vector<_Index>& choose_rows, const std::vector<_Index>& choose_cols)
		{
			auto& from = *this->get_ptr();
			first_layer result;
			for (size_t i = 0, row_count = 0, e = from.size(); row_count < e; row_count++)
			{
				if (std::find(choose_rows.begin(), choose_rows.end(), row_count) == choose_rows.end())continue;
				result.push_back(second_layer());
				for (size_t j = 0, col_count = 0, ej = from[i].size(); col_count < ej; col_count++)
				{
					if (std::find(choose_cols.begin(), choose_cols.end(), col_count) == choose_cols.end())continue;
					result[i].push_back(from[row_count][col_count]);
					j++;
				}
				i++;
			}
			return result;
		}

		void save(const string_indicator::tag& path)
		{
			//open file, out|binary
			std::ofstream out_file(path, std::ios::out | std::ios::binary);
			save(out_file);
			out_file.close();
		}
		void save(std::ofstream& out_file)
		{
			for (auto& i : *this->get_ptr())
			{
				bool isfirst = true;
				for (auto& j : i)
				{
					if (isfirst)
						out_file << j;
					else
						out_file << (_CharTy)splitChar << j;
					isfirst = false;
				}
				out_file << (_CharTy)splitLineChar;
			}

			out_file.flush();
		}

	private:

	};

	using csv_instance = instance<type_list<io_tag_indicator, long_tag_indicator<char, ','>, long_tag_indicator<char, '\n'>>>;
	using csv_w_instance = instance<type_list<io_tag_indicator, long_tag_indicator<wchar_t, ','>, long_tag_indicator<wchar_t, '\n'>>>;

	//config/setting reader and setup global
	template<>
	_LF_C_API(TClass) instance<type_list<io_tag_indicator, config_indicator, char>>
		Symbol_Push _LF_Inherited(instance<config_map>) Symbol_Endl
	{
	public:
		instance() :instance<config_map>(new config_map()) {}
		instance(int argc, char** argv):instance()
		{
			read_config(argc, argv);
		}
		instance(instance&& from) noexcept :instance<config_map>(std::move(from)) {}
		instance& operator=(instance&& from) noexcept
		{
			instance<config_map>::operator=(std::move(from));
			return *this;
		}
		instance(instance& from) noexcept :instance<config_map>(from) {}
		instance& operator=(instance& from) noexcept
		{
			instance<config_map>::operator=(from);
			return *this;
		}
		virtual ~instance() {}

		void read_config(int argc, char** argv)
		{
			config_map& config = *this->get_ptr();
			for (int i = 0; i < argc; i++)
			{
				std::string str(argv[argc]);
				size_t spl = str.find_first_of('=');
				if (spl != std::string::npos)
					config[str.substr(0, spl)] = str.substr(spl + 1, str.size() - spl - 1);
				else
					config[str] = "";
			}
		}
		template<typename _IOS>
		void read_config(_IOS& ost, std::function<std::pair<std::string, std::string>(const std::string&)> format)
		{
			while (ost.eof() == false)
			{
				char str_line[255];
				ost.getline(str_line, 255);
				this->get_ptr()->insert(format(str_line));
			}
		}
		template<typename _IOS>
		void write_config(_IOS& ost, std::function<std::string(const std::string&, const std::string&)> format) const
		{
			if (this->get_ptr()->size() == 0)
			{
				ost << format("__contains", "empty") << "\n";
				return;
			}
			for (auto& i : *this->get_ptr())
			{
				ost << format(i.first, i.second) << "\n";
			}
		}

		bool contains(const std::string& key) const
		{
			return (*this->get_ptr()).count(key) > 0;
		}
		std::string& get_value(const std::string& key) const
		{
			return (*this->get_ptr())[key];
		}
	};
	using config_instance = instance<type_list<io_tag_indicator, config_indicator, char>>;

#if defined(_WINDOWS_)
	template<>
	_LF_C_API(Class) instance<type_list<io_tag_indicator, bitmap_indicator>>
		Symbol_Push _LF_Inherited(instance<BITMAP_FILE>) Symbol_Endl
	{
	public:
		using Bitmap = BITMAP_FILE;
		using IndexCount = DWORD;
		using IndexCountN = WORD;
	private:
		void CreateBitMap(
			_In_ Bitmap * output,
			IndexCount bitCount,
			const int& height,
			const int& width,
			_In_opt_ Bitmap::PaletteBuffer palette,
			size_t paletteSize,
			IndexCount ClrUsed,
			IndexCount ClrImportant)
		{
			const IndexCount size = height * width * 3;
			//Header
			output->BitmapHeader.bfType = 0x4D42;
			output->BitmapHeader.bfReserved1 = 0;
			output->BitmapHeader.bfReserved2 = 0;
			auto headerAndInfo = static_cast<IndexCount>(sizeof(Bitmap::Header) + sizeof(Bitmap::ColorBuffer) + paletteSize);
			output->BitmapHeader.bfSize = headerAndInfo + size;
			output->BitmapHeader.bfOffBits = headerAndInfo;
			//Info Header
			output->BitmapInfoHeader = { 0 };
			output->BitmapInfoHeader.biSize = sizeof(Bitmap::Info);
			output->BitmapInfoHeader.biHeight = height;
			output->BitmapInfoHeader.biWidth = width;
			output->BitmapInfoHeader.biPlanes = 1;
			output->BitmapInfoHeader.biBitCount = (IndexCountN)bitCount;
			output->BitmapInfoHeader.biSizeImage = size;
			output->BitmapInfoHeader.biCompression = BI_RGB;
			output->BitmapInfoHeader.biClrUsed = ClrUsed;
			output->BitmapInfoHeader.biClrImportant = ClrImportant;
			//Palette
			output->BitMapPalette = palette;
			output->PaletteSize = paletteSize;
			//Map
			Bitmap::ColorBuffer bits = (Bitmap::ColorBuffer)(malloc(size));
			memset(bits, 0xFF, size);
			output->BitMapBuffer = bits;
		}

		template<typename _Ty, typename _BTy>
		int GetIndex(_Ty& x, _Ty& y, _BTy& width) const
		{
			return (int)((int)x + (int)y * width) * 3;
		}
	public:
		instance(
			const int& height,
			const int& width,
			IndexCount bitCount = 24,
			_In_opt_ Bitmap::PaletteBuffer palette = nullptr,
			size_t paletteSize = 0,
			IndexCount ClrUsed = 0,
			IndexCount ClrImportant = 0) :instance<Bitmap>(new Bitmap())
		{
			CreateBitMap(this->get_ptr(), bitCount, height, width, palette, paletteSize, ClrUsed, ClrImportant);
		}

		bool SaveBitMap(const char* path)
		{
			Bitmap* source = this->get_ptr();
			FILE* output;
			fopen_s(&output, path, "wb");

			if (output == NULL)
			{
				return false;
			}
			else
			{
				fwrite(&source->BitmapHeader, sizeof(Bitmap::Header), 1, output);
				fwrite(&source->BitmapInfoHeader, sizeof(Bitmap::Info), 1, output);
				fwrite(&source->BitMapPalette, sizeof(Bitmap::PaletteBuffer), source->PaletteSize, output);
				fwrite(source->BitMapBuffer, (size_t)source->BitmapInfoHeader.biSizeImage, 1, output);
				fclose(output);
				return true;
			}
		}

		bool SaveBitMap(const wchar_t* path)
		{
			Bitmap* source = this->get_ptr();
			FILE* output;
			_wfopen_s(&output, path, L"wb");

			if (output == NULL)
			{
				return false;
			}
			else
			{
				fwrite(&source->BitmapHeader, sizeof(Bitmap::Header), 1, output);
				fwrite(&source->BitmapInfoHeader, sizeof(Bitmap::Info), 1, output);
				fwrite(&source->BitMapPalette, sizeof(Bitmap::PaletteBuffer), source->PaletteSize, output);
				fwrite(source->BitMapBuffer, (size_t)source->BitmapInfoHeader.biSizeImage, 1, output);
				fclose(output);
				return true;
			}
		}

		enum class SetBitmapPixelType
		{
			overwrite = 0, multiply = 1, overlay = 2
		};

		enum class ColorSpaceStandardMultiplierType
		{
			floating = 1, integer = 256
		};

		ColorSpaceStandardMultiplierType ColorSpaceStandardMultiplier = ColorSpaceStandardMultiplierType::floating;

	private:
		BOOL SetBitmapPixel(
			Bitmap::ColorBuffer BitMapBuffer,
			const double& x,
			const double& y,
			const double& valueR,
			const double& valueG,
			const double& valueB,
			const SetBitmapPixelType& type)
		{
			const int& height = this->get_ptr()->BitmapInfoHeader.biHeight;
			const int& width = this->get_ptr()->BitmapInfoHeader.biWidth;
			const int index = GetIndex(x, y, width);
			if (index < height * width * 3)
			{
				switch (type)
				{
				case SetBitmapPixelType::overwrite:
				{
					BitMapBuffer[index + 0] = (Bitmap::Color)(valueB * (double)ColorSpaceStandardMultiplier);	// Blue
					BitMapBuffer[index + 1] = (Bitmap::Color)(valueG * (double)ColorSpaceStandardMultiplier);   // Green
					BitMapBuffer[index + 2] = (Bitmap::Color)(valueR * (double)ColorSpaceStandardMultiplier);   // Red
				}
				break;
				case SetBitmapPixelType::multiply:
				{
					BitMapBuffer[index + 0] *= (Bitmap::Color)(valueB * (double)ColorSpaceStandardMultiplier);	 // Blue
					BitMapBuffer[index + 1] *= (Bitmap::Color)(valueG * (double)ColorSpaceStandardMultiplier);   // Green
					BitMapBuffer[index + 2] *= (Bitmap::Color)(valueR * (double)ColorSpaceStandardMultiplier);   // Red
				}
				break;
				case SetBitmapPixelType::overlay:
				{
					BitMapBuffer[index + 0] += (Bitmap::Color)(valueB * (double)ColorSpaceStandardMultiplier);	 // Blue
					BitMapBuffer[index + 1] += (Bitmap::Color)(valueG * (double)ColorSpaceStandardMultiplier);   // Green
					BitMapBuffer[index + 2] += (Bitmap::Color)(valueR * (double)ColorSpaceStandardMultiplier);   // Red
				}
				break;
				}
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
	public:
		BOOL SetBitmapPixel(
			const double& x,
			const double& y,
			const double& valueR,
			const double& valueG,
			const double& valueB,
			const SetBitmapPixelType& type)
		{
			return SetBitmapPixel(this->get_ptr()->BitMapBuffer, x, y, valueR, valueG, valueB, type);
		}

		Bitmap::Color GetBitmapPixel(
			const double& x,
			const double& y,
			_Out_opt_ double* valueR = nullptr,
			_Out_opt_ double* valueG = nullptr,
			_Out_opt_ double* valueB = nullptr)const
		{
			const int& width = this->get_ptr()->BitmapInfoHeader.biWidth;
			Bitmap::ColorBuffer BitMapBuffer = this->get_ptr()->BitMapBuffer;
			const int index = GetIndex(x, y, width);
			if (valueB)
				*valueB = BitMapBuffer[index + 0];
			if (valueG)
				*valueG = BitMapBuffer[index + 1];
			if (valueR)
				*valueR = BitMapBuffer[index + 2];
		}

#define _RGBGET(i) &r[i], &g[i], &b[i]

		constexpr static double _GaussianBlurConvolutionKernel_Centre = 0.1478;
		constexpr static double _GaussianBlurConvolutionKernel_Core = 0.11831;
		constexpr static double _GaussianBlurConvolutionKernel_Marginal = 0.09474;

#define _i_GaussianBlurBlock(i,t,c) \
r[i]+=r[t]*c;g[i]+=g[t]*c;b[i]+=b[t]*c;

		void GaussianBlur(int distance, double Kernel_Centre, double Kernel_Marginal, double Kernel_Core)
		{
			Bitmap* target = this->get_ptr();
			const int height = target->BitmapInfoHeader.biHeight;
			const int width = target->BitmapInfoHeader.biWidth;
			const IndexCount size = height * width * 3;
			Bitmap::ColorBuffer bits = (Bitmap::ColorBuffer)malloc(size);
			memset(bits, 0xFF, size);

			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					const int index = GetIndex(x, y, width);
					for (size_t offset = 0; offset < 3; offset++)
					{
						double r[10], g[10], b[10];
						GetBitmapPixel(Clamp0E(x - distance, width - 1), Clamp0E(y - distance, height - 1), _RGBGET(0));
						GetBitmapPixel(Clamp0E(x - distance, width - 1), y, _RGBGET(1));
						GetBitmapPixel(Clamp0E(x - distance, width - 1), Clamp0E(y + distance, height - 1), _RGBGET(2));
						GetBitmapPixel(x, Clamp0E(y - distance, height - 1), _RGBGET(3));
						GetBitmapPixel(x, y, _RGBGET(4));
						GetBitmapPixel(x, Clamp0E(y + distance, height - 1), _RGBGET(5));
						GetBitmapPixel(Clamp0E(x + distance, width - 1), Clamp0E(y - distance, height - 1), _RGBGET(6));
						GetBitmapPixel(Clamp0E(x + distance, width - 1), y, _RGBGET(7));
						GetBitmapPixel(Clamp0E(x + distance, width - 1), Clamp0E(y + distance, height - 1), _RGBGET(8));
						r[9] = g[9] = b[9] = 0;
						_i_GaussianBlurBlock(9, 4, Kernel_Centre);
						_i_GaussianBlurBlock(9, 0, Kernel_Marginal);
						_i_GaussianBlurBlock(9, 2, Kernel_Marginal);
						_i_GaussianBlurBlock(9, 6, Kernel_Marginal);
						_i_GaussianBlurBlock(9, 8, Kernel_Marginal);
						_i_GaussianBlurBlock(9, 0 + 1, Kernel_Core);
						_i_GaussianBlurBlock(9, 2 + 1, Kernel_Core);
						_i_GaussianBlurBlock(9, 6 + 1, Kernel_Core);
						_i_GaussianBlurBlock(9, 4 + 1, Kernel_Core);
						SetBitmapPixel(bits, x, y,
							r[9] / (int)ColorSpaceStandardMultiplier,
							g[9] / (int)ColorSpaceStandardMultiplier,
							b[9] / (int)ColorSpaceStandardMultiplier, SetBitmapPixelType::overwrite);
					}
				}
			}

			delete target->BitMapBuffer;
			target->BitMapBuffer = bits;
		}

		void GaussianBlur(int distance)
		{
			GaussianBlur(distance, _GaussianBlurConvolutionKernel_Centre, _GaussianBlurConvolutionKernel_Marginal, _GaussianBlurConvolutionKernel_Core);
		}

		BOOL DrawBitmapLine(
			const double& x1,
			const double& y1,
			const double& x2,
			const double& y2,
			const double& width,
			const double& valueR,
			const double& valueG,
			const double& valueB,
			const SetBitmapPixelType& type)
		{
			double normal_x = y2 - y1, normal_y = x1 - x2, direction_x = x2 - x1, direction_y = y2 - y1;
			double normal_len = pow(normal_x * normal_x + normal_y * normal_y, 0.5);
			normal_x /= normal_len;
			normal_y /= normal_len;
			direction_x /= normal_len;
			direction_y /= normal_len;

			for (size_t i = 0, e = static_cast<size_t>(normal_len); i < e; i++)
			{
				for (int j = 0, e2 = static_cast<int>(width); j < e2; j++)
				{
					int x = static_cast<int>(x1 + i * direction_x + j * normal_x);
					int y = static_cast<int>(y1 + i * direction_y + j * normal_y);
					if (!SetBitmapPixel(x, y, valueR, valueG, valueB, type))
					{
						return FALSE;
					}
					SetBitmapPixel(x + (direction_x > direction_y ? 0 : 1), y + (direction_y > direction_x ? 0 : 1), valueR, valueG, valueB, type);
				}
			}

			return TRUE;
		}

		BOOL DrawBitmapTriangle(
			const double& x,
			const double& y,
			const double& x2,
			const double& y2,
			const double& x3,
			const double& y3,
			const double& width,
			const double& valueR,
			const double& valueG,
			const double& valueB,
			const SetBitmapPixelType& type)
		{
			BOOL a = DrawBitmapLine(x, y, x2, y2, width, valueR, valueG, valueB, type);
			BOOL b = DrawBitmapLine(x2, y2, x3, y3, width, valueR, valueG, valueB, type);
			BOOL c = DrawBitmapLine(x3, y3, x, y, width, valueR, valueG, valueB, type);
			return (a == TRUE && b == TRUE && c == TRUE) ? TRUE : FALSE;
		}
	};
#endif
	using bitmap_instance = instance<type_list<io_tag_indicator, bitmap_indicator>>;
}

#pragma region is_ld_instance

template<typename T>
_LF_C_API(TStruct) is_ld_instance
{
	using tag = T;
	constexpr static bool value = false;
};
template<typename T>
_LF_C_API(TStruct) is_ld_instance<ld::instance<T>>
{
	using tag = T;
	constexpr static bool value = true;
};
template<typename T>
_LF_C_API(TStruct) is_ld_instance<ld::instance<T>&>
{
	using tag = T;
	constexpr static bool value = true;
};
template<typename T>
_LF_C_API(TStruct) is_ld_instance<ld::instance<T>&&>
{
	using tag = T;
	constexpr static bool value = true;
};
template<typename T>
_LF_C_API(TStruct) is_ld_instance<const ld::instance<T>&&>
{
	using tag = T;
	constexpr static bool value = true;
};
template<typename T> constexpr bool is_ld_instance_v = is_ld_instance<T>::value;

#pragma endregion

#pragma region remove_instance

template<typename T>
_LF_C_API(TStruct) remove_instance
{
	using tag = T;
};
template<typename T>
_LF_C_API(TStruct) remove_instance<ld::instance<T>>
{
	using tag = T;
};
template<typename T> using remove_instance_v = typename remove_instance<T>::tag;

#pragma endregion

#endif // !__FILE_LF_RAII
