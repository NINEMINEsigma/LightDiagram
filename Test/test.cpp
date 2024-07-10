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
std::atomic_bool finish_bool(false);

int main()
{
	system("chcp 65001");
	cout << __cplusplus << endl;
	console.LogMessage("-----env test--------");
	ld_test test;
	console.LogMessage("-----arch create-----");
	ArchitectureInstance<arch>();
	console.LogMessage("-----register obj----");
	ArchitectureInstance<arch>().RegisterCommand(typeid(command), new command());
	ArchitectureInstance<arch>().RegisterController(typeid(controller), new controller());
	ArchitectureInstance<arch>().RegisterModel(typeid(model), new model());
	ArchitectureInstance<arch>().RegisterSystem(typeid(systemt), new systemt());
	console.LogMessage("-----diff command----");
	ArchitectureInstance<arch>().Diffusing(typeid(command));
	console.LogMessage("-----send command----");
	ArchitectureInstance<arch>().SendCommand(typeid(command));
	console.LogMessage("-----model test------");
	ArchitectureInstance<arch>().GetModel(typeid(model))->AsDynamicPtr<model>()->set_id(500);
	cout << ArchitectureInstance<arch>().GetModel(typeid(model))->AsDynamicPtr<model>()->get_id() << endl;
	console.LogWarning("-----start llm-------");
	{
		//llm::Spark::LLMSystem* sparkLLM = new llm::Spark::LLMSystem(
		//	"1555396e",
		//	"5ed9018f67a8c1a2ee5cede10cc405d5",
		//	"ODUyNDBlNjllNTE4OTQzNzQ1YzVhNWY0");
		llm::Spark::LLMSystem* sparkLLM = new llm::Spark::LLMSystem();
		ld::RegisterOn<arch>(sparkLLM);
		sparkLLM->SetupModel("generalv3.5", "ws(s)://spark-api.xf-yun.com/v3.5/chat", 5);
		//sparkLLM->callback.OnEnd.AddListener([](const char* str, SparkChain::LLMResult* ptr)
		//	{
		//		cout << ld::ConsoleColor::Green << ptr->getRole() << ": ";
		//		cout.flush();
		//		cout << ld::ConsoleColor::None << str << endl;
		//	});
		sparkLLM->callback.OnEvent.AddListener([](const char* str, SparkChain::LLMEvent* ptr)
			{
				console.LogWarning(str);
			});
		sparkLLM->callback.OnEnd.AddListener([sparkLLM](const char* str, SparkChain::LLMResult* ptr)
			{
				string out(str);
				cout << ld::ConsoleColor::Green;
				for (auto& i : out)
				{
					cout << i;
					Sleep(1);
				}
				if (ptr->getStatus() == 2)
				{
					finish_bool.store(true);
					*ld::clog << "<Code>" << (sparkLLM->callback.all_result) << "<!Code>" << endl;
					cout << ld::ConsoleColor::None << endl;
				}
			});
		sparkLLM->callback.OnError.AddListener([](const char* str, SparkChain::LLMError* ptr)
			{
				console.LogError(str);
				finish_bool.store(true);
			});
	}
	//wstring wqes;
	string qes;
	do
	{
		//wqes.clear();
		qes.clear();
		cout << "输入想要发送的问题(q to quit):    ";
		//wchar_t ch;
		//while ((ch=getchar())!='\n')
		//{
		//	wqes += ch;
		//}
		//qes = to_string(wqes);
		char ch;
		while ((ch = getchar()) != '\n')
		{
			qes += ch;
		}
		if (qes == "q")break;
		if (qes.size() < 1)
		{
			console.LogMessage("too short  ");
			continue;
		}
		else console.LogMessage(qes + "---send!");
		finish_bool.store(false);
		auto asyncEndCallback = ArchitectureInstance<arch>().GetSystem(typeid(LLMSystem))->AsDynamicPtr<LLMSystem>()->AsyncSend((qes), 1);
		while (!finish_bool.load())
		{
			Sleep(500);
		}
		asyncEndCallback();
	} while (true);
	console.LogMessage("-----release all-----");
	ArchitectureDestory<arch>();
	cin.get();
	return 0;
}
