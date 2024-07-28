#ifndef __FILE_LF_CONTAINER
#define __FILE_LF_CONTAINER

#include<Core/Header/anyclass.h>

namespace ld
{
	class voidptr_iterator
	{
		void* ptr;
		size_t unit_size;
	public:
		voidptr_iterator(void* ptr, size_t unit_size) :ptr(ptr), unit_size(unit_size) {}

		bool operator !=(const voidptr_iterator& that)
		{
			return this->ptr != that.ptr || this->unit_size != that.unit_size;
		}

		voidptr_iterator& operator ++()
		{
			ptr = (void*)((size_t)ptr + unit_size);
			return *this;
		}

		void* operator*()
		{
			return ptr;
		}

		voidptr_iterator(const voidptr_iterator&) = delete;
		voidptr_iterator& operator =(const voidptr_iterator&) = delete;
	};

	//Stack
	namespace container
	{
		class stack;
		template<typename T>
		class stack_ptr;

		class stack
		{
		public:
			stack(void* ptr0, void* ptr1, size_t unit_size = 1) :
				head(ptr0 > ptr1 ? ptr1 : ptr0), tail(ptr0 > ptr1 ? ptr0 : ptr1), unit_size(unit_size), top(head){}
			template<typename T,size_t size>
			stack(T(&arr)[size]) : stack(&arr[0], &arr[size], sizeof(T)) {}

			size_t get_full_size() const
			{
				return ((size_t)tail - (size_t)head) / unit_size;
			}
			size_t get_size() const
			{
				return ((size_t)top - (size_t)head) / unit_size + 1;
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
				void* tar = &static_cast<char*>(top)[size * unit_size];
				if (tar >= tail || tar < head)return false;
				top = tar;
				return true;
			}
			void* pick()
			{
				return top;
			}
			bool push()
			{
				return move(1);
			}
			bool pop()
			{
				return move(-1);
			}

		private:
			void* head, *tail;
			void* top;
			size_t unit_size;
		};
	}

	//Array
	namespace container
	{

	}
}

#endif // !__FILE_LF_CONTAINER
