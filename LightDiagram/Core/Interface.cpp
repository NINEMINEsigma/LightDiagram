#include<Core/Header/ArchCom/Interface.h>

namespace ld
{
    ConsolePro DefaultConsolePro;
	IAnyArchitecture::~IAnyArchitecture() {}
	ICanInitialize::~ICanInitialize() {}
	ICanGetArchitecture::~ICanGetArchitecture() {}
	IArchitecture* ICanGetArchitecture::Architecture() const
	{
		return this->architecture;
	}

#pragma region ICanGetSystem

	ICanGetSystem::~ICanGetSystem() {}
	ISystem* ICanGetSystem::GetSystem(const type_info& type) const
	{
		return this->Architecture()->GetSystem(type);
	}

#pragma endregion

#pragma region ICanGetModel

	ICanGetModel::~ICanGetModel() {}
	IModel* ICanGetModel::GetModel(const type_info& type) const
	{
		return this->Architecture()->GetModel(type);
	}

#pragma endregion

#pragma region ICanGetController

	ICanGetController::~ICanGetController() {}
	IController* ICanGetController::GetController(const type_info& type) const
	{
		return this->Architecture()->GetController(type);
	}

#pragma endregion

#pragma region ICanSendCommand

	ICanSendCommand::~ICanSendCommand() {}
	void ICanSendCommand::SendCommand(const type_info& type) const
	{
		this->Architecture()->SendCommand(type);
	}

#pragma endregion

#pragma region ICanMonitorCommand

	ICanMonitorCommand::~ICanMonitorCommand() {}

#pragma endregion

#pragma region IArchitecture

	IArchitecture*	IArchitecture::RegisterMessageStream() {}
	IArchitecture*	IArchitecture::AddMessage(IArchitecture::string message) const
	{
		DefaultConsolePro.LogMessage(message);
	}
	IArchitecture*	IArchitecture::AddWarning(IArchitecture::string message) const
	{
		DefaultConsolePro.LogWarning(message);
	}
	IArchitecture*	IArchitecture::AddError(IArchitecture::string message) const
	{
		DefaultConsolePro.LogError(message);
	}

    bool				IArchitecture::Contains(const type_info& type) const
	{
		return this->objects_container.count(type.hash_code());
	}
    IAnyArchitecture*	IArchitecture::ToolGetComponent(const type_info & type) const
	{
		if(this->objects_container.count(type.hash_code()))
		{
			return this->objects_container[type.hash_code()];
		}
		else
		{
			AddWarning("Target component not found");
			return nullptr;
		}
	}
	ISystem*			IArchitecture::GetSystem(const type_info& type) const
	{
		IAnyArchitecture* component = this->ToolGetComponent(type);
		if(component)
		{
			ISystem* result = dynamic_cast<ISystem*>(component);
			if(result) return result;
			else AddWarning("Target component is not a system");
		}
		return nullptr;
	}
	IModel*				IArchitecture::GetModel(const type_info& type) const
	{
		IAnyArchitecture* component = this->ToolGetComponent(type);
		if(component)
		{
			IModel* result = dynamic_cast<IModel*>(component);
			if(result) return result;
			else AddWarning("Target component is not a model");
		}
		return nullptr;
	}
	IController*		IArchitecture::GetController(const type_info& type) const
	{
		IAnyArchitecture* component = this->ToolGetComponent(type);
		if(component)
		{
			IController* result = dynamic_cast<IController*>(component);
			if(result) return result;
			else AddWarning("Target component is not a controller");
		}
		return nullptr;
	}

    IArchitecture*	IArchitecture::Register(const type_info& type,IAnyArchitecture * instance)
	{
		if(instance)
		{
			if(this->Contains(type)) 
				this->AddError("Target component already registered");
			else
			{
				this->objects_container[type.hash_code()] = instance;
				this->AddMessage(IArchitecture::string("Target component[slot=")+type.name()+", real="+
				typeid(*instance).name()+"] registered");
			}
		}
		return this;
	}
    IArchitecture*	IArchitecture::RegisterModel(const type_info& type,IModel * model)
	{
		if(model)
		{
			if(this->Contains(type)) 
				this->AddError("Target model already registered");
			else
				this->Register(type,model);
		}
		return this;
	}
    IArchitecture*	IArchitecture::RegisterSystem(const type_info& type,ISystem * system)
	{
		if(system)
		{
			if(this->Contains(type)) 
				this->AddError("Target system already registered");
			else
				this->Register(type,system);
		}
		return this;
	}
    IArchitecture*	IArchitecture::RegisterController(const type_info& type,IController * controller)
	{
		if(controller)
		{
			if(this->Contains(type)) 
				this->AddError("Target controller already registered");
			else
				this->Register(type,controller);
		}
		return this;
	}
    IArchitecture*	IArchitecture::RegisterCommand(const type_info& type,ICommand * command)
	{
		if(command)
		{
			if(this->Contains(type)) 
				this->AddError("Target command already registered");
			else
				this->Register(type,command);
		}
		return this;
	}
	
	IArchitecture*	IArchitecture::UnRegister(const type_info& type)
	{
		if(this->Contains(type))
		{
			this->AddMessage(IArchitecture::string("Target component[slot=")+type.name()+", real="+
			typeid(*this->objects_container[type.hash_code()]).name()+"] registered");
			this->objects_container.erase(type.hash_code());
		}
		return this;
	}

#pragma endregion

}
