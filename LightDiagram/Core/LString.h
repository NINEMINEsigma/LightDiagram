#ifndef _FILE_LSTRING
#define _FILE_LSTRING

#include <Core/LF_Config.h>
#include <Core/anyclass.h>
#include <Core/LF_Exception.h>

namespace ld
{
	template<typename _First>
	inline std::string go_string(_First&& first)
	{
		return
			to_string(std::forward<_First>(first));
	}
	template<typename _First, typename _LeftT>
	inline std::string go_string(_First&& first, _LeftT&& arg)
	{
		return 
			std::to_string(std::forward<_First>(first)) +
			std::to_string(std::forward<_LeftT>(arg));
	}
	template<typename _First, typename... Args>
	inline std::string go_string(_First&& first, Args&&...args)
	{
		return 
			to_string(std::forward<_First>(first)) +
			go_string<std::string>(std::forward<Args>(args)...);
	}

	// 使用前缀和的形式构建的通用字符串
	// 并使用并查技术池化, 同时通过string_index定向
	// 适用于尽量少的增删操作和尽量多的对比字符串的场景下
	_LF_C_API(Class) LString Symbol_Push public any_class
	{
	public:
		using string_index = size_t;
		constexpr static string_index disable = 0;
	private:
		string_index u_index = 0;
	public:
		LString(const std::string& str);
		LString(const std::wstring& wstr);
		LString(const LString& from) noexcept;
		LString& operator=(const LString& from) noexcept;
		virtual ~LString();

		bool operator==(const LString& from) noexcept;
		operator std::string() const;

		virtual std::string ToString() const override;
		std::wstring ToWString() const;

		static void ReSetMemory();
	};
}

namespace std
{
	Symbol_Extern _LF_C_API(Func) 
		std::string to_string(const ld::LString& str);
}

#endif // !_FILE_LSTRING
