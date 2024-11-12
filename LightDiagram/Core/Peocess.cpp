#if 0
#include<Core/Process.h>

using namespace std;

namespace ld
{
	process_creater::process_creater(bool is_wait, string commandline) :__init(is_wait)
	{
#ifdef _WINDOW_
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
#endif // _WINDOW_
	}
	process_creater::process_creater(bool is_wait, string executer, string commandline_args) :__init(is_wait)
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
	process_creater::operator bool() const noexcept
	{
		return stats;
	}
	process_creater::~process_creater()
	{
#if defined(_WINDOW_)||defined(_LINUX_ON_WINDOW_)
		if (stats)
		{
			if (is_wait)
				WaitForSingleObject(pinfo.hProcess, INFINITE);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
		}
#endif
	}
}

#endif