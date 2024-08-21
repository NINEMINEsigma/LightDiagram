#include<test.h>
#include<Math/Graph.h>

using namespace ld::math::graph;
using namespace Eigen;
using namespace llm::Spark;

string allstr;

int main()
{
	auto llm_system = new llm::Spark::LLMSystem();
	ArchitectureInstance<arch>().RegisterSystem(typeid(LLMSystem), llm_system);
	llm_system->callback.OnEnd.AddListener([&](const char* str, LLMResult* res)
		{
			allstr += str;
			cout << str;
			if (res->getStatus() == 2)
			{
				csv_instance csv;
				csv.get_ref().push_back({ allstr });
				csv.save("ou.txt");
			}
		});
	llm_system->AsyncSend("How to write an ARIMA model in c++ without using any third-party libraries and make time series forecasts",0);
	system("pause");
}


