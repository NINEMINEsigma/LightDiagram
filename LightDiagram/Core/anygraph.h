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
			void init_class(any_binding_instance* forward)
			{
				this->init_forward(forward);
			}

			using _Forward = any_binding_instance;
			using base_instance = binding_instance<any_binding_instance, T>;
#define branch_init\
				for (auto&& item : branch)\
				{\
					item.init_forward(this);\
				}
			// build up with init value
			any_binding_tree(T&& value) : base_instance(new T(std::move(value))) { branch_init }
			any_binding_tree(T& value) : base_instance(new T(value)) { branch_init }
			any_binding_tree(_Forward& forward, T&& value) : base_instance(forward, new T(std::move(value))) { branch_init }
			// init with ptr
			any_binding_tree(T* ptr = nullptr) : base_instance(ptr) { branch_init }
			any_binding_tree(_Forward& forward, T* ptr = nullptr) : base_instance(forward, ptr) { branch_init }
			// build up with move
			any_binding_tree(any_binding_tree& from) noexcept : base_instance(from) { branch_init }
			any_binding_tree(any_binding_tree&& from) noexcept : base_instance(std::move(from)) { branch_init }
			any_binding_tree(_Forward& forward, any_binding_tree& from) noexcept : base_instance(forward, from) { branch_init }
			any_binding_tree(_Forward& forward, any_binding_tree&& from) noexcept : base_instance(forward, std::move(from)) { branch_init }
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

			any_binding_tree& operator=(any_binding_tree& from) noexcept
			{
				base_instance::operator=(from);
				return *this;
			}
			any_binding_tree& operator=(any_binding_tree&& from) noexcept
			{
				base_instance::operator=(std::move(from));
				return *this;
			}
			any_binding_tree operator=(T* ptr)
			{
				base_instance::operator=(ptr);
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
		public:
			virtual std::string SymbolName() const override
			{
				return std::to_string(out_degree) + "-tree<" + typeid(T).name() + ">";
			}
			virtual std::string ToString() const override
			{
				auto result = base_instance::ToString() + "{";
				for (size_t i = 0; i < out_degree; i++)
				{
					result += branch[i].ToString() + (i + 1 < out_degree ? ", " : "");
				}
				result += "}";
				return result;
			}
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

#pragma region linear

		template<typename T>
		using linear_iter = any_binding_tree<T, 2>;
		constexpr static size_t linear_front = 0;
		constexpr static size_t linear_back = 1;
		template<typename T,typename...Args>
		void push_back(linear_iter<T>& iter, Args... args)
		{
			auto& back = binding(iter.at(linear_back), iter, args...);
			binding(back.get_ref().at(linear_front), back.get_ref(), iter);
		}

#pragma endregion
	}
}

#endif // !__FILE_ANY_GRAPH__
