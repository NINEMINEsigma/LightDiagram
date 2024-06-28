#ifndef __FILE_LF_CONTAINER

#define __FILE_LF_CONTAINER

#include<Core/Header/LF_Config.h>
#include<Core/Header/anyclass.h>
#include<Core/Header/LF_Exception.h>
#include<Core/Header/static_exist.h>

namespace ld
{
	template<typename T>
	_LF_C_API(TClass) FourWayPointer
	{
	public:
		using tag = FourWayPointer<T>;
	protected:
		tag* parent_ptr = nullptr;
		tag* right_prt = nullptr;
		tag* left_ptr = nullptr;
		tag* childs_begin_ptr = nullptr;
		tag* childs_end_ptr = nullptr;
	public:
		template<
			typename Key, typename Value, typename IndexOrderIndicator, typename MemoryIndicator,
			typename InsertIndicator, typename EarseIndicator
		>
		friend class LFContainter;

		size_t GetIndex() const;

	protected:
		void SetRight(tag * ptr);
		void SetLeft(tag * ptr);
		tag* GetBegin() const;
		tag* GetEnd() const;
	private:
		size_t index_from_head = 0;
		size_t index_from_tail = 0;
	};

	
	template<typename T>
	void FourWayPointer<T>::SetLeft(FourWayPointer<T>::tag* ptr)
	{
		index_from_head++;
		this->left_ptr->SetRight(ptr);
		ptr->SetRight(this);
	}

	template<
		typename Key,typename Value,typename IndexOrderIndicator,typename MemoryIndicator,
		typename InsertIndicator,typename EarseIndicator
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
			operator const Key&()
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
