#include<Math/MathConfig.h>

using namespace std;
using namespace Eigen;

namespace ld
{
	namespace math
	{
		MatrixXd MatrixToMatrix(const vector<vector<Number>>& from)
		{
			MatrixXd mat(from.size(), from[0].size());
			for (size_t i = 0, e = from.size(); i < e; ++i)
			{
				for (size_t j = 0, es = from[i].size(); j < es; ++j)
				{
					mat(i, j) = from[i][j];
				}
			}
			return mat;
		}
		vector<vector<Number>> MatrixToMatrix(const MatrixXd& from)
		{
			vector<vector<Number>> mat(from.rows());
			for (size_t i = 0, e = from.rows(), es = from.cols(); i < e; ++i)
			{
				mat[i].reserve(es);
				mat[i].resize(es, 0);
				for (size_t j = 0; j < es; ++j)
				{
					mat[i][j] = from(i, j);
				}
			}
			return mat;
		}
        Number adf_test_value(const vector<Number>& series, size_t lag)
        {
            size_t n = series.size();
            Number rss = 0.0;  // �в�ƽ����
            Number mean = 0.0; // ʱ�����о�ֵ

            // �����ֵ
            for (Number y : series)
            {
                mean += y / n;
            }

            // ����OLS�в�
            std::vector<Number> res(n);
            for (size_t i = 0; i < n; ++i)
            {
                Number y = series[i] - mean;
                for (size_t j = 0; j <= lag && i >= 1 + j; ++j)
                {
                    y -= res[i - j - 1] * series[i - j - 1] / n;
                }
                res[i] = y;
                rss += y * y;
            }

            // ����ADFͳ����
            Number result = 0.0;
            for (size_t i = 1; i <= lag; ++i)
            {
                Number r = 0.0;
                for (size_t j = 0; j < n - i; ++j)
                {
                    r += res[j] * res[j + i];
                }
                result += r / (n - i);
            }

            result /= rss;
            return result;
        }
        // ��������غ�����ACF��
        // nlags������ӳٽ���
        vector<Number> acf(const vector<Number>& data, size_t nlags)
        {
            size_t n = data.size();
            vector<Number> acf_values(nlags + 1, 0.0);
            for (size_t i = 0; i <= nlags; ++i)
            {
                for (size_t j = i; j < n; ++j)
                {
                    acf_values[i] += data[j] * data[j - i];
                }
                acf_values[i] /= n;
            }
            return acf_values;
        }
        // ����ƫ����غ�����PACF��
        // nlags������ӳٽ���
        vector<Number> pacf(const vector<Number>& data, size_t nlags)
        {
            size_t n = data.size();
            vector<Number> pacf_values(nlags + 1, 0.0);
            for (size_t i = 0; i <= nlags; ++i)
            {
                for (size_t j = i; j < n; ++j)
                {
                    pacf_values[i] += data[j] * data[j - i];
                }
                pacf_values[i] /= n;
            }
            return pacf_values;
        }
	}
}

