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
    TargetArch& _LF_C_API(TDLL) ArchitectureInstance()
    {
        static_assert(std::is_base_of_v<IArchitecture, TargetArch>, "TargetArch need be architecture");
        if (ArchitectureInstance(typeid(TargetArch)) == nullptr)
            return *dynamic_cast<TargetArch*>(ArchitectureInstance(typeid(TargetArch), new TargetArch()));
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
    SlotType* _LF_C_API(TDLL) RegisterOn(_In_ SlotType* component)
    {
        IArchitecture& arch = *ArchitectureInstance(typeid(Arch));
        arch.Register(typeid(SlotType), component);
        return component;
    }

    template<typename Arch, typename SlotType>
    bool            _LF_C_API(TDLL) UnRegisterOn()
    {
        IArchitecture& arch = *ArchitectureInstance(typeid(Arch));
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
        IArchitecture& arch = *ArchitectureInstance(typeid(Arch));
        return arch.Contains(typeid(SlotType));
    }

    template<typename Arch, typename SlotType>
    void            _LF_C_API(TDLL) TrySendOn()
    {
        IArchitecture& arch = *ArchitectureInstance(typeid(Arch));
        arch.SendCommand(typeid(SlotType));
    }

    template<typename Arch, typename SlotType, typename Target>
    void            _LF_C_API(TDLL) TrySendTo()
    {
        IArchitecture& arch = *ArchitectureInstance(typeid(Arch));
        arch.SendCommand(typeid(SlotType), typeid(Target));
    }

    template<typename Arch, typename SlotType>
    void            _LF_C_API(TDLL) TryDiffusingOn()
    {
        IArchitecture& arch = *ArchitectureInstance(typeid(Arch));
        arch.Diffusing(typeid(SlotType));
    }

    //*
    //  When Func is <Returner>(<void>), OnExecute[send command] is enable to call Listener 
    //*
    template<typename Func>
    _LF_C_API(TClass)
        LDEvent Symbol_Push
        _LF_Inherited(ICommand)
    {
    public:
        using tag = std::function<Func>;
        using func_container = std::vector<tag>;
        func_container functions;

        LDEvent& AddListener(const tag & func)
        {
            functions.push_back(func);
            return *this;
        }
        LDEvent& AddListener(const LDEvent & event)
        {
            for (auto& i : event.functions) AddListener(i);
            return *this;
        }
        LDEvent& AddListener(const func_container & event)
        {
            for (auto& i : event) AddListener(i);
            return *this;
        }
        LDEvent& RemoveListener(const tag & func)
        {
            functions.erase(std::find(functions.begin(), functions.end(), func));
            return *this;
        }
        LDEvent& ClearListeners()
        {
            functions.clear();
            return *this;
        }

        using traits = function_traits_ex<Func>;
        using traits_indicator = typename traits::function_traits_indicator;
        using result = typename traits::result;
        using parameters = typename traits::parameters;
        using belong = typename traits::belong;
        using call = typename traits::call;
        using consting = typename traits::consting;
        using typen = typename traits::typen;

        using OnInvokeResult = typename choose_type<std::is_same_v<result, void>, void, std::vector<result>&>::tag;
        using HoldInvokeResult = typename choose_type<std::is_same_v<OnInvokeResult, void>, bool, OnInvokeResult>::tag;

        typename generate_full_decay_typen<HoldInvokeResult>::unrefer result_data;

        template<typename... Args>
        OnInvokeResult OnInvoke(Args... args)
        {
            if constexpr (std::is_same_v<OnInvokeResult, void>)
            {
                for (auto& i : this->functions)
                {
                    i(args...);
                }
            }
            else
            {
                for (auto& i : this->functions)
                {
                    result_data.push_back(i(args...));
                }
                return result_data;
            }
        }

        LDEvent() {}
        LDEvent(const tag & func)
        {
            AddListener(func);
        }
        LDEvent(LDEvent & right)noexcept
        {
            this->functions = right.functions;
        }
        LDEvent(LDEvent && right) noexcept
        {
            this->functions = std::move(right.functions);
        }
        virtual ~LDEvent()
        {
            this->ClearListeners();
        }
        virtual void OnExecute() override
        {
            if constexpr (std::is_same_v<parameters, type_list<void>>)
            {
                this->Invoke();
            }
        }

        template<typename... Args>
        OnInvokeResult operator()(Args... args)
        {
            this->OnInvoke(args...);
            if constexpr (!std::is_same_v<OnInvokeResult, void>)
            {
                return result_data;
            }
        }

        void operator+=(const tag & func)
        {
            this->AddListener(func);
        }
        void operator+=(const LDEvent & event)
        {
            this->AddListener(event);
        }
        void operator+=(const func_container & event)
        {
            this->AddListener(event);
        }
        void operator-=(const tag & func)
        {
            this->RemoveListener(func);
        }

        template<typename Array>
        void sort(const Array & order)
        {
            if constexpr (!std::is_same_v<OnInvokeResult, void>)
            {
                decltype(result_data) new_data;
                for (auto& i : order)
                {
                    new_data.push_bask(result_data[i]);
                }
                result_data = new_data;
            }
        }
    };
}

#endif // !__FILE_LF_ARCHITECTURE
