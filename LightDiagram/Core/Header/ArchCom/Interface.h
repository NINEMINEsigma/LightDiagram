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

    _LF_C_API(Class) ICanGetSystem Symbol_Push
        _LF_Inherited(ICanGetArchitecture)
    {
    public:
        virtual ~ICanGetSystem();
        ISystem* GetSystem(const type_info & type);
    };

    _LF_C_API(Class) ICanGetModel Symbol_Push
        _LF_Inherited(ICanGetArchitecture)
    {
    public:
        virtual ~ICanGetModel();
        IModel* GetModel(const type_info & type);
    };

    _LF_C_API(Class) ICanGetController Symbol_Push
        _LF_Inherited(ICanGetArchitecture)
    {
    public:
        virtual ~ICanGetController();
        IController* GetController(const type_info & type);
    };

    _LF_C_API(Class) ICanSendCommand Symbol_Push
        _LF_Inherited(ICanGetArchitecture)
    {
    public:
        virtual ~ICanSendCommand();
        void SendCommand(const type_info & type);
    };

    _LF_C_API(Class) ICanMonitorCommand Symbol_Push
        _LF_Inherited(ICanGetArchitecture)
    {
        const type_info& target_type;
    public:
        friend IArchitecture;
        ICanMonitorCommand();
        virtual ~ICanMonitorCommand();
        void OnCommandInvoke(const type_info & type);
    };

    //*
    //  By implementing this interface, you can customize the real behavior of Architectures
    //      ->  The relevant interfaces are : IADCommand, IADController, IADModel, IADSystem
    //*
    _LF_C_API(Class)    IArchitecture Symbol_Push
        _LF_Inherited(ICanInitialize) Symbol_Link
        _LF_Inherited(ICanGetArchitecture) Symbol_Link
        _LF_Inherited(ICanGetSystem) Symbol_Link
        _LF_Inherited(ICanGetModel) Symbol_Link
        _LF_Inherited(ICanGetController) Symbol_Link
        _LF_Inherited(ICanSendCommand)
    {
    public:
        friend ICanGetSystem;
        friend ICanGetModel;
        friend ICanGetController;
        friend ICanSendCommand;

        using string = string_indicator::tag;

        /// <summary>
        /// Save the messages generated during the Architecture running
        /// </summary>
        /// <param name="message">Target message</param>
        /// <returns>Architecture itself</returns>
        IArchitecture* AddMessage(string message);

#pragma region Get
        IModel* GetModel(const type_info & model_type);
        ISystem* GetSystem(const type_info & system_type);
        IController* GetController(const type_info & controller_type);
#pragma endregion

#pragma region Register By Instance
        IArchitecture* RegisterModel(IModel * model);
        IArchitecture* RegisterSystem(ISystem * system);
        IArchitecture* RegisterController(IController * controller);
        IArchitecture* RegisterCommand(ICommand * command);
#pragma endregion

#pragma region Send Command Execute By OnExecute()
        IArchitecture* SendImmediatelyCommand(const type_info & command_type);
        IArchitecture* SendCommand(const type_info & command_type);
#pragma endregion

#pragma region Send Command Or Diffusing Command To Target
        IArchitecture* Diffusing(const type_info & command_type);
        IArchitecture* SendCommand(const type_info & command_type, const type_info & monitor_tyoe);
#pragma endregion

#pragma region Register Or UnRegister Or Contains
        IArchitecture* UnRegister(const type_info& type);
        IArchitecture* Register(IAnyArchitecture * instance);
        bool Contains(const type_info& type);
#pragma endregion
    };
}

#endif // !__FILE_ARCH_INTERFACE
