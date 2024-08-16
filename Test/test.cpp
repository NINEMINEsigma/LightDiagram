//#define __REF_BOOST
#include<test.h>
#include<cstring>

using namespace ld;
using namespace std;
using namespace llm::Spark;

bool stats = false;

string s2s(const char* str)
{
	DWORD dBufSize = MultiByteToWideChar(CP_ACP, 0, str, strlen(str), NULL, 0);
	wchar_t* wdBuf = new wchar_t[dBufSize + 1];
	wmemset(wdBuf, 0, dBufSize);
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str), wdBuf, dBufSize);
	std::wstring wresult(wdBuf);
	delete[] wdBuf;
	dBufSize = WideCharToMultiByte(CP_UTF8, 0, wresult.c_str(), -1, NULL, 0, NULL, FALSE);
	char* dBuf = new char[dBufSize + 1];
	memset(dBuf, 0, dBufSize);
	WideCharToMultiByte(CP_UTF8, 0, wresult.c_str(), -1, dBuf, dBufSize, NULL, FALSE);
	std::string result(dBuf);
	delete[] dBuf;
	return result;
}

int main()
{
	//system("chcp 65001");
	auto llm = new LLMSystem();
	llm->callback.OnEnd.AddListener([](const char* str, SparkChain::LLMResult* re)
		{
			stats = re->getStatus() == 2;
			cout << s2s(str);
		});
	auto arch_ptr = ArchitectureInstance<arch>().RegisterSystem(typeid(LLMSystem), llm);
	string input = s2s("window控制台使用的是什么编码,为什么能显示中文但是输入中文会变成乱码");
	cout << input;
	llm->AsyncSend(input,0);
	while (false==stats)
	{

	}
	ArchitectureDestory<arch>();
	cout << endl;
}
