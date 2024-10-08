#ifndef __FILE_SOME_FEATURES
#define __FILE_SOME_FEATURES

#include <Core/LF_Config.h>
#include <Core/static_indicator.h>

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
}

#endif // !__FILE_SOME_FEATURES
