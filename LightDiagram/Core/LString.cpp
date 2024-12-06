#include "LString.h"

using namespace std;
using namespace ld::internal;

namespace ld
{
	[[nodiscarded]]
	size_t strlen(const char* str)
	{
		return ::strnlen_s(str, max_strlen_return);
	}
	[[nodiscarded]]
	size_t strlen(const std::string& str)
	{
		return str.length();
	}
	[[nodiscarded]]
	size_t strlen(const wchar_t* str)
	{
		return ::wcsnlen_s(str, max_strlen_return);
	}
	[[nodiscarded]]
	size_t strlen(const std::wstring& str)
	{
		return str.length();
	}

	namespace internal
	{
		class ld_internal_string_impl
		{
		public:
			std::string ToString() const
			{
				return "";
			}
		};
	}

	// empty build up
	LString::LString() :string_index(empty_indicator{}) {}

	// build up by LString
	LString::LString(LString& from) noexcept : string_index(from.string_index) {}
	LString::LString(LString&& from) noexcept : string_index(std::move(from.string_index)) {}
	LString::LString(const LString& from) noexcept : string_index(from.string_index) {}
	
	// init on memory block
	LString::LString(const void* ch_start, const void* ch_end, size_t unit_size) :
		string_index(bulidup_lstring_memory(ch_start, ch_end, unit_size, reinterpret_cast<size_t>(ch_end) - reinterpret_cast<size_t>(ch_start)) / unit_size) {}
	LString::LString(const void* ch, size_t unit_size, size_t length) :LString(ch, reinterpret_cast<void*>(reinterpret_cast<size_t>(ch) + unit_size * length), unit_size) {}

	// init on short
	LString::LString(const char* cstr) :LString(cstr, strlen(cstr)) {}
	LString::LString(const char* cstr, size_t size = 0) :
		string_index(bulidup_lstring_memory(cstr, cstr + size, sizeof(char), size)) {}
	// init on width
	LString::LString(const wchar_t* cwstr) :LString(cwstr, strlen(cwstr)) {}
	LString::LString(const wchar_t* cwstr, size_t size = 0):
		string_index(bulidup_lstring_memory(cwstr, cwstr + size, sizeof(char), size)) {}
	LString::~LString()
	{

	}

	std::string LString::ToString() const
	{
		if (this->string_index.empty())
			return "";
		else
			return this->string_index->ToString();
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
		return str.ToString();
	}
}
