#ifndef __FILE_LIGHTDIAGRAM

#define __FILE_LIGHTDIAGRAM

//*
//  Copyright (c) 2024, liu bai, ninemine
//  All rights reserved.
//*

//*
//	Single Toolkit
//*

#include<Core/Header/beepkit.h>

//*
//_Source_DLL_EXPORT Defined is to export
//_Source_DLL_IMPORT Defined is to import
//both no will be complate on local
//*

//*
//	Header
//*

#include<Core/Header/some_features.h>
#include<Core/Header/LF_Config.h>
#include<Core/Header/static_exist.h>
#include<Core/Header/static_indicator.h>
#include<Core/Header/LF_Type.h>
#include<Core/Header/static_traits.h>
#include<Core/Header/anyclass.h>
#include<Core/Header/LF_cache.h>

_LF_C_API(Class) ld_test
{
public:
	ld_test();
};

//*
//	Architecture
//*

namespace ld
{
    using string = string_indicator::tag;

#ifndef _CUSTOM_CLOG
    extern std::ofstream clog;
#endif // !_CUSTOM_CLOG

    // Commonly used exception
    _LF_C_API(Class)    LDException:    _LF_Inherited(any_class)
    {
        LDException(const time_t & ts, const string & msg);
    public:
        LDException();
        LDException(const string & msg);
        LDException(LDException & ex) noexcept;
        LDException(LDException && ex) noexcept;
        virtual ~LDException();
        void release() const noexcept;
        int* counter;
        string message;
    };


}

#endif // !__FILE_LIGHTDIAGRAM