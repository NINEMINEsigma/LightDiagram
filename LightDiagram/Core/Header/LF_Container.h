#define __FILE_LF_CONTAINER
#ifndef __FILE_LF_CONTAINER
#define __FILE_LF_CONTAINER

#include<Core/Header/LF_Config.h>
#include<Core/Header/anyclass.h>
#include<Core/Header/LF_Exception.h>
#include<Core/Header/static_exist.h>

namespace ld
{
#define FourWayPointerLevel public
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
	private:
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
		// beyond ptr, when this ptr is leaf, it will be pointing to leftward leaf
		tag* beyond_back_ptr = nullptr;
	public:
		template< typename Key, typename Value, typename MemoryIndicator, typename Controller >
		friend class LFContainter<Key, Value, MemoryIndicator, Controller>;
		T data;
		T& GetData() const
		{
			return data;
		}
	FourWayPointerLevel:
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
	private:
		// index counter from left to right
		size_t index_from_head = 0;
		// index counter from right to left
		size_t index_from_tail = 0;
	FourWayPointerLevel:
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
	private:
		// index counter which is depth of this tree 
		size_t index_from_root = 0;
		// index counter which is distance from this ptr to farthest leaf
		size_t index_from_farthest_leaf = 0;
	FourWayPointerLevel:
#pragma region 
		// Set new linkship:
		// this
		// |-- ptr ->old-link begin ->...
		void InsertChildBegin(tag * ptr);
		// Set new linkship:
		// -----------------------------this
		// ... <- old-link end <- ptr --|
		void InsertChildEnd(tag * ptr);
		// Break linkship between childs and this, and return old ptr(head)
		tag* BreakChilds();
		// Get childs branch head one
		tag* GetChildsLeft() const;
		// Get childs branch tail one
		tag* GetChildsRight() const;
#pragma endregion
		FourWayPointerLevel:
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
		FourWayPointerLevel:
#pragma region
		// BreakLeft
		void InsertLeft(nullptr_t);
		// BreakRight
		void InsertRight(nullptr_t);
		// BreakParent
		void InsertParent(nullptr_t);
		// Break all linkship(not include childs ptr)
		void BreakLinkship();
#pragma endregion
		FourWayPointerLevel:
#pragma region
		// Rebuild index stats from this ptr to tail on this branch
		// Best time to use this function rebuild index, this ptr need to be the head one
		// return end ptr index
		size_t RebuildBranchIndex();
		// Rebuild depth stats from this ptr to all sub ptr
		// Best time to use this function rebuild depth, this ptr need to be the root one
		// return farthest leaf ptr depth
		size_t RebuildDepthIndex();
#pragma endregion
		FourWayPointerLevel:
#pragma region
		tag* GetPrecursor() const;
		tag* GetSuccessor() const;
#pragma endregion
	public:
		~FourWayPointer()
		{
			for (tag* i = this->childs_begin_ptr; i; i = i->right_prt)
			{
				delete i;
			}
			if (this->left_ptr)
				this->left_ptr->right_prt = this->right_prt;
			if (this->right_prt)
				this->right_prt->left_ptr = this->left_ptr;
		}
	};

#pragma region FourWay Pointer

	template<typename T>
	void FourWayPointer<T>::InsertLeft(tag* ptr)
	{
		if (ptr)
		{
			tag* cat = this->left_ptr;
			cat->right_prt = ptr;
			ptr->left_ptr = cat;
			ptr->parent_ptr = this->parent_ptr;
			ptr->right_prt = this;
			this->left_ptr = ptr;
		}
		else this->BreakLeft();
	}
	template<typename T>
	void FourWayPointer<T>::InsertRight(tag* ptr)
	{
		if (ptr)
		{
			tag* cat = this->right_prt;
			cat->left_ptr = ptr;
			ptr->right_prt = cat;
			ptr->parent_ptr = this->parent_ptr;
			ptr->left_ptr = this;
			this->right_prt = ptr;
		}
		else this->BreakRight();
	}
	template<typename T>
	void FourWayPointer<T>::InsertParent(tag* ptr)
	{
		if (ptr)
		{
			tag* old_left = this->left_ptr, old_right = this->right_prt, old_parent = this->parent_ptr;
			this->left_ptr = this->right_prt = this->parent_ptr = nullptr;
			if (old_left)
			{
				old_left->right_prt = ptr;
			}
			if (old_right)
			{
				old_right.left_ptr = ptr;
			}
			if (old_parent)
			{
				if (old_parent.childs_begin_ptr == this)
				{
					old_parent.childs_begin_ptr = ptr;
				}
				if (old_parent.childs_end_ptr == this)
				{
					old_parent.childs_end_ptr = ptr;
				}
			}
			ptr->parent_ptr = old_parent;
			ptr->left_ptr = old_left;
			ptr->right_prt = old_right;
			ptr->InsertChildEnd(this);
		}
		else this->BreakParent();
	}

	template<typename T>
	void FourWayPointer<T>::InsertLeft(nullptr_t)
	{
		this->BreakLeft();
	}
	template<typename T>
	void FourWayPointer<T>::InsertRight(nullptr_t)
	{
		this->BreakRight();
	}
	template<typename T>
	void FourWayPointer<T>::InsertParent(nullptr_t)
	{
		this->BreakParent();
	}

	template<typename T>
	void FourWayPointer<T>::BreakLinkship()
	{
		this->BreakLeft();
		this->BreakRight();
		this->BreakParent();
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::BreakLeft()
	{
		if (this->left_ptr)
		{
			tag* result = this->left_ptr;
			this->left_ptr->right_prt = nullptr;
			this->left_ptr = nullptr;
			return result;
		}
		return nullptr;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::BreakRight()
	{
		if (this->right_prt)
		{
			tag* result = this->right_prt;
			this->right_prt->left_ptr = nullptr;
			this->right_prt = nullptr;
			return result;
		}
		return nullptr;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::BreakParent()
	{
		if (this->parent_ptr)
		{
			tag* result = this->parent_ptr;
			this->parent_ptr = nullptr;
			return result;
		}
		return nullptr;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::BreakChilds()
	{
		tag* result = this->left_ptr;
		tag* current = this->left_ptr;
		while (current)
		{
			current->parent_ptr = nullptr;
			current = current->right_prt;
		}
		this->left_ptr = this->right_prt = nullptr;
		return result;
	}

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
	}
	template<typename T>
	size_t FourWayPointer<T>::GetRIndex() const
	{
		return this->index_from_tail;
	}
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
	size_t FourWayPointer<T>::RebuildBranchIndex()
	{
		this->index_from_head = this->left_ptr ? (this->left_ptr->index_from_head + 1) : 0;
		size_t result = this->index_from_head;
		if (this->right_prt)
		{
			result = this->right_prt->RebuildBranchIndex();
		}
		this->index_from_tail = result - this->index_from_head;
		return result;
	}
	template<typename T>
	size_t FourWayPointer<T>::RebuildDepthIndex()
	{
		this->index_from_root = this->parent_ptr ? (this->parent_ptr->index_from_root + 1) : 0;
		size_t result = this->index_from_root;
		if (this->childs_begin_ptr)
		{
			for (tag* i = this->childs_begin_ptr; i; i = i->right_prt)
			{
				result = ld::Max(result, i->RebuildDepthIndex());
			}
		}
		this->index_from_farthest_leaf = result - this->index_from_root;
		return result;
	}

	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::GetPrecursor() const
	{
		return this->beyond_back_ptr;
	}
	template<typename T>
	FourWayPointer<T>::tag* FourWayPointer<T>::GetSuccessor() const
	{
		return this->beyond_next_ptr;
	}

#pragma endregion

	_LF_C_API(OClass)
		DefaultContainerMemory
	{
	public:
		static void* Malloc(size_t size);
		static void Free(void* ptr, size_t size);
		template<typename T>
		using ptr_tag = T;
	};

	void* DefaultContainerMemory::Malloc(size_t size)
	{
		return ::malloc(size * sizeof(char));
	}
	void DefaultContainerMemory::Free(void* ptr, size_t size)
	{
		::free(ptr);
	}

	template<typename Key, typename Value, typename Memory>
	_LF_C_API(TClass)
		DefaultContainerController
	{
	public:
		using key_tag = Key;
		using value_tag = Value;
		using memory_indictaor = Memory;
		using pair_type = ld::pair<Key, Value, memory_indictaor>;
		using node = FourWayPointer<pair_type>;
	public:
		node* ReadFromRoot(node* root, node* leaf, const Key& key) const;
		node* QuickDetectContain(node* root, const Key& key) const;
		node* GenerateToRoot(node*& root, node*& leaf, const Key& key, void* new_ptr)
		{
			if (root)
			{

			}
			else
			{
				root = new(new_ptr) node();
			}
		}
		node* RemoveFromRoot(node* root, node* leaf, const Key& key);
		template<_Ty> node* RemoveFromRoot(node* root, _Ty);
	};

	template<typename _Key, typename _Value, typename Memory>
	class pair
	{
	public:
		friend LFContainter;
		using memory_indictaor = Memory;
		using Key = memory_indictaor::ptr_tag<_Key>;
		using Value = memory_indictaor::ptr_tag<_Value>;
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

	template<
		typename Key, typename Value,
		class MemoryIndicator = DefaultContainerMemory,
		class Controller = DefaultContainerController<Key, Value, MemoryIndicator>
	>
	_LF_C_API(TClass) LFContainter
	{
	public:
		// Key and Value: will be build up in target pair type, and be able to create intrusive slot or just new instance(it can free by itself)
		using key_tag = Key;
		// Key and Value: will be build up in target pair type, and be able to create intrusive slot or just new instance(it can free by itself)
		using value_tag = Value;
		// MemoryIndicator: static memeory manager, to control memeory and buffer
		// -> public static void* Malloc(size_t size) const;
		// -> public static void Free(void* ptr, size_t size) const;
		using memory_indictaor = MemoryIndicator;
		// Controller: constructor with no argument, control all the behaviour
		// -> public node* ReadFromRoot(node* root, node* leaf, const Key& key) const;
		// -> public node* QuickDetectContain(node* root, const Key& key) const
		// -> public node* GenerateToRoot(node*& root, node*& leaf, const Key& key, void* new_ptr);
		// -> public node* RemoveFromRoot(node* root, node* leaf, const Key& key)
		// -> public template<_Ty> node* RemoveFromRoot(node* root, _Ty)
		using controller_type = Controller;
		LFContainter(controller_type & controller) :root(nullptr), leaf(nullptr), my_controller(controller) {}
		LFContainter(LFContainter&&) = delete;
		LFContainter(LFContainter& right) :root(right.root), leaf(leaf), my_controller(right.my_controller) noexcept {}
		~LFContainter()
		{
			this->ClearTree();
		}

		using pair_type = ld::pair<Key, Value, memory_indictaor>;
		using node = FourWayPointer<pair_type>;
	private:
		node* root = nullptr;
		node* leaf = nullptr;
		controller_type& my_controller;
	protected:
		void ToolClear(node * _node) const
		{
			_node->data.SetValue(nullptr);
			for (node* i = _node->GetChildsLeft(); i; i = i->GetRight())
			{
				ToolClear(i);
			}
		}
	public:
		bool Isolated(node * _node) const
		{
			if (_node == root)return false;
			else return
				_node->GetLeft() == nullptr &&
				_node->GetRight() == nullptr &&
				_node->GetParent() == nullptr &&
				_node->GetChildsLeft() == nullptr;
		}
		bool Contains(node * _node) const
		{
			return _node->GetRoot() == root;
		}
		bool IsEmpty() const
		{
			return root == nullptr;
		}
		void ClearTree()
		{
			delete root;
		}
		void ClearValue()
		{
			ToolClear(root);
		}

		bool Contains(const Key& key) const
		{
			return my_controller.QuickDetectContain(root, key);
		}
		Value& GetValue(const Key & key) const
		{
			node* result = my_controller.ReadFromRoot(root, leaf, key);
			if (result == nullptr)
			{
				result = my_controller.GenerateToRoot(root, leaf, key, memory_indictaor::Malloc(sizeof(node)));
			}
			return result->data;
		}
		Value& GetValue(Key * key) const
		{
			node* result = my_controller.ReadFromRoot(root, leaf, key);
			if (result == nullptr)
			{
				result = my_controller.GenerateToRoot(root, leaf, *key, memory_indictaor::Malloc(sizeof(node)));
			}
			return result->data;
		}
		void Remove(const Key & key)
		{
			memory_indictaor::Free(my_controller.RemoveFromRoot(root, leaf, key), sizeof(node));
		}
		void SetValue(const Key & key, Value & value) const
		{
			GetValue(key) = value;
		}
		void SetValue(const Key & key, Value && value) const
		{
			GetValue(key) = std::move(value);
		}
		void SetValue(Key * key, Value & value) const
		{
			GetValue(*key) = value;
		}
		void SetValue(Key * key, Value && value) const
		{
			GetValue(*key) = std::move(value);
		}

		node* GetNode(const Key& key) const
		{
			return my_controller.ReadFromRoot(root, leaf, key);
		}
	};
}

#endif // !__FILE_LF_CONTAINER
