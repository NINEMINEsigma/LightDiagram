#ifndef __FILE_DISTRIBUTIONCHECK
#define __FILE_DISTRIBUTIONCHECK

#include<Math/MathConfig.h>
#include<boost/math/distributions.hpp>

namespace ld
{
	namespace math
	{
        template <typename Dist>
        bool is_distribution(const std::vector<Number>& data, const Dist& dist, Number alpha)
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
        bool _LF_C_API(Func) is_normal_distribution(const std::vector<Number>& data, const Number& mean, const Number& std_dev, bool isSingleTail = true, const Number& alpha = 0.05);
        bool _LF_C_API(Func) is_uniform_distribution(const std::vector<Number>& data, const Number& a, const Number& b, bool isSingleTail = true, const Number& alpha = 0.05);
        bool _LF_C_API(Func) is_exponential_distribution(const std::vector<Number>& data, const Number& lambda, bool isSingleTail = true, const Number& alpha = 0.05);
        bool _LF_C_API(Func) kolmogorov_smirnov_test(const std::vector<Number>& data1, const std::vector<Number>& data2, bool isSingleTail = true, const Number& alpha = 0.05);

        // �򵥵��ж����е�ƽ����
        bool _LF_C_API(Func) is_smooth(const std::vector<Number>& data, size_t lag, const Number& alpha = 0.05);
        // �򵥵Ķ����н��зǰ���������,�����Ǽ����������Ե�
        bool _LF_C_API(Func) is_white_noise(const std::vector<Number>& series, size_t max_lag, const Number& alpha = 0.05);

        //DBSCAN�㷨ʵ��
        //���ض�ԭʼ���ݵĴصı��
        std::vector<std::vector<int>> dbscan(
            std::vector<ld::math::Number> datas,
            ld::math::Number eps, 
            ld::math::Number MinPts,
            std::function<ld::math::Number(const ld::math::Number&, const ld::math::Number&)> pr);
        //DBSCAN�㷨ʵ��
        //���ض�ԭʼ���ݵĴصı��
        std::vector<std::vector<int>> dbscan(
            std::vector<ld::math::Integer> datas,
            ld::math::Number eps,
            ld::math::Number MinPts,
            std::function<ld::math::Number(const ld::math::Integer&, const ld::math::Integer&)> pr);
	}
}

#endif // !__FILE_DISTRIBUTIONCHECK


