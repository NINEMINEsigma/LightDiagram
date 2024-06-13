#pragma once

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

#include<Core/Header/LF_Config.h>
#include<Core/Header/static_exist.h>
#include<Core/Header/static_indicator.h>
#include<Core/Header/LF_Type.h>
#include<Core/Header/static_traits.h>
#include<Core/Header/anyclass.h>

_LF_C_API(Class) ld_test
{
public:
	ld_test();
};

//*
//	Architecture
//*

#pragma region SAL

#ifndef _In_
#define _In_
#endif // !_In_
#ifndef _Out_
#define _Out_
#endif // !_Out_

#pragma endregion

namespace ld
{
    _LF_C_API(Class) IBase;
    _LF_C_API(Class) IBaseS;
    _LF_C_API(Class) IBaseMap;
}


namespace ld
{
    using string = string_indicator::tag;

#ifndef _CUSTOM_CLOG
    std::ofstream clog;
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

#pragma region AD_I

    //Implementations for runtime entities or data , The relevant interfaces are : 
    //    IBaseMap is the type used to convert to local data
    //    IBase{T} This type is used for stronger constraints and clear goals
    _LF_C_API(Class)    IBase:  _LF_Inherited(any_class)
    {
    protected:
        IBase();
        IBase(const IBase&);
    public:
        IBase& operator=(const IBase&);
        virtual ~IBase();
        virtual void ToMap(_Out_ IBaseMap * BM) abstract;
        virtual bool FromMap(_In_ IBaseMap * from) abstract;
    };

    //A strongly constrained version of IBase
    _LF_C_API(Class)    IBaseS: _LF_Inherited(IBase)
    {
    protected:
        IBaseS(const type_info& type_id);
        IBaseS(const IBaseS&);
        const type_info& hash_bind_id;
        virtual void ToMapS(_Out_ IBaseMap * BM) abstract;
        virtual bool FromMapS(_In_ IBaseMap * from) abstract;
    public:
        virtual ~IBaseS();
        IBaseS& operator=(const IBaseS&);
        virtual void ToMap(_Out_ IBaseMap * BM) override final;
        virtual bool FromMap(_In_ IBaseMap * from) override final;

    }


        /// <summary>
        /// Implementations for cache data , The relevant interfaces are : 
        /// <para><see cref="IBase"/> is the type used to convert to runtime entities or data</para>
        /// <para><see cref="IBaseMap{T}"/> This type is used for stronger constraints and clear goals</para>
        /// </summary>
        public interface IBaseMap
    {
        void ToObject(out IBase obj);
        bool FromObject(IBase from);
        string Serialize();
        bool Deserialize(string source);
    }

    /// <summary>
    /// A strongly constrained version of <see cref="IBaseMap"/>
    /// </summary>
    /// <typeparam name="T">The target type of <see cref="IBase{T}"/> you want to match</typeparam>
    public interface IBaseMap<T> : IBaseMap where T : class, IBase, new()
    {
        void ToObject(out T obj);
        bool FromObject(T from);
    }
#pragma endregion
}
