#include<DistributionCheck.h>

using namespace std;

namespace ld
{
	namespace math
	{
        bool KSTest_Sorted(const vector<Number>& sortedData, Number alpha, Number test_bound)
        {
            if (sortedData.empty())
                throw Error_Empty;

            Number n = sortedData.size();
            Number d = 0.0;

            for (auto& x : sortedData)
            {
                Number F = cdf(x, sortedData);
                Number f = x / n;
                d = max(d, abs(F - f));
            }

            Number D = test_bound / std::sqrt(n);

            return d <= D * (1 - alpha);
        }
		bool KSTest(const vector<Number>& data, Number alpha, Number test_bound)
        {
            vector<Number> sortedData = data;
            std::sort(sortedData.begin(), sortedData.end());
            return KSTest_Sorted(sortedData, alpha, test_bound);
        }

        bool KSTest_Sorted(const vector<Number>& sortedSample1, const vector<Number>& sortedSample2, Number alpha, Number test_bound)
        {
            if (sortedSample1.empty() || sortedSample2.empty())
                throw Error_Empty;

            Number n1 = sortedSample1.size();
            Number n2 = sortedSample2.size();
            Number d = 0.0;

            for (size_t i = 0; i < n1; ++i) 
            {
                Number F = cdf(sortedSample1[i], sortedSample1);
                Number f = sortedSample1[i] / n1;
                d = std::max(d, std::abs(F - f));
            }

            for (size_t i = 0; i < n2; ++i) 
            {
                Number F = cdf(sortedSample2[i], sortedSample2);
                Number f = sortedSample2[i] / n2;
                d = std::max(d, std::abs(F - f));
            }

            double D = test_bound / std::sqrt(n1 + n2);

            return d <= D * (1 - alpha);
        }
        bool KSTest(const vector<Number>& sample1, const vector<Number>& sample2, Number alpha, Number test_bound)
        {
            vector<Number> sortedData = sample1;
            std::sort(sortedData.begin(), sortedData.end());
            vector<Number> sortedData2 = sample2;
            std::sort(sortedData2.begin(), sortedData2.end());
            return KSTest_Sorted(sortedData, sortedData2, alpha, test_bound);
        }

        bool KSLTest_Sorted(const std::vector<Number>& sortedData, Number alpha, Number test_bound)
        {
            if (sortedData.empty())
                throw Error_Empty;

            Number n = sortedData.size();
            Number d = 0.0;

            for (auto& x : sortedData)
            {
                Number F = cdf(x, sortedData);
                Number f = x / n;
                d = max(d, abs(F - f));
            }
            Number D = test_bound / sqrt(n);

            return d <= D * (1 - alpha);
        }
        bool KSLTest(const vector<Number>& data, Number alpha, Number test_bound)
        {
            vector<Number> sortedData = data;
            std::sort(sortedData.begin(), sortedData.end());
            return KSLTest_Sorted(sortedData, alpha, test_bound);
        }
	}
}

