#include"LightDiagram.h"

#include<Windows.h>
#include<iostream>

using namespace std;

template<int index, class FuntionType>
struct ArgTypeAt;
    template<class ResultType, class FirstArgType, class... ArgsType>                  
	struct ArgTypeAt<0, ResultType _stdcall(FirstArgType, ArgsType...)>
	{
		using type = FirstArgType;
	};
    template<int index, class ResultType, class FirstArgType, class... ArgsType>       
	struct ArgTypeAt<index, ResultType _stdcall(FirstArgType, ArgsType...)>
	{
		using type = typename ArgTypeAt<index - 1, ResultType _stdcall(ArgsType...)>::type;
	};

class test
{
public:
	using tagx = void;
	int add(int a,int b)
	{
		return a + b;
	}
};

int _stdcall sub(int a, double b)
{
	return a - b;
}

int main()
{
	ld_test();
	cout << typeid(function_traits_ex<decltype(sub)>).name() << "\n";
	cout << "awake success\n";
	for (int i = 0, e = 100; i <= e; i++)
	{
		cout << "\r";
		int t = i * 100 / e;
		for (int j = 0; j < t / 10; j++)
		{
			cout << "X";
		}
		for (int j = t / 10; j < e / 10; j++)
		{
			cout << " ";
		}
		cout << " " << t << "%";
		Sleep(100 * i / e);
	}
}
