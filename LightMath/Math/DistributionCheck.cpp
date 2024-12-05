#include "DistributionCheck.h"

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

        vector<vector<int>> dbscan(vector<Number> datas, Number eps, Number MinPts, function<Number(const Number&, const Number&)> pr)
        {
            using namespace std;

            vector<vector<int>> clusters;
            set<int> visited;

            for (size_t i = 0, e = datas.size(); i < e; i++)
            {
                if (visited.find(i) == visited.end())
                {
                    vector<int> neighbors;
                    for (size_t j = 0; j < e; j++)
                    {
                        if (pr(datas[i], datas[j]) <= eps)
                        {
                            neighbors.push_back(j);
                        }
                    }

                    if (neighbors.size() >= MinPts)
                    {
                        vector<int> cluster;
                        cluster.push_back(i);
                        visited.insert(i);

                        for (auto& neighbor : neighbors)
                        {
                            if (visited.find(neighbor) == visited.end())
                            {
                                visited.insert(neighbor);
                                cluster.push_back(neighbor);
                            }
                        }

                        clusters.push_back(cluster);
                    }
                }
            }

            return clusters;
        }
        vector<vector<int>> dbscan(vector<Integer> datas, Number eps, Number MinPts, function<Number(const Integer&, const Integer&)> pr)
        {
            using namespace std;

            vector<vector<int>> clusters;
            set<int> visited;

            for (size_t i = 0, e = datas.size(); i < e; i++)
            {
                if (visited.find(i) == visited.end())
                {
                    vector<int> neighbors;
                    for (size_t j = 0; j < e; j++)
                    {
                        if (pr(datas[i], datas[j]) <= eps)
                        {
                            neighbors.push_back(j);
                        }
                    }

                    if (neighbors.size() >= MinPts)
                    {
                        vector<int> cluster;
                        cluster.push_back(i);
                        visited.insert(i);

                        for (auto& neighbor : neighbors)
                        {
                            if (visited.find(neighbor) == visited.end())
                            {
                                visited.insert(neighbor);
                                cluster.push_back(neighbor);
                            }
                        }

                        clusters.push_back(cluster);
                    }
                }
            }

            return clusters;
        }

        // K-Means算法
        vector<vector<DataPoint>> kMeans(vector<DataPoint>& datas, int k, int maxIterations, double epsilon) 
        {
            // 初始化聚类中心
            vector<DataPoint> centroids(k);
            for (int i = 0; i < k; ++i) {
                centroids[i].x = datas[i].x;
                centroids[i].y = datas[i].y;
                centroids[i].cluster = -1;
            }

            int iteration = 0;
            while (iteration < maxIterations) {
                // 清空聚类结果
                for (DataPoint& data : datas) {
                    data.cluster = -1;
                }

                // 将每个数据点分配到最近的聚类中心
                for (DataPoint& data : datas) {
                    double minDist = DBL_MAX;
                    for (int i = 0; i < k; ++i) {
                        double dist = sqrt(pow(data.x - centroids[i].x, 2) + pow(data.y - centroids[i].y, 2));
                        if (dist < minDist) {
                            minDist = dist;
                            data.cluster = i;
                        }
                    }
                }

                // 更新聚类中心
                vector<int> counts(k, 0);
                vector<double> sumX(k, 0);
                vector<double> sumY(k, 0);
                for (DataPoint& data : datas) {
                    int cluster = data.cluster;
                    counts[cluster]++;
                    sumX[cluster] += data.x;
                    sumY[cluster] += data.y;
                }
                for (int i = 0; i < k; ++i) {
                    if (counts[i] > 0) {
                        centroids[i].x = sumX[i] / counts[i];
                        centroids[i].y = sumY[i] / counts[i];
                    }
                }

                // 检查聚类结果是否收敛
                bool converged = true;
                for (int i = 0; i < k; ++i) {
                    double dist = sqrt(pow(centroids[i].x - centroids[i].x, 2) + pow(centroids[i].y - centroids[i].y, 2));
                    if (dist > epsilon) {
                        converged = false;
                        break;
                    }
                }
                if (converged) {
                    break;
                }

                iteration++;
            }

            // 将聚类结果分组
            vector<vector<DataPoint>> clusters(k);
            for (DataPoint& data : datas) {
                clusters[data.cluster].push_back(data);
            }

            return clusters;
        }
    }
}

