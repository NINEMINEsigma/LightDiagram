#include<Math/Pretreatment.h>
#include<boost/math/constants/constants.hpp>

using namespace std;

namespace ld
{
    namespace math
    {
        vector<vector<Number>> NormalizeData(const vector<vector<Number>>& data)
        {
            size_t rowe = data.size(), cole = data[0].size();
            vector<vector<Number>> normalizedData(rowe, vector<Number>(cole));

            for (size_t col = 0; col < cole; col++)
            {
                Number mean(0), std(0);
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
            }

            return normalizedData;
        }

        vector<vector<Number>> NormalizeDataMinMax(const vector<vector<Number>>& data)
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
            }

            return normalizedData;
        }

        vector<vector<Number>> NormalizeDataSum(const vector<vector<Number>>& data)
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
            }

            return normalizedData;
        }
    }
}
