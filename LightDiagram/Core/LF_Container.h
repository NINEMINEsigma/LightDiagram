#ifndef __FILE_LF_CONTAINER
#define __FILE_LF_CONTAINER

#include<Core/anyclass.h>

namespace ld
{
	class voidptr_continuous_iterator
	{
		void* ptr;
		size_t unit_size;
	public:
		voidptr_continuous_iterator(void* ptr, size_t unit_size) :ptr(ptr), unit_size(unit_size) {}
		voidptr_continuous_iterator(const voidptr_continuous_iterator& right) :ptr(right.ptr), unit_size(right.unit_size) {}
		voidptr_continuous_iterator& operator =(const voidptr_continuous_iterator& right)
		{
			ptr = right.ptr;
			unit_size = right.unit_size;
		}

		bool operator !=(const voidptr_continuous_iterator& that)
		{
			return this->ptr != that.ptr;
		}
		voidptr_continuous_iterator& operator ++()
		{
			ptr = (void*)((size_t)ptr + unit_size);
			return *this;
		}
		voidptr_continuous_iterator& operator --()
		{
			ptr = (void*)((size_t)ptr - unit_size);
			return *this;
		}
		void* operator*()
		{
			return ptr;
		}

	};

#define defined_indicator(con,tem)				\
	constexpr static bool is_container_v=con;	\
	constexpr static bool is_template_v=tem;	\

	//Stack
	namespace container
	{
		class stack;

		class stack
		{
		public:
			defined_indicator(true, false);

			stack(void* ptr0, void* ptr1, size_t unit_size = 1) :
				head(ptr0 > ptr1 ? ptr1 : ptr0), tail(ptr0 > ptr1 ? ptr0 : ptr1), unit_size(unit_size), top(head) {}
			template<typename T, size_t size>
			stack(T(&arr)[size]) : stack(&arr[0], &arr[size], sizeof(T)) {}
			stack(const stack& right) :head(right.head), tail(right.tail), unit_size(right.unit_size), top(head) {}
			stack& operator=(const stack& right)
			{
				head = right.head;
				tail = right.tail;
				unit_size = right.unit_size;
				top = head;
			}

			size_t get_full_size() const
			{
				return ((size_t)tail - (size_t)head) / unit_size;
			}
			size_t get_size() const
			{
				return ((size_t)top - (size_t)head) / unit_size;
			}
			void* get_head() const
			{
				return head;
			}
			void* get_tail() const
			{
				return tail;
			}
			void* get_top()
			{
				return top;
			}
			size_t get_unit_size() const
			{
				return unit_size;
			}

			bool move(int size)
			{
				if (size == 0)return top < tail && top >= head;
				size_t temp = (size_t)top + size * unit_size;
				if ((size > 0 && temp <= (size_t)tail) || (size < 0 && temp >= (size_t)head))
				{
					top = &static_cast<char*>(top)[size * unit_size];
					return true;
				}
				else return false;
			}
			void* pick()
			{
				return (void*)((size_t)top - unit_size);
			}
			bool push()
			{
				return move(1);
			}
			bool pop()
			{
				return move(-1);
			}

			using iterator = voidptr_continuous_iterator;
			iterator begin()
			{
				return iterator(head, unit_size);
			}
			iterator end()
			{
				return iterator(top, unit_size);
			}
			iterator rbegin()
			{
				return iterator((void*)((size_t)top - unit_size), unit_size);
			}
			iterator rend()
			{
				return iterator((void*)((size_t)head - unit_size), unit_size);
			}
			iterator full_range_begin()
			{
				return iterator(head, unit_size);
			}
			iterator full_range_end()
			{
				return iterator(tail, unit_size);
			}

		private:
			void* head, * tail;
			void* top;
			size_t unit_size;
		};

		namespace accurate
		{
			template<typename _Ty>
			class stack
			{
			public:
				defined_indicator(true, true);

				stack(_Ty* ptr0, _Ty* ptr1) :head(ptr0 > ptr1 ? ptr1 : ptr0), tail(ptr0 > ptr1 ? ptr0 : ptr1), top(head) {}
				template<size_t size>
				stack(_Ty(&arr)[size]) : stack(&arr[0], &arr[size]) {}
				stack(const stack& right) :head(right.head), tail(right.tail), unit_size(right.unit_size), top(head) {}
				stack& operator=(const stack& right)
				{
					head = right.head;
					tail = right.tail;
					unit_size = right.unit_size;
					top = head;
				}

				size_t get_full_size() const
				{
					return ((size_t)tail - (size_t)head) / unit_size;
				}
				size_t get_size() const
				{
					return ((size_t)top - (size_t)head) / unit_size;
				}
				_Ty* get_head() const
				{
					return head;
				}
				_Ty* get_tail() const
				{
					return tail;
				}
				_Ty* get_top()
				{
					return top;
				}
				size_t get_unit_size() const
				{
					return unit_size;
				}

				bool move(int size)
				{
					if (size == 0)return top < tail && top >= head;
					size_t temp = (size_t)top + size * unit_size;
					if ((size > 0 && temp <= (size_t)tail) || (size < 0 && temp >= (size_t)head))
					{
						top = (_Ty*)temp;
						return true;
					}
					else return false;
				}
				_Ty* pick()
				{
					return (_Ty*)((size_t)top - unit_size);
				}
				bool push()
				{
					return move(1);
				}
				bool pop()
				{
					return move(-1);
				}

				using iterator = _Ty*;
				iterator begin()
				{
					return head;
				}
				iterator end()
				{
					return top;
				}
				iterator rbegin()
				{
					return (_Ty*)((size_t)top - unit_size);
				}
				iterator rend()
				{
					return (_Ty*)((size_t)head - unit_size);
				}
				iterator full_range_begin()
				{
					return head;
				}
				iterator full_range_end()
				{
					return tail;
				}
			private:
				_Ty* head, * tail;
				_Ty* top;
				constexpr static size_t unit_size = sizeof(_Ty);
			};
		}
	}

	//Array
	namespace container
	{
		class arrayX;

		class arrayX
		{
		public:
			defined_indicator(true, false);

			arrayX(void* ptr0, void* ptr1, size_t unit_size = 1) :
				head(ptr0 > ptr1 ? ptr1 : ptr0), tail(ptr0 > ptr1 ? ptr0 : ptr1), unit_size(unit_size) {}
			template<typename T, size_t size>
			arrayX(T(&arr)[size]) : arrayX(&arr[0], &arr[size], sizeof(T)) {}
			arrayX(const arrayX& right) :head(right.head), tail(right.tail), unit_size(right.unit_size) {}
			arrayX& operator=(const arrayX& right)
			{
				head = right.head;
				tail = right.tail;
				unit_size = right.unit_size;
			}

			size_t get_full_size() const
			{
				return ((size_t)tail - (size_t)head) / unit_size;
			}
			size_t get_size() const
			{
				return ((size_t)tail - (size_t)head) / unit_size;
			}
			void* get_head() const
			{
				return head;
			}
			void* get_tail() const
			{
				return tail;
			}
			size_t get_unit_size() const
			{
				return unit_size;
			}

			void* operator[](size_t index)
			{
				return (void*)((size_t)head + index * unit_size);
			}

			using iterator = voidptr_continuous_iterator;
			iterator begin()
			{
				return iterator(head, unit_size);
			}
			iterator end()
			{
				return iterator(tail, unit_size);
			}
			iterator rbegin()
			{
				return iterator((void*)((size_t)tail - unit_size), unit_size);
			}
			iterator rend()
			{
				return iterator((void*)((size_t)head - unit_size), unit_size);
			}
			iterator full_range_begin()
			{
				return iterator(head, unit_size);
			}
			iterator full_range_end()
			{
				return iterator(tail, unit_size);
			}

		private:
			void* head, * tail;
			size_t unit_size;
		};

		namespace accurate
		{
			template<typename _Ty>
			class arrayX
			{
			public:
				defined_indicator(true, true);

				arrayX(_Ty* ptr0, _Ty* ptr1) :head(ptr0 > ptr1 ? ptr1 : ptr0), tail(ptr0 > ptr1 ? ptr0 : ptr1){}
				template<size_t size>
				arrayX(_Ty(&arr)[size]) : stack(&arr[0], &arr[size]) {}
				arrayX(const arrayX& right) :head(right.head), tail(right.tail), unit_size(right.unit_size){}
				arrayX& operator=(const arrayX& right)
				{
					head = right.head;
					tail = right.tail;
					unit_size = right.unit_size;
				}

				size_t get_full_size() const
				{
					return ((size_t)tail - (size_t)head) / unit_size;
				}
				size_t get_size() const
				{
					return ((size_t)tail - (size_t)head) / unit_size;
				}
				_Ty* get_head() const
				{
					return head;
				}
				_Ty* get_tail() const
				{
					return tail;
				}
				size_t get_unit_size() const
				{
					return unit_size;
				}

				_Ty& operator[](size_t index)
				{
					return head[index];
				}

				using iterator = _Ty*;
				iterator begin()
				{
					return head;
				}
				iterator end()
				{
					return tail;
				}
				iterator rbegin()
				{
					return (_Ty*)((size_t)tail - unit_size);
				}
				iterator rend()
				{
					return (_Ty*)((size_t)head - unit_size);
				}
				iterator full_range_begin()
				{
					return head;
				}
				iterator full_range_end()
				{
					return tail;
				}
			private:
				_Ty* head, * tail;
				constexpr static size_t unit_size = sizeof(_Ty);
			};
		}
	}
}

#endif // !__FILE_LF_CONTAINER
