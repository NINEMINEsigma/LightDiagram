#include<Core/some_features.h>

using namespace std;

namespace ld
{
	namespace resources
	{
		string GetLoadPath(_Inout_ LPOPENFILENAMEA file)
		{
			if (::GetOpenFileNameA(file))
			{
				return file->lpstrFile;
			}
			return "";
		}

		string GetLoadPath(LPCSTR labelAndfilter)
		{
			OPENFILENAMEA targetFile = { 0 };
			char path[MAX_PATH] = { 0 };

			targetFile.lStructSize = sizeof(OPENFILENAMEA);
			targetFile.hwndOwner = nullptr;
			targetFile.hInstance = (HINSTANCE)GetModuleHandle(NULL);
			targetFile.lpstrFilter = (LPCSTR)labelAndfilter;
			targetFile.lpstrFile = path;
			targetFile.nMaxFile = MAX_PATH;
			targetFile.Flags = OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

			string result = GetLoadPath(&targetFile);

			return result;
		}
	}

	process_creater::process_creater(bool is_wait, string commandline):__init(is_wait)
	{
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
	}
	process_creater::process_creater(bool is_wait, string executer, string commandline_args):__init(is_wait)
	{
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
	}
	process_creater::operator bool() const noexcept
	{
		return stats;
	}
	process_creater::~process_creater()
	{
		if (stats)
		{
			if (is_wait)
				WaitForSingleObject(pinfo.hProcess, INFINITE);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
		}
	}
}
