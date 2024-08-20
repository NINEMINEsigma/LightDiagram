#ifndef __FILE_STATIC_EXIST

#define __FILE_STATIC_EXIST

#include<Core/LF_Config.h>

#pragma region Exist (Static)

#define _LFKE_API(var,name)		_LFK_API( Exist_##var )(name)
#define _LFKE_DEF(var,name)		_LFK_DEF( Exist_##var )(name)
#define _LFKWE_API(var,name)	_LFK_API( WeakExist_##var )(name)
#define _LFKWE_DEF(var,name)	_LFK_DEF( WeakExist_##var )(name)

#pragma region Class::Type

#define _LFramework_Kit_API_Exist_Type_Define(name)														\
template< typename , typename = void>																	\
_LF_C_API(OStruct) __exist_type_##name									: std::false_type	{ };		\
template< typename T >																					\
_LF_C_API(OStruct) __exist_type_##name <T,std::void_t<typename T::name>>	: std::true_type	{ };	\
template< typename T > _LF_C_API(TDLL) constexpr bool __exist_type_##name##_v = __exist_type_##name<T>();
#define _LFramework_Kit_API_Exist_Type(name) __exist_type_##name##_v
#define if_type_exist_def(name)	_LFKE_DEF(Type,name)
#define if_type_exist(name)		_LFKE_API(Type,name)
// if_type_exist(name)<type>

#pragma endregion

#pragma region Class::Func

#define _LFramework_Kit_API_Exist_Func_Define(name)																			\
template< typename, typename, typename = void > _LF_C_API(OStruct) __exist_function_##name : std::false_type { };			\
template< typename T, typename Ret, typename... Args>																		\
_LF_C_API(OStruct) __exist_function_##name<																					\
	T,																														\
	Ret(Args...),																											\
	typename std::enable_if<std::is_same_v<decltype(std::declval<T>().##name##(std::declval<Args>()...)), Ret>>::type>		\
	: std::true_type { };																									\
template< typename T, typename Ret > _LF_C_API(TDLL) constexpr bool __exist_function_##name##_v = __exist_function_##name<T,Ret>();
#define _LFramework_Kit_API_Exist_Func(name)	__exist_function_##name##_v
#define if_func_exist_def(name)	_LFKE_DEF(Func,name)
#define if_func_exist(name)		_LFKE_API(Func,name)
// if_func_exist(name)<type,result(...Args)>



#pragma endregion

#pragma region Class::Field

#define _LFramework_Kit_API_Exist_Field_Define(name)																		\
template< typename, typename, typename = void > _LF_C_API(OStruct) __exist_field_##name : std::false_type { };				\
template< typename T, typename MType> _LF_C_API(OStruct) __exist_field_##name<												\
	T,																														\
	MType,																													\
	typename std::enable_if<std::is_same_v<decltype(std::declval<T>().##name), MType>>::type>								\
	: std::true_type { };																									\
template< typename T, typename MType> _LF_C_API(TDLL) constexpr bool __exist_field_##name##_v = __exist_field_##name<T, MType>();
#define _LFramework_Kit_API_Exist_Field(name)	__exist_field_##name##_v
#define if_field_exist_def(name)	_LFKE_DEF(Field,name)
#define if_field_exist(name)		_LFKE_API(Field,name)

#pragma endregion

#pragma region Class::Property

#define _LFramework_Kit_API_Exist_Property_Define(name)																		\
template< typename, typename, typename = void > _LF_C_API(OStruct) __exist_property_##name : std::false_type { };			\
template< typename T, typename MType> _LF_C_API(OStruct) __exist_property_##name<											\
	T,																														\
	MType,																													\
	typename std::enable_if<std::is_same_v<decltype(T:: name ), MType>>::type>												\
	: std::true_type { };																									\
template< typename T, typename MType> _LF_C_API(TDLL) constexpr bool __exist_property_##name##_v = __exist_property_##name<T, MType>();
#define _LFramework_Kit_API_Exist_Property(name)	__exist_property_##name##_v
#define if_property_exist_def(name)	_LFKE_DEF(Property,name)
#define if_property_exist(name)		_LFKE_API(Property,name)

#pragma endregion

#pragma endregion


if_type_exist_def(pointer_indicator);
if_type_exist_def(owner_indicator);
if_type_exist_def(counter_indicator);
if_type_exist_def(counter_num_indicator);

if_func_exist_def(size);


#endif // !__FILE_STATIC_EXIST
