//#define _Source_DLL_EXPORT

#include"LightDiagram.h"

#include<iostream>

#include <cstdio>

using namespace std;
using namespace ld;

int main()
{
	ld_test();
	ConsolePro console;

	socketkit::CSockWrap socker1(SOCK_STREAM), socker2(SOCK_STREAM);
	socker1.SetAddress("192.168.43.100", 800);
	socker2.SetAddress("192.168.43.100", 800);
	char str[] = "test string";
	char str2[50];
	console.LogMessage(string(str) + " is send");
	auto result = socker1.TrySend(str, sizeof(str), 3000);
	cout << result.nbytes << "\t" << result.nbytes << "\n";
	result = socker2.TryRecv(str2, sizeof(str2), 3000);
	this_thread::sleep_for(chrono::milliseconds(3000));
	cout <<result.nbytes << "\t" << result.nbytes << "\n";
	console.LogMessage(str2);

	getchar();
}