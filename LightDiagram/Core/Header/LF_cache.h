#pragma once

#include<Core/Header/LF_Config.h>
#define Symbol_Push :

namespace ld
{
    _LF_C_API(Class) IBase;
    _LF_C_API(Class) IBaseMap;

    // Implementations for runtime entities or data , The relevant interfaces are : 
    //    IBaseMap is the type used to convert to local data
    _LF_C_API(Class)
        IBase Symbol_Push
    _LF_Inherited(any_class)
    {
    protected:
        IBase();
    public:
        virtual IBase& operator=(const IBase&) abstract;
        virtual ~IBase();
        virtual void ToMap(_Out_ IBaseMap * BM) abstract;
        virtual bool FromMap(_In_ IBaseMap * from) abstract;
    };

    // Implementations for cache data , The relevant interfaces are : 
    //      IBase is the type used to convert to runtime entities or data
    _LF_C_API(Class)
        IBaseMap Symbol_Push
    _LF_Inherited(any_class)
    {
    protected:
        IBaseMap();
    public:
        virtual IBaseMap& operator=(const IBaseMap&) abstract;
        virtual ~IBaseMap();
        virtual void ToInstance(_Out_ IBase * obj) abstract;
        virtual bool FromInstance(_In_ IBase * from) abstract;
    };

}
