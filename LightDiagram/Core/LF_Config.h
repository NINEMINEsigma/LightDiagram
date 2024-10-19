﻿#ifndef __FILE_LF_CONFIG

#define __FILE_LF_CONFIG

#pragma region config defined

#ifndef is_monitor_the_constructor_of_anyclass

#if defined(_DEBUG)
#ifdef not_monitor_the_constructor_of_anyclass
#define is_monitor_the_constructor_of_anyclass false
#else
#define is_monitor_the_constructor_of_anyclass true
#endif // !not_monitor_the_constructor_of_anyclass
#else
#define is_monitor_the_constructor_of_anyclass false
#endif // _DEBUG

#endif // !is_monitor_the_constructor_of_anyclass

#pragma warning(disable : 4267)
#pragma warning(disable : 4244)

#pragma endregion

//release:	std::type_info to global namespace
//release:	std::addressof to global namespace

#pragma region easyx
#if defined(__REF_EASYX)
#include <easyx.h>
#include <graphics.h>
#endif
#pragma endregion

#pragma region Boost

#ifdef __REF_BOOST

#include <boost/align.hpp>
#include <boost/aligned_storage.hpp>
#include <boost/any.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/assign.hpp>
#include <boost/atomic.hpp>
#include <boost/beast.hpp>
#include <boost/bimap.hpp>
#include <boost/bind/bind.hpp>
using namespace boost::placeholders;
#include <boost/blank.hpp>
#include <boost/blank_fwd.hpp>
#include <boost/callable_traits.hpp>
#include <boost/call_traits.hpp>
#include <boost/cast.hpp>
#include <boost/cerrno.hpp>
//#include <boost/charconv.hpp>
#include <boost/checked_delete.hpp>
#include <boost/chrono.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/circular_buffer_fwd.hpp>
//#include <boost/cobalt.hpp>
#include <boost/compressed_pair.hpp>
#ifdef CL_PLATFORM_VERSION
#include <boost/compute.hpp>
#endif
#include <boost/concept_archetype.hpp>
#include <boost/concept_check.hpp>
#ifdef MPI_MAX_PROCESSOR_NAME
#include <boost/config.hpp>
#endif
#include <boost/contract.hpp>
#include <boost/contract_macro.hpp>
#include <boost/convert.hpp>
#include <boost/crc.hpp>
#include <boost/cregex.hpp>
#include <boost/cstdfloat.hpp>
#include <boost/cstdint.hpp>
#include <boost/cstdlib.hpp>
#include <boost/current_function.hpp>
#include <boost/cxx11_char_types.hpp>
#include <boost/date_time.hpp>
#include <boost/describe.hpp>
#include <boost/dll.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/dynamic_bitset_fwd.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/endian.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/flyweight.hpp>
#include <boost/foreach.hpp>
#include <boost/foreach_fwd.hpp>
#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/functional.hpp>
#include <boost/function_equal.hpp>
#include <boost/function_output_iterator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/geometry.hpp>
#include <boost/get_pointer.hpp>
#include <boost/gil.hpp>
#include <boost/hana.hpp>
#include <boost/histogram.hpp>
#include <boost/hof.hpp>
#include <boost/implicit_cast.hpp>
#include <boost/indirect_reference.hpp>
#include <boost/integer.hpp>
#include <boost/integer_fwd.hpp>
#include <boost/integer_traits.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/io_fwd.hpp>
#include <boost/is_placeholder.hpp>
#include <boost/iterator_adaptors.hpp>
#include <boost/json.hpp>
#include <boost/lambda2.hpp>
#include <boost/leaf.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/limits.hpp>
#include <boost/locale.hpp>
#include <boost/local_function.hpp>
#include <boost/make_default.hpp>
#include <boost/make_shared.hpp>
#include <boost/make_unique.hpp>
#include <boost/math_fwd.hpp>
#include <boost/memory_order.hpp>
#include <boost/mem_fn.hpp>
#include <boost/metaparse.hpp>
#include <boost/mp11.hpp>
#include <boost/mpi.hpp>
#include <boost/multi_array.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index_container_fwd.hpp>
#ifdef __REF_MYSQL
#include <boost/mysql.hpp>
#endif
#include <boost/next_prior.hpp>
#include <boost/noncopyable.hpp>
#include <boost/nondet_random.hpp>
#include <boost/none.hpp>
#include <boost/none_t.hpp>
#include <boost/non_type.hpp>
#include <boost/operators.hpp>
#include <boost/operators_v1.hpp>
#include <boost/optional.hpp>
#include <boost/outcome.hpp>
#include <boost/parameter.hpp>
#include <boost/pfr.hpp>
#include <boost/phoenix.hpp>
#include <boost/pointee.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/pointer_to_other.hpp>
#include <boost/polymorphic_cast.hpp>
#include <boost/polymorphic_pointer_cast.hpp>
#include <boost/predef.h>
#include <boost/preprocessor.hpp>
#include <boost/process.hpp>
#include <boost/program_options.hpp>
#include <boost/progress.hpp>
#ifdef __REF_PYTHON
#include <boost/python.hpp>
#endif
#include <boost/qvm.hpp>
#include <boost/qvm_lite.hpp>
#include <boost/random.hpp>
#include <boost/range.hpp>
#include <boost/ratio.hpp>
#include <boost/rational.hpp>
#include <boost/ref.hpp>
#include <boost/regex.h>
#include <boost/regex.hpp>
#include <boost/regex_fwd.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scope_exit.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_container_iterator.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/spirit.hpp>
#include <boost/stacktrace.hpp>
#include <boost/static_assert.hpp>
#include <boost/static_string.hpp>
#include <boost/swap.hpp>
#include <boost/system.hpp>
#include <boost/thread.hpp>
#include <boost/throw_exception.hpp>
#include <boost/timer.hpp>
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>
#include <boost/token_iterator.hpp>
#include <boost/type.hpp>
#include <boost/type_index.hpp>
#include <boost/type_traits.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/url.hpp>
#include <boost/utility.hpp>
#include <boost/variant.hpp>
#include <boost/variant2.hpp>
#include <boost/version.hpp>
#include <boost/visit_each.hpp>
#include <boost/wave.hpp>
#include <boost/weak_ptr.hpp>

#endif // __REF_BOOST

#ifdef __REF_BOOST_MATH

#endif // __REF_BOOST_MATH


#pragma endregion

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

enum class platform_current
{
	linux_on_windows_platform,windows_platform,linux_platform
};

#define NOMINMAX

#if defined(_LINUX_ON_WINDOW_)
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <io.h>
struct platform_indicator
{
	using tag = void;
	constexpr static bool value = false;
	constexpr static const char* name = "linux on windows";
	constexpr static platform_current mode = platform_current::linux_on_windows_platform;
	constexpr static bool is_mscv = false;
};
#endif

#if defined(_WINDOW_)
#include <Windows.h>
#include <io.h>
#include <wingdi.h>
#include <gdiplus.h>
struct platform_indicator
{
	using tag = void;
	constexpr static bool value = false;
	constexpr static const char* name = "windows";
	constexpr static platform_current mode = platform_current::windows_platform;
#ifdef _MSC_VER
	constexpr static bool is_mscv = true;
#else
	constexpr static bool is_mscv = false;
#endif // _MSC_VER
};
#endif

#if defined(_LINUX_)
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <netinet/tcp.h>
#include <dirent.h>
#define _USE_DEFINED_CALL_
struct platform_indicator
{
	using tag = void;
	constexpr static bool value = false;
	constexpr static const char* name = "linux";
	constexpr static platform_current mode = platform_current::linux_platform;
	constexpr static bool is_mscv = false;
};
#endif

using type_info = std::type_info;
using std::addressof;

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

#define _allocator_ret_ __declspec(allocator)

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

//use define : _USE_DEFINED_CALL_
#if defined(_USE_DEFINED_CALL_)&&!defined(_USE_DEFINED_CALL_DEFINED)//&&!defined(_MSC_VER)

#define _USE_DEFINED_CALL_DEFINED
#define __stdcall
#define _stdcall
#define __cdecl
#define _cdecl
#define __fastcall
#define _fastcall
#define __thiscall
#define abstract =0

#endif // _USE_DEFINED_CALL_

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
#define Symbol_Push :
#define Symbol_Link ,
#define Symbol_Endl

//*
//  This allows you to declare a field's Property Binder
//  and allow it to use pointers and dereferences for assignment and exgression
//*
#define _LFramework_API_PropertyBindToFieldObj(name)    \
void set_##name(decltype(name)* value){name = *value;}  \
decltype(name)* get_##name() const{return &name;}

//*
//  This allows you to declare a field's Property Binder
//  and allow the field itself to be a pointer type, which is assigned and passed out directly to its type
//*
#define _LFramework_API_PropertyBindToFieldPtr(name)    \
void set_##name(decltype(name) value){name = value;}    \
decltype(name) get_##name() const{return name;}

//*
//  This allows you to declare a field's Property Binder, it is a ref-type
//*
#define _LFramework_API_PropertyBindToFieldRef(name)    \
void set_##name(decltype(name)& value){name = value;}   \
void set_##name(decltype(name)&& value){name = value;}	\
decltype(name)& get_##name(){return name;}

#define _LF_SL_(x)		#x
#define _LF_Strline_(x) _LF_SL_(x)
#define _STR_LINE_		_LF_Strline_(__LINE__)

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

namespace ld
{
	template<typename T>
	const T& Max(const T& first, const T& second)
	{
		if (first > second)
			return first;
		else
			return second;
	}
	template<typename T, typename ...Args>
	const T& Max(const T& first, const T& second, const Args&... args)
	{
		if (first > second)
			return Max(first, args...);
		else
			return Max(second, args...);
	}
}

template<typename T = std::string, typename _Is>
T& next(_Is& s)
{
	static T item;
	s >> item;
	return item;
}
template<typename _Is, size_t _BufferSize = 2048>
std::string next_line(_Is& s)
{
	static char buffer[_BufferSize];
	s.getline(buffer, _BufferSize);
	return buffer;
}
template<class _Mapper,typename _Is>
decltype(auto) next_group(_Mapper& mapper, _Is& s)
{
	for (auto&& i : mapper)
	{
		if (static_cast<bool>(s >> i) == false)
			return false;
	}
	return static_cast<bool>(s);
}
template<class _Mapper,  typename _Is>
decltype(auto) next_matrix(_Mapper& mapper, _Is& s)
{
	for (auto&& i : mapper)
	{
		for (auto&& j : i)
			if (static_cast<bool>(s >> j) == false)
				return false;
	}
	return static_cast<bool>(s);
}

#pragma endregion

#pragma region TempRef

template<typename Type, Type Index> _LF_C_API(Class) ConstexprMode
{
public:
	virtual ~ConstexprMode() {}
	using tag = Type;
	constexpr static Type value = Index;
	constexpr operator Type()
	{
		return value;
	}
};

template<typename Type, size_t Slot> _LF_C_API(Class) SlotMode
{
public:
	using tag = Type;
	constexpr static size_t value = Slot;
};

template<size_t size>
using ConstexprCount = ConstexprMode<size_t, size>;

#pragma endregion


#pragma endregion

#pragma region SAL

/*---------------------------------------------------------------------------*/
/* SAL ANNOTATIONS                                                           */
/*---------------------------------------------------------------------------*/
/*
 * Define SAL annotations if they aren't defined yet.
 */
#ifndef _Success_
#define _Success_( x )
#endif
#ifndef _Notref_
#define _Notref_
#endif
#ifndef _When_
#define _When_( x, y )
#endif
#ifndef _Pre_valid_
#define _Pre_valid_
#endif
#ifndef _Pre_opt_valid_
#define _Pre_opt_valid_
#endif
#ifndef _Post_invalid_
#define _Post_invalid_
#endif
#ifndef _In_
#define _In_
#endif
#ifndef _In_z_
#define _In_z_
#endif
#ifndef _In_opt_
#define _In_opt_
#endif
#ifndef _In_range_
#define _In_range_( x, y )
#endif
#ifndef _In_reads_
#define _In_reads_( x )
#endif
#ifndef _In_reads_z_
#define _In_reads_z_( x )
#endif
#ifndef _In_reads_opt_
#define _In_reads_opt_( x )
#endif
#ifndef _In_reads_bytes_opt_
#define _In_reads_bytes_opt_( x )
#endif
#ifndef _Out_
#define _Out_
#endif
#ifndef _Out_opt_
#define _Out_opt_
#endif
#ifndef _Out_writes_
#define _Out_writes_( x )
#endif
#ifndef _Out_writes_z_
#define _Out_writes_z_( x )
#endif
#ifndef _Out_writes_opt_
#define _Out_writes_opt_( x )
#endif
#ifndef _Out_writes_to_opt_
#define _Out_writes_to_opt_( x, y )
#endif
#ifndef _Out_writes_bytes_opt_
#define _Out_writes_bytes_opt_( x )
#endif
#ifndef _Inout_
#define _Inout_
#endif
#ifndef _Inout_opt_
#define _Inout_opt_
#endif
#ifndef _Inout_updates_opt_
#define _Inout_updates_opt_( x )
#endif
#ifndef _Deref_in_range_
#define _Deref_in_range_( x, y )
#endif
#ifndef _Deref_out_range_
#define _Deref_out_range_( x, y )
#endif
#ifndef _Pre_satisfies_
#define _Pre_satisfies_( x )
#endif
#ifndef _Post_satisfies_
#define _Post_satisfies_( x )
#endif
#ifndef _Post_equal_to_
#define _Post_equal_to_( x )
#endif

#pragma endregion

#pragma region Console

#pragma endregion

#ifdef NULL
#undef NULL
#define NULL nullptr
#endif // NULL

#ifdef Null
#undef Null
#define Null nullptr
#endif // NULL

#pragma region string wstring

#include <locale>
#include <codecvt>

namespace std
{
	// convert wstring to string 
	inline std::string to_string(const std::wstring& input)
	{
#if defined(_LINUX_ON_WINDOW_)||defined(_WINDOW_)
		DWORD dBufSize = WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, NULL, 0, NULL, FALSE);
		char* dBuf = new char[dBufSize];
		memset(dBuf, 0, dBufSize);
		WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, dBuf, dBufSize, NULL, FALSE);
		std::string result(dBuf);
		delete[] dBuf;
		return result;
#else
		//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(input);
#endif
	}
	inline std::string& to_string(std::string& str)
	{
		return str;
	}
	inline std::string to_string(const std::string& str)
	{
		return str;
	}

	// convert string to wstring
	inline std::wstring to_wstring(const std::string& input)
	{
#if defined(_LINUX_ON_WINDOW_)||defined(_WINDOW_)
		DWORD dBufSize = MultiByteToWideChar(CP_ACP, 0, input.c_str(), (int)input.size(), NULL, 0);
		wchar_t* dBuf = new wchar_t[dBufSize];
		wmemset(dBuf, 0, dBufSize);
		MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, dBuf, dBufSize);
		std::wstring result(dBuf);
		delete[] dBuf;
		return result;
#else
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(input);
#endif 
	}
	inline std::string back_to_string(const char* input)
	{
		return to_string(to_wstring(input));
	}

	inline std::wstring& to_wstring(std::wstring& str)
	{
		return str;
	}
	inline std::wstring to_string(std::wstring& str)
	{
		return str;
	}
}


template<typename T> constexpr bool enable_to_string =
std::is_arithmetic_v<T>
|| std::is_same_v< std::remove_cv_t<T>, std::string>
|| std::is_same_v< std::remove_cv_t<T>, std::wstring>
|| std::is_same_v< T, const char*>
|| std::is_same_v< T, char*>;

inline bool isGBK(unsigned char* data, int len) 
{
	int i = 0;
	while (i < len) 
	{
		if (data[i] <= 0x7f) {
			//编码小于等于127,只有一个字节的编码，兼容ASCII
			i++;
			continue;
		}
		else 
		{
			//大于127的使用双字节编码
			if (data[i] >= 0x81 &&
				data[i] <= 0xfe &&
				data[i + 1] >= 0x40 &&
				data[i + 1] <= 0xfe &&
				data[i + 1] != 0xf7)
			{
				i += 2;
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

template<typename _ReTy>
inline auto to_value(const std::string& str)
{
	if constexpr (std::is_floating_point_v<_ReTy>)
		return static_cast<_ReTy>(std::atof(str.c_str()));
	else if constexpr (std::is_integral_v<_ReTy>)
		return static_cast<_ReTy>(std::atoi(str.c_str()));
	else if constexpr (std::is_same_v<const char*, _ReTy>)
		return str.c_str();
	else if constexpr (std::is_same_v<std::string, _ReTy>)
		return str;
	else
	{
		static_assert(std::is_same_v<_ReTy, void > == true, "not support for this type");
		return;
	}
}

template<typename _Str, typename _CharFirst>
_Str trim(const _Str& str, _CharFirst ch)
{
	size_t size = str.size();
	if (size == 0)
		return _Str();
	bool start = str.front() == ch, last = str.back() == ch;
	if (size == 1)
		return start ? str : _Str();
	if (start == false && last == false)
		return str;
	size_t offset = 
		start 
		? (std::distance(str.cbegin(), std::find_if_not(str.cbegin(), str.cend(), [ch](const _CharFirst& _c) {return ch == _c; }))) 
		: 0;
	size_t roffset =
		last 
		? (std::distance(str.crbegin(), std::find_if_not(str.crbegin(), str.crend(), [ch](const _CharFirst& _c) {return ch == _c; }))) 
		: (size - offset);
	return str.substr(offset, size - offset - roffset);
}

#pragma endregion

#pragma region Kit


#pragma pack (1)
struct tagBITMAPFILEHEADER_OnLF 
{
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
};
typedef _LF_C_API(OStruct) tagBITMAPFILE
{
	using Header = tagBITMAPFILEHEADER_OnLF;
	Header BitmapHeader;
	using Info = BITMAPINFOHEADER;
	Info BitmapInfoHeader;
	using Palette = PALETTEENTRY;
	using PaletteBuffer = Palette*;
	PaletteBuffer BitMapPalette;
	size_t PaletteSize;
	using Color = UCHAR;
	using ColorBuffer = Color*;
	ColorBuffer BitMapBuffer;
} BITMAP_FILE;
#pragma pack()
template<typename _T>
_T Clamp01(const _T& t)
{
	if (t > 1)return 1;
	else if (t < 0)return 0;
	else return t;
}

template<typename _T>
_T Clamp0E(const _T& t, const _T& max)
{
	if (t > max)return 1;
	else if (t < 0)return 0;
	else return t;
}

template<typename _T>
_T Clamp(const _T& t, const _T& min, const _T& max)
{
	if (t > max)return 1;
	else if (t < min)return 0;
	else return t;
}

#pragma endregion

#pragma region Kit

#define sync_with_stdio_false(name)			\
auto name = []()							\
{											\
	std::cin.tie(0);						\
	std::cout.tie(0);						\
	std::ios::sync_with_stdio(false);		\
	return 0;								\
}											\

#ifndef __init
#define __init(member) member(member)
#endif // !__init


#pragma endregion

#pragma region Kit

namespace ld
{
	inline std::new_handler set_new_bad_catch(std::new_handler handler)
	{
		return std::set_new_handler(handler);
	}
	inline std::new_handler get_new_bad_catch()
	{
		return std::get_new_handler();
	}
}

#pragma endregion

#pragma region Kit

#if _HAS_CXX20
#define is_constant_env() std::is_constant_evaluated()
#else
constexpr bool is_constant_env()
{
	return false;
}
#endif

constexpr bool is_clang_env()
{
#ifdef __clang__
	return true;
#else
	return false;
#endif // __clang__
}

#pragma endregion

#pragma region Kit

_LF_C_API(OClass) alloc_default_traits
{
public:
	__declspec(allocator) static _CONSTEXPR20 void* _Allocate(const size_t _Bytes)
	{
		return ::operator new(_Bytes);
	}

#ifdef __cpp_aligned_new
	__declspec(allocator) static _CONSTEXPR20 void* _Allocate_aligned(const size_t _Bytes, const size_t _Align)
	{
		if (is_constant_env() && is_clang_env())
		{
			return ::operator new(_Bytes);
		}
		else
		{
			return ::operator new(_Bytes, std::align_val_t{ _Align });
		}
	}
#endif // defined(__cpp_aligned_new)
};

#pragma endregion


#endif // !__FILE_LF_CONFIG
