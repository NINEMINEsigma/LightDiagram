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
			binding_instance<any_binding_instance, any_binding_tree> branch[out_degree];
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


	#define ptr_array_at_index\
			inline decltype(auto) at(size_t index)\
			{\
				if (index >= out_degree)\
					ThrowLDException("index is overflow");\
				return branch[index];\
			}\
			decltype(auto) operator[](size_t index)\
			{\
				return branch[index % out_degree];\
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
			static binding_instance<any_binding_instance, any_binding_tree>& sentinel();
			ptr_array_at_index
		};
		template<typename T, size_t out_degree>
		binding_instance<any_binding_instance, any_binding_tree<T, out_degree>>& any_binding_tree<T, out_degree>::sentinel()
		{
			static binding_instance<any_binding_instance, any_binding_tree<T, out_degree>> __sentinel__(nullptr);
			return __sentinel__;
		}

#define any_binding_tree_init(type)\
		type(T* ptr = nullptr) : base_instance(ptr) {}\
		type(any_binding_instance& forward, T* ptr = nullptr) : base_instance(forward, ptr) {}\
		type(type& ins) noexcept : base_instance(ins) {}\
		type(type&& ins) noexcept : base_instance(std::move(ins)) {}\
		type(any_binding_instance& forward, type& ins) : base_instance(forward, ins) {}\
		type(any_binding_instance& forward, type&& ins) : base_instance(forward, std::move(ins)) {}\
		type(type& from) noexcept : base_instance(from) {}\
		type(type&& from) noexcept : base_instance(std::move(from)) {}\
		type(any_binding_instance& forward, type& from) noexcept : base_instance(forward, from) {}\
		type(any_binding_instance& forward, type&& from) noexcept : base_instance(forward, std::move(from)) {}\
		template<typename... Args>\
		type(Args&&... args) : base_instance(new T(args...)) {}\
		template<typename... Args>\
		type(any_binding_instance& forward, Args&&... args) : base_instance(forward, new T(args...)) {}

		template<size_t index, typename T, size_t _OD>
		decltype(auto) bounding(binding_instance<any_binding_instance, any_binding_tree<T, _OD>>& iter)
		{
			static_assert(index < _OD, "index cannt larger than _OD(out degree)");
			auto& current = iter;
			while (current.get_ref().at(index).empty() == false)
			{
				current = current.get_ref().at(index);
			}
			return current;
		}
		template<size_t index, typename T, size_t _OD>
		decltype(auto) bounding(binding_instance<global_indicator, any_binding_tree<T, _OD>>& iter)
		{
			static_assert(index < _OD, "index cannt larger than _OD(out degree)");
			if (iter.get_ref().at(index).empty()) return any_binding_tree<T, _OD>::sentinel();
			else return bounding<index>(iter->at(index));
		}
		template<size_t index, typename T, size_t _OD>
		decltype(auto) bounding_pr(binding_instance<any_binding_instance, any_binding_tree<T, _OD>>& iter)
		{
			static_assert(index < _OD, "index cannt larger than _OD(out degree)");
			if (iter.empty() || iter->at(index).empty())return any_binding_tree<T, _OD >::sentinel();
			auto& current = iter;
			while (current.get_ref().at(index).get_ref().at(index).empty() == false)
			{
				current = current.get_ref().at(index);
			}
			return current;
		}
		template<size_t index, typename T, size_t _OD>
		decltype(auto) bounding_pr(binding_instance<global_indicator, any_binding_tree<T, _OD>>& iter)
		{
			static_assert(index < _OD, "index cannt larger than _OD(out degree)");
			if (iter.empty() || iter->at(index).empty())return any_binding_tree<T, _OD >::sentinel();
			else if (iter->at(index)->at(index).empty())return iter->at(index);
			else return bounding_pr(iter->at(index));
		}

#pragma region linear

		template<typename T>
		using stack_iter = any_binding_tree<T, 1>;
		constexpr static size_t stack_next = 0;
		template<typename T, typename _Forward, typename...Args>
		decltype(auto) link(binding_instance<_Forward, stack_iter<T>>& iter, Args&&... args)
		{
			return binding(iter->.at(stack_next), iter, args...);
		}
		template<typename T, typename _Forward>
		decltype(auto) back(binding_instance<_Forward, stack_iter<T>>& iter)
		{
			return bounding<stack_next>(iter);
		}
		template<typename T, typename _Forward>
		decltype(auto) back_pr(binding_instance<_Forward, stack_iter<T>>& iter)
		{
			return bounding_pr<stack_next>(iter);
		}
		template<typename T, typename _Forward, typename...Args>
		decltype(auto) push(binding_instance<_Forward, stack_iter<T>>& iter, Args&&...args)
		{
			return link(back(iter), args...);
		}
		template<typename T, typename _Forward>
		decltype(auto) pop(binding_instance<_Forward, stack_iter<T>>& iter)
		{
			return link(back_pr(iter), nullptr);
		}


		template<typename T>
		using linear_iter = any_binding_tree<T, 2>;
		constexpr static size_t linear_front = 0;
		constexpr static size_t linear_back = 1;
		template<typename T,typename _Forward,typename...Args>
		decltype(auto) link(binding_instance<_Forward,linear_iter<T>>& iter, Args&&... args)
		{
			auto& back = binding(iter.get_ref().at(linear_back), iter, args...);
			binding(back.get_ref().at(linear_front), back, iter);
			return back;
		}

#pragma endregion
	}
}

#endif // !__FILE_ANY_GRAPH__
