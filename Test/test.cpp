#include<test.h>
#include<Math/Graph.h>

using namespace ld::math::graph;
using namespace Eigen;

int main()
{
	ARIMA arima(3, 1, 3);
	VectorXd xd(0, 1, 2, 3, 4, 5, 6);
	arima.fit(xd);
	auto whatis = arima.predict(5);
	for (auto& i : whatis)
	{
		cout << i << " ";
	}
	cout << "\n";

	console.LogMessage("end");
}


