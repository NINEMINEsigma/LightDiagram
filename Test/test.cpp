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
	llm::Spark::LLMSystem* sparkLLM = new llm::Spark::LLMSystem(
		"1555396e",
		"5ed9018f67a8c1a2ee5cede10cc405d5",
		"ODUyNDBlNjllNTE4OTQzNzQ1YzVhNWY0");
	sparkLLM->SetupModel("generalv3.5", "ws(s)://spark-api.xf-yun.com/v3.5/chat", 5);
	sparkLLM->callback.OnEnd.AddListener([](const char* str, SparkChain::LLMResult* ptr)
		{
			cout << str << endl;
		});
	string qes;
	do
	{
		ld::clog->setstate(std::ios::beg);
		wcout.setstate(std::ios::beg);
		wcout << L"输入想要发送的问题(q to quit):";
		wcout.flush();
		cin >> qes;
		if (qes == "q")break;
		sparkLLM->SyncSend(qes);
	} while (true);
	console.LogMessage(L"-----release all-----");
	ArchitectureDestory<arch>();
	Sleep(1000);
	ld::LDEvent<int(int,int)> event(add__);
	event.AddListener(mut__);
	cout << event.OnInvoke(2, 3)[0] << event.OnInvoke(2, 3)[1];
	return 0;
}
