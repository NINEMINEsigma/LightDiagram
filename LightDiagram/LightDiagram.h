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

#include<Core/LF_Config.h>
#include<Core/static_indicator.h>
#include<Core/static_traits.h>
#include<Core/some_features.h>
#if defined(_LINUX_ON_WINDOW_)
#include <Core/uni_utility.h>
#endif
#include<Core/LF_Type.h>
#include<Core/anyclass.h>
#include<Core/LF_Cache.h>
#include<Core/LF_Exception.h>
#include<Core/LF_Time.h>
#include<Core/LF_RAII.h>
#include<Core/LF_Container.h>
#include<Core/algorithm.h>
#include<Core/anygraph.h>

#include<Core/LF_Architecture.h>

#pragma region IO QUES

#define check_ans(name)\
			do\
			{\
				auto __res = next<std::remove_reference_t<std::remove_cv_t<decltype(name)>>>(anss);\
				if(anss)\
				{\
				if (__res == name)\
					std::cout << name << " ";\
				else\
					std::cout << ld::ConsoleColor::Red << name << "(" << __res << ") " << ld::ConsoleColor::None;\
				}\
				else std::cout << ld::ConsoleColor::Red << name << "<empty, no ans> " << ld::ConsoleColor::None;\
			}while(false)
#define try_solve_io_ques(__path__)\
using namespace ld;\
using namespace std; \
int main()\
{\
	GlobalExceptionInit\
		tool_file __dir__(ques_path);\
		auto dir_itor = __dir__.get_dir_itor();\
		int e = 0;\
		for(auto&& _ : dir_itor) e++;\
		for (int i = 1; i <= e; i++)\
		{\
			console.LogMessage(to_string(i));\
			string path = __path__;\
			tool_file input(path + to_string(i) + ".in");\
			input.redirect_cin();\
			auto anss = ifstream(path + to_string(i) + ".ans");\
			solve(anss);\
			next<string>(anss);\
			if (anss)\
			{\
				cout << ConsoleColor::Red << "ans is not end " << ConsoleColor::None;\
			}\
			cin.sync();\
			cin.clear();\
			cout << "\n------------------------------------------" << endl;\
		}\
	GlobalExcpetionApply;\
	console.LogMessage(string("any binding ptr count: ") + to_string(get_size_indicator_count()));\
}

#pragma endregion

//*
//	Engine
//*

#include<Engine/Process.h>

#endif // !__FILE_LIGHTDIAGRAM
