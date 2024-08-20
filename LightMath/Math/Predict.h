#include<Math/MathConfig.h>

namespace ld
{
	namespace math
	{
		// ��������غ�����ACF��
		// nlags������ӳٽ���
		std::vector<Number> acf(const std::vector<Number>& data, size_t nlags);
		// ����ƫ����غ�����PACF��
		// nlags������ӳٽ���
		std::vector<Number> pacf(const std::vector<Number>& data, size_t nlags);

        _LF_C_API(Class) ARIMA
        {
        public:
            ARIMA(size_t p, size_t d, size_t q);

            // ����ARIMAģ�͵Ĳ���
            void fit(const Eigen::VectorXd& y);

            // Ԥ��
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

