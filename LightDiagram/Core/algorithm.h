#pragma once

#ifndef __FILE_ALGORITHM
#define __FILE_ALGORITHM

#include<Core/LF_Config.h>

namespace ld
{
	template<template<typename> class _Container,typename _Ty>
	_Container<_Container<_Ty>> transposeVxV(const _Container<_Container<_Ty>>& from)
	{
		if (from.size() == 0)return{};
		_Container<_Container<_Ty>> result(from[0].size());
		for (size_t i = 0, e = from[0].size(); i < e; i++)
		{
			result[i] = std::vector<_Ty>(from.size());
		}
		for (size_t i = 0, e = from.size(); i < e; i++)
		{
			for (size_t j = 0, ej = from[i].size(); j < ej; j++)
			{
				result[j][i] = from[i][j];
			}
		}
		return result;
	}

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

	//dfs
	namespace algorithm
	{
#define __Check__Mapper(x,y) ((x)>=0&&(y)>=0&&(y)<mapper.size()&&(x)<mapper[(y)].size())
		template<typename _PosN, typename _Mapper, typename _Recorder, typename _Pr>
		void DFS_Matrix_4(const _PosN& x, const _PosN& y, _Mapper& mapper, _Recorder& record, _Pr pred)
		{
			auto&& current = mapper[y][x];
			record[y][x] = true;
			if (__Check__Mapper(x, y + 1) && record[y + 1][x] == false && pred(current, mapper[y + 1][x], 0, 1))
				DFS_Matrix_4(x, y + 1, mapper, record, pred);
			if (__Check__Mapper(x, y - 1) && record[y - 1][x] == false && pred(current, mapper[y - 1][x], 0, -1))
				DFS_Matrix_4(x, y - 1, mapper, record, pred);
			if (__Check__Mapper(x + 1, y) && record[y][x + 1] == false && pred(current, mapper[y][x + 1], 1, 0))
				DFS_Matrix_4(x + 1, y, mapper, record, pred);
			if (__Check__Mapper(x - 1, y) && record[y][x - 1] == false && pred(current, mapper[y][x - 1], -1, 0))
				DFS_Matrix_4(x - 1, y, mapper, record, pred);
		}
		template<typename _PosN, template<typename> class _Layer, typename _KeyTy, typename _Pr>
		_Layer<_Layer<bool>> Get_DFS_Matrix_4(const _PosN& x, const _PosN& y, _Layer<_Layer<_KeyTy>>& mapper, _Pr pred)
		{
			_Layer<_Layer<bool>> record(mapper.size(), _Layer<bool>(mapper.begin()->size(), false));
			DFS_Matrix_4<_PosN, _Layer<_Layer<_KeyTy>>, _Layer<_Layer<bool>>, _Pr>(x, y, mapper, record, pred);
			return record;
		}
		template<typename _PosN, typename _Mapper, typename _Recorder, typename _Pr>
		void rDFS_Matrix_4(const _PosN& x, const _PosN& y, _Mapper& mapper, _Recorder& record, _Pr pred)
		{
			auto&& current = mapper[y][x];
			record[y][x] = true;
			if (__Check__Mapper(x, y + 1) && record[y + 1][x] == false && pred(mapper[y + 1][x], current, 0, -1))
				rDFS_Matrix_4(x, y + 1, mapper, record, pred);
			if (__Check__Mapper(x, y - 1) && record[y - 1][x] == false && pred(mapper[y - 1][x], current, 0, 1))
				rDFS_Matrix_4(x, y - 1, mapper, record, pred);
			if (__Check__Mapper(x + 1, y) && record[y][x + 1] == false && pred(mapper[y][x + 1], current, -1, 0))
				rDFS_Matrix_4(x + 1, y, mapper, record, pred);
			if (__Check__Mapper(x - 1, y) && record[y][x - 1] == false && pred(mapper[y][x - 1], current, 1, 0))
				rDFS_Matrix_4(x - 1, y, mapper, record, pred);
		}
		template<typename _PosN, template<typename> class _Layer, typename _KeyTy, typename _Pr>
		_Layer<_Layer<bool>> Get_rDFS_Matrix_4(const _PosN& x, const _PosN& y, _Layer<_Layer<_KeyTy>>& mapper, _Pr pred)
		{
			_Layer<_Layer<bool>> record(mapper.size(), _Layer<bool>(mapper.begin()->size(), false));
			rDFS_Matrix_4<_PosN, _Layer<_Layer<_KeyTy>>, _Layer<_Layer<bool>>, _Pr>(x, y, mapper, record, pred);
			return record;
		}
#undef __Check__Mapper

		template<typename _PosN, template<typename> class _Layer, typename _KeyTy>
		_Layer<_Layer<bool>> flood_fill(const _PosN& x, const _PosN& y, _Layer<_Layer<_KeyTy>>& mapper, _KeyTy& setter, const std::function<bool(_KeyTy&, _KeyTy&, const _PosN&, const _PosN&)>& pred)
		{
			return Get_DFS_Matrix_4<_PosN,_Layer,_KeyTy, std::function<bool(_KeyTy&, _KeyTy&, const _PosN&, const _PosN&)>>
			(x, y, mapper, std::function([&pred,&setter](_KeyTy& current, _KeyTy& next, const _PosN& dx, const _PosN& dy)->bool
				{
					bool result = pred(current, next, dx, dy);
					current = setter;
					if (result)
						next = setter;
					return result;
				}));
		}
	}

	//bfs
	namespace algorithm
	{
#define __Check__Mapper(x,y) ((x)>=0&&(y)>=0&&(y)<mapper.size()&&(x)<mapper[(y)].size())
		template<typename _Quene, typename _Mapper, typename _Recorder, typename _Pr>
		void BFS_Matrix_4(_Quene& quene, _Mapper& mapper, _Recorder& record, _Pr pred)
		{
			while (quene.empty() == false)
			{
				_Quene next_layer;
				for (auto&& pos : quene)
				{
					auto x = get_left(pos), y = get_right(pos);
					auto& current = mapper[y][x];
					if (__Check__Mapper(x, y + 1) && record[y + 1][x] == 0 && pred(current, mapper[y + 1][x], 0, 1))
					{
						next_layer.insert(next_layer.end(), { x,y + 1 });
						record[y + 1][x] = record[y][x] + 1;
					}
					if (__Check__Mapper(x, y - 1) && record[y - 1][x] == 0 && pred(current, mapper[y - 1][x], 0, 1))
					{
						next_layer.insert(next_layer.end(), { x,y - 1 });
						record[y - 1][x] = record[y][x] + 1;
					}
					if (__Check__Mapper(x + 1, y) && record[y][x + 1] == 0 && pred(current, mapper[y][x + 1], 1, 0))
					{
						next_layer.insert(next_layer.end(), { x + 1,y });
						record[y][x + 1] = record[y][x] + 1;
					}
					if (__Check__Mapper(x - 1, y) && record[y][x - 1] == 0 && pred(current, mapper[y][x - 1], -1, 0))
					{
						next_layer.insert(next_layer.end(), { x - 1,y });
						record[y][x - 1] = record[y][x] + 1;
					}
				}
				quene.swap(next_layer);
			}
		}
		template<typename _Quene, template<typename> class _Layer, typename _KeyTy, typename _Pr, typename _RecordTy = int>
		_Layer<_Layer<_RecordTy>> Get_BFS_Matrix_4(_Quene& quene, _Layer<_Layer<_KeyTy>>& mapper, _Pr pred)
		{
			_Layer<_Layer<_RecordTy>> record(mapper.size(), _Layer<_RecordTy>(mapper.begin()->size(), 0));
			BFS_Matrix_4<_Quene, _Layer<_Layer<_KeyTy>>>(quene, mapper, record, pred);
			return record;
		}
#undef __Check__Mapper
	}
}

#endif // !__FILE_ALGORITHM
