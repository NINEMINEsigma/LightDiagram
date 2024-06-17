#ifndef __FILE_ARCH_INTERFACE

#define __FILE_ARCH_INTERFACE

#include<Core/Header/anyclass.h>
#include<Core/Header/LF_Exception.h>

#define PropertyBindToField(name)                               \
void                    set_##name(decltype(name)* value)       \
{                                                               \
    name = value;                                               \
}                                                               \
decltype(*name)&         get_##name() const                      \
{                                                               \
    return *name;                                                \
}

namespace ld
{
    _LF_C_API(Class)    IAnyArchitecture;
    _LF_C_API(Class)    ICanInitialize;
    _LF_C_API(Class)    ICanGetArchitecture;
    _LF_C_API(Class)    IADArchitecture;

    //  The lowest-level interface of all AD Architecture interfaces
    _LF_C_API(Class) IAnyArchitecture: _LF_Inherited(any_class)
    {
    public:
        virtual ~IAnyArchitecture();
    };

    //  Init : used to initialize or reset the class 
    _LF_C_API(Class) ICanInitialize: _LF_Inherited(IAnyArchitecture)
    {
    public:
        virtual ~ICanInitialize();
        virtual void Init() abstract;
    };

    //*
    // Implement this interface to get or set the Architecture
    // IADArchitecture : Target Architecture Interface
    //*
    _LF_C_API(Class) ICanGetArchitecture : _LF_Inherited(IAnyArchitecture)
    {
        IADArchitecture Architecture{ get; set; }
    }
}

#endif // !__FILE_ARCH_INTERFACE
