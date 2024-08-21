#include<Math/DistributionCheck.h>

using namespace std;

namespace ld
{
    namespace math
    {
        /*
           正态分布（Normal）：boost::math::normal。
           均匀分布（Uniform）：boost::math::uniform。
           指数分布（Exponential）：boost::math::exponential。
           贝塔分布（Beta）：boost::math::beta。
           伽玛分布（Gamma）：boost::math::gamma。
           威布分布（Weibull）：boost::math::weibull。
           贝拉分布（Binomial）：boost::math::binomial。
           多项分布（Multinomial）：boost::math::multinomial。
           泊松分布（Poisson）：boost::math::poisson。
           几何分布（Geometric）：boost::math::geometric。
        */

        bool is_normal_distribution(const vector<Number>& data, const Number& mean, const Number& std_dev, bool isSingleTail, const Number& alpha)
        {
            if (data.size() == 0)
                throw Error_Empty;

            // 计算卡方值
            Number chi_squared(0);
            for (auto& value : data)
            {
                chi_squared += (value - mean) * (value - mean) / (std_dev * std_dev);
            }
            chi_squared /= data.size();

            // 计算p值
            Number p_value = 2 * (1 - boost::math::cdf(boost::math::normal_distribution<Number>(mean, std_dev), chi_squared));

            // 判断是否满足正态分布
            return p_value > 1 - alpha * (isSingleTail ? 1 : 0.5);
        }

        bool is_uniform_distribution(const vector<Number>& data, const Number& a, const Number& b, bool isSingleTail, const Number& alpha)
        {
            if (data.size() == 0)
                throw Error_Empty;

            boost::math::uniform_distribution<double> uniform(a, b);

            Number test_statistic(0.0);
            for (auto& value : data)
            {
                test_statistic += boost::math::pdf(uniform, value);
            }

            Number p_value = 2 * (1 - boost::math::cdf(uniform, test_statistic));

            return p_value > 1 - alpha * (isSingleTail ? 1 : 0.5);
        }

        bool is_exponential_distribution(const vector<Number>& data, const Number& lambda, bool isSingleTail, const Number& alpha)
        {
            if (data.size() == 0)
                throw Error_Empty;

            boost::math::exponential_distribution<Number> exponential(lambda);

            Number test_statistic(0.0);
            for (auto& value : data)
            {
                test_statistic += boost::math::pdf(exponential, value);
            }

            Number p_value = 2 * (1 - boost::math::cdf(exponential, test_statistic));

            return p_value > 1 - alpha * (isSingleTail ? 1 : 0.5);
        }

        bool kolmogorov_smirnov_test(const vector<Number>& data1, const vector<Number>& data2, bool isSingleTail, const Number& alpha)
        {
            if (data1.size() == 0 || data2.size() == 0)
                throw Error_Empty;

            vector<Number> data(data1.size() + data2.size());
            std::merge(data1.begin(), data1.end(), data2.begin(), data2.end(), data.begin());
            std::sort(data.begin(), data.end());

            Number maxdiff(0);
            for (auto& value : data)
            {
                maxdiff = ::max(maxdiff, std::abs(boost::math::cdf(data1, value) - boost::math::cdf(data2, value)));
            }

            Number p_value = 2 * (1 - boost::math::cdf(data, maxdiff));

            return p_value > 1 - alpha * (isSingleTail ? 1 : 0.5);
        }

        bool is_smooth(const vector<Number>& data, size_t lag, const Number& alpha)
        {
            return adf_test_value(data, lag) < -alpha;
        }
        bool is_white_noise(const vector<Number>& series, size_t max_lag, const Number& alpha)
        {
            vector<Number> acf_val = acf(series, max_lag);
            vector<Number> pacf_val = pacf(series, max_lag);

            for (size_t i = 1; i <= max_lag; ++i)
            {
                if (acf_val[i] > alpha || pacf_val[i] > alpha)
                {
                    return false;
                }
            }

            return true;
        }
    }
}

