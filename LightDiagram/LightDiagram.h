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

#ifndef __FILE_LIGHTDIAGRAM

#define __FILE_LIGHTDIAGRAM

//*
//	Single Toolkit
//*

#if defined(_LINUX_ON_WINDOW_)||defined(_WINDOW_)
#include<Core/Header/beepkit.h>
#endif

//*
//	Header
//*

#include<Core/Header/some_features.h>
#include<Core/Header/LF_Config.h>
#if defined(_LINUX_ON_WINDOW_)
#include <Core/Header/uni_utility.h>
#endif
#include<Core/Header/LF_Type.h>
#include<Core/Header/anyclass.h>
#include<Core/Header/LF_Cache.h>
#include<Core/Header/LF_Exception.h>
//#include<Core/Header/LF_Container.h>

_LF_C_API(Class) ld_test
{
public:
	ld_test();
};

#include<Core/Header/LF_Architecture.h>

//*
//	Extension
//*

#include<Extension/Header/KitSocket.h>

//*
//	Utility
//*

#include <Utility/FileSystem.h>

#endif // !__FILE_LIGHTDIAGRAM
