//*
//  Copyright (c) 2024, liu bai, ninemine
//  All rights reserved.
//*

//*
//	_Source_DLL_EXPORT Defined is to export
//	_Source_DLL_IMPORT Defined is to import
//	Both no will be complate on local
//*

//*
//	__REF_BOOST Defined is to include boost headers
//	You need to use Boost_Root to focus on those files
//	like: include_directories("C:\Boost") -> C:\Boost\boost\align.hpp ...
//	lib is also need install on Path youself
// 
//	->At Boost, you can define __REF_PYTHON to include <boost/python.hpp>
//*

//*
//	__REF_EASYX Defined is to include easyx headers
//*

#define NOMINMAX

#ifndef __FILE_LIGHTDIAGRAM

#define __FILE_LIGHTDIAGRAM

//*
//	Single Toolkit
//*

#if defined(_LINUX_ON_WINDOW_)||defined(_WINDOW_)
#include<Core/beepkit.h>
#endif

//*
//	Header
//*

#include<Core/some_features.h>
#include<Core/LF_Config.h>
#if defined(_LINUX_ON_WINDOW_)
#include <Core/uni_utility.h>
#endif
#include<Core/LF_Type.h>
#include<Core/anyclass.h>
#include<Core/LF_Cache.h>
#include<Core/LF_Exception.h>
#include<Core/LF_RAII.h>
#include<Core/LF_Container.h>

_LF_C_API(OClass) ld_test
{
public:
	ld_test() {}
};

#include<Core/LF_Architecture.h>

#endif // !__FILE_LIGHTDIAGRAM
