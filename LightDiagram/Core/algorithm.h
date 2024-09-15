#pragma once

#ifndef __FILE_ALGORITHM
#define __FILE_ALGORITHM

#include<Core/LF_Config.h>

namespace ld
{
	namespace algorithm
	{
		template<
			typename _First, typename _End, typename _CheakPred, typename _Opt
		>
		void InsituOperation(
			_First&& first,
			_End&& end,
			_CheakPred&& pred,
			_Opt&& _operator)
		{
			_First _first = first;
			_End _end = end;
			while (_first != _end)
			{
				if (pred(*_first))
				{
					_operator(first, end, _first, _end);
				}
				else
				{
					_first++;
				}
			}
		}

		template<
			typename _Ty, typename _CheakPred, typename _Opt
		>
		void InsituOperation(
			_Ty&& data,
			_CheakPred&& pred,
			_Opt&& _operator)
		{
			InsituOperation(data.begin(), data.end(), std::forward<_CheakPred>(pred), std::forward<_Opt>(_operator));
		}
	}

	template<template<typename, typename> class _Pair, typename _Ty>
	auto& get_left(_Pair<_Ty, _Ty>& _pair)
	{
		return _pair.first;
	}
	template<template<typename, typename> class _Pair, typename _Ty>
	auto& get_right(_Pair<_Ty, _Ty>& _pair)
	{
		return _pair.second;
	}
	template<class _Cont>
	auto& get_left(_Cont& _data)
	{
		return *std::min_element(_data.begin(), _data.end());
	}
	template<class _Cont>
	auto& get_right(_Cont& _data)
	{
		return *std::max_element(_data.begin(), _data.end());
	}

	template<
		class _Container
	>
	void MergeIntervals(_Container& intervals)
	{
		using iter_unwap = decltype(intervals.front());
		using iter_unwap_lv = std::add_lvalue_reference_t<iter_unwap>;
		std::sort(intervals.begin(), intervals.end(), []( 
			iter_unwap_lv _left, iter_unwap_lv _right)
			{
				return get_left(_left) < get_left(_right);
			});
		std::remove_reference_t<_Container> result;
		for (auto&& item : intervals)
		{
			if (result.empty())
				result.insert(result.begin(), item);
			else if (get_right(result.back()) < get_left(item))
				result.insert(result.end(), item);
			else
				get_right(result.back()) = std::max(get_right(result.back()), get_right(item));
		}
		intervals = std::move(result);
	}
}

#endif // !__FILE_ALGORITHM
