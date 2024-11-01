#ifndef __FILE_SOME_FEATURES
#define __FILE_SOME_FEATURES

#include <Core/LF_Config.h>
#include <Core/static_indicator.h>
#include<Core/anyclass.h>

namespace ld
{
	namespace resources
	{
#ifdef _WINDOW_
		using string = std::string;

		string _LF_C_API(Func) GetLoadPath(_Inout_ LPOPENFILENAMEA file);

		string _LF_C_API(Func) GetLoadPath(LPCSTR labelAndfilter);

#endif
	}

	_LF_C_API(Class) process_creater
	{
#if defined(_WINDOW_)
		STARTUPINFOA start_info;
		PROCESS_INFORMATION pinfo;
#endif // _WINDOW_
		bool stats;
		bool is_wait;
	public:
		process_creater(bool is_wait,std::string commandline);
		process_creater(bool is_wait, std::string executer, std::string commandline_args);
		process_creater(const process_creater&) = delete;
		virtual ~process_creater();
		operator bool() const noexcept;
	};
}

#endif // !__FILE_SOME_FEATURES
