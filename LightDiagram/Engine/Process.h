#ifndef __FILE_PROCESS
#define __FILE_PROCESS

#include<Core/LF_Config.h>

namespace ld
{
	_LF_C_API(Class) process_kit
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		using start_info_type = STARTUPINFOA;
		using process_info_type = PROCESS_INFORMATION;
#else defined(_LINUX_)

#endif // _WINDOW_
	private:
		start_info_type start_info;
		process_info_type pinfo;
		bool stats;
	public:
		using config_type = int;

		using tag = void;
		constexpr static bool value = true;

		process_kit();
		process_kit(std::string commandline, const config_type & config = 0);
		process_kit(std::string executer, std::string commandline_args, const config_type & config = 0);
		process_kit(const process_kit&) = delete;
		virtual ~process_kit();
		bool get_stats() const noexcept;

#if 0
		static bool run(std::string commandline, const config_type & config = 0);
		static bool run(std::string executer, std::string commandline_args, const config_type & config = 0);
#endif
	};
}

#endif // !__FILE_PROCESS
