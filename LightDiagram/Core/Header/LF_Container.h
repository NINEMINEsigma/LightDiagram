#ifndef __FILE_LF_CONTAINER

#define __FILE_LF_CONTAINER

#include<Core/Header/LF_Config.h>
#include<Core/Header/anyclass.h>
#include<Core/Header/LF_Exception.h>
#include<Core/Header/static_exist.h>

namespace ld
{
	// root(0,0)
	// --|
	// first(0,1) ->                        second(1,1) ->                   thrid(2,1)
	// --|                                   |                                |
	// lestest ptr(0,2) -> one ptr(1,2) --- mid ptr(0,2) -> one ptr(1,2) --- rightest ptr(0,2) -> one ptr(1,2)
	template<typename T>
	_LF_C_API(TClass) FourWayPointer
	{
	public:
		using tag = FourWayPointer<T>;
	protected:
		// upward ptr, which is parent and root
		tag* parent_ptr = nullptr;
		// rightward ptr, which is on the same branch and layer
		tag* right_prt = nullptr;
		// leftward ptr, which is on the same branch and layer
		tag* left_ptr = nullptr;
		// downward ptr, which is the branch undering this and pointing to leftest one
		tag* childs_begin_ptr = nullptr;
		// downward ptr, which is the branch undering this and pointing to rightest one
		tag* childs_end_ptr = nullptr;
		// beyond ptr, when this ptr is leaf, it will be pointing to rightward leaf
		tag* beyond_next_ptr = nullptr;
	public:
		template<
			typename Key, typename Value, typename IndexOrderIndicator, typename MemoryIndicator,
			typename InsertIndicator, typename EarseIndicator
		>
		friend class LFContainter;
#pragma region 
		//*
		// Set new linkship: this -> ptr -> old-link right
		//*
		void InsertRight(tag * ptr);
		//*
		// Set new linkship: old-link left -> ptr -> this
		//*
		void InsertLeft(tag * ptr);
		// Set childs tail's right
		void InsertEnd(tag * ptr);
		// Set childs head's left
		void InsertBegin(tag * ptr);
		// Break linkship between right and this, and return old ptr
		tag* BreakRight();
		// Break linkship between left and this, and return old ptr
		tag* BreakLeft();
		// Get link left one
		tag* GetLeft() const;
		// Get link right one
		tag* GetRight() const;
		// Get this branch head one
		tag* GetBegin() const;
		// Get this branch tail one
		tag* GetEnd() const;
		// Get size of this branch
		size_t GetSizeOfBranch() const;
#pragma endregion
	protected:
		// index counter from left to right
		size_t index_from_head = 0;
		// index counter from right to left
		size_t index_from_tail = 0;
	public:
#pragma region 
		//*
		// Set new linkship: 
		// old-link parent
		// |-- ptr
		// ----| this
		//*
		void InsertParent(tag * ptr);
		// Break linkship between parent and this, and return old ptr(parent)
		tag* BreakParent();
		// Get parent ptr
		tag* GetParent() const;
		// Get root ptr
		tag* GetRoot() const;
#pragma endregion
	protected:
#pragma region
		// index counter which is depth of this tree 
		size_t index_from_root = 0;
		// index counter which is distance from this ptr to farthest leaf
		size_t index_from_farthest_leaf = 0;
#pragma endregion
	public:
#pragma region 
		// Set new linkship:
		// this
		// |-- ptr ->old-link begin ->...
		void InsertChildBegin(tag * ptr);
		// Set new linkship:
		// -----------------------------this
		// ... <- old-link end <- ptr --|
		void InsertChildEnd(tag * ptr)
			// Break linkship between childs and this, and return old ptr(head)
			tag* BreakChilds();
		// Get childs branch head one
		tag* GetChildsLeft() const;
		// Get childs branch tail one
		tag* GetChildsRight() const;
#pragma endregion
	public:
#pragma region 
		// Get index from head
		size_t GetIndex() const;
		// Get index from tail
		size_t GetRIndex() const;
		// Get depth from root(index from root)
		size_t GetDepth() const;
		// Get distance from leaf(index from farthest leaf)
		size_t GetRDepth() const;
		// Get this sub tree depth(from root to farthest leaf of this ptr's childs)
		size_t GetTreeDepth() const;
#pragma endregion
	public:
#pragma region

#pragma endregion
	};

#pragma region FourWay Pointer

	template<typename T>
	void FourWayPointer<T>::InsertBegin(tag* ptr)
	{
		this->GetBegin()->InsertLeft(ptr);
	}
	template<typename T>
	void FourWayPointer<T>::InsertEnd(tag* ptr)
	{
		this->GetEnd()->InsertRight(ptr);
	}
	template<typename T>
	void FourWayPointer<T>::InsertChildBegin(tag* ptr)
	{
		if (ptr == nullptr)return;
		ptr->BreakParent();
		if (this->childs_begin_ptr)
		{
			this->childs_begin_ptr->InsertLeft(ptr);
		}
		else
		{
			ptr->InsertParent(this);
		}
	}
	template<typename T>
	void FourWayPointer<T>::InsertChildEnd(tag* ptr)
	{
		if (ptr == nullptr)return;
		ptr->BreakParent();
		if (this->childs_end_ptr)
		{
			this->childs_end_ptr->InsertRight(ptr);
		}
		else
		{
			ptr->InsertParent(this);
		}
	}

	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::GetLeft() const
	{
		return this->left_ptr;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::GetRight() const
	{
		return this->right_ptr;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::GetBegin() const
	{
		tag* result = this;
		while (result->left_ptr)
			result = result->left_ptr;
		return result;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::GetEnd() const
	{
		tag* result = this;
		while (result->right_prt)
			result = result->right_prt;
		return result;
	}
	template<typename T>
	size_t FourWayPointer<T>::GetSizeOfBranch() const
	{
		return this->index_from_head + this->index_from_tail + 1;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::GetParent() const
	{
		return this->parent_ptr;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::GetChildsLeft() const
	{
		return  this->childs_begin_ptr;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::GetChildsRight() const
	{
		return  this->childs_end_ptr;
	}
	template<typename T>
	size_t FourWayPointer<T>::GetIndex() const
	{
		return this->index_from_head;
	}template<typename T>
		template<typename T>
	size_t FourWayPointer<T>::GetRIndex() const
	{
		return this->index_from_tail;
	}template<typename T>
		template<typename T>
	size_t FourWayPointer<T>::GetDepth() const
	{
		return this->index_from_root;
	}
	template<typename T>
	size_t FourWayPointer<T>::GetRDepth() const
	{
		return this->index_from_farthest_leaf;
	}
	template<typename T>
	size_t FourWayPointer<T>::GetTreeDepth() const
	{
		return this->index_from_root + this->index_from_farthest_leaf + 1;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::GetRoot() const
	{
		tag* result = this;
		while (result->parent_ptr)
		{
			result = this->parent_ptr;
		}
		result = result->GetBegin();
		return result;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::GetParent() const
	{
		return this->parent_ptr;
	}


#pragma endregion

	template<
		typename Key, typename Value, typename IndexOrderIndicator, typename MemoryIndicator,
		typename InsertIndicator, typename EarseIndicator
	>
	//*
	//	
	//*
	_LF_C_API(TClass) LFContainter
	{
	public:
		using index_indicator = IndexOrderIndicator;
		using memory_indictaor = MemoryIndicator;
		using insert_indicator = InsertIndicator;
		using earse_indicator = EarseIndicator;
		LFContainter() :root(nullptr), leaf(nullptr)
		{

		}

		class pair
		{
		public:
			friend LFContainter;
		private:
			Key* key_ptr = nullptr;
			Value* value_ptr = nullptr;
			bool is_key_intrusive = false;
			bool is_value_intrusive = false;
		public:
			pair(Key* key = nullptr, Value* value = nullptr) :key_ptr(key), value_ptr(value), is_key_intrusive(key != nullptr), is_value_intrusive(value != nullptr) {}
			~pair()
			{
				if (!is_key_intrusive)delete key_ptr;
				if (!is_value_intrusive)delete value_ptr;
			}
			const Key& GetKey()
			{
				if (key_ptr == nullptr)
				{
					is_key_intrusive = false;
					key_ptr = new Key();
				}
				return *key_ptr;
			}
			Value& GetValue()
			{
				if (value_ptr == nullptr)
				{
					is_value_intrusive = false;
					value_ptr = new Value();
				}
				return *value_ptr;
			}
			void SetValue(Value& value)
			{
				GetValue() = value;
			}
			void SetValue(Value* value)
			{
				if (!is_value_intrusive)delete value_ptr;
				is_value_intrusive = true;
				value_ptr = value;
			}
			operator const Key& ()
			{
				return GetKey();
			}
			operator Value& ()
			{
				return GetValue();
			}
		};
		using node = FourWayPointer<pair>;
	private:
		node* root = nullptr;
		node* leaf = nullptr;
	};
}

#endif // !__FILE_LF_CONTAINER
