#include<Core/Header/ArchCom/Interface.h>

namespace ld
{
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

	IArchitecture* IArchitecture::RegisterMessageStream() {}
	IArchitecture* IArchitecture::AddMessage(IArchitecture::string message) const
	{
		static ConsolePro DefaultConsolePro;
		DefaultConsolePro.LogMessage(message);
	}

#pragma endregion

}
