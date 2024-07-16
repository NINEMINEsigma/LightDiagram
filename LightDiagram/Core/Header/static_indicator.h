#ifndef __FILE_STATIC_INDICATOR

#define __FILE_STATIC_INDICATOR

#include<Core/Header/static_exist.h>

#pragma region Typen (Define)

#define _LFramework_Indicator_Def(name,_tag,_value)													\
_LF_C_API(OStruct) name##_indicator																	\
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
_LFramework_Indicator_Def(const, void, true);
_LFramework_Indicator_Def(unconst, void, false);
_LFramework_Indicator_Def(template_fill, void, false);
_LFramework_Indicator_Def(key, void, true);
_LFramework_Indicator_Def(string, std::string, true);
_LFramework_Indicator_Def(class, void, true);
_LFramework_Indicator_Def(struct, void, true);

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
template<typename T>
constexpr bool is_type_indicator(typename T::type_indicator*) { return true; }
template<typename T>
constexpr bool is_type_indicator(...) { return false; }
template<typename T>
constexpr bool is_type_list_end() { return !std::is_same_v<typename T::type_indicator, bad_indicator>; }
template<typename T>
constexpr bool is_indicator_typen(typename T::tag* t, bool v) { return true; }
template<typename T>
constexpr bool is_indicator_typen(...) { return false; }

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
	if constexpr (std::is_same_v<type_list_type, type_list<void>>)
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

#endif // !__FILE_STATIC_INDICATOR
