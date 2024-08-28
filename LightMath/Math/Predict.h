#ifndef __FILE_PREDICT
#define __FILE_PREDICT

#include<Math/MathConfig.h>
#include<Math/Perceptron.hpp>

namespace ld
{
    //ARIMA
	namespace math
	{
        _LF_C_API(Class) ARMAMath 
        {
        public:
            Number avgData(std::vector<Number> dataArray);
            Number sumData(std::vector<Number> dataArray);
            Number stderrData(std::vector<Number> dataArray);
            Number varerrData(std::vector<Number> dataArray);
            std::vector<Number>  autocorData(std::vector<Number> dataArray, Integer order);
            std::vector<Number>  autocovData(std::vector<Number> dataArray, Integer order);

            Number mutalCorr(std::vector<Number> dataFir, std::vector<Number> dataSec);
            Number getModelAIC(std::vector<std::vector<Number>> vec, std::vector<Number> data, Integer type);

            std::vector<std::vector<Number>> LevinsonSolve(std::vector<Number> garma);
            std::vector<Number> computeARCoe(std::vector<Number> dataArray, Integer p);
            std::vector<Number> computeMACoe(std::vector<Number> dataArray, Integer q);
            std::vector<Number> computeARMACoe(std::vector<Number> dataArray, Integer p, Integer q);
        };

        _LF_C_API(Class) ARMAModel
        {
        private:
            std::vector<Number> data;
            int p;
            int q;

        public:
            ARMAModel(std::vector<Number> data, Integer p, Integer q);

            std::vector<std::vector<Number>> solveCoeOfARMA();
        };
        
        _LF_C_API(Class) ARIMAModel
        {
        private:
            std::vector<Number> dataArray;
            std::vector<Number> dataFirDiff;

            std::vector<std::vector<Number>> arima;
        public:
            ARIMAModel(std::vector<Number> dataArray);

            std::vector<Number> preFirDiff(std::vector<Number> preData);

            std::vector<Number> preSeasonDiff(std::vector<Number> preData);
            std::vector<Number> preDealDiff(int period);

            std::vector<int> getARIMAModel(int period, std::vector<std::vector<int>> notModel, bool needNot);

            int aftDeal(int predictValue, int period);

            double gaussrand();

            int predictValue(int p, int q, int period);

        };

        _LF_C_API(Class) MAMoel
        {
        private:
            std::vector<double> data;
            int p;

        public:
            MAMoel(std::vector<double> data, int p);

            std::vector<std::vector<double>> solveCoeOfMA();
        };

        _LF_C_API(Class) ARModel 
        {
        private:
            std::vector<double> data;
            int p;

        public:
            ARModel(std::vector<double> data, int p);

            std::vector<std::vector<double> > solveCoeOfAR();
        };
	}

    namespace math
    {

    }
}

#endif // !__FILE_PREDICT

