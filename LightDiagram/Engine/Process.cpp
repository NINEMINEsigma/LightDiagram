#include<Engine/Process.h>

using namespace std;

namespace ld
{
	process_kit::process_kit() :stats(false), start_info({}), pinfo({}) {}
	process_kit::process_kit(
		std::string commandline,
		const config_type& config) :process_kit()
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		memset(&start_info, 0, sizeof(start_info));
		char* cl = new char[commandline.size() + 10];
		strcpy(cl, commandline.c_str());
		start_info.cb = sizeof(start_info);
		if (CreateProcessA(
			0,
			cl,
			0,
			0,
			FALSE,
			NORMAL_PRIORITY_CLASS,
			0,
			0,
			&start_info,
			&pinfo))
		{
			stats = true;
		}
		else
			stats = false;
		delete[] cl;
#else defined(_LINUX_)

#endif
	}
	process_kit::process_kit(
		std::string executer,
		std::string commandline_args,
		const config_type& config) :process_kit()
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		auto exepath = executer.c_str();
		memset(&start_info, 0, sizeof(start_info));
		string clstr = executer + " " + commandline_args;
		char* cl = new char[clstr.size() + 10];
		strcpy(cl, clstr.c_str());
		start_info.cb = sizeof(start_info);
		if (CreateProcessA(
			exepath,
			cl,
			0,
			0,
			FALSE,
			NORMAL_PRIORITY_CLASS,
			0,
			0,
			&start_info,
			&pinfo))
		{
			stats = true;
		}
		else
			stats = false;
		delete[] cl;
#else defined(_LINUX_)

#endif
	}

	process_kit::~process_kit()
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		if (stats)
		{
			WaitForSingleObject(pinfo.hProcess, INFINITE);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
		}
#else defined(_LINUX_)

#endif
	}
	bool process_kit::get_stats() const noexcept
	{
		return stats;
	}

#if 0
	bool process_kit::run(
		std::string commandline,
		const config_type& config)
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		start_info_type temp_start_info;
		process_info_type temp_pinfo;
		bool result = false;
		memset(&temp_start_info, 0, sizeof(temp_start_info));
		char* cl = new char[commandline.size() + 10];
		strcpy(cl, commandline.c_str());
		temp_start_info.cb = sizeof(temp_start_info);
		result = CreateProcessA(
			0,
			cl,
			0,
			0,
			FALSE,
			NORMAL_PRIORITY_CLASS,
			0,
			0,
			&temp_start_info,
			&temp_pinfo);
		delete[] cl;
#else defined(_LINUX_)

#endif
		return result;
	}
	bool process_kit::run(
		std::string executer,
		std::string commandline_args,
		const config_type& config)
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		start_info_type temp_start_info;
		process_info_type temp_pinfo;
		bool result = false;
		auto exepath = executer.c_str();
		memset(&temp_start_info, 0, sizeof(temp_start_info));
		string clstr = executer + " " + commandline_args;
		char* cl = new char[clstr.size() + 10];
		strcpy(cl, clstr.c_str());
		temp_start_info.cb = sizeof(temp_start_info);
		result = CreateProcessA(
			exepath,
			cl,
			0,
			0,
			FALSE,
			NORMAL_PRIORITY_CLASS,
			0,
			0,
			&temp_start_info,
			&temp_pinfo);
		delete[] cl;
#else defined(_LINUX_)

#endif
		return result;
	}
#endif
}
