#ifndef __FILE_STATIC_INDICATOR

#define __FILE_STATIC_INDICATOR

#include<Core/static_exist.h>

namespace std
{

}

#pragma region Typen (Define)

#define _LFramework_Indicator_Def(name,_tag,_value)													\
_LF_C_API(OStruct) name##_indicator	: public std::_value##_type										\
{																									\
	using tag = _tag;																				\
	constexpr static bool value = _value;															\
};																									\
template< typename indicator>																		\
constexpr bool is_##name##_indicator_v = std::is_same_v<indicator, name##_indicator>

struct bad_indicator 
{
	operator void* () const noexcept
	{
		return nullptr;
	}
	using tag = void; 
	constexpr static bool value = false;
}; 
template< typename indicator> constexpr bool is_bad_indicator_v = std::is_same_v<indicator, bad_indicator>;
_LFramework_Indicator_Def(empty, void, false);
_LFramework_Indicator_Def(void, void, false);
_LFramework_Indicator_Def(unknown, void, false);
_LFramework_Indicator_Def(_cdecl, void, true);
_LFramework_Indicator_Def(_stdcall, void, false);
_LFramework_Indicator_Def(_fastcall, void, false);
_LFramework_Indicator_Def(__thiscall, void, false);
_LFramework_Indicator_Def(global, void, false);
_LFramework_Indicator_Def(namespace, void, false);
_LFramework_Indicator_Def(new, void, false);
_LFramework_Indicator_Def(const, void, true);
_LFramework_Indicator_Def(unconst, void, false);
_LFramework_Indicator_Def(noexcept, void, true);
_LFramework_Indicator_Def(except, void, false);
_LFramework_Indicator_Def(template_fill, void, false);
_LFramework_Indicator_Def(key, void, true);
_LFramework_Indicator_Def(string, std::string, true);
_LFramework_Indicator_Def(wstring, std::wstring, true);
_LFramework_Indicator_Def(class, void, true);
_LFramework_Indicator_Def(struct, void, true);
_LFramework_Indicator_Def(io_tag, void, true);
_LFramework_Indicator_Def(weak, void, true);
_LFramework_Indicator_Def(true, void, true);
_LFramework_Indicator_Def(false, void, false);
_LFramework_Indicator_Def(container, void, true);
_LFramework_Indicator_Def(config, void, true);
_LFramework_Indicator_Def(bitmap, void, true);
_LFramework_Indicator_Def(file, void, true);
_LFramework_Indicator_Def(disable_template, void, false);
_LFramework_Indicator_Def(enable_template, void, true);

#define __Global_Space

_LF_C_API(OStruct) LDType_Bad_Indicator
{
	using tag = bad_indicator;
	constexpr static bool value = false;
	using type_indicator = key_indicator;
};

#pragma endregion

#pragma region type_indicator

template<typename ...Args> struct type_list;
template<typename T> constexpr bool is_type_indicator(typename T::type_indicator*);
template<typename T> constexpr bool is_type_indicator(...);
template<typename T> constexpr bool is_type_list_end();
template<typename T> constexpr bool is_indicator_typen(typename T::tag* t, bool v = T::value);
template<typename T> constexpr bool is_indicator_typen(...);
template<typename L, int pos>  _LF_C_API(OStruct)  type_decltype;

template<int index>
_LF_C_API(OStruct) is_type_list_contains_detect
{
	constexpr static bool value = true;
};
template<>
_LF_C_API(OStruct) is_type_list_contains_detect<-1>
{
	constexpr static bool value = false;
};

template<>
_LF_C_API(OStruct) type_list<void>
{
	using tag = bad_indicator;
	constexpr static bool value = false;
	using type_indicator = tag;
	template<typename T>
	constexpr static int is_type_list_contains(size_t pos)
	{
		return -1;
	};

	template<typename Default, typename T>
	using decltype_type = Default;
};
template<typename Last>
_LF_C_API(OStruct) type_list<Last>
{
	using tag = Last;
	constexpr static bool value = true;
	using type_indicator = type_list<void>;
	template<typename T>
	constexpr static int is_type_list_contains(size_t pos)
	{
		if constexpr (std::is_same_v<Last, T>)
			return pos;
		else
			return type_indicator::template is_type_list_contains<T>(pos + 1);
	};

	template<typename Default, typename T>
	using decltype_type = typename choose_type<!is_type_list_contains_detect<type_list::is_type_list_contains<T>(0)>::value, Default, T>::tag;
};
template<typename First, typename ...Args>
_LF_C_API(OStruct) type_list<First, Args...>
{
	using tag = First;
	constexpr static bool value = true;
	using type_indicator = type_list<Args...>;
	template<typename T>
	constexpr static int is_type_list_contains(size_t pos)
	{
		if constexpr (std::is_same_v<First, T>)
			return pos;
		else
			return type_indicator::template is_type_list_contains<T>(pos + 1);
	};

	template<typename Default, typename T>
	using decltype_type = typename choose_type<!is_type_list_contains_detect<is_type_list_contains<T>(0)>::value, Default, T>::tag;
};

template<typename L>
_LF_C_API(OStruct) type_decltype<L, -2>
{
	using tag = bad_indicator;
	constexpr static bool value = false;
};
template<typename L>
_LF_C_API(OStruct) type_decltype<L, -1>
{
	using tag = bad_indicator;
	constexpr static bool value = false;
};
template<typename L>
_LF_C_API(OStruct) type_decltype<L, 0>
{
	using tag = typename L::tag;
	constexpr static bool value = true;
};
template<typename L, int pos>
_LF_C_API(OStruct) type_decltype
{
	using tag = typename type_decltype<typename L::type_indicator, pos - 1>::tag;
	constexpr static bool value = true;
};

template<typename type_list_type, bool _IsF = true> const string_indicator::tag& get_type_list_string()
{
	if constexpr (type_list_type::value == false)
	{
		static string_indicator::tag bad("bad_type_list");
		return bad;
	}
	else if constexpr (std::is_same_v<type_list_type, type_list<void>>)
	{
		static string_indicator::tag empty("");
		return empty;
	}
	else
	{
		if constexpr (_IsF)
		{
			static string_indicator::tag str(string_indicator::tag(typeid(typename type_list_type::tag).name()) + get_type_list_string<typename type_list_type::type_indicator, false>());
			return str;
		}
		else
		{
			static string_indicator::tag str(string_indicator::tag(",") + typeid(typename type_list_type::tag).name() + get_type_list_string<typename type_list_type::type_indicator, false>());
			return str;
		}
	}
}

#pragma endregion

#pragma region x_tag_indicator

template<typename NextType, size_t UID> _LF_C_API(TStruct) long_tag_indicator;

template<typename NextType, size_t UID>
_LF_C_API(TStruct) long_tag_indicator
{
	using tag = NextType;
	constexpr static size_t value = UID;
};

#pragma endregion

#pragma region muti_argpackage_indicator

template<typename T> _LF_C_API(TClass) multi_argpackage_indicator
{
public:
	using tag = T;
	constexpr static bool value = true;
	using list = multi_argpackage_indicator<T>;
	template<int index> using find_type = typename choose_type<index == 0, tag, bad_indicator>::tag;
};
template<typename... Args> _LF_C_API(TClass) multi_argpackage_indicator<type_list<Args...>>
{
public:
	using tag = type_list<Args...>;
	constexpr static bool value = true;
	using list = type_list<Args...>;
	template<int index> using find_type = multi_argpackage_indicator<typename type_decltype<list, index>::tag>;
};

#pragma endregion

#pragma region class_component_indicatior

template<typename... Args> _LF_C_API(TClass) class_component_indicatior;
template<typename _Last> _LF_C_API(TClass) class_component_indicatior<_Last> Symbol_Endl
{
public:
	using tag = _Last;
	constexpr static bool value = false;
	constexpr static size_t length = 1;
private:
	tag current_value;
public:
	template<size_t index> const tag& get_value() const
	{
		static_assert(index == 0, "over range");
		return this->current_value;
	}
	template<size_t index,typename _T> void set_value(_T&& from)
	{
		static_assert(index == 0, "over range");
		this->current_value = std::forward<_T>(from);
	}
	class_component_indicatior()
	{
		if constexpr (std::is_pointer_v<tag>)
		{
			current_value = nullptr;
		}
		else if constexpr (std::is_arithmetic_v<tag>)
		{
			current_value = 0;
		}
		else
		{
			current_value = nullptr;
		}
	}
	template<typename LvTag>
	class_component_indicatior(LvTag&& first) :current_value(first) {}
};
template<typename _First, typename... Args> _LF_C_API(TClass) class_component_indicatior<_First,Args...> Symbol_Endl
{
public:
	using tag = _First;
	constexpr static bool value = true;
	constexpr static size_t length = sizeof...(Args);
private:
	tag current_value;
	class_component_indicatior<Args...> next_container;
public:
	template<size_t index> decltype(auto) get_value()
	{
		if constexpr (index == 0)
		{
			return this->current_value;
		}
		else
		{
			return next_container. template get_value<index - 1>();
		}
	}
	template<size_t index> decltype(auto) get_c_value() const
	{
		if constexpr (index == 0)
		{
			return this->current_value;
		}
		else
		{
			return next_container. template get_c_value<index - 1>();
		}
	}
	template<size_t index, typename _T> void set_value(_T && from)
	{
		if constexpr (index == 0)
		{
			this->current_value = std::forward<_T>(from);
		}
		else
		{
			next_container. template set_value<index - 1>(std::forward<_T>(from));
		}
	}
	template<size_t index, typename _T> void set_value(const _T& from)
	{
		if constexpr (index == 0)
		{
			this->current_value = from;
		}
		else
		{
			next_container. template set_value<index - 1>(from);
		}
	}
	class_component_indicatior()
	{
		if constexpr (std::is_pointer_v<tag>)
		{
			current_value = nullptr;
		}
		else if constexpr (std::is_arithmetic_v<tag>)
		{
			current_value = tag{};
		}
	}
	template<typename LvTag,typename... LvArgs>
	class_component_indicatior(LvTag&& first, LvArgs&&... args) 
		:current_value(std::forward<LvTag>(first)), next_container(std::forward<LvArgs>(args)...) {}
	operator tag& ()
	{
		return current_value;
	}
	operator const tag& () const
	{
		return current_value;
	}
	constexpr tag* operator->()
	{
		return &current_value;
	}
};

#pragma endregion


#endif // !__FILE_STATIC_INDICATOR
