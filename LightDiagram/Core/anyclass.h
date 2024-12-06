#ifndef __FILE_ANY_CLASS
#define __FILE_ANY_CLASS

#include "LF_Config.h"

#pragma pack(push, 8)

#pragma region is_base_of_template

// case1: T* can cast to C*
template <template <typename...> class C, typename...Ts>
std::true_type is_base_of_template_impl(const C<Ts...>*);
// case2: T* cannot cast to C*
template <template <typename...> class C>
std::false_type is_base_of_template_impl(...);

template <template <typename...> class C, typename T>
using is_base_of_template = decltype(is_base_of_template_impl<C>(std::declval<T*>()));

#pragma endregion

#pragma region decay and evolve

#pragma region remove_full_ptr

template<typename T>
_LF_C_API(TStruct) remove_full_ptr
{
	using tag = T;
};
template<typename T>
_LF_C_API(TStruct) remove_full_ptr<T*>
{
	using tag = typename remove_full_ptr<T>::tag;
};

#pragma endregion

#pragma region count_full_ptr

template<typename T, size_t counter = 0>
_LF_C_API(TStruct) _count_full_ptr
{
	constexpr static size_t value = counter;
};
template<typename T, size_t counter>
_LF_C_API(TStruct) _count_full_ptr<T*, counter>
{
	constexpr static size_t value = _count_full_ptr<T, counter + 1>::value;
};
template<typename T>
_LF_C_API(TStruct) count_full_ptr
{
	constexpr static size_t value = _count_full_ptr<T, 0>::value;
};
template<typename T> constexpr size_t count_full_ptr_v = count_full_ptr<T>::value;

#pragma endregion

#pragma region remove_atomic

template<typename T>
_LF_C_API(TStruct) remove_atomic
{
	using tag = T;
};
template<typename T>
_LF_C_API(TStruct) remove_atomic<std::atomic<T>>
{
	using tag = T;
};

#pragma endregion

#pragma region remove_array

template<typename T>
_LF_C_API(TStruct) remove_array
{
	using tag = T;
};
template<typename T, size_t size>
_LF_C_API(TStruct) remove_array<std::array<T, size>>
{
	using tag = T;
};
template<typename T>
_LF_C_API(TStruct) remove_array<T[]>
{
	using tag = T;
};

#pragma endregion

template<typename T>
_LF_C_API(TStruct)	generate_full_decay_typen
{
	//	template arg[T]
	using tag = T;
	//	remove const
	using unconst = typename std::remove_const<tag>::type;
	//	remove reference
	using unrefer = typename std::remove_reference<tag>::type;
	//	remove pointer
	using unptrto = typename remove_full_ptr<tag>::tag;
	//	remove volatile
	using unvolat = typename std::remove_volatile<tag>::type;
	//	remove array
	using unarray = typename remove_array<tag>::tag;
	//	remove atomic
	using unatcto = T;

	using origin =
		typename remove_array<
		typename remove_full_ptr<
		typename std::decay<
		typename remove_atomic<tag>
		::tag>::type>::tag>::tag;
};

#pragma endregion

#pragma region void_ptr_t

_LF_C_API(Struct) void_ptr_t
{
	template<typename T> operator T& ()
	{
		return *static_cast<T*>(ptr);
	}

	void* ptr;
};

#pragma endregion

class any_class;
template<typename T> class null_package;
_LF_C_API(TDLL) 
template<typename T> null_package<T> make_null_package(any_class* ptr);

_LF_C_API(OClass)
type_class
{
public:
	virtual const type_info& GetType() const abstract;
	virtual std::string ToString() const abstract;
	virtual std::string SymbolName() const abstract;
};
_LF_C_API(OClass)
any_class : public type_class
{
public:
	inline decltype(auto) GetAnyAdr()
	{
		return static_cast<void*>(this);
	}
#if (is_monitor_the_constructor_of_anyclass)
#ifndef is_monitor_the_constructor_of_instance
#define is_monitor_the_constructor_of_instance false
#endif // !is_monitor_the_constructor_of_instance
	bool __is_log = true;
	any_class(bool is_log) :__is_log(is_log)
	{
		if (is_log)
			std::cout << this->AsDynamicPtr<type_class>()->SymbolName() << "[" << static_cast<const void*>(this) << "] is in constructor\n";
	}
	any_class() :any_class(true) {}
	virtual ~any_class()
	{
		if (__is_log)
			std::cout << this->AsDynamicPtr<type_class>()->SymbolName() << "[" << static_cast<const void*>(this) << "] is in destructor\n";
	}
#else
#undef is_monitor_the_constructor_of_instance
#define is_monitor_the_constructor_of_instance
	virtual ~any_class() {}
#endif
#define instance_any_class any_class(is_monitor_the_constructor_of_instance)
	template<typename T> T& AsRef()
	{
		return *static_cast<T*>(this);
	}
	template<typename T> T AsValue()
	{
		return static_cast<T>(*this);
	}
	template<typename T> T* AsStaticPtr()
	{
		return static_cast<T*>(this);
	}
	template<typename T> T* AsDynamicPtr()
	{
		return dynamic_cast<T*>(this);
	}

	template<typename T> T& Fetch(T& from) const
	{
		return from;
	}
	template<typename T> T&& Fetch(T&& from) const
	{
		return from;
	}
	template<typename T> T* FetchPtr(T* from) const
	{
		return from;
	}
	template<typename T> any_class* StaticShare(_Inout_ T** object_ptr)
	{
		*object_ptr = static_cast<T*>(this);
		return this;
	}
	template<typename T> any_class* DynamicShare(_Inout_ T** object_ptr)
	{
		*object_ptr = dynamic_cast<T*>(this);
		return this;
	}

	virtual const type_info& GetType() const
	{
		return typeid(*this);
	}
	virtual std::string ToString() const
	{
		return GetType().name();
	}
	virtual std::string SymbolName() const
	{
		return GetType().name();
	}

	template<typename T, typename Ret, typename C> any_class* IfIam(Ret(C::* foo)(T*), C* user)
	{
		T* cat = dynamic_cast<T*>(this);
		if (cat)
		{
			((*user).*foo)(cat);
		}
		return this;
	}
	template<typename T, typename R> any_class* AsIam(R(foo)(T*))
	{
		T* cat = dynamic_cast<T*>(this);
		if (cat)
			foo(cat);
		return this;
	}
	template<typename T, typename R> any_class* AsIam(R foo)
	{
		T* cat = dynamic_cast<T*>(this);
		if (cat)
			foo(cat);
		return this;
	}

	template<typename T> null_package<T> As() const
	{
		return make_null_package<T>(this);
	}
	template<typename T> null_package<T> Is() const
	{
		return make_null_package<T>(this);
	}

	bool Is(const type_info& type) const
	{
		return this->GetType() == type;
	}
};

template<typename T>
_LF_C_API(TClass)	null_package final
{
	T* ptr = nullptr;
public:
	null_package(any_class* ptr) :ptr(dynamic_cast<T*>(ptr)) {}
	null_package(const null_package& lv) noexcept :ptr(lv.ptr) {}
	operator bool() const
	{
		return ptr != nullptr;
	}
	operator T* () const
	{
		return ptr;
	}
	template<typename Ret,typename... Args> 
	null_package<T>& Try(std::function<Ret(const T&)> func) const
	{
		if (this->ptr)
		{
			func(*ptr);
		}
		return *this;
	}
	template<typename Ret, typename... Args>
	null_package<T>& Try(std::function<Ret(T&&)> func) const
	{
		if (this->ptr)
		{
			func(std::move(*ptr));
			ptr = nullptr;
		}
		return *this;
	}
	template<typename Ret, typename... Args>
	null_package<T>& Try(std::function<Ret(T&)> func) const
	{
		if (this->ptr)
		{
			func(*ptr);
		}
		return *this;
	}
	template<typename MemberFunc, typename... Args>
	null_package<T>& Try(MemberFunc invoker,Args... args) const
	{
		if (this->ptr)
		{
			((*ptr).*invoker)(args...);
		}
		return *this;
	}
	null_package& operator=(const null_package& right)
	{
		this->ptr = right.ptr;
	}
	template<typename OtherT>
	bool operator==(const null_package<OtherT>& right) const
	{
		return this->ptr == right.ptr;
	}
	T* operator*() const
	{
		return ptr;
	}

	using tag = T;
	using decay = generate_full_decay_typen<T>;
};

template<typename T> _LF_C_API(TDLL) null_package<T> make_null_package(any_class* ptr)
{
	return { ptr };
}

template<typename Func,typename ArgsPackage>
_LF_C_API(TClass) closures final
{
public:
	std::function<Func> invoker;
	ArgsPackage args;
	closures(std::function<Func> func, ArgsPackage && args) :invoker(func), args(args) {}
	closures(closures&& right) :invoker(std::move(right.func)), args(std::move(right.args)) {}
	void operator()()
	{
		invoker(std::move(args));
	}
	void Invoke()
	{
		invoker(std::move(args));
	}
};
template<typename Func>
_LF_C_API(TClass) closures<Func, void> final Symbol_Endl
{
public:
	std::function<Func> invoker;
	closures(std::function<Func> func) :invoker(func) {}
	closures(closures&& right) :invoker(std::move(right.func)) {}
	void operator()()
	{
		invoker();
	}
	void Invoke()
	{
		invoker();
	}
};

template<typename Func, typename ArgsPackage>
_LF_C_API(TClass) release_closures final:protected std::shared_ptr<closures<Func, ArgsPackage>>
{
	bool is_invoke;
public:
	using tag = closures<Func,ArgsPackage>;
	release_closures(std::function<Func> func, ArgsPackage&& args) :is_invoke(false), std::shared_ptr<closures<Func, ArgsPackage>>(new closures<Func, ArgsPackage>(func, std::move(args))) {}
	release_closures(release_closures&& right) :is_invoke(right.is_invoke), std::shared_ptr<closures<Func, ArgsPackage>>(std::move(right)) { right.is_invoke = true; }
	~release_closures()
	{
		if (!is_invoke)
			this->Invoke();
	}
	void operator()()
	{
		(*this)->Invoke();
		is_invoke = true;
	}
	void Invoke()
	{
		(*this)->Invoke();
		is_invoke = true;
	}
};
template<typename Func>
_LF_C_API(TClass) release_closures<Func, void> final Symbol_Endl
{
	bool is_invoke;
public:
	using tag = closures<Func, void>;
	release_closures(std::function<Func> func) :is_invoke(false), std::shared_ptr<closures<Func, void>>(new closures<Func, void>(func)) {}
	release_closures(release_closures&& right) :is_invoke(right.is_invoke), std::shared_ptr<closures<Func, void>>(std::move(right)) { right.is_invoke = true; }
	~release_closures()
	{
		if (!is_invoke)
			this->Invoke();
	}
	void operator()()
	{
		(*this)->Invoke();
		is_invoke = true;
	}
	void Invoke()
	{
		(*this)->Invoke();
		is_invoke = true;
	}
};

#define	null_able	auto

_LF_C_API(Class) copy_enable Symbol_Push public any_class 
{
public:
	using tag = void;
	constexpr static bool value = true;
protected:
	copy_enable() {}
	copy_enable(const copy_enable&) {}
	~copy_enable() {}
	copy_enable& operator=(const copy_enable&)
	{
		return *this;
	}
};
_LF_C_API(Class) copy_disable Symbol_Push public any_class
{
public:
	using tag = void;
	constexpr static bool value = true;
protected:
	copy_disable() {}
	virtual ~copy_disable() {}
private:
	copy_disable(const copy_disable&) = delete;
	copy_disable& operator=(const copy_disable&) = delete;
};
using noncopyable = copy_disable;

using config_map = std::map<std::string, std::string>;

using vptr_t = intptr_t**;
template<typename _T>
vptr_t get_vptr(_T* from)
{
	return reinterpret_cast<vptr_t>(from);
}
template<typename _T>
void set_vptr(_T* from, vptr_t vptr)
{
	*reinterpret_cast<vptr_t>(from) = *vptr;
}

#pragma pack(pop)

#endif // !__FILE_ANY_CLASS

