
#include"LightDiagram.h"

#include<iostream>

#include <cstdio>

using namespace std;
using namespace ld;

int main()
{
	ld_test();
	ConsolePro console;

	if (ld::socketkit::InitializeSocketEnvironment() == -1)
	{
		throw LDException("cannt init");
	}
	socketkit::CSockWrap socker1(SOCK_STREAM), socker2(SOCK_STREAM);
	socker1.SetAddress("127.0.0.1", 800);
	socker1.SetBufferSize(50, 50);
	socker2.SetAddress("127.0.0.1", 800);
	socker2.SetBufferSize(50, 50);
	char str[] = "test string";
	char str2[50];
	auto result = socker1.Send(str, sizeof(str));
	console.LogMessage(string(str) + " is send");
	cout //<<ConsoleColor::White
		<< result.nbytes << "\t" << result.nbytes << "\n";
	result = socker2.Recv(str2, sizeof(str2));
	this_thread::sleep_for(chrono::milliseconds(3000));
	cout <<result.nbytes << "\t" << result.nbytes << "\n";
	console.LogMessage(str2);
	ld::socketkit::FreeSocketEnvironment();

	getchar();
}