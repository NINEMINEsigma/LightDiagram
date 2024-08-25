#include<test.h>
#include<Math/Graph.h>

using namespace ld::math::graph;
using namespace Eigen;
using namespace llm::Spark;

string allstr;

int main()
{
	console.LogMessage("start");
	cout << get_std({ 3,4,0,1,2,100 }) << "\n";
	console.LogMessage("end");
}


