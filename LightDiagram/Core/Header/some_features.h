#ifndef __FILE_SOME_FEATURES

#define __FILE_SOME_FEATURES

//use define : _USE_DEFINED_CALL_
#if defined(_USE_DEFINED_CALL_)&&!defined(_USE_DEFINED_CALL_DEFINED)//&&!defined(_MSC_VER)

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

#endif // !__FILE_SOME_FEATURES
