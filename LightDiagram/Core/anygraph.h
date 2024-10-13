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
			Symbol_Push public binding_instance<any_binding_instance, T> Symbol_Endl
		{
		public:
			using tag = T;
			constexpr static size_t OD = out_degree;
		private:
			binding_instance<any_binding_instance, any_binding_tree> branch[out_degree];
		public:
			using _Forward = any_binding_instance;
			using base_instance = binding_instance<any_binding_instance, T>;
#define branch_init\
				for (auto&& item : branch)\
				{\
					ld::binding(item, *this, nullptr);\
				}
#define branch_init_with_args\
				for (auto&& item : branch)\
				{\
					ld::binding(item, *this, args...);\
				}
			// init with ptr
			any_binding_tree(T* ptr = nullptr) : base_instance(ptr) { branch_init }
			any_binding_tree(_Forward& forward, T* ptr = nullptr) : base_instance(forward, ptr) { branch_init }
			// build up with move
			any_binding_tree(any_binding_tree& ins) noexcept : base_instance(ins) { branch_init }
			any_binding_tree(any_binding_tree&& ins) noexcept : base_instance(std::move(ins)) { branch_init }
			any_binding_tree(_Forward& forward, any_binding_tree& ins) : base_instance(forward, ins) { branch_init }
			any_binding_tree(_Forward& forward, any_binding_tree&& ins) : base_instance(forward, std::move(ins)) { branch_init }
			any_binding_tree(any_binding_tree& from) noexcept : base_instance(from) { branch_init }
			any_binding_tree(any_binding_tree&& from) noexcept : base_instance(std::move(from)) { branch_init }
			any_binding_tree(_Forward& forward, any_binding_tree& from) noexcept : base_instance(forward, from) { branch_init }
			any_binding_tree(_Forward& forward, any_binding_tree&& from) noexcept : base_instance(forward, std::move(from)) { branch_init }
			// build up with args
			template<typename... Args>
			any_binding_tree(Args&&... args) : base_instance(new T(args...)) { branch_init }
			template<typename... Args>
			any_binding_tree(_Forward& forward, Args&&... args) : base_instance(forward, new T(args...)) { branch_init }
			virtual ~any_binding_tree() {}

			T& value()
			{
				return this->get_ref();
			}
			template<typename _Val>
			_Val value() const
			{
				return static_cast<_Val>(this->get_ref());
			}

	#define ptr_array_at_index\
			inline decltype(auto) at(size_t index) const\
			{\
				if (index >= out_degree)\
					ThrowLDException("index is overflow");\
				return branch[index];\
			}\
			decltype(auto) operator[](size_t index) const\
			{\
				return branch[index % out_degree];\
			}
		public:
			ptr_array_at_index
		};

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

		template<typename T>
		_LF_C_API(TClass) list
			Symbol_Push public any_binding_tree<T, 1> Symbol_Endl
		{
		public:
			any_binding_tree_init(list) Symbol_Endl;
			virtual ~list() {}
			decltype(auto) next_bi() const
			{
				return this->at(0);
			}
			decltype(auto) next() const
			{
				return this->at(0).get_ref();
			}
			decltype(auto) next_value() const
			{
				return this->at(0).get_ref().get_ref();
			}
		};
	}
}

#endif // !__FILE_ANY_GRAPH__
