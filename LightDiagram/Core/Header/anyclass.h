#ifndef __FILE_ANY_CLASS

#define __FILE_ANY_CLASS

#include<Core/Header/LF_Config.h>

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
_LF_C_API(Struct) remove_atomic
{
	using tag = T;
};
template<typename T>
_LF_C_API(Struct) remove_atomic<std::atomic<T>>
{
	using tag = T;
};

#pragma endregion

#pragma region remove_array

template<typename T>
_LF_C_API(Struct) remove_array
{
	using tag = T;
};
template<typename T, size_t size>
_LF_C_API(Struct) remove_array<std::array<T, size>>
{
	using tag = T;
};
template<typename T>
_LF_C_API(Struct) remove_array<T[]>
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

_LF_C_API(OClass)	any_class
{
public:
	virtual ~any_class() {}
	template<typename T> T& AsRef()
	{
		return *this;
	}
	template<typename T> T AsValue()
	{
		return *this;
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
	template<typename T> const T& Fetch(const T& from) const
	{
		return from;
	}
};

#endif // !__FILE_ANY_CLASS

