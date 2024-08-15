#include<MathConfig.h>

namespace ld
{
	namespace math
	{
		constexpr Number SingleTailedTestBound = 1.15;
		constexpr Number TwoTailedTestBound = 1.36;

		//Kolmogorov-Smirnov Test for Normal- Distributed,
		//It is recommended for sample sizes of more than 2000
		//Suppose the data is ordered
		bool KSTest_Sorted(const std::vector<Number>& sortedData, Number alpha = 0.05, Number test_bound = TwoTailedTestBound);
		//Kolmogorov-Smirnov Test for Normal- Distributed
		//It is recommended for sample sizes of more than 2000
		//Assume the data isn't sorted
		bool KSTest(const std::vector<Number>& data, Number alpha = 0.05, Number test_bound = TwoTailedTestBound);

		//Kolmogorov-Smirnov Test for two sample,
		//It is recommended for sample sizes of more than 2000
		//Suppose the data is ordered
		bool KSTest_Sorted(const vector<Number>& sortedSample1, const vector<Number>& sortedSample2, Number alpha, Number test_bound);
		//Kolmogorov-Smirnov Test for two sample,
		//It is recommended for sample sizes of more than 2000
		//Assume the data isn't sorted
		bool KSTest(const vector<Number>& sortedSample1, const vector<Number>& sortedSample2, Number alpha, Number test_bound);

		//Lilliefors test for Normal- Distributed,
		//It is recommended for sample sizes of more than 2000
		//Suppose the data is ordered
		bool KSLTest_Sorted(const std::vector<Number>& sortedData, Number alpha, Number test_bound);
		//Lilliefors test for Normal- Distributed,
		//It is recommended for sample sizes of more than 2000
		//Assume the data isn't sorted
		bool KSLTest(const std::vector<Number>& sortedData, Number alpha, Number test_bound);
	}
}

