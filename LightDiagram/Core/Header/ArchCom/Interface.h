#ifndef __FILE_ARCH_INTERFACE

#define __FILE_ARCH_INTERFACE

#include<Core/Header/anyclass.h>
#include<Core/Header/LF_Exception.h>

#define _LFramework_API_BindingTo(name,type) _LFramework_API_PropertyBindToField##type ( name )

namespace ld
{
    _LF_C_API(Class)    IAnyArchitecture;
    _LF_C_API(Class)    ICanInitialize;
    _LF_C_API(Class)    ICanGetArchitecture;
    _LF_C_API(Class)    ICanGetSystem;
    _LF_C_API(Class)    ICanGetModel;
    _LF_C_API(Class)    ICanGetController;
    _LF_C_API(Class)    ICanSendCommand;
    _LF_C_API(Class)    ICanMonitorCommand;

    _LF_C_API(Class)    ISystem;
    _LF_C_API(Class)    IModel;
    _LF_C_API(Class)    IController;
    _LF_C_API(Class)    ICommand;
    _LF_C_API(Class)    IArchitecture;

    //  The lowest-level interface of all <AD> Architecture interfaces
    _LF_C_API(Class) IAnyArchitecture Symbol_Push
        _LF_Inherited(any_class)
    {
    public:
        virtual ~IAnyArchitecture();
    };

    //  Init : used to initialize or reset the class 
    _LF_C_API(Class) ICanInitialize Symbol_Push
        _LF_Inherited(IAnyArchitecture)
    {
    public:
        virtual ~ICanInitialize();
        virtual void Init() abstract;
    };

    //*
    // Implement this interface to get or set the Architecture
    // IADArchitecture : Target Architecture Interface
    //*
    _LF_C_API(Class) ICanGetArchitecture Symbol_Push
        _LF_Inherited(IAnyArchitecture)
    {
        IArchitecture* architecture;
        _LF_API(BindingTo)(architecture, Ptr)
    public:
        friend IArchitecture;
        virtual ~ICanGetArchitecture();
        IArchitecture* Architecture() const;
    };

    //  Can get System from Architecture
    _LF_C_API(Class) ICanGetSystem Symbol_Push
        _LF_Inherited(ICanGetArchitecture)
    {
    public:
        virtual ~ICanGetSystem();
        ISystem* GetSystem(const type_info & type) const;
    };

    //  Can get Model from Architecture
    _LF_C_API(Class) ICanGetModel Symbol_Push
        _LF_Inherited(ICanGetArchitecture)
    {
    public:
        virtual ~ICanGetModel();
        IModel* GetModel(const type_info & type) const;
    };

    //  Can get Controller from Architecture
    _LF_C_API(Class) ICanGetController Symbol_Push
        _LF_Inherited(ICanGetArchitecture)
    {
    public:
        virtual ~ICanGetController();
        IController* GetController(const type_info & type) const;
    };

    //  Can obtain Command from Architecture and send them
    _LF_C_API(Class) ICanSendCommand Symbol_Push
        _LF_Inherited(ICanGetArchitecture)
    {
    public:
        virtual ~ICanSendCommand();
        void SendCommand(const type_info & type) const;
    };

    //  When target command is diffusion on Architecture, it invoke <OnCommandInvoke>
    _LF_C_API(Class) ICanMonitorCommand Symbol_Push
        _LF_Inherited(ICanGetArchitecture)
    {
    public:
        virtual ~ICanMonitorCommand();
        virtual void OnCommandInvoke(const type_info & type) abstract;
        virtual const type_info& GetCommandType() const abstract;
    };

    extern ConsolePro DefaultConsolePro;

    _LF_C_API(Class)    ISystem Symbol_Push
        _LF_Inherited(ICanInitialize) Symbol_Link
        _LF_Inherited(ICanGetArchitecture) Symbol_Link
        _LF_Inherited(ICanGetSystem) Symbol_Link
        _LF_Inherited(ICanGetModel) Symbol_Link
        _LF_Inherited(ICanGetController) Symbol_Link
        _LF_Inherited(ICanSendCommand)
    {
        
    }
    {

    }
    _LF_C_API(Class) IModel
    {

    }
    _LF_C_API(Class) IController
    {

    }
    _LF_C_API(Class) ICommand
    {

    }

    //*
    //  By implementing this interface, you can customize the real behavior of Architectures
    //      ->  The relevant behaviour interfaces are : IADCommand, IADController, IADModel, IADSystem
    //      ->  The relevant invoker interfaces are : ICanSendCommand, ICanMonitorCommand
    //*
    _LF_C_API(Class)    IArchitecture Symbol_Push
        _LF_Inherited(ICanInitialize) Symbol_Link
        _LF_Inherited(ICanGetArchitecture) Symbol_Link
        _LF_Inherited(ICanGetSystem) Symbol_Link
        _LF_Inherited(ICanGetModel) Symbol_Link
        _LF_Inherited(ICanGetController) Symbol_Link
        _LF_Inherited(ICanSendCommand)
    {
        using objects_container_type = std::map<size_t, IAnyArchitecture*>;
        objects_container_type objects_container;
    private:
        /// <summary>
        /// Obtain target component on this architecture
        /// </summary>
        /// <param name="type">:please use typeid(type) to get arg</param>
        /// <returns>If exist, return ptr, otherwise nullptr</returns>
        IAnyArchitecture* ToolGetComponent(const type_info & type) const;
    public:
        IArchitecture();
        IArchitecture(const IArchitecture&) = delete;
        virtual ~IArchitecture();

#pragma region Message

        using string = string_indicator::tag;

        /// <summary>
        /// virtual function, you need to override it 
        /// </summary>
        /// <returns>Itself</returns>
        virtual IArchitecture* RegisterMessageStream();
        /// <summary>
        /// Save the messages generated during the Architecture running
        /// </summary>
        /// <param name="message">:Target message</param>
        /// <returns>Itself</returns>
        IArchitecture* AddMessage(string message) const;
        /// <summary>
        /// Save the warning generated during the Architecture running
        /// </summary>
        /// <param name="message">:Target message</param>
        /// <returns>Itself</returns>
        IArchitecture* AddWarning(string message) const;
        /// <summary>
        /// Save the error message generated during the Architecture running
        /// </summary>
        /// <param name="message">:Target message</param>
        /// <returns>Itself</returns>
        IArchitecture* AddError(string message) const;

#pragma endregion

#pragma region Get
        /// <summary>
        /// Obtain model on this architecture
        /// </summary>
        /// <param name="model_type">:please use typeid(type) to get arg</param>
        /// <returns>If exist, return ptr, otherwise nullptr</returns>
        IModel* GetModel(const type_info & model_type);
        /// <summary>
        /// Obtain system on this architecture
        /// </summary>
        /// <param name="system_type">:please use typeid(type) to get arg</param>
        /// <returns>If exist, return ptr, otherwise nullptr</returns>
        ISystem* GetSystem(const type_info & system_type);
        /// <summary>
        /// Obtain controller on this architecture
        /// </summary>
        /// <param name="model_type">:please use typeid(type) to get arg</param>
        /// <returns>If exist, return ptr, otherwise nullptr</returns>
        IController* GetController(const type_info & controller_type);
#pragma endregion

#pragma region Register By Instance
        IArchitecture* RegisterModel(const type_info& type,IModel * model);
        IArchitecture* RegisterSystem(const type_info& type,ISystem * system);
        IArchitecture* RegisterController(const type_info& type,IController * controller);
        IArchitecture* RegisterCommand(const type_info& type,ICommand * command);
#pragma endregion

#pragma region Send Command Execute By OnExecute()
        IArchitecture* SendCommand(const type_info & command_type);
#pragma endregion

#pragma region Send Command Or Diffusing Command To Target
        IArchitecture* Diffusing(const type_info & command_type);
        IArchitecture* SendCommand(const type_info & command_type, const type_info & monitor_tyoe);
#pragma endregion

#pragma region Register Or UnRegister Or Contains
        IArchitecture* UnRegister(const type_info& type);
        IArchitecture* Register(const type_info& type,IAnyArchitecture * instance);
        bool Contains(const type_info& type) const;
#pragma endregion
    };
    
    // When first use this function to obtain architecture's instance
    // the instance will be generate, but it will be never delete
    // Generate Process ->new TargetArch() -> Init()
    template<typename TargetArch>
    TargetArch* ArchitectureInstance()
    {
        static_assert(std::is_base_of<IArchitecture, TargetArch>::value, "TargetArch must be derived from IArchitecture");
        static TargetArch* instance = nullptr;
        if (instance == nullptr) 
        {
            instance = new TargetArch();
            IArchitecture* arch = instance;
            arch->Init();
            arch->AddMessage("Architecture Instance Generated");
        }
        return instance;
    }
}

#endif // !__FILE_ARCH_INTERFACE
