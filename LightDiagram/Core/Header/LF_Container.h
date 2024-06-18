#ifndef __FILE_LF_CONTAINER

#define __FILE_LF_CONTAINER

#include<Core/Header/LF_Config.h>
#include<Core/Header/anyclass.h>
#include<Core/Header/LF_Exception.h>
#include<Core/Header/static_exist.h>

if_type_exist_def(container_key_ptr_enable);
if_type_exist_def(container_value_ptr_enable);

namespace ld
{
	namespace kit
	{
		template
			<
			typename _Key,
			typename _Value,
			typename _Malloc,
			typename _Linker
			>
			_LF_C_API(TClass) _Origin_Container;


		template
			<
			typename _Key,
			typename _Value
			>
			_LF_C_API(Class) DataNode Symbol_Push
			_LF_Inherited(any_class)
		{
			using SelfType = DataNode<_Key, _Value>;
			SelfType* parent_node;
			SelfType* left_node;
			SelfType* right_node;
			SelfType* childs_head_node;
			SelfType* childs_tail_node;
		public:
			template <  typename _Malloc, typename _Linker >
			friend typename _Origin_Container<_Key, _Value, _Malloc, _Linker>;

			virtual ~DataNode();

			constexpr static bool IsKeyEnablePtr = if_type_exist(container_key_ptr_enable) < _Key > ;
			using KeyType = choose_type<IsKeyEnablePtr, _Key*, _Key>::tag;
			constexpr static bool IsValueEnablePtr = if_type_exist(container_value_ptr_enable) < _Value > ;
			using ValueType = choose_type<IsValueEnablePtr, _Value*, _Value>::tag;

			DataNode(const DataNode&) = delete;
			DataNode(KeyType _key);
			DataNode(KeyType _key, ValueType _value);

			//It will detect value and return true if IsValueEnablePtr is true and value(ptr) is nullptr
			bool IsEmpty() const;
			const KeyType& GetKey() const;
			ValueType& GetValue();

			SelfType* GetParent() const;
			SelfType* GetLeft() const;
			//If left(ptr) is exist, return left,
			//else return parent
			SelfType* GetPrecursor() const;
			SelfType* GetRight() const;
			//If right(ptr) is exist, return right,
			//else return parent's right
			SelfType* GetSuccessor() const;
			SelfType* GetChildsBegin() const;
			SelfType* GetChildsEnd() const;
			//Return it self
			SelfType* GetSelf() const;
		private:
			KeyType key;
			ValueType value;
		};

		template
			<
			typename _Key,
			typename _Value,
			typename _Malloc,
			typename _Linker
			>
			_LF_C_API(TClass) _Origin_Container Symbol_Push
			_LF_Inherited(any_class)
		{
		public:
			virtual ~_Origin_Container()
			{

			}

			using DataNodeType = DataNode<_Key, _Value>;
			using KeyType = DataNodeType::KeyType;
			using ValueType = DataNodeType::ValueType;

			//If key is not exist, it will be generate new node which one the key-value is this key.
			//The last time to find value, if key and this is same. it will return result on O1 times
			ValueType& operator[](const KeyType& key)
			{
				static _Origin_Container<_Key, _Value, _Malloc, _Linker>* _last_container_ptr = nullptr;
				static DataNodeType* _last_node_ptr = nullptr;
				if (_last_container_ptr == this)
				{
					if (_last_node_ptr->GetKey() == key)
					{
						return _last_node_ptr->GetValue();
					}
				}
				else _last_container_ptr = this;
				DataNodeType* node = nullptr;
				if ((node = ToolGetDataNode(MyRoot, key)) == nullptr)
				{
					node = ToolGenerateDataNode(MyRoot, key);
				}
				_last_node_ptr = node;
				return node->GetValue();
			}

		private:
			DataNodeType* ToolGetDataNode(DataNodeType * root, const KeyType & key);
			DataNodeType* ToolGenerateDataNode(DataNodeType* root, const KeyType& key)
			{
#define __DELETE_NODE  delete node; node = nullptr;
				DataNodeType* node = nullptr;
				try
				{

				}
				CatchingSTDException(__DELETE_NODE)CatchingUnknown(__DELETE_NODE);
			}
			DataNodeType* MyRoot;
		public:
			size_t count(const KeyType & key) const
			{
				size_t result = 0;
				ToolCount(MyRoot, key, result);
				return result;
			}
		private:
			void ToolCount(DataNodeType * root, const KeyType & key, size_t & counter) const
			{
				if (root == nullptr)return;
				if (root->GetKey() == counter)
					counter++;
				ToolCount(root->GetLeft(), key, counter);
				ToolCount(root->GetRight(), key, counter);
				ToolCount(root->GetChildsBegin(), key, counter);
			}
		};
	}
}

#endif // !__FILE_LF_CONTAINER
