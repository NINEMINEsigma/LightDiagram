#ifndef __FILE_PROCESS
#define __FILE_PROCESS

#include <Core/LF_Config.h>
#include <Core/LF_RAII.h>

namespace ld
{
	_LF_C_API(Class) process_creater
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		STARTUPINFOA start_info;
		PROCESS_INFORMATION pinfo;
#endif // _WINDOW_
		bool stats;
		bool is_wait;
	public:
		process_creater(bool is_wait, std::string commandline);
		process_creater(bool is_wait, std::string executer, std::string commandline_args);
		process_creater(const process_creater&) = delete;
		virtual ~process_creater();
		operator bool() const noexcept;
	};
}

#endif // !__FILE_PROCESS
