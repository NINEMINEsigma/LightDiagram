#pragma once
#include <LightDiagram.h>
#include <../LLMToolkit/LLMToolkit.h>
using namespace std;
using namespace ld;

class SMD :_LF_Inherited(IAnyArchitecture)
{
public:
	~SMD()
	{
		console.LogMessage(L"one instance is end life");
	}
	IAnyArchitecture::DestroyAction WithDestroy() const override
	{
		return [](IAnyArchitecture* r)
			{
				console.LogMessage(to_wstring(typeid(*r).raw_name()) + L" is delete");
				delete r;
			};
	}
};

_LF_C_API(Class) 
arch Symbol_Push
_LF_Inherited(IArchitecture) Symbol_Link
_LF_Inherited(llm::Spark::LLMArchitecture) Symbol_Link
_LF_Inherited(SMD)
{
public:
	arch()
	{
		this->appID = "1555396e";
		this->apiKey = "5ed9018f67a8c1a2ee5cede10cc405d5";
		this->apiSecret = "ODUyNDBlNjllNTE4OTQzNzQ1YzVhNWY0";
	}
	~arch()
	{
		console.LogMessage(L"arch is end life");
	}
	void Init() override
	{
		console.LogMessage(L"arch generate successful");
	}
};

class command :_LF_Inherited(ICommand) Symbol_Link
	_LF_Inherited(SMD)
{
public:
	void OnExecute() override
	{
		console.LogMessage(L"command has send successful");
	}
	IAnyArchitecture::ReleaseAction WithRelease() const override
	{
		return [](IAnyArchitecture* r)
			{
				console.LogMessage(L"command has release successful");
			};
	}
};

class controller :_LF_Inherited(IController), _LF_Inherited(ld::ICanMonitorCommand) Symbol_Link
	_LF_Inherited(SMD)
{
public:
	void Init() override
	{
		console.LogMessage(L"controller init successful");
	}
	void OnCommandInvoke(const type_info& type)
	{
		if (type == typeid(command))
		{
			console.LogMessage(L"command obtain successful");
		}
		else
		{
			console.LogError(L"error unknown command");
		}
	}
	const type_info& GetCommandType() const
	{
		return typeid(command);
	}
	IAnyArchitecture::ReleaseAction WithRelease() const override
	{
		return [](IAnyArchitecture* r)
			{
				console.LogMessage(L"controller has release successful");
			};
	}
};

class model :_LF_Inherited(IModel) Symbol_Link
	_LF_Inherited(SMD)
{
private:
	int id;
public:
	void Init() override
	{
		console.LogMessage(L"model init successful");
	}
	_LFramework_API_BindingTo(id, Ref);
	IAnyArchitecture::ReleaseAction WithRelease() const override
	{
		return [](IAnyArchitecture* r)
			{
				console.LogMessage(L"model has release successful");
			};
	}
};

class systemt :_LF_Inherited(ISystem) Symbol_Link
	_LF_Inherited(SMD)
{
private:
	int id;
public:
	void Init() override
	{
		console.LogMessage(L"system init successful");
	}
	_LFramework_API_BindingTo(id, Ref);
	IAnyArchitecture::ReleaseAction WithRelease() const override
	{
		return [](IAnyArchitecture* r)
			{
				console.LogMessage(L"system has release successful");
			};
	}
};
