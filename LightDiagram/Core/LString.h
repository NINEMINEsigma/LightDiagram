#ifndef _FILE_LSTRING
#define _FILE_LSTRING

#include "LF_Config.h"
#include "anyclass.h"
#include "LF_Exception.h"
#include "LF_RAII.h"

namespace ld
{
	constexpr static size_t max_strlen_return = 1 << 18;
	using ld_internal_string_impl_unit = size_t;

	extern _LF_C_API(Func) [[nodiscard]] size_t strlen(const char* str);
	extern _LF_C_API(Func) [[nodiscard]] size_t strlen(const std::string& str);
	extern _LF_C_API(Func) [[nodiscard]] size_t strlen(const wchar_t* str);
	extern _LF_C_API(Func) [[nodiscard]] size_t strlen(const std::wstring& str);

	namespace internal
	{
		using ld_internal_string_impl = std::basic_string<ld_internal_string_impl_unit>;
		extern _LF_C_API(Func) instance<ld_internal_string_impl> bulidup_lstring_memory(const void* start,const void* end, size_t unit_size, size_t length);
		//extern _LF_C_API(Func) 
	}

	using string_index_type = instance<internal::ld_internal_string_impl>;

	_LF_C_API(Class) LString Symbol_Push public any_class
	{
		string_index_type string_index;
	public:
		constexpr static size_t max_unit_size = sizeof(ld_internal_string_impl_unit);

		// empty build up
		LString();
		// build up by LString
		LString(LString& from) noexcept;
		LString(LString&& from) noexcept;
		LString(const LString& from) noexcept;
		// init on short
		LString(const char* cstr);
		LString(const char* cstr, size_t size);
		template<size_t size>
		LString(char cstr[size]) :LString(cstr, size) {}
		// init on width
		LString(const wchar_t* cwstr);
		LString(const wchar_t* cwstr, size_t size);
		template<size_t size>
		LString(wchar_t cwstr[size]) :LString(cwstr, size) {}
		// init on memory block
		LString(const void* ch_start, const void* ch_end, size_t unit_size);
		LString(const void* ch, size_t unit_size, size_t length);
		// build up by string
		template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
		LString(const std::basic_string<_Elem, _Traits, _Alloc>& str) :
			LString(str.c_str(), sizeof(_Elem), str.size()) {}
		virtual ~LString();

		virtual std::string ToString() const override;
		virtual std::string SymbolName() const override;
		operator std::string() const;

		template<typename _CharTy>
		std::basic_string<_CharTy> GetString() const
		{
			return std::to_xstring<_CharTy>(string_index);
		}
	};
}

namespace std
{
	Symbol_Extern _LF_C_API(Func) 
		std::string to_string(const ld::LString& str);
}

#endif // !_FILE_LSTRING
