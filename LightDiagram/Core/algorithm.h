#pragma once

#ifndef __FILE_ALGORITHM
#define __FILE_ALGORITHM

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
}

#endif // !__FILE_ALGORITHM
