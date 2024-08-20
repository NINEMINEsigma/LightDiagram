#include <Math/Predict.h>
#include <iostream>
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;
using namespace std;

namespace ld
{
	namespace math
	{
        // 计算自相关函数（ACF）
        // nlags是最大延迟阶数
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

        // 计算偏自相关函数（PACF）
        // nlags是最大延迟阶数
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

        ARIMA::ARIMA(size_t p, size_t d, size_t q) : P(p), D(d), Q(q) {}

        // 计算ARIMA模型的参数
        void ARIMA::fit(const VectorXd& y)
        {
            size_t n = y.size();
            MatrixXd X(n - D, P + Q);
            for (size_t i = 0; i < n - D; ++i)
            {
                for (size_t j = 0; j < P; ++j)
                {
                    X(i, j) = y(i - j);
                }
                for (size_t j = 0; j < Q; ++j)
                {
                    X(i, P + j) = y(i - j - D);
                }
            }

            VectorXd ones(n - D);
            ones.setOnes();
            MatrixXd X1 = X.rowwise().begin().operator*() - ones * X.colwise().mean();
            MatrixXd H = (X1.transpose() * X1).ldlt().solve(X1.transpose() * y);

            AR.resize(P, 1);
            for (size_t i = 0; i < P; ++i)
            {
                AR(i) = H(i);
            }

            MA.resize(Q, 1);
            for (size_t i = 0; i < Q; ++i)
            {
                MA(i) = H(P + i);
            }

            auto temp = ((y.transpose() * y) - (H.transpose() * H));
            sigma2 = temp(0, 0);
        }

        // 预测
        VectorXd ARIMA::predict(int steps)
        {
            int n = AR.size() + steps;
            VectorXd y_pred(n);
            y_pred.setZero();

            for (int i = 0; i < AR.size(); ++i)
            {
                y_pred(i) = AR(i);
            }

            for (int i = AR.size(); i < n; ++i)
            {
                double sum = 0;
                for (int j = 0; j < MA.size(); ++j)
                {
                    sum += MA(j) * y_pred(i - j - D);
                }
                y_pred(i) = sum;
            }

            return y_pred;
        }

	}
}

