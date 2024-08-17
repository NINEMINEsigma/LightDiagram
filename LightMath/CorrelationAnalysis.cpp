#include<LightDiagram.h>
#include<Math/CorrelationAnalysis.h>
#include<iostream>

using namespace std;

namespace ld
{
	namespace math
	{
		Number Pearson(const vector<Number>& sorted_data1, const vector<Number>& sorted_data2, long Length)
		{
			if (sorted_data1.size() != sorted_data2.size())
				throw Error_Aligned;

			Number
				sumA(std::accumulate(sorted_data1.begin(), sorted_data1.end(), 0.0)),
				sumB(std::accumulate(sorted_data2.begin(), sorted_data2.end(), 0.0));
			Number
				aveA(sumA / Number(Length)),
				aveB(sumB / Number(Length));

			Number R1(0), R2(0), R3(0);
			for (long i = 0; i < Length; i++)
			{
				R1 += (sorted_data1[i] - aveA) * (sorted_data2[i] - aveB);
				R2 += pow((sorted_data1[i] - aveA), 2);
				R3 += pow((sorted_data2[i] - aveB), 2);
			}

			return (R1 / sqrt(R2 * R3));
		}
		Number Pearson_T_value(const Number& r,const Integer& n)
		{
			return r / (sqrt(1 - r * r) / (n - 2));
		}

		Number Spearman(const vector<Number>& x,const vector<Number>& y)
		{
			if (x.size() != y.size())
				throw Error_Aligned;
			int n = x.size();

			vector<pair<Number, int>> ranks_x;
			vector<pair<Number, int>> ranks_y;
			for (int i = 0; i < n; ++i)
			{
				ranks_x.push_back({ x[i],i });
				ranks_y.push_back({ y[i],i });
			}

			sort(ranks_x.begin(), ranks_x.end());
			sort(ranks_y.begin(), ranks_y.end());

			vector<int> d_x(n), d_y(n);

			for (int i = 0, e = n; i < e; i++)
			{
				d_x[ranks_x[i].second] = i;
				d_y[ranks_y[i].second] = i;
			}

			Number sum(0);
			for (int i = 0, e = n; i < e; i++)
			{
				Number dpv = d_x[i] - d_y[i];
				sum += dpv * dpv;
			}
			return 1 - (6 * sum) / (n * (n * n - 1));
		}
	}

	//PCA
	namespace math
	{
        // 计算均值
        vector<double> calculateMean(const vector<vector<double>>& data) 
        {
            vector<double> mean(data[0].size());
            for (const auto& vec : data) 
            {
                for (size_t i = 0; i < vec.size(); ++i) 
                {
                    mean[i] += vec[i];
                }
            }
            for (size_t i = 0; i < mean.size(); ++i) 
            {
                mean[i] /= data.size();
            }
            return mean;
        }

        // 中心化数据
        vector<vector<double>> centerData(const vector<vector<double>>& data, const vector<double>& mean) 
        {
            vector<vector<double>> centeredData(data.size());
            for (size_t i = 0; i < data.size(); ++i) 
            {
                centeredData[i].resize(mean.size());
                for (size_t j = 0; j < mean.size(); ++j) 
                {
                    centeredData[i][j] = data[i][j] - mean[j];
                }
            }
            return centeredData;
        }

        // 计算协方差矩阵
        vector<vector<double>> calculateCovarianceMatrix(const vector<vector<double>>& centeredData)
        {
            vector<vector<double>> cov(centeredData[0].size(), vector<double>(centeredData[0].size()));
            for (const auto& vec : centeredData) 
            {
                for (size_t i = 0; i < vec.size(); ++i)
                {
                    for (size_t j = 0; j < vec.size(); ++j)
                    {
                        cov[i][j] += vec[i] * vec[j];
                    }
                }
            }
            for (size_t i = 0; i < cov.size(); ++i)
            {
                for (size_t j = 0; j < cov[i].size(); ++j)
                {
                    cov[i][j] /= centeredData.size();
                }
            }
            return cov;
        }

        // 计算特征值和特征向量
        pair<vector<double>, vector<vector<double>>> calculateEigen(const vector<vector<double>>& cov) 
        {
            vector<double> eigenValues(cov.size());
            vector<vector<double>> eigenVectors(cov.size(), vector<double>(cov.size()));
            for (size_t i = 0; i < cov.size(); ++i) 
            {
                for (size_t j = 0; j < cov.size(); ++j) 
                {
                    eigenVectors[i][j] = (i == j) ? 1 : 0;
                }
            }
            for (size_t i = 0; i < cov.size(); ++i) 
            {
                double maxVal = 0;
                int maxIndex = -1;
                for (size_t j = 0; j < cov.size(); ++j)
                {
                    if (abs(cov[i][j]) > maxVal) 
                    {
                        maxVal = abs(cov[i][j]);
                        maxIndex = j;
                    }
                }
                eigenValues[i] = cov[i][maxIndex];
                cov[i][maxIndex] = 0;
                for (size_t j = 0; j < cov.size(); ++j) 
                {
                    eigenVectors[i][j] -= eigenVectors[maxIndex][j];
                }
            }
            return make_pair(eigenValues, eigenVectors);
        }

        // 主成分分析
        vector<vector<double>> performPCA(const vector<vector<double>>& data) 
        {
            auto mean = calculateMean(data);
            auto centeredData = centerData(data, mean);
            auto cov = calculateCovarianceMatrix(centeredData);
            auto eigen = calculateEigen(cov);

            vector<vector<double>> pcaResults(eigen.second[0].size());
            for (const auto& vec : eigen.second)
            {
                pcaResults.push_back(vec);
            }
            return pcaResults;
        }
	}
}
