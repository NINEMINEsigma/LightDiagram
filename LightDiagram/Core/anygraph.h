#pragma once

#ifndef __FILE_ANY_GRAPH__
#define __FILE_ANY_GRAPH__

#include<Core/LF_RAII.h>

namespace ld
{
	namespace graph
	{
		template<typename T, size_t out_degree>
		_LF_C_API(TClass) any_binding_tree
			Symbol_Push public any_class Symbol_Endl
		{
		public:
			using tag = T;
			constexpr static size_t OD = out_degree;
		private:
			binding_instance<any_binding_tree> branch[out_degree];
			tag value_instance;
		public:
			void init_class(any_binding_instance* forward)
			{
				for (auto&& item : branch)
				{
					if (item.is_init())continue;
					item.init_forward(forward);
				}
			}

			using _Forward = any_binding_instance;
			// build up with init value
			any_binding_tree(tag&& value) : value_instance(std::move(value)) {}
			any_binding_tree(tag& value) : value_instance(value) {}
			// build up with move
			any_binding_tree(any_binding_tree& from) noexcept : value_instance(from.value_instance) {}
			any_binding_tree(any_binding_tree&& from) noexcept : value_instance(std::move(from.value_instance)) {}
			virtual ~any_binding_tree() {}

			operator tag& ()
			{
				return this->value_instance;
			}
			tag& value()
			{
				return this->value_instance;
			}
			template<typename _Val>
			_Val value() const
			{
				return static_cast<_Val>(this->get_ref());
			}

			any_binding_tree& operator=(any_binding_tree& from) noexcept
			{
				value_instance = from.value_instance;
				for (size_t i = 0; i < OD; i++)
				{
					branch[i] = from.branch[i];
				}
				return *this;
			}
			any_binding_tree& operator=(any_binding_tree&& from) noexcept
			{
				value_instance = std::move(from.value_instance);
				for (size_t i = 0; i < OD; i++)
				{
					branch[i] = std::move(from.branch[i]);
				}
				return *this;
			}
			any_binding_tree operator=(tag& val)
			{
				value_instance = val;
				return *this;
			}
			any_binding_tree operator=(tag&& val)
			{
				value_instance = std::move(val);
				return *this;
			}

		private:
		public:
			virtual std::string SymbolName() const override
			{
				return std::to_string(out_degree) + "-tree<" + typeid(T).name() + ">";
			}
			virtual std::string ToString() const override
			{
				if constexpr (if_func_exist(ToString) < tag, std::string() > )
				{
					return this->value_instance.ToString();
				}
				else if constexpr (enable_to_string<tag>)
				{
					return std::to_string(this->value_instance);
				}
				else
				{
					return this->GetType().name();
				}
			}
			decltype(auto) at(size_t index) 
			{
				if (index >= out_degree)
					ThrowLDException("index is overflow");
				return branch[index];
			}
			decltype(auto) operator[](size_t index) 
			{
				return branch[index % out_degree];
			}
		};

		template<size_t index, typename T, size_t _OD>
		decltype(auto) bounding(binding_instance<any_binding_tree<T, _OD>>& iter)
		{
			static_assert(index < _OD, "index cannt larger than _OD(out degree)");
			auto* current = &iter;
			while ((*current)->at(index).empty() == false)
			{
				current = &((*current)->at(index));
			}
			return *current;
		}
		template<size_t index, typename T, size_t _OD>
		decltype(auto) bounding_pr(binding_instance<any_binding_tree<T, _OD>>& iter)
		{
			static_assert(index < _OD, "index cannt larger than _OD(out degree)");
			if (iter.empty() || iter->at(index).empty())
			{
				ThrowLDException("index is overflow");
			}
			else
			{
				auto* current = &iter;
				while ((*current)->at(index)->at(index).empty() == false)
				{
					current = &((*current)->at(index));
				}
				return *current;
			}
		}
		template<size_t index, typename T, size_t _OD>
		decltype(auto) iter_at(binding_instance<any_binding_tree<T, _OD>>& iter, size_t _index)
		{
			auto* current = &iter;
			while (_index--)
			{
				if (current->empty())
					ThrowLDException("index is overflow");
				current = &((*current)->at(index));
			}
			return *current;
		}

#pragma region linear

		template<typename T>
		using stack_iter = any_binding_tree<T, 1>;
		constexpr static size_t stack_next = 0;
		template<typename T, typename...Args>
		decltype(auto) link(binding_instance<stack_iter<T>>& iter, Args&&... args)
		{
			return binding(iter->at(stack_next), iter, args...);
		}
		template<typename T>
		decltype(auto) back(binding_instance<stack_iter<T>>& iter)
		{
			return bounding<stack_next>(iter);
		}
		template<typename T>
		decltype(auto) back_pr(binding_instance<stack_iter<T>>& iter)
		{
			return bounding_pr<stack_next>(iter);
		}
		template<typename T, typename...Args>
		decltype(auto) push(binding_instance<stack_iter<T>>& iter, Args&&...args)
		{
			return link(back(iter), args...);
		}
		template<typename T, bool is_move = true>
		decltype(auto) pop(binding_instance<stack_iter<T>>& iter)
		{
			if (iter.empty())
				ThrowLDException("index is overflow");
			if (iter->at(stack_next).empty())
			{
				if constexpr (is_move)
				{
					auto&& result = std::move(iter->value());
					iter = nullptr;
					return std::move(result);
				}
				else
				{
					auto result = iter->value();
					iter = nullptr;
					return result;
				}
			}
			else
			{
				auto& pr = back_pr(iter);
				if constexpr (is_move)
				{
					auto&& result = std::move(pr->at(stack_next)->value());
					pr->at(stack_next) = nullptr;
					return std::move(result);
				}
				else
				{
					auto result = pr->at(stack_next)->value();
					pr->at(stack_next) = nullptr;
					return result;
				}
			}
		}

		template<typename T>
		using linear_iter = any_binding_tree<T, 2>;
		constexpr static size_t linear_front = 0;
		constexpr static size_t linear_back = 1;
		template<typename T, typename...Args>
		decltype(auto) link(binding_instance<linear_iter<T>>& iter, Args&&... args)
		{
			auto& back = binding(iter.get_ref().at(linear_back), iter, args...);
			binding(back.get_ref().at(linear_front), back, iter);
			return back;
		}
		template<typename T, typename...Args>
		decltype(auto) rlink(binding_instance<linear_iter<T>>& iter, Args&&... args)
		{
			auto& back = binding(iter->at(linear_front), iter, args...);
			binding(back->at(linear_back), back, iter);
			return back;
		}
		template<typename T>
		decltype(auto) back(binding_instance<linear_iter<T>>& iter)
		{
			return bounding<linear_back>(iter);
		}
		template<typename T>
		decltype(auto) front(binding_instance<linear_iter<T>>& iter)
		{
			return bounding<linear_front>(iter);
		}
		template<typename T>
		decltype(auto) back_pr(binding_instance<linear_iter<T>>& iter)
		{
			return bounding_pr<linear_back>(iter);
		}
		template<typename T>
		decltype(auto) front_pr(binding_instance<linear_iter<T>>& iter)
		{
			return bounding_pr<linear_front>(iter);
		}
		template<typename T, typename...Args>
		decltype(auto) push_back(binding_instance<linear_iter<T>>& iter, Args&&...args)
		{
			return link(back(iter), args...);
		}
		template<typename T, typename...Args>
		decltype(auto) push_front(binding_instance<linear_iter<T>>& iter, Args&&...args)
		{
			return rlink(front(iter), args...);
		}
		template<typename T, bool is_move = true>
		decltype(auto) pop_back(binding_instance<linear_iter<T>>& iter)
		{
			if (iter.empty())
				ThrowLDException("index is overflow");
			if (iter->at(linear_back).empty())
			{
				if constexpr (is_move)
				{
					auto&& result = std::move(iter->value());
					iter = nullptr;
					return std::move(result);
				}
				else
				{
					auto result = iter->value();
					iter = nullptr;
					return result;
				}
			}
			else
			{
				auto& pr = back_pr(iter);
				if constexpr (is_move)
				{
					auto&& result = std::move(pr->at(linear_back)->value());
					pr->at(linear_back) = nullptr;
					return std::move(result);
				}
				else
				{
					auto result = pr->at(linear_back)->value();
					pr->at(linear_back) = nullptr;
					return result;
				}
			}
		}
		template<typename T, bool is_move = true>
		decltype(auto) pop_front(binding_instance<linear_iter<T>>& iter)
		{
			if (iter.empty())
				ThrowLDException("index is overflow");
			if (iter->at(linear_front).empty())
			{
				if constexpr (is_move)
				{
					auto&& result = std::move(iter->value());
					iter = nullptr;
					return std::move(result);
				}
				else
				{
					auto result = iter->value();
					iter = nullptr;
					return result;
				}
			}
			else
			{
				auto& pr = front_pr(iter);
				if constexpr (is_move)
				{
					auto&& result = std::move(pr->at(linear_front)->value());
					pr->at(linear_front) = nullptr;
					return std::move(result);
				}
				else
				{
					auto result = pr->at(linear_front)->value();
					pr->at(linear_front) = nullptr;
					return result;
				}
			}
		}

		template<typename T>
		using vector_iter = any_binding_tree<T, 2>;
		constexpr static size_t vector_begin = 0;
		constexpr static size_t vector_back = 1;
		template<typename T>
		decltype(auto) vecbegin(binding_instance<vector_iter<T>>& iter)
		{
			if (iter.empty())return iter;
			if (iter->at(vector_begin).empty())return iter;
			return iter->at(vector_begin);
		}
		template<typename T>
		decltype(auto) vecback(binding_instance<vector_iter<T>>& iter)
		{
			return bounding<vector_back>(iter);
		}
		template<typename T, typename...Args>
		decltype(auto) vecinsert(binding_instance<vector_iter<T>>& iter, Args&&...args)
		{
			if (iter.empty())
			{
				iter->value() = T{args...};
				return iter;
			}
			else if (iter->at(vector_back).empty())
				return link(iter, args...);
			else
			{
				auto* ptr = new vector_iter<T>(args...);
				ptr->at(vector_back) = iter->at(vector_back);
				ptr->at(vector_begin) = vecbegin(iter);
				return binding(iter->at(vector_back), ptr);
			}

		}
		template<typename T, typename Right>
		decltype(auto) vecinsert(binding_instance<vector_iter<T>>& iter, Right&& right)
		{
			if (iter.empty())
			{
				iter.get_ref() = std::forward<Right>(right);
				return iter;
			}
			else if (iter->at(vector_back).empty())
				return link(iter, std::forward<Right>(right));
			else
			{
				auto* ptr = new vector_iter<T>(std::forward<Right>(right));
				ptr->at(vector_back) = iter->at(vector_back);
				ptr->at(vector_begin) = vecbegin(iter);
				return binding(iter->at(vector_back), ptr);
			}

		}
		template<typename T, typename...Args>
		decltype(auto) vecpush(binding_instance<vector_iter<T>>& iter, Args&&...args)
		{
			return vecinsert(vecback(iter), args...);
		}
		template<typename T>
		decltype(auto) vecback_pr(binding_instance<linear_iter<T>>& iter)
		{
			return bounding_pr<vector_back>(iter);
		}
		template<typename T, bool is_move = true>
		decltype(auto) vecpop(binding_instance<linear_iter<T>>& iter)
		{
			if (iter.empty())
				ThrowLDException("index is overflow");
			if (iter->at(vector_back).empty())
			{
				if constexpr (is_move)
				{
					auto&& result = std::move(iter->value());
					iter = nullptr;
					return std::move(result);
				}
				else
				{
					auto result = iter->value();
					iter = nullptr;
					return result;
				}
			}
			else
			{
				auto& pr = vecback_pr(iter);
				if constexpr (is_move)
				{
					auto&& result = std::move(pr->at(vector_back)->value());
					pr->at(vector_back) = nullptr;
					return std::move(result);
				}
				else
				{
					auto result = pr->at(vector_back)->value();
					pr->at(vector_back) = nullptr;
					return result;
				}
			}
		}
		template<typename T>
		decltype(auto) vec_at(binding_instance<vector_iter<T>>& iter, size_t index)
		{
			return iter_at<vector_back>(iter, index);
		}


#pragma endregion


	}
}

#endif // !__FILE_ANY_GRAPH__
