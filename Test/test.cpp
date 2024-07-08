// test.cpp: 目标的源文件。
//

#include "test.h"

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
	console.LogMessage(L"-----release all-----");
	ArchitectureDestory<arch>();
	Sleep(1000);
	ld::LDEvent<int(int,int)> event(add__);
	event.AddListener(mut__);
	cout << event.OnInvoke(2, 3)[0] << event.OnInvoke(2, 3)[1];
	return 0;
}
