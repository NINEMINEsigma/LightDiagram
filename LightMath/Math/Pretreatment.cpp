#include<Math/Pretreatment.h>
#include<boost/math/constants/constants.hpp>

using namespace std;

namespace ld
{
    namespace math
    {
        vector<vector<Number>> PretreatmentBy3sigmaRule(const vector<vector<Number>>& data)
        {
            vector<Number> mean, std;
            vector<size_t> count;
            return PretreatmentBy3sigmaRule(data, mean, std, count);
        }
        vector<vector<Number>> PretreatmentBy3sigmaRule(const vector<vector<Number>>& data, vector<Number>& means, vector<Number>& stds,vector<size_t>& counts)
        {
            size_t rowe = data.size(), cole = data[0].size();
            vector<vector<Number>> result(rowe, vector<Number>(cole));

            for (size_t col = 0; col < cole; col++)
            {
                Number mean = 0;
                Number std = 0;
                size_t count = 0;
                if (rowe > 1)
                {
                    for (size_t row = 0; row < rowe; row++)
                    {
                        mean += data[row][col];
                    }
                    mean /= (Number)rowe;
                    for (size_t row = 0; row < rowe; row++)
                    {
                        std += pow(data[row][col] - mean, 2);
                    }
                    std = sqrt(std / (Number)rowe);
                }
                else mean = data[0][col];
                for (size_t row = 0; row < rowe; row++)
                {
                    if (abs(mean - data[row][col]) > 3 * std)
                    {
                        count++;
                        result[row][col] = mean;
                    }
                    else
                        result[row][col] = data[row][col];
                }
                means.push_back(mean);
                stds.push_back(std);
                counts.push_back(count);
            }

            return result;
        }

        vector<vector<Number>> _LF_C_API(Func) decenter(const vector<vector<Number>>& data)
        {
            vector<vector<Number>> result(transposeVxV(data));
            for (auto& line : result)
            {
                Number mean = get_mean(line);
                for (auto& item : line)
                {
                    item -= mean;
                }
            }
            return transposeVxV(result);
        }


        vector<vector<Number>> NormalizeData(const vector<vector<Number>>& data)
        {
            vector<Number> mean, std;
            return NormalizeData(data, mean, std);
        }
        vector<vector<Number>> NormalizeData(const vector<vector<Number>>& data, vector<Number>& means,vector<Number>& stds)
        {
            size_t rowe = data.size(), cole = data[0].size();
            vector<vector<Number>> normalizedData(rowe, vector<Number>(cole));

            for (size_t col = 0; col < cole; col++)
            {
                Number mean = 0;
                Number std = 0;
                if (rowe > 1)
                {
                    for (size_t row = 0; row < rowe; row++)
                    {
                        mean += data[row][col];
                    }
                    mean /= (Number)rowe;
                    for (size_t row = 0; row < rowe; row++)
                    {
                        std += pow(data[row][col] - mean, 2);
                    }
                    std = sqrt(std / (Number)rowe);
                }
                else mean = data[0][col];
                for (size_t row = 0; row < rowe; row++)
                {
                    normalizedData[row][col] = (data[row][col] - mean) / std;
                }
                means.push_back(mean);
                stds.push_back(std);
            }

            return normalizedData;
        }

        vector<vector<Number>> NormalizeDataMinMax(const vector<vector<Number>>& data)
        {
            vector<pair<Number, Number>> minmax;
            return NormalizeDataMinMax(data, minmax);
        }
        vector<vector<Number>> NormalizeDataMinMax(const vector<vector<Number>>& data,vector<pair<Number,Number>>& minmaxs)
        {
            size_t rowe = data.size(), cole = data[0].size();
            vector<vector<Number>> normalizedData(rowe, vector<Number>(cole));

            for (size_t col = 0; col < cole; col++)
            {
                Number min = data[0][col], max = data[0][col];
                if (rowe > 1)
                {
                    for (size_t row = 0; row < rowe; row++)
                    {
                        min = data[row][col] < min ? data[row][col] : min;
                        max = data[row][col] > max ? data[row][col] : max;
                    }
                }
                for (size_t row = 0; row < rowe; row++)
                {
                    normalizedData[row][col] = (data[row][col] - min) / (max - min);
                }
                minmaxs.push_back(make_pair(min, max));
            }

            return normalizedData;
        }

        vector<vector<Number>> NormalizeDataSum(const vector<vector<Number>>& data)
        {
            vector<Number> sum;
            return NormalizeDataSum(data, sum);
        }
        vector<vector<Number>> NormalizeDataSum(const vector<vector<Number>>& data,vector<Number>& sums)
        {
            size_t rowe = data.size(), cole = data[0].size();
            vector<vector<Number>> normalizedData(rowe, vector<Number>(cole));

            for (size_t col = 0; col < cole; col++)
            {
                Number sum(0);
                for (size_t row = 0; row < rowe; row++)
                {
                    sum += data[row][col];
                }

                for (size_t row = 0; row < rowe; row++)
                {
                    normalizedData[row][col] = data[row][col] / sum;
                }
                sums.push_back(sum);
            }

            return normalizedData;
        }

        Number get_sum(const vector<Number>& data)
        {
            Number result(0);
            for (auto& i : data)
            {
                result += i;
            }
            return result;
        }
        Number get_mean(const vector<Number>& data)
        {
            return get_sum(data) / (Number)data.size();
        }
        Number get_variance(const vector<Number>& data)
        {
            Number mean = get_mean(data);
            Number result(0);
            for(auto& i:data)
            {
                result += pow(i - mean, 2);
            }
            return result;
        }
        Number get_std(const std::vector<Number>& data)
        {
            return sqrt(get_variance(data) / (Number)data.size());
        }
    }
}
