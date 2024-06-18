#ifndef __FILE_LF_CACHE

#define __FILE_LF_CACHE

#include<Core/Header/LF_Config.h>
#include<Core/Header/anyclass.h>

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
        virtual IBase& operator=(const IBase&) =0;
        virtual ~IBase();
        virtual void ToMap(_Out_ IBaseMap * BM) =0;
        virtual bool FromMap(_In_ IBaseMap * from) =0;
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
        virtual IBaseMap& operator=(const IBaseMap&) =0;
        virtual ~IBaseMap();
        virtual void ToInstance(_Out_ IBase * obj) =0;
        virtual bool FromInstance(_In_ IBase * from) =0;
    };

}

#endif // !__FILE_LF_CACHE
