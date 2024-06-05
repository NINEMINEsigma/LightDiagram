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

#pragma endregion

#pragma region MSVC Features

#ifndef __Non_Portable_Features

#define __Non_Portable_Features

//Depends on the Microsoft C++ implementation

#include <sal.h>


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

#include<yvals.h>

//If you enable debug mode, you can only compile directly with the code of this project
#ifndef _DEBUG

#ifdef _Source_Development
#define _LFramework_Config_API_DLL _declspec(dllexport)
#endif // _Source_Development

#ifndef _LFramework_Config_API_DLL
#define _LFramework_Config_API_DLL _declspec(dllimport)
#endif // _LFramework_Config_API_DLL

#else

#define _LFramework_Config_API_DLL

#endif // !_DEBUG

#define _LFramework_Config_API_Call __stdcall 

#define _LFramework_Config_API_Class			class _LFramework_Config_API_DLL
#define _LFramework_Config_API_Struct			struct _LFramework_Config_API_DLL
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

// case1: T* can cast to C*
template <template <typename...> class C, typename...Ts>
std::true_type is_base_of_template_impl(const C<Ts...>*);
// case2: T* cannot cast to C*
template <template <typename...> class C>
std::false_type is_base_of_template_impl(...);

template <template <typename...> class C, typename T>
using is_base_of_template = decltype(is_base_of_template_impl<C>(std::declval<T*>()));

template < bool value, typename _True, typename _False> _LF_C_API(Struct) choose_type;
template < typename _True, typename _False>
_LF_C_API(Struct) choose_type < true, _True, _False>
{
	using tag = _True;
	constexpr static bool value = true;
};
template < typename _True, typename _False>
_LF_C_API(Struct) choose_type < false, _True, _False >
{
	using tag = _False;
	constexpr static bool value = false;
};

_LFramework_Interface(any_class);

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
_LF_C_API(Struct) __exist_type_##name									: std::false_type	{ };		\
template< typename T >																					\
_LF_C_API(Struct) __exist_type_##name <T,std::void_t<typename T::name>>	: std::true_type	{ };	\
template< typename T > _LF_C_API(DLL) constexpr bool __exist_type_##name##_v = __exist_type_##name<T>();
#define _LFramework_Kit_API_Exist_Type(name) __exist_type_##name##_v
#define if_type_exist_def(name)	_LFKE_DEF(Type,name)
#define if_type_exist(name)		_LFKE_API(Type,name)
// if_type_exist(name)<type>

#pragma endregion

#pragma region Class::Func

#define _LFramework_Kit_API_Exist_Func_Define(name)																			\
template< typename, typename, typename = void > _LF_C_API(Struct) __exist_function_##name : std::false_type { };			\
template< typename T, typename Ret, typename... Args>																		\
_LF_C_API(Struct) __exist_function_##name<																					\
	T,																														\
	Ret(Args...),																											\
	typename std::enable_if<std::is_same_v<decltype(std::declval<T>().##name##(std::declval<Args>()...)), Ret>>::type>		\
	: std::true_type { };																									\
template< typename T, typename Ret > _LF_C_API(DLL) constexpr bool __exist_function_##name##_v = __exist_function_##name<T,Ret>();
#define _LFramework_Kit_API_Exist_Func(name)	__exist_function_##name##_v
#define if_func_exist_def(name)	_LFKE_DEF(Func,name)
#define if_func_exist(name)		_LFKE_API(Func,name)
// if_func_exist(name)<type,result(...Args)>



#pragma endregion

#pragma region Class::Field

#define _LFramework_Kit_API_Exist_Field_Define(name)																		\
template< typename, typename, typename = void > _LF_C_API(Struct) __exist_field_##name : std::false_type { };				\
template< typename T, typename MType> _LF_C_API(Struct) __exist_field_##name<												\
	T,																														\
	MType,																													\
	typename std::enable_if<std::is_same_v<decltype(std::declval<T>().##name), MType>>::type>								\
	: std::true_type { };																									\
template< typename T, typename MType> _LF_C_API(DLL) constexpr bool __exist_field_##name##_v = __exist_field_##name<T, MType>();
#define _LFramework_Kit_API_Exist_Field(name)	__exist_field_##name##_v
#define if_field_exist_def(name)	_LFKE_DEF(Field,name)
#define if_field_exist(name)		_LFKE_API(Field,name)

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
_LF_C_API(DLL) constexpr bool is_##name##_indicator_v = std::is_same_v<indicator, name##_indicator>

_LFramework_Indicator_Def(bad, void, false);
_LFramework_Indicator_Def(empty, void, false);
_LFramework_Indicator_Def(void, void, false);
_LFramework_Indicator_Def(unknown, void, false);
_LFramework_Indicator_Def(_cdecl, void, true);
_LFramework_Indicator_Def(_stdcall, void, false);
_LFramework_Indicator_Def(_fastcall, void, false);
_LFramework_Indicator_Def(__thiscall, void, false);
_LFramework_Indicator_Def(global, void, false);
_LFramework_Indicator_Def(const, void, true);
_LFramework_Indicator_Def(unconst, void, false);
_LFramework_Indicator_Def(template_fill, void, false);
_LFramework_Indicator_Def(key, void, true);

#pragma region LDType

if_field_exist_def(value);
if_type_exist_def(integral_indicator);
if_type_exist_def(floating_point_indicator);
if_type_exist_def(unsigned_indicator);

#define _LFramework_IsType(name,T)\
std::is_##name##_v<T> || if_type_exist( name##_indicator ) < T >

template<typename T>
_LF_C_API(Struct) LDType_Number
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
_LF_C_API(Struct) LDType
{
	//	number type state
	using tag_num = LDType_Number<T>;

	using tag = T;
	constexpr static bool value = true;
	using type_indicator = key_indicator;
};

#pragma endregion


#pragma endregion

#pragma region type_indicator

template<typename First, typename ...Args> struct type_list;
template<typename T> constexpr bool is_type_indicator(typename T::type_indicator*);
template<typename T> constexpr bool is_type_indicator(...);
template<typename T> constexpr bool is_type_list_end();
template<typename T> constexpr bool is_indicator_typen(typename T::tag * t, bool v);
template<typename T> constexpr bool is_indicator_typen(...);
template<typename L, int pos> struct type_decltype;

template<int index> constexpr bool is_type_list_contains_detect = true;
template<> constexpr bool is_type_list_contains_detect<-1> = false;

template<>
struct type_list<void>
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
struct type_list<Last>
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
			return type_indicator::is_type_list_contains<T>(pos + 1);
	};

	template<typename Default, typename T>
	using decltype_type = typename choose_type<!is_type_list_contains_detect<is_type_list_contains<T>(0)>, Default, T>::tag;
};
template<typename First, typename ...Args>
struct type_list
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
			return type_indicator::is_type_list_contains<T>(pos + 1);
	};

	template<typename Default, typename T>
	using decltype_type = typename choose_type<!is_type_list_contains_detect<is_type_list_contains<T>(0)>, Default, T>::tag;
};
template<typename T>
constexpr bool is_type_indicator(typename T::type_indicator*) { return true; }
template<typename T>
constexpr bool is_type_indicator(...) { return false; }
template<typename T>
constexpr bool is_type_list_end() { return !std::is_same_v<typename T::type_indicator, VoidType>; }
template<typename T>
constexpr bool is_indicator_typen(typename T::tag * t, bool v = T::value) { return true; }
template<typename T>
constexpr bool is_indicator_typen(...) { return false; }

template<typename L>
struct type_decltype<L, -2>
{
	using tag = bad_indicator;
	constexpr static bool value = false;
};
template<typename L>
struct type_decltype<L, -1>
{
	using tag = bad_indicator;
	constexpr static bool value = false;
};
template<typename L>
struct type_decltype<L, 0>
{
	using tag = typename L::tag;
	constexpr static bool value = true;
};
template<typename L, int pos>
struct type_decltype
{
	using tag = typename type_decltype<typename L::type_indicator, pos - 1>::tag;
	constexpr static bool value = true;
};

#pragma endregion

#pragma region Traits (Static)

template<typename _T> _LF_C_API(Struct)	check_type			:std::true_type{};
template<> _LF_C_API(Struct)			check_type<void>	:std::false_type{};

#define _LFramework_Kit_API_StaticOperatorBool(boolen)	operator bool() { return boolen ; }

#pragma region function_traits

/*
	fail to get function information
*/
template<typename _T> _LF_C_API(Struct) function_traits
{
	_LFramework_Kit_API_StaticOperatorBool(false);
	using tag = void;
	constexpr static bool value = false;

	using result = bad_indicator;
	using parameters = bad_indicator;
	using belong = unknown_indicator;
	using call = unknown_indicator;
	using consting = unconst_indicator;
};

/*
	get regular function information
*/
template<typename Ret, typename... Args> _LF_C_API(Struct) function_traits<Ret(_cdecl*)(Args...)>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(_cdecl*)(Args...);
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = global_indicator;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
};
#ifndef _WIN64
template<typename Ret, typename... Args> _LF_C_API(Struct) function_traits<Ret(_stdcall*)(Args...)>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(_stdcall*)(Args...);
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = global_indicator;
	using call = _stdcall_indicator;
	using consting = unconst_indicator;
};
template<typename Ret, typename... Args> _LF_C_API(Struct) function_traits<Ret(_fastcall*)(Args...)>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(_fastcall*)(Args...);
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = global_indicator;
	using call = _fastcall_indicator;
	using consting = unconst_indicator;
};
#endif // !_WIN64


/*
	get const member function information
*/
template<typename Ret, typename C, typename... Args> _LF_C_API(Struct) function_traits<Ret(_cdecl C::*)(Args...) const>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(_cdecl C::*)(Args...) const;
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = const_indicator;
};
#ifndef _WIN64
template<typename Ret, typename C, typename... Args> _LF_C_API(Struct) function_traits<Ret(_stdcall C::*)(Args...) const>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(_stdcall C::*)(Args...) const;
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _stdcall_indicator;
	using consting = const_indicator;
};
template<typename Ret, typename C, typename... Args> _LF_C_API(Struct) function_traits<Ret(_fastcall C::*)(Args...) const>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(_fastcall C::*)(Args...) const;
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _fastcall_indicator;
	using consting = const_indicator;
};
template<typename Ret, typename C, typename... Args> _LF_C_API(Struct) function_traits<Ret(__thiscall C::*)(Args...) const>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(__thiscall C::*)(Args...) const;
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = __thiscall_indicator;
	using consting = const_indicator;
};
#endif // !_WIN64


/*
	get unconst member function information
*/
template<typename Ret, typename C, typename... Args> _LF_C_API(Struct) function_traits<Ret(_cdecl C::*)(Args...)>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(_cdecl C::*)(Args...);
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
};
#ifndef _WIN64
template<typename Ret, typename C, typename... Args> _LF_C_API(Struct) function_traits<Ret(_stdcall C::*)(Args...)>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(_stdcall C::*)(Args...);
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _stdcall_indicator;
	using consting = unconst_indicator;
};
template<typename Ret, typename C, typename... Args> _LF_C_API(Struct) function_traits<Ret(_fastcall C::*)(Args...)>
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(_fastcall C::*)(Args...);
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _fastcall_indicator;
	using consting = unconst_indicator;
};
#endif // !_WIN64

/*
	get regular function information
*/
template<typename T, typename = template_fill_indicator> _LF_C_API(Struct) function_traits_ex : public function_traits<T>
{
	using function_traits_indicator = void;
};
/*
	get lambda or Functor information
*/
template<typename Lambda>
_LF_C_API(Struct) function_traits_ex<Lambda, std::void_t<decltype(&Lambda::operator())>> : public function_traits<decltype(&Lambda::operator())>
{
	using function_traits_indicator = void;
};

#pragma endregion

#define LF_not_void_return(cond)			LF_return(is_bad_indicator_v<cond>)

#pragma region function_info

_LF_C_API(Class)	function_base:	_LF_Inherited(any_class)
{
public:

private:
	const char* name;
	const type_info& _type;
};

template<typename func>
_LF_C_API(Class)	function_info:	_LF_Inherited(function_base), _LF_Inherited(any_class)
{
public:
	function_info(const func & func_ptr) :invoker(func_ptr) {}

	using tag = func;
	constexpr static bool value = true;
	
	using traits = function_traits_ex<func>;
	using result = typename traits::result;
	using parameters = typename traits::parameters;
	using belong = typename traits::belong;

	const func& invoker;
private:

};

#pragma endregion

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
