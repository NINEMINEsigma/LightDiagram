#ifndef _FILE_LSTRING
#define _FILE_LSTRING

#include "LF_Config.h"
#include "anyclass.h"
#include "LF_Exception.h"

namespace ld
{


	_LF_C_API(Class) LString Symbol_Push public any_class
	{

	};
}

namespace std
{
	Symbol_Extern _LF_C_API(Func) 
		std::string to_string(const ld::LString& str);
}

#endif // !_FILE_LSTRING
