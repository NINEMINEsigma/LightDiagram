// test.cpp: 目标的源文件。
//

#include "test.h"
#include <../LLMToolkit/LLMToolkit.h>

int add__(int a, int b)
{
	return a + b;
}
int mut__(int a, int b)
{
	return a * b;
}

using llm::Spark::LLMSystem;

int main()
{
	system("chcp 65001");
	cout << __cplusplus << endl;
	console.LogMessage(L"-----env test--------");
	ld_test test;
	console.LogMessage(L"-----arch create-----");
	ArchitectureInstance<arch>();
	console.LogMessage(L"-----register obj----");
	ArchitectureInstance<arch>().RegisterCommand(typeid(command), new command());
	ArchitectureInstance<arch>().RegisterController(typeid(controller), new controller());
	ArchitectureInstance<arch>().RegisterModel(typeid(model), new model());
	ArchitectureInstance<arch>().RegisterSystem(typeid(systemt), new systemt());
	console.LogMessage(L"-----diff command----");
	ArchitectureInstance<arch>().Diffusing(typeid(command));
	console.LogMessage(L"-----send command----");
	ArchitectureInstance<arch>().SendCommand(typeid(command));
	console.LogMessage(L"-----model test------");
	ArchitectureInstance<arch>().GetModel(typeid(model))->AsDynamicPtr<model>()->set_id(500);
	cout << ArchitectureInstance<arch>().GetModel(typeid(model))->AsDynamicPtr<model>()->get_id() << endl;
	console.LogWarning(L"-----start llm-------");
	{
		//llm::Spark::LLMSystem* sparkLLM = new llm::Spark::LLMSystem(
		//	"1555396e",
		//	"5ed9018f67a8c1a2ee5cede10cc405d5",
		//	"ODUyNDBlNjllNTE4OTQzNzQ1YzVhNWY0");
		llm::Spark::LLMSystem* sparkLLM = new llm::Spark::LLMSystem();
		ld::RegisterOn<arch>(sparkLLM);
		sparkLLM->SetupModel("generalv3.5", "ws(s)://spark-api.xf-yun.com/v3.5/chat", 5);
		sparkLLM->callback.OnEnd.AddListener([](const char* str, SparkChain::LLMResult* ptr)
			{
				cout << ld::ConsoleColor::Green << ptr->getRole() << ": ";
				cout.flush();
				cout << ld::ConsoleColor::None << str << endl;
			});
	}
	//ArchitectureInstance<arch>().GetSystem(typeid(LLMSystem))->AsDynamicPtr<LLMSystem>()->SyncSend("你现在介绍一下自己.");
	wstring wqes;
	string qes;
	do
	{
		wcout << ("输入想要发送的问题(q to quit):");
		wchar_t ch;
		while ((ch=getchar())!='\n')
		{
			wqes += ch;
		}
		//qes = to_string(wqes);
		if (wqes == L"q")break;
		qes = to_string(wqes);
		wqes.clear();
		if (qes.size() < 1)continue;
		wcout << ld::ConsoleColor::Blue << ("已发送!.") << endl;
		ArchitectureInstance<arch>().GetSystem(typeid(LLMSystem))->AsDynamicPtr<LLMSystem>()->SyncSend((qes));
	} while (true);
	console.LogMessage(L"-----release all-----");
	ArchitectureDestory<arch>();
	cin.get();
	return 0;
}
