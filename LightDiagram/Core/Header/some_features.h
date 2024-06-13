#pragma once

//use define : _USE_DEFINED_CALL_
#if defined(_USE_DEFINED_CALL_)&&!defined(_USE_DEFINED_CALL_DEFINED)

#define _USE_DEFINED_CALL_DEFINED
#define __stdcall
#define _stdcall
#define __cdecl
#define _cdecl
#define __fastcall
#define _fastcall
#define __thiscall
#define abstract =0

#endif // _USE_DEFINED_CALL_
