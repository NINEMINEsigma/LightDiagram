#ifndef __FILE_SOME_FEATURES
#define __FILE_SOME_FEATURES

#include <Core/LF_Config.h>
#include <Core/static_indicator.h>

namespace ld
{
	namespace resources
	{
		using string = string_indicator::tag;

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
}

#endif // !__FILE_SOME_FEATURES
