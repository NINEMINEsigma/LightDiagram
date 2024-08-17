#include<Core/ArchCom/Interface.h>

namespace ld
{
	/// <summary>
	/// No thing happen
	/// </summary>
	/// <param name="ptr"></param>
	void __DefaultAction(IAnyArchitecture* ptr) {}
	/// <summary>
	/// If can init
	/// </summary>
	void __TryInit(ICanInitialize* ptr)
	{
		ptr->Init();
	}

	ConsolePro DefaultConsolePro;
	IAnyArchitecture::~IAnyArchitecture() {}
	ICanInitialize::~ICanInitialize() {}
	ICanGetArchitecture::ICanGetArchitecture():architecture(nullptr){}
	ICanGetArchitecture::~ICanGetArchitecture() {}
	IArchitecture* ICanGetArchitecture::Architecture() const
	{
		return this->architecture;
	}
	IAnyArchitecture::ReleaseAction IAnyArchitecture::WithRelease() const
	{
		return __DefaultAction;
	}
	IAnyArchitecture::BuildupAction IAnyArchitecture::WithBuildup() const
	{
		return __DefaultAction;
	}
	IAnyArchitecture::DestroyAction IAnyArchitecture::WithDestroy() const
	{
		return __DefaultAction;
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

	ISystem::~ISystem() {}
	IModel::~IModel() {}
	IController::~IController() {}
	ICommand::~ICommand() {}

#pragma region IArchitecture

	IArchitecture::IArchitecture()
	{

	}
	IArchitecture::~IArchitecture()
	{
		for (auto& i : this->objects_container)
		{
			IAnyArchitecture* cat = i.second;
			(cat->WithRelease())(cat);
			cat->AsIam(&IArchitecture::ToolTryReleaseComponentArchitectureParent);
			(cat->WithDestroy())(cat);
		}
	}

	IArchitecture* IArchitecture::AddMessage(IArchitecture::string message)
	{
		DefaultConsolePro.LogMessage(message);
		return this;
	}
	IArchitecture* IArchitecture::AddWarning(IArchitecture::string message)
	{
		DefaultConsolePro.LogWarning(message);
		return this;
	}
	IArchitecture* IArchitecture::AddError(IArchitecture::string message)
	{
		DefaultConsolePro.LogError(message);
		return this;
	}
	void IArchitecture::AddMessageConst(IArchitecture::string message) const
	{
		DefaultConsolePro.LogMessage(message);
	}
	void IArchitecture::AddWarningConst(IArchitecture::string message) const
	{
		DefaultConsolePro.LogWarning(message);
	}
	void IArchitecture::AddErrorConst(IArchitecture::string message) const
	{
		DefaultConsolePro.LogError(message);
	}

	bool IArchitecture::Contains(const type_info& type) const
	{
		return this->objects_container.count(type.hash_code());
	}
	IAnyArchitecture* IArchitecture::ToolGetComponent(const type_info& type) const
	{
		if (this->objects_container.count(type.hash_code()))
		{
			return this->objects_container.find(type.hash_code())->second;
		}
		else
		{
			this->AddErrorConst(IArchitecture::string("Target component[") + type.name() + "] not found");
			return nullptr;
		}
	}
	ISystem* IArchitecture::GetSystem(const type_info& type) const
	{
		IAnyArchitecture* component = this->ToolGetComponent(type);
		if (component)
		{
			ISystem* result = dynamic_cast<ISystem*>(component);
			if (result) return result;
			else AddWarningConst("Target component is not a system");
		}
		return nullptr;
	}
	IModel* IArchitecture::GetModel(const type_info& type) const
	{
		IAnyArchitecture* component = this->ToolGetComponent(type);
		if (component)
		{
			IModel* result = dynamic_cast<IModel*>(component);
			if (result) return result;
			else AddWarningConst("Target component is not a model");
		}
		return nullptr;
	}
	IController* IArchitecture::GetController(const type_info& type) const
	{
		IAnyArchitecture* component = this->ToolGetComponent(type);
		if (component)
		{
			IController* result = dynamic_cast<IController*>(component);
			if (result) return result;
			else AddWarningConst("Target component is not a controller");
		}
		return nullptr;
	}

	void IArchitecture::ToolTrySetupComponentArchitectureParent(ICanGetArchitecture* ptr)
	{
		if (ptr->get_architecture())
			this->AddError("Target component is not release from old architecture");
		else
			ptr->set_architecture(this);
	}
	void IArchitecture::ToolTryReleaseComponentArchitectureParent(ICanGetArchitecture* ptr)
	{
		ptr->set_architecture(nullptr);
	}
	IArchitecture* IArchitecture::Register(const type_info& type, IAnyArchitecture* instance)
	{
		if (instance)
		{
			if (this->Contains(type))
				this->AddError("Target component already registered");
			else
			{
				if (instance->AsDynamicPtr<ICanGetArchitecture>()&& 
					instance->AsDynamicPtr<ICanGetArchitecture>()->Architecture())
				{
					throw ld::LDException("Target component registered on other architecture");
				}
				this->objects_container[type.hash_code()] = instance;
				this->AddMessage(IArchitecture::string("Target component[slot=") + type.name() + ", real=" +
					typeid(*instance).name() + "] registered");
				instance
					->IfIam(&IArchitecture::ToolTrySetupComponentArchitectureParent,this)
					->AsIam(__TryInit);
			}
		}
		return this;
	}
	IArchitecture* IArchitecture::RegisterModel(const type_info& type, IModel* model)
	{
		if (model)
		{
			if (this->Contains(type))
				this->AddError("Target model already registered");
			else
				this->Register(type, model);
		}
		return this;
	}
	IArchitecture* IArchitecture::RegisterSystem(const type_info& type, ISystem* system)
	{
		if (system)
		{
			if (this->Contains(type))
				this->AddError("Target system already registered");
			else
				this->Register(type, system);
		}
		return this;
	}
	IArchitecture* IArchitecture::RegisterController(const type_info& type, IController* controller)
	{
		if (controller)
		{
			if (this->Contains(type))
				this->AddError("Target controller already registered");
			else
				this->Register(type, controller);
		}
		return this;
	}
	IArchitecture* IArchitecture::RegisterCommand(const type_info& type, ICommand* command)
	{
		if (command)
		{
			if (this->Contains(type))
				this->AddError("Target command already registered");
			else
				this->Register(type, command);
		}
		return this;
	}

	IArchitecture* IArchitecture::UnRegister(const type_info& type)
	{
		if (this->Contains(type))
		{
			IAnyArchitecture* cat = this->objects_container[type.hash_code()];
			this->AddMessage(IArchitecture::string("Target component[slot=") + type.name() + ", real=" +
				typeid(*cat).name() + "] registered");
			(cat->WithRelease())(cat);
			this->objects_container.erase(type.hash_code());
			cat->AsIam(&IArchitecture::ToolTryReleaseComponentArchitectureParent);
		}
		return this;
	}

	IArchitecture* IArchitecture::SendCommand(const type_info& command_type)
	{
		IAnyArchitecture* cat = ToolGetComponent(command_type);
		if (cat)
		{
			ICommand* command = dynamic_cast<ICommand*>(cat);
			if (command)
				command->OnExecute();
			else
				this->AddError(IArchitecture::string("Target component[slot=") + command_type.name() + ", real=" +
					typeid(*cat).name() + "] is not a command");
		}
		return this;
	}
	IArchitecture* IArchitecture::Diffusing(const type_info& command_type)
	{
		IAnyArchitecture* cat = ToolGetComponent(command_type);
		if (cat)
		{
			ICommand* command = dynamic_cast<ICommand*>(cat);
			if (cat)
				for (auto& pair : this->objects_container)
				{
					ICanMonitorCommand* monitor = dynamic_cast<ICanMonitorCommand*>(pair.second);
					if (monitor != nullptr && monitor->GetCommandType() == typeid(*cat))
						monitor->OnCommandInvoke(typeid(*cat));
				}
			else
				this->AddError(IArchitecture::string("Target component[slot=") + command_type.name() + ", real=" +
					typeid(*cat).name() + "] is not a command");
		}
		return this;
	}

	std::map<size_t, IArchitecture*> architecture_container;

	IArchitecture** IArchitecture::ToolGetArchitecture(const type_info& type)
	{
		return &architecture_container[type.hash_code()];
	}

	IArchitecture* ArchitectureInstance(const type_info& type,_In_ IArchitecture* ptr)
	{
		if (*IArchitecture::ToolGetArchitecture(type) == nullptr)
		{
			architecture_container[type.hash_code()] = ptr;
			IArchitecture* arch = *IArchitecture::ToolGetArchitecture(type);
			arch->Init();
			arch->AddMessage("Architecture Instance Generated");
			return arch;
		}
		else if (ptr == nullptr)
		{
			return *IArchitecture::ToolGetArchitecture(type);
		}
		else throw ld::LDException("multiple generate architecture");
	}
	IArchitecture* ArchitectureInstance(const type_info& type)
	{
		return *IArchitecture::ToolGetArchitecture(type);
	}
	void  ArchitectureDestory(const type_info& type)
	{
		delete* IArchitecture::ToolGetArchitecture(type);
		*IArchitecture::ToolGetArchitecture(type) = nullptr;
		architecture_container.erase(type.hash_code());
	}

#pragma endregion

}
