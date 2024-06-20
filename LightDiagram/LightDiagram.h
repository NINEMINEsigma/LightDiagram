//*
//  Copyright (c) 2024, liu bai, ninemine
//  All rights reserved.
//*

//*
//	_Source_DLL_EXPORT Defined is to export
//	_Source_DLL_IMPORT Defined is to import
//	Both no will be complate on local
//*

//*
//	__REF_BOOST Defined is to include boost headers
//	You need to use include_directories(boost directory) to put on those files
//	like: include_directories("C:\Boost") -> C:\Boost\boost\align.hpp ...
//	lib is also need install on Path youself
//*

#ifndef __FILE_LIGHTDIAGRAM

#define __FILE_LIGHTDIAGRAM

//*
//	Single Toolkit
//*

#include<Core/Header/beepkit.h>

//*
//	Header
//*

#include<Core/Header/some_features.h>
#include<Core/Header/LF_Config.h>
#include<Core/Header/LF_Type.h>
#include<Core/Header/anyclass.h>
#include<Core/Header/LF_Cache.h>
#include<Core/Header/LF_Exception.h>
//#include<Core/Header/LF_Container.h>

_LF_C_API(Class) ld_test
{
public:
	ld_test();
};

//#include<Core/Header/LF_Architecture.h>

//	Extension

#include<Extension/Header/KitSocket.h>

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
#include <boost/bind.hpp>
#include <boost/blank.hpp>
#include <boost/blank_fwd.hpp>
#include <boost/callable_traits.hpp>
#include <boost/call_traits.hpp>
#include <boost/cast.hpp>
#include <boost/cerrno.hpp>
#include <boost/charconv.hpp>
#include <boost/checked_delete.hpp>
#include <boost/chrono.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/circular_buffer_fwd.hpp>
#include <boost/cobalt.hpp>
#include <boost/compressed_pair.hpp>
#include <boost/compute.hpp>
#include <boost/concept_archetype.hpp>
#include <boost/concept_check.hpp>
#include <boost/config.hpp>
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
#include <boost/iterator.hpp>
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
#include <boost/mysql.hpp>
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
#include <boost/python.hpp>
#include <boost/qvm.hpp>
#include <boost/qvm_lite.hpp>
#include <boost/random.hpp>
#include <boost/range.hpp>
#include <boost/ratio.hpp>
#include <boost/rational.hpp>
#include <boost/redis.hpp>
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

#endif // !__FILE_LIGHTDIAGRAM