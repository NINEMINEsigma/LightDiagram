#include<Math/MathConfig.h>

namespace ld
{
	namespace math
	{
		// 计算自相关函数（ACF）
		// nlags是最大延迟阶数
		std::vector<Number> acf(const std::vector<Number>& data, size_t nlags);
		// 计算偏自相关函数（PACF）
		// nlags是最大延迟阶数
		std::vector<Number> pacf(const std::vector<Number>& data, size_t nlags);

        _LF_C_API(Class) ARIMA
        {
        public:
            ARIMA(size_t p, size_t d, size_t q);

            // 计算ARIMA模型的参数
            void fit(const Eigen::VectorXd& y);

            // 预测
            Eigen::VectorXd predict(int steps);

        private:
            size_t P;
            size_t D;
            size_t Q;
            Eigen::VectorXd AR;
            Eigen::VectorXd MA;
            Number sigma2;
        };
	}
}

