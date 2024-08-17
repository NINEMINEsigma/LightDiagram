#include<Core/static_traits.h>

function_base::function_bases_type function_base::function_bases;
field_base::field_bases_type field_base::field_bases;


const char* any_trait_base::read_symbol_name() const
{
	return single_name;
}
const any_trait_base::string& any_trait_base::read_any_name() const
{
	return name;
}
const type_info& any_trait_base::read_type() const
{
	return _type;
}
auto any_trait_base::read_type_hash() const
{
	return _type.hash_code();
}

any_trait_base::any_trait_base(
	const char* symbol_name, 
	const string& func_name,
	const type_info& symbol_type) :
	single_name(symbol_name),
	name(func_name),
	_type(symbol_type) {}

function_base::function_base(
	const char* symbol_name,
	const string& func_name,
	const type_info& symbol_type) :
	any_trait_base(symbol_name, func_name, symbol_type) {}

field_base::field_base(
	const char* symbol_name,
	const string& field_name, 
	const type_info& symbol_type) :
	any_trait_base(symbol_name, field_name, symbol_type) {}
