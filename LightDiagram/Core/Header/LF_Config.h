#ifndef __FILE_LF_CONFIG

#define __FILE_LF_CONFIG

//release:	std::type_info to global namespace

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

#ifdef _WINDOW_
#include <Windows.h>
#endif // OS_TYPE_WINDOWS_CC

using type_info = std::type_info;

#pragma endregion

#pragma region Key Check

// xkeycheck.h internal header

// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef _XKEYCHECK_H
#define _XKEYCHECK_H

// xkeycheck.h assumes that it's being included by yvals_core.h in a specific order.
// Nothing else should include xkeycheck.h.
//*by here, is one try for check

#if _STL_COMPILER_PREPROCESSOR

#if !defined(_ALLOW_KEYWORD_MACROS) && !defined(__INTELLISENSE__)

// clang-format off
// #if defined($KEYWORD)
// #define $KEYWORD EMIT WARNING C4005
// #error The C++ Standard Library forbids macroizing the keyword "$KEYWORD". \
// Enable warning C4005 to find the forbidden define.
// #endif // $KEYWORD
// clang-format on

// *don't* check the "alternative token representations"

// keywords:
#if defined(alignas)
#define alignas EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "alignas". \
Enable warning C4005 to find the forbidden define.
#endif // alignas

#if defined(alignof)
#define alignof EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "alignof". \
Enable warning C4005 to find the forbidden define.
#endif // alignof

#if defined(asm)
#define asm EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "asm". \
Enable warning C4005 to find the forbidden define.
#endif // asm

#if defined(auto)
#define auto EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "auto". \
Enable warning C4005 to find the forbidden define.
#endif // auto

#if defined(bool)
#define bool EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "bool". \
Enable warning C4005 to find the forbidden define.
#endif // bool

#if defined(break)
#define break EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "break". \
Enable warning C4005 to find the forbidden define.
#endif // break

#if defined(case)
#define case EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "case". \
Enable warning C4005 to find the forbidden define.
#endif // case

#if defined(catch)
#define catch EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "catch". \
Enable warning C4005 to find the forbidden define.
#endif // catch

#if defined(char)
#define char EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "char". \
Enable warning C4005 to find the forbidden define.
#endif // char

#if defined(char8_t) && _HAS_CXX20
#define char8_t EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "char8_t". \
Enable warning C4005 to find the forbidden define.
#endif // char8_t

#if defined(char16_t)
#define char16_t EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "char16_t". \
Enable warning C4005 to find the forbidden define.
#endif // char16_t

#if defined(char32_t)
#define char32_t EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "char32_t". \
Enable warning C4005 to find the forbidden define.
#endif // char32_t

#if defined(class)
#define class EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "class". \
Enable warning C4005 to find the forbidden define.
#endif // class

#if defined(concept) && _HAS_CXX20
#define concept EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "concept". \
Enable warning C4005 to find the forbidden define.
#endif // concept

#if defined(const)
#define const EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "const". \
Enable warning C4005 to find the forbidden define.
#endif // const

#if defined(consteval) && _HAS_CXX20
#define consteval EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "consteval". \
Enable warning C4005 to find the forbidden define.
#endif // consteval

#if defined(constexpr)
#define constexpr EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "constexpr". \
Enable warning C4005 to find the forbidden define.
#endif // constexpr

#if defined(constinit) && _HAS_CXX20
#define constinit EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "constinit". \
Enable warning C4005 to find the forbidden define.
#endif // constinit

#if defined(const_cast)
#define const_cast EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "const_cast". \
Enable warning C4005 to find the forbidden define.
#endif // const_cast

#if defined(continue)
#define continue EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "continue". \
Enable warning C4005 to find the forbidden define.
#endif // continue

#if defined(co_await) && _HAS_CXX20
#define co_await EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "co_await". \
Enable warning C4005 to find the forbidden define.
#endif // co_await

#if defined(co_return) && _HAS_CXX20
#define co_return EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "co_return". \
Enable warning C4005 to find the forbidden define.
#endif // co_return

#if defined(co_yield) && _HAS_CXX20
#define co_yield EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "co_yield". \
Enable warning C4005 to find the forbidden define.
#endif // co_yield

#if defined(decltype)
#define decltype EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "decltype". \
Enable warning C4005 to find the forbidden define.
#endif // decltype

#if defined(default)
#define default EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "default". \
Enable warning C4005 to find the forbidden define.
#endif // default

#if defined(delete)
#define delete EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "delete". \
Enable warning C4005 to find the forbidden define.
#endif // delete

#if defined(do)
#define do EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "do". \
Enable warning C4005 to find the forbidden define.
#endif // do

#if defined(double)
#define double EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "double". \
Enable warning C4005 to find the forbidden define.
#endif // double

#if defined(dynamic_cast)
#define dynamic_cast EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "dynamic_cast". \
Enable warning C4005 to find the forbidden define.
#endif // dynamic_cast

#if defined(else)
#define else EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "else". \
Enable warning C4005 to find the forbidden define.
#endif // else

#if defined(enum)
#define enum EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "enum". \
Enable warning C4005 to find the forbidden define.
#endif // enum

#if defined(explicit)
#define explicit EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "explicit". \
Enable warning C4005 to find the forbidden define.
#endif // explicit

#if defined(export)
#define export EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "export". \
Enable warning C4005 to find the forbidden define.
#endif // export

#if defined(extern)
#define extern EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "extern". \
Enable warning C4005 to find the forbidden define.
#endif // extern

#if defined(false)
#define false EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "false". \
Enable warning C4005 to find the forbidden define.
#endif // false

#if defined(float)
#define float EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "float". \
Enable warning C4005 to find the forbidden define.
#endif // float

#if defined(for)
#define for EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "for". \
Enable warning C4005 to find the forbidden define.
#endif // for

#if defined(friend)
#define friend EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "friend". \
Enable warning C4005 to find the forbidden define.
#endif // friend

#if defined(goto)
#define goto EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "goto". \
Enable warning C4005 to find the forbidden define.
#endif // goto

#if defined(if)
#define if EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "if". \
Enable warning C4005 to find the forbidden define.
#endif // if

#if defined(inline)
#define inline EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "inline". \
Enable warning C4005 to find the forbidden define.
#endif // inline

#if defined(int)
#define int EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "int". \
Enable warning C4005 to find the forbidden define.
#endif // int

#if defined(long)
#define long EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "long". \
Enable warning C4005 to find the forbidden define.
#endif // long

#if defined(mutable)
#define mutable EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "mutable". \
Enable warning C4005 to find the forbidden define.
#endif // mutable

#if defined(namespace)
#define namespace EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "namespace". \
Enable warning C4005 to find the forbidden define.
#endif // namespace

#if defined(new) && defined(_ENFORCE_BAN_OF_MACRO_NEW)
#define new EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "new", though macroized new is supported on this \
implementation as a nonstandard extension. Enable warning C4005 to find the forbidden define, or re-enable the \
extension by removing _ENFORCE_BAN_OF_MACRO_NEW.
#endif // new

#if defined(noexcept)
#define noexcept EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "noexcept". \
Enable warning C4005 to find the forbidden define.
#endif // noexcept

#if defined(nullptr)
#define nullptr EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "nullptr". \
Enable warning C4005 to find the forbidden define.
#endif // nullptr

#if defined(operator)
#define operator EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "operator". \
Enable warning C4005 to find the forbidden define.
#endif // operator

#if defined(private)
#define private EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "private". \
Enable warning C4005 to find the forbidden define.
#endif // private

#if defined(protected)
#define protected EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "protected". \
Enable warning C4005 to find the forbidden define.
#endif // protected

#if defined(public)
#define public EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "public". \
Enable warning C4005 to find the forbidden define.
#endif // public

#if defined(register)
#define register EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "register". \
Enable warning C4005 to find the forbidden define.
#endif // register

#if defined(reinterpret_cast)
#define reinterpret_cast EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "reinterpret_cast". \
Enable warning C4005 to find the forbidden define.
#endif // reinterpret_cast

#if defined(requires) && _HAS_CXX20
#define requires EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "requires". \
Enable warning C4005 to find the forbidden define.
#endif // requires

#if defined(return)
#define return EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "return". \
Enable warning C4005 to find the forbidden define.
#endif // return

#if defined(short)
#define short EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "short". \
Enable warning C4005 to find the forbidden define.
#endif // short

#if defined(signed)
#define signed EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "signed". \
Enable warning C4005 to find the forbidden define.
#endif // signed

#if defined(sizeof)
#define sizeof EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "sizeof". \
Enable warning C4005 to find the forbidden define.
#endif // sizeof

#if defined(static)
#define static EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "static". \
Enable warning C4005 to find the forbidden define.
#endif // static

#if defined(static_assert)
#define static_assert EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "static_assert". \
Enable warning C4005 to find the forbidden define.
#endif // static_assert

#if defined(static_cast)
#define static_cast EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "static_cast". \
Enable warning C4005 to find the forbidden define.
#endif // static_cast

#if defined(struct)
#define struct EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "struct". \
Enable warning C4005 to find the forbidden define.
#endif // struct

#if defined(switch)
#define switch EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "switch". \
Enable warning C4005 to find the forbidden define.
#endif // switch

#if defined(template)
#define template EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "template". \
Enable warning C4005 to find the forbidden define.
#endif // template

#if defined(this)
#define this EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "this". \
Enable warning C4005 to find the forbidden define.
#endif // this

#if defined(thread_local)
#define thread_local EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "thread_local". \
Enable warning C4005 to find the forbidden define.
#endif // thread_local

#if defined(throw)
#define throw EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "throw". \
Enable warning C4005 to find the forbidden define.
#endif // throw

#if defined(true)
#define true EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "true". \
Enable warning C4005 to find the forbidden define.
#endif // true

#if defined(try)
#define try EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "try". \
Enable warning C4005 to find the forbidden define.
#endif // try

#if defined(typedef)
#define typedef EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "typedef". \
Enable warning C4005 to find the forbidden define.
#endif // typedef

#if defined(typeid)
#define typeid EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "typeid". \
Enable warning C4005 to find the forbidden define.
#endif // typeid

#if defined(typename)
#define typename EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "typename". \
Enable warning C4005 to find the forbidden define.
#endif // typename

#if defined(union)
#define union EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "union". \
Enable warning C4005 to find the forbidden define.
#endif // union

#if defined(unsigned)
#define unsigned EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "unsigned". \
Enable warning C4005 to find the forbidden define.
#endif // unsigned

#if defined(using)
#define using EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "using". \
Enable warning C4005 to find the forbidden define.
#endif // using

#if defined(virtual)
#define virtual EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "virtual". \
Enable warning C4005 to find the forbidden define.
#endif // virtual

#if defined(void)
#define void EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "void". \
Enable warning C4005 to find the forbidden define.
#endif // void

#if defined(volatile)
#define volatile EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "volatile". \
Enable warning C4005 to find the forbidden define.
#endif // volatile

#if defined(wchar_t)
#define wchar_t EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "wchar_t". \
Enable warning C4005 to find the forbidden define.
#endif // wchar_t

#if defined(while)
#define while EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "while". \
Enable warning C4005 to find the forbidden define.
#endif // while

// contextual keywords (a.k.a. "identifiers with special meaning"):
#if defined(final)
#define final EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the contextual keyword "final". \
Enable warning C4005 to find the forbidden define.
#endif // final

#if defined(import) && _HAS_CXX20
#define import EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the contextual keyword "import". \
Enable warning C4005 to find the forbidden define.
#endif // import

#if defined(module) && _HAS_CXX20
#define module EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the contextual keyword "module". \
Enable warning C4005 to find the forbidden define.
#endif // module

#if defined(override)
#define override EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the contextual keyword "override". \
Enable warning C4005 to find the forbidden define.
#endif // override

// attribute-tokens:
#if defined(carries_dependency)
#define carries_dependency EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the attribute-token "carries_dependency". \
Enable warning C4005 to find the forbidden define.
#endif // carries_dependency

#if defined(deprecated)
#define deprecated EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the attribute-token "deprecated". \
Enable warning C4005 to find the forbidden define.
#endif // deprecated

#if defined(fallthrough) && _HAS_CXX17
#define fallthrough EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the attribute-token "fallthrough". \
Enable warning C4005 to find the forbidden define.
#endif // fallthrough

// not checking "likely" because it is commonly defined as a function-like macro

#if defined(maybe_unused) && _HAS_CXX17
#define maybe_unused EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the attribute-token "maybe_unused". \
Enable warning C4005 to find the forbidden define.
#endif // maybe_unused

#if defined(nodiscard) // C++17 attribute-token, also enforced in C++14 mode
#define nodiscard EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the attribute-token "nodiscard". \
Enable warning C4005 to find the forbidden define.
#endif // nodiscard

#if defined(noreturn)
#define noreturn EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the attribute-token "noreturn". \
Enable warning C4005 to find the forbidden define.
#endif // noreturn

#if defined(no_unique_address) && _HAS_CXX20
#define no_unique_address EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the attribute-token "no_unique_address". \
Enable warning C4005 to find the forbidden define.
#endif // no_unique_address

// not checking "unlikely" because it is commonly defined as a function-like macro

#endif // !defined(_ALLOW_KEYWORD_MACROS) && !defined(__INTELLISENSE__)

#endif // _STL_COMPILER_PREPROCESSOR
#endif // _XKEYCHECK_H


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

#include<Core/Header/some_features.h>

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
#ifdef OTYPE_IS_DLLTYPE
#define _LFramework_Config_API_OClass			_LFramework_Config_API_Class	
#define _LFramework_Config_API_OStruct			_LFramework_Config_API_Struct
#define _LFramework_Config_API_OTClass			_LFramework_Config_API_TClass
#define _LFramework_Config_API_OTStruct			_LFramework_Config_API_TStruct
#else
#define _LFramework_Config_API_OClass			class 
#define _LFramework_Config_API_OStruct			struct
#define _LFramework_Config_API_OTClass			class 
#define _LFramework_Config_API_OTStruct			struct
#endif // !OTYPE_IS_DLLTYPE
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

#pragma region Kit

#define _LFK_API(name)	_LFramework_Kit_API_##name
#define _LFK_DEF(name)	_LFramework_Kit_API_##name##_Define

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

#pragma endregion

#pragma region SAL

#ifndef _In_
#define _In_
#endif // !_In_
#ifndef _Out_
#define _Out_
#endif // !_Out_

#pragma endregion

#pragma region Console

#pragma endregion

#endif // !__FILE_LF_CONFIG
