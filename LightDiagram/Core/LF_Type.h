#ifndef __FILE_LF_TYPE

#define __FILE_LF_TYPE

#include<Core/static_indicator.h>

#pragma region LDType

if_property_exist_def(value);
if_type_exist_def(tag);
if_type_exist_def(integral_indicator);
if_type_exist_def(floating_point_indicator);
if_type_exist_def(unsigned_indicator);
if_type_exist_def(type_indicator)

#define _LFramework_IsType(name,T)\
std::is_##name##_v<T> || if_type_exist( name##_indicator ) < T >

template<typename T>	_LF_C_API(OStruct)	LDType;
template<typename T>	_LF_C_API(OStruct)	LDType_Number;
template<typename T>	_LF_C_API(OStruct)	LDType_Indicator;
template<typename T>	_LF_C_API(OStruct)	LDType_Traits;

template<typename T>
_LF_C_API(OStruct) LDType
{
	//	number type state
	using tag_num = LDType_Number<T>;
	//	indicator type state
	using tag_idc = LDType_Indicator<T>;
	//	traits type state
	using tag_tra = LDType_Traits<T>;

	//	is class or struct
	constexpr static bool is_class = std::is_class_v<T>;
	//	is abstract
	constexpr static bool is_abstract = std::is_abstract_v<T>;
	//	is union
	constexpr static bool is_union = std::is_union_v<T>;

	using tag = T;
	constexpr static bool value = true;
	using type_indicator = key_indicator;
};

template<typename T>
_LF_C_API(OStruct)  LDType_Number
{
	//	is integral number
	constexpr static bool is_int = _LF_(IsType)(integral, T);
	//	is floating point number
	constexpr static bool is_flp = _LF_(IsType)(floating_point, T);
	//	is un-signed
	constexpr static bool is_uns = _LF_(IsType)(unsigned, T);
	//	is likely number
	constexpr static bool is_ind = if_type_exist(integral_indicator) < T > || if_type_exist(floating_point_indicator) < T > ;
	//	is number
	constexpr static bool is_num = is_int || is_flp;

	using tag = T;
	constexpr static bool value = is_num;
	using type_indicator = key_indicator;
};

template<typename T>
_LF_C_API(OStruct) LDType_Indicator
{
	//	is indicator type
	constexpr static bool is_idc = if_type_exist(tag) < T > && if_property_exist(value) < T, bool > ;
	//	is key indicator
	constexpr static bool is_key = std::is_same_v<T, key_indicator>;
	//	is type indicator
	constexpr static bool is_tid = if_type_exist(type_indicator) < T > ;
	//	is pseudo indicator(contain indicator element)
	constexpr static bool is_pse = if_type_exist(tag) < T > != if_property_exist(value) < T, bool > ;

	using tag = T;
	constexpr static bool value = true;
	using type_indicator = key_indicator;
};

#pragma endregion

#endif // !__LF_TYPE


