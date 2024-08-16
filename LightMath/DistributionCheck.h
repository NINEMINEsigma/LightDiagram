#ifndef __FILE_DISTRIBUTIONCHECK
#define __FILE_DISTRIBUTIONCHECK

#include<MathConfig.h>
#include<boost/math/distributions.hpp>

namespace ld
{
	namespace math
	{
        template <typename Dist>
        bool _LF_C_API(Func) is_distribution(const std::vector<Number>& data, const Dist& dist, Number alpha)
        {
            Number test_statistic = 0.0;
            for (auto& value : data)
            {
                test_statistic += boost::math::pdf(dist, value);
            }

            // You can use a p-value to determine if the data follows the distribution
            Number p_value = 1 - boost::math::cdf(dist, test_statistic);

            // You can decide on a threshold for the p-value, e.g. 0.05
            return p_value > alpha;
        }
        bool is_normal_distribution(const std::vector<Number>& data, const Number& mean, const Number& std_dev, bool isSingleTail = true, const Number& alpha = 0.05);
        bool is_uniform_distribution(const std::vector<Number>& data, const Number& a, const Number& b, bool isSingleTail = true, const Number& alpha = 0.05);
        bool is_exponential_distribution(const std::vector<Number>& data, const Number& lambda, bool isSingleTail = true, const Number& alpha = 0.05);
        bool kolmogorov_smirnov_test(const std::vector<Number>& data1, const std::vector<Number>& data2, bool isSingleTail = true, const Number& alpha = 0.05);

	}
}

#endif // !__FILE_DISTRIBUTIONCHECK


