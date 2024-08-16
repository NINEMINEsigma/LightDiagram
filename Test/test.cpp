
//#include "test.h"
//#define __REF_BOOST;

#include <boost\math\distributions\normal.hpp>
#include <random>
#include <math.h>
#include<OpenXLSX.hpp>
#include<LightDiagram.h>
#include<MathConfig.h>
#include<DistributionCheck.h>
#include<CorrelationAnalysis.h>

using namespace ld::math;
using namespace std;

int main()
{
	boost::math::normal_distribution norm(1.0, 0.02);//ÆÚÍû£¬·½²î
	vector<Number> vec(11);
	for (int i = -5; i <= 5; i++)
	{
		cout << (
			vec[i+5] = boost::math::pdf<Number>(norm, i)
			) << "\n";
	}
	cout << ld::math::sper(vec, 0, 1) << "\nend";
}

