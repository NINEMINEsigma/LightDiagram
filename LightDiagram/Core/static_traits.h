#ifndef __FILE_STATIC_TRAITS
#define __FILE_STATIC_TRAITS

#include "anyclass.h"
#include "static_indicator.h"
#include "static_exist.h"
#include "LF_Type.h"

#pragma region Traits (Static)

_LF_C_API(Class) 
any_trait_base:	_LF_Inherited(any_class)
{
public:
	using string = typename string_indicator::tag;

	const char* read_symbol_name() const;
	const string& read_any_name() const;
	const type_info& read_type() const;
	auto read_type_hash() const;
protected:
	any_trait_base(const char* symbol_name, const string & func_name, const type_info & symbol_type);
private:
	const char* single_name;
	string name;
	const type_info& _type;
};

#define _LFramework_Kit_API_StaticOperatorBool(boolen)	operator bool() { return boolen ; }

#pragma region function_traits

/*
	fail to get function information
*/
template<typename _T> _LF_C_API(OStruct)
function_traits
{
	_LFramework_Kit_API_StaticOperatorBool(false);
	using tag = void;
	constexpr static bool value = false;

	using result = bad_indicator;
	using parameters = bad_indicator;
	using belong = unknown_indicator;
	using call = unknown_indicator;
	using consting = unconst_indicator;
	using typen = LDType_Bad_Indicator;

	template<class ThisType> using extension_func = function_traits<ThisType>;
};

/*
	get regular function information
*/
template<typename Ret, typename... Args> _LF_C_API(OStruct) function_traits<Ret(Args...)> Symbol_Endl
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(*)(Args...);
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = namespace_indicator;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
	using noexcepting = except_indicator;
	using typen = LDType<tag>;

	template<class ThisType> using extension_func = function_traits<Ret(ThisType*, Args...)>;
};

/*
	get regular function information
*/
template<typename Ret> _LF_C_API(OStruct) function_traits<Ret(void)> Symbol_Endl
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(*)();
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<void>;
	using belong = namespace_indicator;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
	using noexcepting = except_indicator;
	using typen = LDType<tag>;

	template<class ThisType> using extension_func = function_traits<Ret(ThisType*)>;
};

#pragma region class function const type

/*
	get const member function information
*/
template<typename Ret, typename C, typename... Args> _LF_C_API(OStruct) function_traits<Ret(C::*)(Args...) const> Symbol_Endl
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(C::*)(Args...) const;
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = const_indicator;
	using noexcepting = except_indicator;
	using typen = LDType<tag>;

	template<class ThisType> using extension_func = function_traits<Ret(C::*)(ThisType*, Args...) const>;
};

/*
	get const member function information
*/
template<typename Ret, typename C > _LF_C_API(OStruct) function_traits<Ret(C::*)() const> Symbol_Endl
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(C::*)() const;
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<void>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = const_indicator;
	using noexcepting = except_indicator;
	using typen = LDType<tag>;

	template<class ThisType> using extension_func = function_traits<Ret(C::*)(ThisType*) const>;
};

#pragma endregion

#pragma region class function non-symbol

/*
	get unconst member function information
*/
template<typename Ret, typename C, typename... Args> _LF_C_API(OStruct) function_traits<Ret(C::*)(Args...)> Symbol_Endl
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(C::*)(Args...);
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
	using noexcepting = except_indicator;
	using typen = LDType<tag>;

	template<class ThisType> using extension_func = function_traits<Ret(C::*)(ThisType*, Args...)>;
};

/*
	get unconst member function information
*/
template<typename Ret, typename C> _LF_C_API(OStruct) function_traits<Ret(C::*)()> Symbol_Endl
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(C::*)();
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<void>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
	using noexcepting = except_indicator;
	using typen = LDType<tag>;

	template<class ThisType> using extension_func = function_traits<Ret(C::*)(ThisType*)>;
};

#pragma endregion

#ifdef __Using_Noexcept_Func_Traits

#pragma region class function noexcept

#pragma region class function const type

/*
	get const noexcept member function information
*/
template<typename Ret, typename C, typename... Args> _LF_C_API(OStruct) function_traits<Ret(C::*)(Args...) const noexcept> Symbol_Endl
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(C::*)(Args...) const;
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = const_indicator;
	using noexcepting = noexcept_indicator;
	using typen = LDType<tag>;

	template<class ThisType> using extension_func = function_traits<Ret(C::*)(ThisType*, Args...) const noexcept>;
};

/*
	get const noexcept member function information
*/
template<typename Ret, typename C > _LF_C_API(OStruct) function_traits<Ret(C::*)() const noexcept> Symbol_Endl
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(C::*)() const;
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<void>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = const_indicator;
	using noexcepting = noexcept_indicator;
	using typen = LDType<tag>;

	template<class ThisType> using extension_func = function_traits<Ret(C::*)(ThisType*) const noexcept>;
};

#pragma endregion

#pragma region class function non-symbol

/*
	get unconst noexcept member function information
*/
template<typename Ret, typename C, typename... Args> _LF_C_API(OStruct) function_traits<Ret(C::*)(Args...) noexcept> Symbol_Endl
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(C::*)(Args...);
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<Args...>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
	using noexcepting = noexcept_indicator;
	using typen = LDType<tag>;

	template<class ThisType> using extension_func = function_traits<Ret(C::*)(ThisType*, Args...) noexcept>;
};

/*
	get unconst noexcept member function information
*/
template<typename Ret, typename C> _LF_C_API(OStruct) function_traits<Ret(C::*)() noexcept> Symbol_Endl
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = Ret(C::*)();
	constexpr static bool value = true;

	using result = Ret;
	using parameters = type_list<void>;
	using belong = C;
	using call = _cdecl_indicator;
	using consting = unconst_indicator;
	using noexcepting = noexcept_indicator;
	using typen = LDType<tag>;

	template<class ThisType> using extension_func = function_traits<Ret(C::*)(ThisType*) noexcept>;
};

#pragma endregion

#pragma endregion

#endif // __Using_Noexcept_Func_Traits

/*
	get regular function information
*/
template<typename T, typename = template_fill_indicator> 
_LF_C_API(OStruct) function_traits_ex : public function_traits<T>
{
	using function_traits_indicator = function_traits<T>;
};
/*
	get lambda or Functor information
*/
template<typename Lambda>
_LF_C_API(OStruct) function_traits_ex<Lambda, std::void_t<decltype(&Lambda::operator())>> : public function_traits<decltype(&Lambda::operator())>
{
	using function_traits_indicator = function_traits<decltype(&Lambda::operator())>;
};

#pragma endregion

#pragma region field_traits

/*
	get regular field information
*/
template<typename _T> _LF_C_API(OStruct)
field_traits
{
	_LFramework_Kit_API_StaticOperatorBool(true);
	using tag = _T;
	constexpr static bool value = true;

	using origin = _T;
	using typen = LDType<tag>;
};

template<typename _Ret,typename... Args> _LF_C_API(OStruct)
field_traits<_Ret(*)(Args...)>
{
	_LFramework_Kit_API_StaticOperatorBool(false);
	using tag = _Ret(*)(Args...);
	constexpr static bool value = false;

	using origin = tag;
	using typen = LDType<tag>;
};

template<typename _Ret, typename _C, typename... Args> _LF_C_API(OStruct)
field_traits<_Ret(_C::*)(Args...)>
{
	_LFramework_Kit_API_StaticOperatorBool(false);
	using tag = _Ret(*)(Args...);
	constexpr static bool value = false;

	using origin = tag;
	using typen = LDType<tag>;
};

/*
	get regular field information
*/
template<typename T>
_LF_C_API(OStruct)
field_traits_ex : public field_traits<T>
{
	using field_traits_indicator = void;
	using decay = generate_full_decay_typen<T>;
};

#pragma endregion

#define LF_not_void_return(cond)			LF_return(is_bad_indicator_v<cond>)

#pragma region function_info

_LF_C_API(Class) function_base;
template<typename func> _LF_C_API(TClass) function_info;

_LF_C_API(Class)
function_base:	_LF_Inherited(any_trait_base)
{
public:
	template<typename _func>
	friend const function_info<_func>& create_or_get_function_info(const _func & func_ptr, const char* function_name);

	using string = typename string_indicator::tag;

	function_base(function_base&) = delete;
	function_base(function_base&&) = delete;

	using function_bases_type = std::map<size_t, function_base*>;
protected:
	function_base(const char* symbol_name, const string & func_name, const type_info & symbol_type);
private:
	static function_bases_type function_bases;
};

template<typename func>
_LF_C_API(TClass)
function_info:	_LF_Inherited(function_base)
{
public:
	using string = typename string_indicator::tag;
private:
	function_info(const func & func_ptr, const char* symbol_name, const string & func_name, const type_info & symbol_type) :
		function_base(symbol_name, func_name, symbol_type),
		any_trait_base(symbol_name, func_name, symbol_type),
		invoker(func_ptr) {}
public:
	template<typename _func>
	friend const function_info<_func>& create_or_get_function_info(const _func & func_ptr, const char* function_name);

	using tag = func;
	constexpr static bool value = true;

	using trait = function_traits_ex<func>;
	using result = typename trait::result;
	using parameters = typename trait::parameters;
	using belong = typename trait::belong;

private:
	function_info(const func & func_ptr, const char* function_name) :
		function_info(func_ptr, function_name,
			string(typeid(result).name()) + " [" + typeid(belong).name() + "]::" + function_name + "(" + get_type_list_string<parameters>() + ")",
			typeid(func)) {}
public:
	function_info(function_info&) = delete;
	function_info(function_info&&) = delete;
	const func invoker;

	template<typename... Args>
	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke(belong * instance, Args... args) const
	{
		if constexpr (std::is_same_v<parameters, type_list<Args...>>)
		{
			if constexpr (std::is_same_v<belong, namespace_indicator>)
			{
				if constexpr (std::is_same_v<result, void>)
				{
					invoker(args...);
					return 0;
				}
				else
				{
					return invoker(args...);
				}
			}
			else
			{
				if constexpr (std::is_same_v<result, void>)
				{
					((*instance).*invoker)(args...);
					return 0;
				}
				else
				{
					return ((*instance).*invoker)(args...);
				}
			}
		}
		else
		{
			static_assert(std::is_same_v<parameters, type_list<Args...>>, "invoke args check type: failed");
		}
	}
	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke(belong * instance) const
	{
		if constexpr (std::is_same_v<parameters, type_list<void>>)
		{
			if constexpr (std::is_same_v<belong, namespace_indicator>)
			{
				if constexpr (std::is_same_v<result, void>)
				{
					invoker();
					return 0;
				}
				else
				{
					return invoker();
				}
			}
			else
			{
				if constexpr (std::is_same_v<result, void>)
				{
					((*instance).*invoker)();
					return 0;
				}
				else
				{
					return ((*instance).*invoker)();
				}
			}
		}
		else
		{
			static_assert(std::is_same_v<parameters, type_list<void>>, "invoke args check type: failed");
		}
	}
	template<typename... Args>
	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke(belong& instance, Args... args) const
	{
		if constexpr (std::is_same_v<parameters, type_list<Args...>>)
		{
			if constexpr (std::is_same_v<belong, namespace_indicator>)
			{
				if constexpr (std::is_same_v<result, void>)
				{
					invoker(args...);
					return 0;
				}
				else
				{
					return invoker(args...);
				}
			}
			else
			{
				if constexpr (std::is_same_v<result, void>)
				{
					(instance.*invoker)(args...);
					return 0;
				}
				else
				{
					return (instance.*invoker)(args...);
				}
			}
		}
		else
		{
			static_assert(std::is_same_v<parameters, type_list<Args...>>, "invoke args check type: failed");
		}
	}
	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke(belong& instance) const
	{
		if constexpr (std::is_same_v<parameters, type_list<void>>)
		{
			if constexpr (std::is_same_v<belong, namespace_indicator>)
			{
				if constexpr (std::is_same_v<result, void>)
				{
					invoker();
					return 0;
				}
				else
				{
					return invoker();
				}
			}
			else
			{
				if constexpr (std::is_same_v<result, void>)
				{
					(instance.*invoker)();
					return 0;
				}
				else
				{
					return (instance.*invoker)();
				}
			}
		}
		else
		{
			static_assert(std::is_same_v<parameters, type_list<void>>, "invoke args check type: failed");
		}
	}
	template<typename... Args>
	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke(const belong& instance, Args... args) const
	{
		if constexpr (std::is_same_v<parameters, type_list<Args...>>)
		{
			if constexpr (std::is_same_v<belong, namespace_indicator>)
			{
				if constexpr (std::is_same_v<result, void>)
				{
					invoker(args...);
					return 0;
				}
				else
				{
					return invoker(args...);
				}
			}
			else
			{
				if constexpr (std::is_same_v<result, void>)
				{
					(instance.*invoker)(args...);
					return 0;
				}
				else
				{
					return (instance.*invoker)(args...);
				}
			}
		}
		else
		{
			static_assert(std::is_same_v<parameters, type_list<Args...>>, "invoke args check type: failed");
		}
	}
	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke(const belong& instance) const
	{
		if constexpr (std::is_same_v<parameters, type_list<void>>)
		{
			if constexpr (std::is_same_v<belong, namespace_indicator>)
			{
				if constexpr (std::is_same_v<result, void>)
				{
					invoker();
					return 0;
				}
				else
				{
					return invoker();
				}
			}
			else
			{
				if constexpr (std::is_same_v<result, void>)
				{
					(instance.*invoker)();
					return 0;
				}
				else
				{
					return (instance.*invoker)();
				}
			}
		}
		else
		{
			static_assert(std::is_same_v<parameters, type_list<void>>, "invoke args check type: failed");
		}
	}

	template<typename... Args>
	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke_uncheck(belong * instance, Args... args) const
	{
		if constexpr (std::is_same_v<belong, namespace_indicator>)
		{
			if constexpr (std::is_same_v<result, void>)
			{
				invoker(args...);
				return 0;
			}
			else
			{
				return invoker(args...);
			}
		}
		else
		{
			if constexpr (std::is_same_v<result, void>)
			{
				((*instance).*invoker)(args...);
				return 0;
			}
			else
			{
				return ((*instance).*invoker)(args...);
			}
		}
	}

	typename choose_type < std::is_same_v<void, result>, int, result >::tag invoke_uncheck(belong * instance) const
	{
		if constexpr (std::is_same_v<belong, namespace_indicator>)
		{
			if constexpr (std::is_same_v<result, void>)
			{
				invoker();
				return 0;
			}
			else
			{
				return invoker();
			}
		}
		else
		{
			if constexpr (std::is_same_v<result, void>)
			{
				((*instance).*invoker)();
				return 0;
			}
			else
			{
				return ((*instance).*invoker)();
			}
		}
	}

private:

};

template<typename func>
const function_info<func>& create_or_get_function_info(const func& func_ptr, const char* function_name)
{
	if (!function_base::function_bases.count(typeid(func).hash_code()))
	{
		function_base::function_bases[typeid(func).hash_code()] = new function_info(func_ptr, function_name);
	}
	return *dynamic_cast<function_info<func>*>(function_base::function_bases[typeid(func).hash_code()]);
}

using func_base = const function_base&;

#define make_function_info(belong,name)		create_or_get_function_info(& belong::name, #name )
#define func_base							const function_base&
#define func_info 							const auto&

#pragma endregion

#pragma region field_info

_LF_C_API(Class) field_base;
template<typename field, typename C> _LF_C_API(TClass) field_info;

_LF_C_API(Class)
field_base:	_LF_Inherited(any_trait_base)
{
private:
	struct maper_sorter
	{
		bool operator() (const char* lhs, const char* rhs) const
		{
			return strcmp(lhs, rhs) < 0;
		}
	};
public:
	template<typename _field, typename _C>
	friend const field_info<_field, _C>& create_or_get_field_info(_field _C:: * _right_ptr, const char* field_name);
	template<typename _field, typename _C>
	friend const field_info<_field, _C>& create_or_get_field_info(size_t _offset, const char* field_name);

	using string = typename string_indicator::tag;

	field_base(function_base&) = delete;
	field_base(function_base&&) = delete;

	using map_container = std::map<const char*, field_base*, maper_sorter>;
	using field_bases_type = std::map<size_t, map_container>;

	virtual void* get(void* instance) const = 0;
	virtual void set(void* instance, void* value) const = 0;
	template<typename T>
	void set_rv(void* instance, T && value) const
	{
		set(instance, &value);
	}

protected:
	field_base(const char* symbol_name, const string& field_name, const type_info& symbol_type);
private:
	static field_bases_type field_bases;
};

template<typename field, typename C = namespace_indicator>
_LF_C_API(TClass)
field_info: _LF_Inherited(field_base)
{
public:
	using string = typename string_indicator::tag;
private:
	field_info(size_t _offset, const char* symbol_name, const string & field_name, const type_info & symbol_type) :
		field_base(symbol_name, field_name, symbol_type),
		any_trait_base(symbol_name, field_name, symbol_type),
		offset(_offset) {}
public:
	template<typename _field, typename _C>
	friend const field_info<_field, _C>& create_or_get_field_info(_field _C:: * _right_ptr, const char* field_name);
	template<typename _field, typename _C>
	friend const field_info<_field, _C>& create_or_get_field_info(size_t _offset, const char* field_name);

	using tag = field;
	constexpr static bool value = true;
	using belong = C;

	using trait = field_traits_ex<field>;
private:
	field_info(field C:: * _right_ptr, const char* field_name) :
		field_info(
			reinterpret_cast<size_t>(*(void**)(&_right_ptr)),
			field_name,
			string(typeid(C).name()) + "::" + field_name,
			typeid(field)) {}
	field_info(const size_t & _offset, const char* field_name) :
		field_info(
			_offset,
			field_name,
			string(typeid(C).name()) + "::" + field_name,
			typeid(field)) {}
public:
	field_info(field_info&) = delete;
	field_info(field_info&&) = delete;
	const size_t offset;

	void set(C * instance, field & arg) const
	{
		if constexpr (std::is_same_v<C, namespace_indicator>)
		{
			*static_cast<field*>(reinterpret_cast<void*>(offset)) = arg;
		}
		else
		{
			*((field*)((size_t)instance + offset)) = arg;
		}
	}
	void set(C * instance, field && arg) const
	{
		if constexpr (std::is_same_v<C, namespace_indicator>)
		{
			*static_cast<field*>(reinterpret_cast<void*>(offset)) = std::move(arg);
		}
		else
		{
			*((field*)((size_t)instance + offset)) = std::move(arg);
		}
	}
	virtual void set(void* instance, void* value) const override
	{
		set(static_cast<C*>(instance), *static_cast<field*>(value));
	}

	field& get(C * instance) const
	{
		if constexpr (std::is_same_v<C, namespace_indicator>)
		{
			return *static_cast<field*>(reinterpret_cast<void*>(offset));
		}
		else
		{
			return *((field*)((size_t)instance + offset));
		}
	}
	virtual void* get(void* instance) const override
	{
		return &get(static_cast<C*>(instance));
	}
};

template<typename field, typename C>
const field_info<field, C>& create_or_get_field_info(field C::* _right_ptr, const char* field_name)
{
	if (!field_base::field_bases[typeid(C).hash_code()].count(field_name))
	{
		field_base::field_bases[typeid(C).hash_code()][field_name] = new field_info<field, C>(_right_ptr, field_name);
	}
	return *dynamic_cast<field_info<field, C>*>(field_base::field_bases[typeid(C).hash_code()][field_name]);
}
template<typename field, typename C>
const field_info<field, C>& create_or_get_field_info(size_t _offset, const char* field_name)
{
	if (!field_base::field_bases[typeid(C).hash_code()].count(field_name))
	{
		field_base::field_bases[typeid(C).hash_code()][field_name] = new field_info<field, C>(_offset, field_name);
	}
	return *dynamic_cast<field_info<field, C>*>(field_base::field_bases[typeid(C).hash_code()][field_name]);
}

#define make_field_info(belong,name)		create_or_get_field_info( &belong::name, #name )
#define fvar_base							const field_base&
#define fvar_info							const auto&

#pragma endregion

template<typename T>
_LF_C_API(OStruct) 
LDType_Traits
{
	using tag_function = function_traits_ex<T>;
	using tag_field = field_traits_ex<T>;

	using tag = T;
	constexpr static bool value = tag_field::value != tag_function::value;
	using type_indicator = key_indicator;
};

#pragma endregion

#pragma region extension_func_traits

template<typename FullType>struct extension_func_traits
{
	using tag = bad_indicator(FullType);
	constexpr static bool value = false;
};

template<typename ThisType, typename ResultType, typename... Args>
struct extension_func_traits<type_list<ThisType,ResultType(Args...)>>
{
	using tag = ResultType(ThisType, Args...);
	constexpr static bool value = true;
};
template<typename ThisType, typename ResultType,class Belong, typename... Args>
struct extension_func_traits<type_list<ThisType, ResultType(Belong::*)(Args...)>>
{
	using tag = ResultType(Belong::*)(ThisType, Args...);
	constexpr static bool value = true;
};
template<typename ThisType, typename ResultType, class Belong, typename... Args>
struct extension_func_traits<type_list<ThisType, ResultType(Belong::*)(Args...) const>>
{
	using tag = ResultType(Belong::*)(ThisType, Args...) const;
	constexpr static bool value = true;
};

#pragma endregion

#define define_any_exist(funcname,func) \
if_func_exist_def(funcname);\
template<typename T>\
constexpr auto if_tc_##funcname##_exist = if_func_exist(funcname) < T, func > ;

define_any_exist(GetType, const type_info&());
define_any_exist(ToString, std::string());
define_any_exist(SymbolName, std::string());
define_any_exist(GetClone, any_class*());

#undef define_any_exist

#endif // !__FILE_STATIC_TRAITS
