#pragma once

#ifndef __FILE_ANY_GRAPH__
#define __FILE_ANY_GRAPH__

#include<Core/LF_RAII.h>

namespace ld
{
	template<typename T,size_t out_degree>
	_LF_C_API(TClass) any_binding_tree
		Symbol_Push public virtual binding_instance<any_binding_instance, T>
	{
	public:
		using tag = T;
		constexpr static size_t OD = out_degree;
		binding_instance<any_binding_instance, any_binding_tree> branch[out_degree];
	};
}

#endif // !__FILE_ANY_GRAPH__
