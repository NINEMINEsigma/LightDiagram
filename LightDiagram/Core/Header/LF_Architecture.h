#ifndef __FILE_LF_ARCHITECTURE

#define __FILE_LF_ARCHITECTURE

//*
//	The Ligdiagram Architecture is a LineFramework Architecture 
//	with a simplified version of Alpadiagram
//*

#include<Core/Header/LF_Config.h>
#include<Core/Header/static_traits.h>
#include<Core/Header/LF_Exception.h>

#include<Core/Header/ArchCom/Interface.h>

namespace ld
{
    // When first use this function to obtain architecture's instance
    // the instance will be generate, but it will be never delete
    // Generate Process ->new TargetArch() -> Init()
    template<typename TargetArch>
    TargetArch&     _LF_C_API(TDLL) ArchitectureInstance()
    {
        static_assert(std::is_base_of_v<IArchitecture, TargetArch>, "TargetArch need be architecture");
        if (ArchitectureInstance(typeid(TargetArch)) == nullptr)
            return *dynamic_cast<TargetArch*>(ArchitectureInstance(typeid(TargetArch)), new TargetArch());
        else
            return *dynamic_cast<TargetArch*>(ArchitectureInstance(typeid(TargetArch)));
    }

    // End target architecture life
    template<typename TargetArch>
    void            _LF_C_API(TDLL) ArchitectureDestory()
    {
        ArchitectureDestory(typeid(TargetArch));
    }

    template<typename Arch, typename SlotType>
    SlotType*       _LF_C_API(TDLL) RegisterOn(_In_ SlotType* component)
    {
        IArchitecture& arch = *ArchitectureInstance(typeid(TargetArch));
        arch.Register(typeid(SlotType), component);
        return component;
    }

    template<typename Arch, typename SlotType>
    bool            _LF_C_API(TDLL) UnRegisterOn()
    {
        IArchitecture& arch = *ArchitectureInstance(typeid(TargetArch));
        if (arch.Contains(typeid(SlotType)))
        {
            arch.UnRegister(typeid(SlotType));
            return true;
        }
        else return false;
    }

    template<typename Arch, typename SlotType>
    bool            _LF_C_API(TDLL) ContainsOn()
    {
        IArchitecture& arch = *ArchitectureInstance(typeid(TargetArch));
        return arch.Contains(typeid(SlotType)))
    }

    template<typename Arch, typename SlotType>
    void            _LF_C_API(TDLL) TrySendOn()
    {
        IArchitecture& arch = *ArchitectureInstance(typeid(TargetArch));
        arch.SendCommand(typeid(SlotType));
    }

    template<typename Arch, typename SlotType, typename Target>
    void            _LF_C_API(TDLL) TrySendTo()
    {
        IArchitecture& arch = *ArchitectureInstance(typeid(TargetArch));
        arch.SendCommand(typeid(SlotType), typeid(Target));
    }

    template<typename Arch, typename SlotType>
    void            _LF_C_API(TDLL) TryDiffusingOn()
    {
        IArchitecture& arch = *ArchitectureInstance(typeid(TargetArch));
        arch.Diffusing(typeid(SlotType));
    }
}

#endif // !__FILE_LF_ARCHITECTURE
