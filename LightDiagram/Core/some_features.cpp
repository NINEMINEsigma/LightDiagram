#include<Core/some_features.h>

using namespace std;

namespace ld
{
	namespace resources
	{
#ifdef _WINDOW_

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

#endif // !_WINDOW_
	}
}
