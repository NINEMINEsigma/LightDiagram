#pragma once

/*
    Copyright (c) 2024, liu bai, ninemine
    All rights reserved.
*/

#pragma region bits/stdc++

// C++ includes used for precompiling -*- C++ -*-

// Copyright (C) 2003-2014 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file stdc++.h
 *  This is an implementation file for a precompiled header.
 */

 // 17.4.1.2 Headers

 // C
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>

#include <stdlib.h>

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

using type_info = std::type_info;

#pragma endregion

#pragma region MSVC Features

#ifndef __Non_Portable_Features

#define __Non_Portable_Features

//Depends on the Microsoft C++ implementation

#ifdef _MSC_VER

#include <sal.h>

#endif // _MSC_VER

#pragma region __TEST_MICROSOFT_IMPLEMENTATION

#if defined(__USE__) || defined(_DEBUG) || defined(_USE_Non_Portable_Features)

//Variadic
//__declspec(align(#))

#endif // __TEST_MICROSOFT_IMPLEMENTATION

#pragma endregion

//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------

#pragma region __based

#if defined(__USE_BASE_PTR) || defined(_DEBUG) || defined(_USE_Non_Portable_Features)

//class
//__based
template<typename _T, _T* _Ptr>
class BasePtr
{
public:
	typedef _T __based(_Ptr)*Offset;
	_T& operator[](_In_ const size_t index)
	{
		Offset offset = 0;
		return *(offset + index);
	}
};

//Variadic
//__based
#define Typedef_T__Based(_T,_Ptr_Name,_Ptr_Org,_P)			\
	_T*	_Ptr_Name = &_Ptr_Org[0];							\
	typedef _T __based(_Ptr_Name)* _P;						\

//Variadic
//__based
#define Transfrom_T__Based(_Ptr_Name,_Ptr_Org)				\
	_Ptr_Name = &_Ptr_Org[0]								\

#endif // __USE_BASE_PTR

#pragma endregion

#pragma region __if(_not)_exists

#if defined(__USE_IF_EXISTS) || defined(_DEBUG) || defined(_USE_Non_Portable_Features)

//Variadic
//__if_exists
#define If_Exists(_Symbol)			\
	__if_exists(_Symbol){			\

//Variadic
//__if_not_exists
#define If_Not_Exists(_Symbol)			\
	__if_not_exists(_Symbol){			\

//Variadic
//__if_not_exists
#define Else_Exists(_Symbol)			\
	}__if_not_exists(_Symbol){			\

//Variadic
//__if_exists
#define End_Exists }

#endif // __USE_IF_EXISTS

#pragma endregion

#pragma region __inheritance

#if defined(__USE_INHERITANCE) || defined(_DEBUG) || defined(_USE_Non_Portable_Features)

//Variadic
//__single_inheritance
#define Single_Inheritance __single_inheritance

//Variadic
//__single_inheritance
#define BaseClass class __single_inheritance

//Variadic
//__single_inheritance
#define InheritancedClass class __single_inheritance

//Variadic
//__single_inheritance
#define InterfaceClass class __single_inheritance

//Variadic
//virtual public
#define Virtual public virtual

#endif // __USE_INHERITANCE

#pragma endregion

#pragma region alignof

#if defined(__USE_ALIGNOF) || defined(_DEBUG) || defined(_USE_Non_Portable_Features)

template<class _T>
class align_info final
{
public:
	align_info() :type(typeid(_T)), align_size(alignof(_T)), memory_size(sizeof(_T))
	{
	}

	const type_info& type;
	const size_t align_size;
	const size_t memory_size;

	template<typename _P>
	bool operator==(const align_info<_P>& _Right)
	{
		return this->align_size == _Right.align_size;
	}
	template<typename _P>
	bool operator!=(const align_info<_P>& _Right)
	{
		return this->align_size != _Right.align_size;
	}
	template<>
	bool operator==(const align_info<_T>& _Right)
	{
		return true;
	}
	template<>
	bool operator!=(const align_info<_T>& _Right)
	{
		return false;
	}
};

//Variadic
//__declspec(align(#))
#define AlignClass(size_move) __declspec(align(1<<size_move)) class

//Variadic
//__declspec(align(#))
#define AlignStruct (size_move) __declspec(align(1<<size_move)) struct 

//Variadic
//__declspec(align(#)) 
#define RealignClass(_T,size_move,_NewClass) typedef __declspec(align(1 << size_move)) class _T _NewClass;

//Variadic
//__declspec(align(#)) 
#define RealignStruct(_T,size_move,_NewClass) typedef __declspec(align(1 << size_move)) struct _T _NewClass;

#endif // __USE_ALIGNOF

#pragma endregion

#pragma region __assert

#if defined(__USE_ASSERT) || defined(_DEBUG) || defined(_USE_Non_Portable_Features)

//Variadic
//__assert
#define assume_where(e) (((e) || (assert(e), (e))), __assume(e))

//Variadic
//__assert
#define assume0 __assume(0)

#endif // __USE_ASSERT

#pragma endregion

#pragma region restrict

#if defined(__USE_RESTRICT) || defined(_DEBUG) || defined(_USE_Non_Portable_Features)

//Variadic
//__declspec(restrict)
#define Restrict __declspec(restrict)

#endif // __USE_RESTRICT

#pragma endregion

#pragma region __super

#if defined(__USE_SUPER) || defined(_DEBUG) || defined(_USE_Non_Portable_Features)

//Variadic
//__super
#define FindBase __super::

//Variadic
//__super
#define BaseSpace __super

#endif // __super

#pragma endregion

#pragma region __vector

#if defined(__USE_VECTORCALL) || defined(_DEBUG) || defined(_USE_Non_Portable_Features)

//Variadic
//__vectorcall
#define vectorcall __vectorcall 

//Variadic
//__vectorcall
#define vector_call __vectorcall 

#endif // __TEST_MICROSOFT_IMPLEMENTATION

#pragma endregion


//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------

#endif // !__Non_Portable_Features

#pragma endregion

#pragma region Config

//Line Framework Config
#ifndef _LFramework_Config_

#define _LFramework_Config_

#ifdef _MSC_VER

#include<yvals.h>

#endif

#if defined(_LINUX_)&&!defined(_MSC_VER)

#define __stdcall
#define _stdcall
#define __cdecl
#define _cdecl
#define __fastcall
#define _fastcall
#define __thiscall
#define abstract =0

#endif // _MSC_VER

#ifdef _Source_DLL_EXPORT
#define _LFramework_Config_API_DLL _declspec(dllexport)
#define _LFramework_Config_API_TDLL _LFramework_Config_API_DLL
#endif // _Source_Development

#ifdef _Source_DLL_IMPORT
#define _LFramework_Config_API_DLL _declspec(dllimport)
#define _LFramework_Config_API_TDLL _LFramework_Config_API_DLL
#endif // _Source_Development

#ifndef _LFramework_Config_API_DLL
#define _LFramework_Config_API_DLL
#endif // _LFramework_Config_API_DLL
#ifndef _LFramework_Config_API_TDLL
#define _LFramework_Config_API_TDLL
#endif // !_LFramework_Config_API_TDLL

#define _LFramework_Config_API_Call __stdcall 

#define _LFramework_Config_API_Class			class _LFramework_Config_API_DLL
#define _LFramework_Config_API_Struct			struct _LFramework_Config_API_DLL
#define _LFramework_Config_API_TClass			class _LFramework_Config_API_TDLL
#define _LFramework_Config_API_TStruct			struct _LFramework_Config_API_TDLL
#define _LFramework_Config_API_Func				_LFramework_Config_API_DLL _LFramework_Config_API_Call
#define _LFramework_Config_API_Func_VarParas	_LFramework_Config_API_DLL __cdecl
#define _LFramework_Config_API_Func_Fast		_LFramework_Config_API_DLL __fastcall

#define FVP										Func_VarParas
#define FFs										Func_Fast

#define __LFramework_T(name)					template<typename name>
#define _LFramework_Config_API_Template(name)	__LFramework_T(_T) name

#define _LF_(name)								_LFramework_##name
#define _LF_C_(name)							_LF_( Config_##name )
#define _LF_C_API(name)							_LF_C_( API_##name )
#define _LF_C_API_T_(name)						_LFramework_Config_API_Template(name)
#define _LF_API(name)							_LF_( API_##name )

#define _LF_T(name)								__LFramework_T(name)
#define _LF__T(name)							__LFramework_T( _##name )

#define _LF_T_C _LF_C_API_T_(_LF_C_API(Class))

#define _LFramework_Inherited public virtual

#define _LFramework_Interface(name) _LFramework_Config_API_Class name {public : virtual ~##name (){}}
#define _LFramework_Inherited_Interface(name) _LFramework_Inherited name

#define _LF_Inherited(name) _LFramework_Inherited_Interface(name)

_LFramework_Config_API_Struct ___utype{ size_t ignore; __LFramework_T(Type) constexpr operator Type& () const noexcept; };


#ifdef __clang__
#define _LFramework_Report_Error(cond, mesg)                                               \
    _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wassume\"") do { \
        if (cond) { /* contextually convertible to bool paranoia */                        \
        } else {                                                                           \
            _STL_REPORT_ERROR(mesg);                                                       \
        }                                                                                  \
                                                                                           \
        _Analysis_assume_(cond);                                                           \
    }                                                                                      \
    while (false)                                                                          \
    _Pragma("clang diagnostic pop")
#else // ^^^ Clang / MSVC vvv
#define _LFramework_Report_Error(cond, mesg)                        \
    do {                                                            \
        if (cond) { /* contextually convertible to bool paranoia */ \
        } else {                                                    \
            _STL_REPORT_ERROR((mesg));                              \
        }                                                           \
                                                                    \
        _Analysis_assume_(cond);                                    \
    } while (false)
#endif // ^^^ MSVC ^^^

#define _LFramework_Config_API_Result_Constexpr(key) if constexpr (key) return 
#ifndef _LFramework_Config_API_Result_Not_Only

#define LF_return(key) _LFramework_Config_API_Result_Constexpr(key)

#endif // !_LFramework_Config_API_Result_Not_Only

#endif // !_LFramework_Config_

#pragma endregion

#pragma region Global

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

#pragma region choose_type

template < bool value, typename _True, typename _False> _LF_C_API(TStruct) choose_type;
template < typename _True, typename _False>
_LF_C_API(TStruct) choose_type < true, _True, _False>
{
	using tag = _True;
};
template < typename _True, typename _False>
_LF_C_API(TStruct) choose_type < false, _True, _False >
{
	using tag = _False;
};

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
	template<typename T> operator T&()
	{
		return *static_cast<T*>(ptr);
	}

	void* ptr;
};

#pragma endregion


_LF_C_API(Class)	any_class
{
public:
	virtual ~any_class() {}
private:
};

#pragma endregion

#pragma region Kit

#define _LFK_API(name)	_LFramework_Kit_API_##name
#define _LFK_DEF(name)	_LFramework_Kit_API_##name##_Define

#pragma endregion

#pragma region Exist (Static)

#define _LFKE_API(var,name)		_LFK_API( Exist_##var )(name)
#define _LFKE_DEF(var,name)		_LFK_DEF( Exist_##var )(name)
#define _LFKWE_API(var,name)	_LFK_API( WeakExist_##var )(name)
#define _LFKWE_DEF(var,name)	_LFK_DEF( WeakExist_##var )(name)

#pragma region Class::Type

#define _LFramework_Kit_API_Exist_Type_Define(name)														\
template< typename , typename = void>																	\
_LF_C_API(TStruct) __exist_type_##name									: std::false_type	{ };		\
template< typename T >																					\
_LF_C_API(TStruct) __exist_type_##name <T,std::void_t<typename T::name>>	: std::true_type	{ };	\
template< typename T > _LF_C_API(TDLL) constexpr bool __exist_type_##name##_v = __exist_type_##name<T>();
#define _LFramework_Kit_API_Exist_Type(name) __exist_type_##name##_v
#define if_type_exist_def(name)	_LFKE_DEF(Type,name)
#define if_type_exist(name)		_LFKE_API(Type,name)
// if_type_exist(name)<type>

#pragma endregion

#pragma region Class::Func

#define _LFramework_Kit_API_Exist_Func_Define(name)																			\
template< typename, typename, typename = void > _LF_C_API(TStruct) __exist_function_##name : std::false_type { };			\
template< typename T, typename Ret, typename... Args>																		\
_LF_C_API(TStruct) __exist_function_##name<																					\
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
template< typename, typename, typename = void > _LF_C_API(TStruct) __exist_field_##name : std::false_type { };				\
template< typename T, typename MType> _LF_C_API(TStruct) __exist_field_##name<												\
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
template< typename, typename, typename = void > _LF_C_API(TStruct) __exist_property_##name : std::false_type { };			\
template< typename T, typename MType> _LF_C_API(TStruct) __exist_property_##name<											\
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

#pragma region Typen (Define)

#define _LFramework_Indicator_Def(name,_tag,_value)	\
_LF_C_API(Struct) name##_indicator					\
{													\
	using tag = _tag;								\
	constexpr static bool value = _value;			\
};													\
template< typename indicator>						\
_LF_C_API(TDLL) constexpr bool is_##name##_indicator_v = std::is_same_v<indicator, name##_indicator>

_LFramework_Indicator_Def(bad, void, false);
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

#pragma region LDType

if_property_exist_def(value);
if_type_exist_def(tag);
if_type_exist_def(integral_indicator);
if_type_exist_def(floating_point_indicator);
if_type_exist_def(unsigned_indicator);
if_type_exist_def(type_indicator)

#define _LFramework_IsType(name,T)\
std::is_##name##_v<T> || if_type_exist( name##_indicator ) < T >

template<typename T>	_LF_C_API(TStruct)	LDType;
template<typename T>	_LF_C_API(TStruct)	LDType_Number;
template<typename T>	_LF_C_API(TStruct)	LDType_Indicator;
template<typename T>	_LF_C_API(TStruct)	LDType_Traits;
_LF_C_API(Struct)	LDType_Bad_Indicator;

template<typename T>
_LF_C_API(TStruct) LDType
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
_LF_C_API(TStruct)  LDType_Number
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
_LF_C_API(TStruct) LDType_Indicator
{
	//	is indicator type
	constexpr static bool is_idc = if_type_exist(tag) < T > && if_property_exist(value) < T > ;
	//	is key indicator
	constexpr static bool is_key = std::is_same_v<T, key_indicator>;
	//	is type indicator
	constexpr static bool is_tid = if_type_exist(type_indicator) < T > ;
	//	is pseudo indicator(contain indicator element)
	constexpr static bool is_pse = if_type_exist(tag) < T > != if_property_exist(value) < T > ;

	using tag = T;
	constexpr static bool value = true;
	using type_indicator = key_indicator;
};

_LF_C_API(Struct) LDType_Bad_Indicator
{
	using tag = bad_indicator;
	constexpr static bool value = false;
	using type_indicator = key_indicator;
};

#pragma endregion

#pragma endregion

#pragma region type_indicator

template<typename ...Args> struct type_list;
template<typename T> constexpr bool _LF_C_API(TDLL) is_type_indicator(typename T::type_indicator*);
template<typename T> constexpr bool _LF_C_API(TDLL) is_type_indicator(...);
template<typename T> constexpr bool _LF_C_API(TDLL) is_type_list_end();
template<typename T> constexpr bool _LF_C_API(TDLL) is_indicator_typen(typename T::tag* t, bool v = T::value);
template<typename T> constexpr bool _LF_C_API(TDLL) is_indicator_typen(...);
template<typename L, int pos>  _LF_C_API(TStruct)  type_decltype;

template<int index> constexpr bool is_type_list_contains_detect = true;
template<> constexpr bool _LF_C_API(TDLL) is_type_list_contains_detect<-1> = false;

template<>
_LF_C_API(Struct) type_list<void>
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
_LF_C_API(TStruct) type_list<Last>
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
	using decltype_type = typename choose_type<!is_type_list_contains_detect<is_type_list_contains<T>(0)>, Default, T>::tag;
};
template<typename First, typename ...Args>
_LF_C_API(TStruct) type_list<First, Args...>
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
	using decltype_type = typename choose_type<!is_type_list_contains_detect<is_type_list_contains<T>(0)>, Default, T>::tag;
};
template<typename T>
constexpr bool _LF_C_API(TDLL) is_type_indicator(typename T::type_indicator*) { return true; }
template<typename T>
constexpr bool _LF_C_API(TDLL) is_type_indicator(...) { return false; }
template<typename T>
constexpr bool _LF_C_API(TDLL) is_type_list_end() { return !std::is_same_v<typename T::type_indicator, bad_indicator>; }
template<typename T>
constexpr bool _LF_C_API(TDLL) is_indicator_typen(typename T::tag* t, bool v) { return true; }
template<typename T>
constexpr bool _LF_C_API(TDLL) is_indicator_typen(...) { return false; }

template<typename L>
_LF_C_API(TStruct) type_decltype<L, -2>
{
	using tag = bad_indicator;
	constexpr static bool value = false;
};
template<typename L>
_LF_C_API(TStruct) type_decltype<L, -1>
{
	using tag = bad_indicator;
	constexpr static bool value = false;
};
template<typename L>
_LF_C_API(TStruct) type_decltype<L, 0>
{
	using tag = typename L::tag;
	constexpr static bool value = true;
};
template<typename L, int pos>
_LF_C_API(TStruct) type_decltype
{
	using tag = typename type_decltype<typename L::type_indicator, pos - 1>::tag;
	constexpr static bool value = true;
};

template<typename type_list_type, bool _IsF = true> const string_indicator::tag& _LF_C_API(TDLL) get_type_list_string()
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

#pragma region Traits (Static)

template<typename _T> _LF_C_API(TStruct)	check_type			:std::true_type{};
template<> _LF_C_API(TStruct)			check_type<void>	:std::false_type{};


_LF_C_API(Class)
any_trait_base:	_LF_Inherited(any_class)
{
public:
	using string = typename string_indicator::tag;

	const char* read_symbol_name() const
	{
		return single_name;
	}
	const string& read_any_name() const
	{
		return name;
	}
	const type_info& read_type() const
	{
		return _type;
	}
	auto read_type_hash() const
	{
		return _type.hash_code();
	}
protected:
	any_trait_base(const char* symbol_name,const string& func_name, const type_info& symbol_type) :
		single_name(symbol_name),
		name(func_name),
		_type(symbol_type) {}
private:
	const char* single_name;
	string name;
	const type_info& _type;

public:

};

#define _LFramework_Kit_API_StaticOperatorBool(boolen)	operator bool() { return boolen ; }

#pragma region function_traits

/*
	fail to get function information
*/
template<typename _T> _LF_C_API(TStruct) function_traits

{
	_LFramework_Kit_API_StaticOperatorBool(false);
	using tag = void;
	constexpr static bool value = false;

	using result = bad_indicator;
	using parameters = bad_indicator;
	using belong = unknown_indicator;
	using call = unknown_indicator;
	using consting = unconst_indicator;
	using typen = LDType_Bad_Indicator;
};


/*
	get regular function information
*/
template<typename Ret, typename... Args> _LF_C_API(TStruct) function_traits<Ret(*)(Args...)>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(*)(Args...);
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = namespace_indicator;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
	using typen = LDType<tag>;
};

/*
	get regular function information
*/
template<typename Ret> _LF_C_API(TStruct) function_traits<Ret(*)()>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(*)();
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<void>;
	using belong = namespace_indicator;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
	using typen = LDType<tag>;
};


/*
	get const member function information
*/
template<typename Ret, typename C, typename... Args> _LF_C_API(TStruct) function_traits<Ret( C::*)(Args...) const>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret( C::*)(Args...) const;
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = const_indicator;
	using typen = LDType<tag>;
};

/*
	get const member function information
*/
template<typename Ret, typename C > _LF_C_API(TStruct) function_traits<Ret( C::*)() const>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret( C::*)() const;
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<void>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = const_indicator;
	using typen = LDType<tag>;
};

/*
	get unconst member function information
*/
template<typename Ret, typename C, typename... Args> _LF_C_API(TStruct) function_traits<Ret( C::*)(Args...)>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret( C::*)(Args...);
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
	using typen = LDType<tag>;
};

/*
	get unconst member function information
*/
template<typename Ret, typename C> _LF_C_API(TStruct) function_traits<Ret( C::*)()>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret( C::*)();
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<void>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
	using typen = LDType<tag>;
};

/*
	get regular function information
*/
template<typename T, typename = template_fill_indicator> _LF_C_API(TStruct) function_traits_ex : public function_traits<T>
{
	using function_traits_indicator = void;
};
/*
	get lambda or Functor information
*/
template<typename Lambda>
_LF_C_API(TStruct) function_traits_ex<Lambda, std::void_t<decltype(&Lambda::operator())>> : public function_traits<decltype(&Lambda::operator())>
{
	using function_traits_indicator = void;
};

#pragma endregion

#pragma region field_traits

/*
	get regular field information
*/
template<typename _T> _LF_C_API(TStruct) field_traits
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = _T;
	constexpr static bool value = true;

	using origin = _T;
	using typen = LDType<tag>;
};

/*
	get regular field information
*/
template<typename T>
_LF_C_API(TStruct)
field_traits_ex : public function_traits<T>
{
	using field_traits_indicator = void;
	using decay = generate_full_decay_typen<T>;
};

#pragma endregion

#define LF_not_void_return(cond)			LF_return(is_bad_indicator_v<cond>)

#pragma region function_info

_LF_C_API(Class) function_base;
template<typename func> _LF_C_API(TClass) function_info;

_LF_C_API(Class)
function_base:	_LF_Inherited(any_trait_base)
{
public:
	template<typename _func>
	friend const function_info<_func>& create_or_get_function_info(const _func & func_ptr, const char* function_name);

	using string = typename string_indicator::tag;

	function_base(function_base&) = delete;
	function_base(function_base&&) = delete;

	using function_bases_type = std::map<size_t, function_base*>;
protected:
	function_base(const char* symbol_name, const string & func_name, const type_info & symbol_type) :
		any_trait_base(symbol_name, func_name, symbol_type) {}
private:
	static function_bases_type function_bases;
};

template<typename func>
_LF_C_API(TClass)
function_info:	_LF_Inherited(function_base)
{
public:
	using string = typename string_indicator::tag;
private:
	function_info(const func& func_ptr,const char* symbol_name, const string& func_name, const type_info& symbol_type) :
		function_base(symbol_name, func_name, symbol_type),
		any_trait_base(symbol_name, func_name, symbol_type),
		invoker(func_ptr) {}
public:
	template<typename _func>
	friend const function_info<_func>& create_or_get_function_info(const _func& func_ptr, const char* function_name);

	using tag = func;
	constexpr static bool value = true;

	using trait = function_traits_ex<func>;
	using result = typename trait::result;
	using parameters = typename trait::parameters;
	using belong = typename trait::belong;

private:
	function_info(const func& func_ptr, const char* function_name) :
		function_info(func_ptr, function_name,
			string(typeid(result).name()) + " [" + typeid(belong).name() + "]::" + function_name + "(" + get_type_list_string<parameters>() + ")",
			typeid(func)) {}
public:
	function_info(function_info&) = delete;
	function_info(function_info&&) = delete;
	const func invoker;

	template<typename... Args>
	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke(belong* instance, Args... args) const
	{
		if constexpr (std::is_same_v<parameters, type_list<Args...>>)
		{
			if constexpr (std::is_same_v<belong, namespace_indicator>)
			{
				if constexpr (std::is_same_v<result, void>)
				{
					invoker(args...);
					return 0;
				}
				else
				{
					return invoker(args...);
				}
			}
			else
			{
				if constexpr (std::is_same_v<result, void>)
				{
					((*instance).*invoker)(args...);
					return 0;
				}
				else
				{
					return ((*instance).*invoker)(args...);
				}
			}
		}
		else
		{
			static_assert(std::is_same_v<parameters, type_list<Args...>>, "invoke args check type: failed");
		}
	}
	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke(belong* instance) const
	{
		if constexpr (std::is_same_v<parameters, type_list<void>>)
		{
			if constexpr (std::is_same_v<belong, namespace_indicator>)
			{
				if constexpr (std::is_same_v<result, void>)
				{
					invoker();
					return 0;
				}
				else
				{
					return invoker();
				}
			}
			else
			{
				if constexpr (std::is_same_v<result, void>)
				{
					((*instance).*invoker)();
					return 0;
				}
				else
				{
					return ((*instance).*invoker)();
				}
			}
		}
		else
		{
			static_assert(std::is_same_v<parameters, type_list<void>>, "invoke args check type: failed");
		}
	}

	template<typename... Args>
	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke_uncheck(belong* instance, Args... args) const
	{
		if constexpr (std::is_same_v<belong, namespace_indicator>)
		{
			if constexpr (std::is_same_v<result, void>)
			{
				invoker(args...);
				return 0;
			}
			else
			{
				return invoker(args...);
			}
		}
		else
		{
			if constexpr (std::is_same_v<result, void>)
			{
				((*instance).*invoker)(args...);
				return 0;
			}
			else
			{
				return ((*instance).*invoker)(args...);
			}
		}
	}

	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke_uncheck(belong* instance) const
	{
		if constexpr (std::is_same_v<belong, namespace_indicator>)
		{
			if constexpr (std::is_same_v<result, void>)
			{
				invoker();
				return 0;
			}
			else
			{
				return invoker();
			}
		}
		else
		{
			if constexpr (std::is_same_v<result, void>)
			{
				((*instance).*invoker)();
				return 0;
			}
			else
			{
				return ((*instance).*invoker)();
			}
		}
	}

private:

};

template<typename func>
const function_info<func>& _LF_C_API(TDLL) create_or_get_function_info(const func& func_ptr, const char* function_name)
{
	if (!function_base::function_bases.count(typeid(func).hash_code()))
	{
		function_base::function_bases[typeid(func).hash_code()] = new function_info(func_ptr, function_name);
	}
	return *dynamic_cast<function_info<func>*>(function_base::function_bases[typeid(func).hash_code()]);
}

using func_base = const function_base&;

#define make_function_info(belong,name)		create_or_get_function_info(& belong::name, #name )
#define func_base							const function_base&
#define func_info 							const auto&

#pragma endregion

#pragma region field_info

_LF_C_API(Class) field_base;
template<typename field, typename C> _LF_C_API(TClass) field_info;

_LF_C_API(Class)
field_base:	_LF_Inherited(any_trait_base)
{
private:
	struct maper_sorter
	{
		bool operator() (const char* lhs, const char* rhs) const
		{
			return strcmp(lhs, rhs) < 0;
		}
	};
public:
	template<typename _field,typename _C>
	friend const field_info<_field, _C>& create_or_get_field_info(_field _C::* _right_ptr, const char* field_name);
	template<typename _field, typename _C>
	friend const field_info<_field, _C>& create_or_get_field_info(size_t _offset, const char* field_name);

	using string = typename string_indicator::tag;

	field_base(function_base&) = delete;
	field_base(function_base&&) = delete;

	using map_container = std::map<const char*, field_base*, maper_sorter>;
	using field_bases_type = std::map<size_t, map_container>;

	virtual void* get(void* instance) const = 0;
	virtual void set(void* instance, void* value) const = 0;
	template<typename T>
	void set_rv(void* instance, T&& value) const
	{
		set(instance, &value);
	}

protected:
	field_base(const char* symbol_name, const string & field_name, const type_info & symbol_type) :
		any_trait_base(symbol_name, field_name, symbol_type) {}
private:
	static field_bases_type field_bases;
};

template<typename field,typename C = namespace_indicator>
_LF_C_API(TClass) 
field_info: _LF_Inherited(field_base)
{
public:
	using string = typename string_indicator::tag;
private:
	field_info(size_t _offset, const char* symbol_name, const string & field_name, const type_info & symbol_type) :
		field_base(symbol_name, field_name, symbol_type),
		any_trait_base(symbol_name, field_name, symbol_type),
		offset(_offset) {}
public:
	template<typename _field, typename _C>
	friend const field_info<_field, _C>& create_or_get_field_info(_field _C::* _right_ptr, const char* field_name);
	template<typename _field, typename _C>
	friend const field_info<_field, _C>& create_or_get_field_info(size_t _offset, const char* field_name);

	using tag = field;
	constexpr static bool value = true;
	using belong = C;

	using trait = field_traits_ex<field>;
private:
	field_info(field C::* _right_ptr, const char* field_name) :
		field_info(
			static_cast<size_t>(reinterpret_cast<int>(*(void**)(&_right_ptr))),
			field_name,
			string(typeid(C).name()) + "::" + field_name,
			typeid(field)) {}
	field_info(const size_t& _offset, const char* field_name) :
		field_info(
			_offset,
			field_name,
			string(typeid(C).name()) + "::" + field_name,
			typeid(field)) {}
public:
	field_info(field_info&) = delete;
	field_info(field_info&&) = delete;
	const size_t offset;

	void set(C* instance, field& arg) const
	{
		if constexpr (std::is_same_v<C, namespace_indicator>)
		{
			*static_cast<field*>(reinterpret_cast<void*>(offset)) = arg;
		}
		else
		{
			*((field*)((size_t)instance + offset)) = arg;
		}
	}
	void set(C* instance, field&& arg) const
	{
		if constexpr (std::is_same_v<C, namespace_indicator>)
		{
			*static_cast<field*>(reinterpret_cast<void*>(offset)) = std::move(arg);
		}
		else
		{
			*((field*)((size_t)instance + offset)) = std::move(arg);
		}
	}
	virtual void set(void* instance, void* value) const override
	{
		set(static_cast<C*>(instance), *static_cast<field*>(value));
	}

	field& get(C* instance) const
	{
		if constexpr (std::is_same_v<C, namespace_indicator>)
		{
			return *static_cast<field*>(reinterpret_cast<void*>(offset));
		}
		else
		{
			return *((field*)((size_t)instance + offset));
		}
	}
	virtual void* get(void* instance) const override
	{
		return &get(static_cast<C*>(instance));
	}
};

template<typename field, typename C>
const field_info<field, C>& create_or_get_field_info(field C::* _right_ptr, const char* field_name)
{
	if (!field_base::field_bases[typeid(C).hash_code()].count(field_name))
	{
		field_base::field_bases[typeid(C).hash_code()][field_name] = new field_info<field, C>(_right_ptr, field_name);
	}
	return *dynamic_cast<field_info<field, C>*>(field_base::field_bases[typeid(C).hash_code()][field_name]);
}
template<typename field, typename C>
const field_info<field, C>& create_or_get_field_info(size_t _offset, const char* field_name)
{
	if (!field_base::field_bases[typeid(C).hash_code()].count(field_name))
	{
		field_base::field_bases[typeid(C).hash_code()][field_name] = new field_info<field, C>(_offset, field_name);
	}
	return *dynamic_cast<field_info<field, C>*>(field_base::field_bases[typeid(C).hash_code()][field_name]);
}

#define make_field_info(belong,name)		create_or_get_field_info( &belong::name, #name )
#define fvar_base							const field_base&
#define fvar_info							const auto&

#pragma endregion

template<typename T>
_LF_C_API(TStruct) LDType_Traits
{
	using tag_function = function_traits_ex<T>;
	using tag_field = field_traits_ex<T>;

	using tag = T;
	constexpr static bool value = tag_field::value != tag_function::value;
	using type_indicator = key_indicator;
};

#pragma endregion

class ld_test
{
public:
	ld_test();
};

namespace ld
{
	class undering
	{
	public:
		virtual ~undering();
	};

	class i_any_architecture :public virtual undering
	{
	public:
		virtual ~i_any_architecture();
	};

	namespace convention
	{

	}
}
