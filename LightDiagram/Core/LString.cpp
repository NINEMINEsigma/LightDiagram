#include "LString.h"

using namespace std;
using namespace ld::internal;

namespace ld
{
	[[nodiscard]]
	size_t strlen(const char* str)
	{
		return ::strnlen_s(str, max_strlen_return);
	}
	[[nodiscard]]
	size_t strlen(const std::string& str)
	{
		return str.length();
	}
	[[nodiscard]]
	size_t strlen(const wchar_t* str)
	{
		return ::wcsnlen_s(str, max_strlen_return);
	}
	[[nodiscard]]
	size_t strlen(const std::wstring& str)
	{
		return str.length();
	}

	namespace internal
	{
		struct string_impl_data_source
		{
			instance<ld_internal_string_impl> source;
			map<ld_internal_string_impl_unit, instance<string_impl_data_source>> leafs;
		};

		//static 
			instance<string_impl_data_source> impl_mapper(empty_indicator{});

		instance<ld_internal_string_impl> bulidup_lstring_memory(const void* start, const void* end, size_t unit_size, size_t length)
		{
			// init env
			if (impl_mapper.empty())
				impl_mapper = new_indicator{};
			if (impl_mapper->source.empty())
				impl_mapper->source = ld_internal_string_impl{};
			// empty source
			if (start >= end)
			{
				return impl_mapper->source;
			}
			// if single unit is too big, impl's item-size will unsupport it
			if (unit_size > LString::max_unit_size)
				throw exception("bulidup_lstring_memory error: unit_size > LString::max_unit_size");
			char* buffer = (char*)::malloc(unit_size / sizeof(char));
			instance<string_impl_data_source> current_impl_mapper = impl_mapper;
			while (start < end)
			{
				// get current unit
				memset(buffer, 0, unit_size / sizeof(char));
				memmove_s(buffer, unit_size / sizeof(char), start, 1);
				ld_internal_string_impl_unit current = *reinterpret_cast<ld_internal_string_impl_unit*>(buffer);

				// build up and find
				do
				{
					if (current_impl_mapper->leafs[current].empty())
					{
						current_impl_mapper->leafs[current] = new_indicator{};
					}
					if (current_impl_mapper->leafs[current]->source.empty())
					{
						current_impl_mapper->leafs[current]->source = current_impl_mapper->source.get_ref() + current;
					}
				} while (false);

				// next step
				start = reinterpret_cast<void*>(reinterpret_cast<size_t>(start) + unit_size);
				current_impl_mapper = current_impl_mapper->leafs[current];
			}
			// release and return
			::free(buffer);
			return current_impl_mapper->source;
		}
		
	}

	// empty build up
	LString::LString() :string_index(empty_indicator{}) {}

	// build up by LString
	LString::LString(LString& from) noexcept : string_index(from.string_index) {}
	LString::LString(LString&& from) noexcept : string_index(std::move(from.string_index)) {}
	LString::LString(const LString& from) noexcept : string_index(from.string_index) {}
	
	// init on memory block
	LString::LString(const void* ch_start, const void* ch_end, size_t unit_size) :
		string_index(bulidup_lstring_memory(
			ch_start, 
			ch_end,
			unit_size,
			(reinterpret_cast<size_t>(ch_end) - reinterpret_cast<size_t>(ch_start)) / unit_size)) {}
	LString::LString(const void* ch, size_t unit_size, size_t length) :
		LString(
			ch, 
			reinterpret_cast<void*>(reinterpret_cast<size_t>(ch) + unit_size * length), 
			unit_size) {}

	// init on short
	LString::LString(const char* cstr) :LString(cstr, strlen(cstr)) {}
	LString::LString(const char* cstr, size_t size) :
		string_index(bulidup_lstring_memory(
			cstr,
			cstr + size, 
			sizeof(char),
			size)) {}
	// init on width
	LString::LString(const wchar_t* cwstr) :LString(cwstr, strlen(cwstr)) {}
	LString::LString(const wchar_t* cwstr, size_t size):
		string_index(bulidup_lstring_memory(
			cwstr, 
			cwstr + size,
			sizeof(wchar_t),
			size)) {}
	LString::~LString()
	{

	}

	std::string LString::ToString() const
	{
		if (this->string_index.empty())
			return "";
		else
			return to_xstring<char>(this->string_index.get_ref());
	}
	std::string LString::SymbolName() const
	{
		return "LString";
	}
	LString::operator std::string() const
	{
		return this->ToString();
	}
}

namespace std
{
	std::string to_string(const ld::LString& str)
	{
		return str.ToString() + "\0";
	}
}
