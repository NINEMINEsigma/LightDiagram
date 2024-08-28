#include <Math/Predict.h>
#include <iostream>
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;
using namespace std;

namespace ld
{
    //ARIMA
    namespace math
    {
        ARModel::ARModel(std::vector<double> data, int p)
        {
            this->data.assign(data.begin(), data.end());
            this->p = p;
        }

        std::vector<std::vector<double>> ARModel::solveCoeOfAR() 
        {
            std::vector<std::vector<double> > vec;
            ARMAMath ar_math;
            std::vector<double>  arCoe(ar_math.computeARCoe(this->data, this->p));
            vec.push_back(arCoe);
            return vec;
        }

        Number ARMAMath::avgData(std::vector<Number> dataArray)
        {
            return this->sumData(dataArray) / dataArray.size();
        }

        Number ARMAMath::sumData(std::vector<Number> dataArray)
        {
            Number sumData = 0;
            for (size_t i = 0, e = dataArray.size(); i < e; i++)
                sumData += dataArray[i];
            return sumData;
        }
        Number ARMAMath::stderrData(std::vector<Number> dataArray)
        {
            return std::sqrt(this->varerrData(dataArray));
        }

        Number ARMAMath::varerrData(std::vector<Number> dataArray)
        {
            if (dataArray.size() <= 1)
                return 0.0;
            Number variance = 0;
            Number avgsumData = this->avgData(dataArray);

            for (size_t i = 0, e = dataArray.size(); i < e; i++)
            {
                dataArray[i] -= avgsumData;
                variance += dataArray[i] * dataArray[i];
            }
            return variance / (dataArray.size() - 1);
        }

        std::vector<Number>  ARMAMath::autocorData(std::vector<Number> dataArray, Integer order)
        {
            std::vector<Number> autoCor;
            std::vector<Number> autoCov(this->autocovData(dataArray, order));
            Number varData = this->varerrData(dataArray);
            if (varData != 0)
            {
                for (size_t i = 0; i < order; i++)
                {
                    autoCor[i] = autoCov[i] / varData;
                }
            }
            return autoCor;
        }
        std::vector<Number>  ARMAMath::autocovData(std::vector<Number> dataArray, Integer order)
        {
            std::vector<Number>  autoCov(order + 1);
            Number mu = this->avgData(dataArray);
            for (size_t i = 0; i <= order; i++)
            {
                autoCov[i] = 0.0;
                for (size_t j = 0; j + i < dataArray.size(); j++)
                {
                    autoCov[i] += (dataArray[j + i] - mu) * (dataArray[j] - mu);
                }
                autoCov[i] /= (dataArray.size() - i);
            }
            return autoCov;
        }

        Number ARMAMath::mutalCorr(std::vector<Number> dataFir, std::vector<Number> dataSec)
        {
            Number sumX = 0.0;
            Number sumY = 0.0;
            Number sumXY = 0.0;
            Number sumXSq = 0.0;
            Number sumYSq = 0.0;
            Integer len = 0;

            if (dataFir.size() != dataSec.size()) len = (Integer)std::min(dataFir.size(), dataSec.size());
            else len = static_cast<Integer>(dataFir.size());

            for (size_t i = 0; i < len; i++)
            {
                sumX += dataFir[i];
                sumY += dataSec[i];
                sumXY += dataFir[i] * dataSec[i];
                sumXSq += dataFir[i] * dataFir[i];
                sumYSq += dataSec[i] * dataSec[i];
            }

            Number numerator = sumXY - sumX * sumY / len;
            Number denominator = std::sqrt((sumXSq - sumX * sumX / len) * (sumYSq - sumY * sumY / len));

            if (denominator == 0) return 0.0;
            return numerator / denominator;

        }
        Number gaussrand0()
        {
            static Number V1, V2, S;
            static Integer phase = 0;
            Number X;

            if (phase == 0)
            {
                do
                {
                    Number U1 = (Number)rand() / RAND_MAX;
                    Number U2 = (Number)rand() / RAND_MAX;

                    V1 = 2 * U1 - 1;
                    V2 = 2 * U2 - 1;
                    S = V1 * V1 + V2 * V2;
                } while (S >= 1 || S == 0);

                X = V1 * sqrt(-2 * log(S) / S);
            }
            else X = V2 * sqrt(-2 * log(S) / S);

            phase = 1 - phase;
            return X;
        }
        Number ARMAMath::getModelAIC(std::vector<std::vector<Number>> vec, std::vector<Number> data, Integer type)
        {
            size_t n = data.size();
            size_t p = 0;
            size_t q = 0;
            Number tmpAR = 0.0, tmpMA = 0.0;
            Number sumErr = 0.0;

            if (type == 1)
            {
                std::vector<Number> maCoe = vec[0];
                q = maCoe.size();
                std::vector<Number> errData(q);

                for (int i = q - 1; i < n; i++)
                {
                    tmpMA = 0.0;
                    for (int j = 1; j < q; j++)
                    {
                        tmpMA += maCoe[j] * errData[j];
                    }
                    for (int j = q - 1; j > 0; j--)
                    {
                        errData[j] = errData[j - 1];
                    }
                    errData[0] = gaussrand0() * std::sqrt(maCoe[0]);
                    sumErr += (data[i] - tmpMA) * (data[i] - tmpMA);
                }
                return (n - (q - 1)) * std::log(sumErr / (n - (q - 1))) + (q + 1) * 2;
            }
            else if (type == 2)
            {
                std::vector<Number> arCoe = vec[0];
                p = (Integer)arCoe.size();

                for (int i = p - 1; i < n; ++i)
                {
                    tmpAR = 0.0;
                    for (int j = 0; j < p - 1; ++j)
                    {
                        tmpAR += arCoe[j] * data[i - j - 1];
                    }
                    sumErr += (data[i] - tmpAR) * (data[i] - tmpAR);
                }
                return (n - (p - 1)) * std::log(sumErr / (n - (p - 1))) + (p + 1) * 2;
            }
            else
            {
                std::vector<Number> arCoe = vec[0];
                std::vector<Number> maCoe = vec[1];
                p = (Integer)arCoe.size();
                q = (Integer)maCoe.size();
                std::vector<Number> errData(q);

                for (size_t i = p - 1; i < n; ++i)
                {
                    tmpAR = 0.0;
                    for (int j = 0; j < p - 1; ++j)
                    {
                        tmpAR += arCoe[j] * data[i - j - 1];
                    }
                    tmpMA = 0.0;
                    for (int j = 1; j < q; ++j)
                    {
                        tmpMA += maCoe[j] * errData[j];
                    }

                    for (int j = q - 1; j > 0; --j)
                    {
                        errData[j] = errData[j - 1];
                    }
                    errData[0] = gaussrand0() * std::sqrt(maCoe[0]);

                    sumErr += (data[i] - tmpAR - tmpMA) * (data[i] - tmpAR - tmpMA);
                }
                return (n - (q + p - 1)) * std::log(sumErr / (n - (q + p - 1))) + (p + q) * 2;
            }
        }

        std::vector<std::vector<Number>> ARMAMath::LevinsonSolve(std::vector<Number> garma)
        {
            Integer order = garma.size() - 1;
            std::vector<std::vector<Number>> result;

            result.resize(order + 1);
            for (int i = 0; i < order + 1; i++) result[i].resize(order + 1);


            std::vector<Number> sigmaSq(order + 1);

            sigmaSq[0] = garma[0];
            result[1][1] = garma[1] / sigmaSq[0];
            sigmaSq[1] = sigmaSq[0] * (1.0 - result[1][1] * result[1][1]);
            for (size_t k = 1; k < order; ++k)
            {
                Number sumTop = 0.0;
                Number sumSub = 0.0;
                for (size_t j = 1; j <= k; ++j)
                {
                    sumTop += garma[k + 1 - j] * result[k][j];
                    sumSub += garma[j] * result[k][j];
                }
                result[k + 1][k + 1] = (garma[k + 1] - sumTop) / (garma[0] - sumSub);
                for (size_t j = 1; j <= k; ++j)
                {
                    result[k + 1][j] = result[k][j] - result[k + 1][k + 1] * result[k][k + 1 - j];
                }
                sigmaSq[k + 1] = sigmaSq[k] * (1.0 - result[k + 1][k + 1] * result[k + 1][k + 1]);
            }
            result[0] = sigmaSq;

            return result;
        }

        std::vector<Number> ARMAMath::computeARCoe(std::vector<Number> dataArray, Integer p)
        {
            std::vector<Number> garma = this->autocovData(dataArray, p);

            std::vector<std::vector<Number>> result(this->LevinsonSolve(garma));

            std::vector<Number> ARCoe(p + 1);

            for (int i = 0; i < p; i++)
            {
                ARCoe[i] = result[p][i + 1];

            }
            ARCoe[p] = result[0][p];
            return ARCoe;

        }
        std::vector<Number> ARMAMath::computeMACoe(std::vector<Number> dataArray, Integer q) {

            auto p = (Integer)std::log(dataArray.size());

            //		System.out.println("The best p is " + p);
                // 求取系数
            std::vector<Number> bestGarma(this->autocovData(dataArray, p));
            std::vector<std::vector<Number>> bestResult(this->LevinsonSolve(bestGarma));

            std::vector<Number> alpha(p + 1);
            alpha[0] = -1;
            for (size_t i = 1; i <= p; ++i)
            {
                alpha[i] = bestResult[p][i];
            }

            std::vector<Number> paraGarma(q + 1);
            for (size_t k = 0; k <= q; ++k)
            {
                Number sum = 0.0;
                for (int j = 0; j <= p - k; ++j)
                {
                    sum += alpha[j] * alpha[k + j];
                }
                paraGarma[k] = sum / bestResult[0][p];
            }

            std::vector<std::vector<Number>> tmp(this->LevinsonSolve(paraGarma));
            std::vector<Number> MACoe(q + 1);
            for (int i = 1; i < MACoe.size(); ++i)
            {
                MACoe[i] = -tmp[q][i];
            }
            MACoe[0] = 1 / tmp[0][q];		//噪声参数

            return MACoe;
        }
        std::vector<Number> ARMAMath::computeARMACoe(std::vector<Number> dataArray, Integer p, Integer q)
        {
            std::vector<Number> allGarma(this->autocovData(dataArray, p + q));
            std::vector<Number> garma(p + 1);
            for (size_t i = 0; i < garma.size(); ++i)
            {
                garma[i] = allGarma[q + i];
            }
            std::vector<std::vector<Number>> arResult(this->LevinsonSolve(garma));

            // AR
            std::vector<Number> ARCoe(p + 1);
            for (size_t i = 0; i < p; ++i)
            {
                ARCoe[i] = arResult[p][i + 1];
            }
            ARCoe[p] = arResult[0][p];
            //		double [] ARCoe = this.YWSolve(garma);

                // MA
            std::vector<Number> alpha(p + 1);
            alpha[0] = -1;
            for (size_t i = 1; i <= p; ++i)
            {
                alpha[i] = ARCoe[i - 1];
            }

            std::vector<Number> paraGarma(q + 1);
            for (size_t k = 0; k <= q; ++k)
            {
                Number sum = 0.0;
                for (size_t i = 0; i <= p; ++i)
                {
                    for (size_t j = 0; j <= p; ++j)
                    {
                        sum += alpha[i] * alpha[j] * allGarma[std::abs((Integer)(k + i - j))];
                    }
                }
                paraGarma[k] = sum;
            }
            std::vector<std::vector<Number>> maResult(this->LevinsonSolve(paraGarma));
            std::vector<Number> MACoe(q + 1);
            for (size_t i = 1; i <= q; ++i)
            {
                MACoe[i] = maResult[q][i];
            }
            MACoe[0] = maResult[0][q];

            //		double [] tmp = this.YWSolve(paraGarma);
            //		double [] MACoe = new double[q + 1];
            //		System.arraycopy(tmp, 0, MACoe, 1, tmp.length - 1);
            //		MACoe[0] = tmp[tmp.length - 1];

            std::vector<Number> ARMACoe(p + q + 2);
            for (size_t i = 0; i < ARMACoe.size(); ++i)
            {
                if (i < ARCoe.size())
                {
                    ARMACoe[i] = ARCoe[i];
                }
                else
                {
                    ARMACoe[i] = MACoe[i - ARCoe.size()];
                }
            }
            return ARMACoe;
        }

        ARMAModel::ARMAModel(std::vector<Number> data, Integer p, Integer q)
        {
            this->data = data;
            this->p = p;
            this->q = q;
        }

        std::vector<std::vector<Number>> ARMAModel::solveCoeOfARMA()
        {
            std::vector<std::vector<Number>> vec;
            ARMAMath ar_math;

            std::vector<Number> armaCoe(ar_math.computeARMACoe(this->data, p, q));
            std::vector<Number> arCoe(this->p + 1);
            for (int i = 0; i < arCoe.size(); i++) arCoe[i] = armaCoe[i];

            std::vector<Number>  maCoe(this->q + 1);

            for (int i = 0; i < maCoe.size(); i++) {
                maCoe[i] = armaCoe[i + this->p + 1];
            }
            vec.push_back(arCoe);
            vec.push_back(maCoe);

            return vec;
        }

        ARIMAModel::ARIMAModel(std::vector<Number> dataArray)
        {
            this->dataArray.assign(dataArray.begin(), dataArray.end());
        }

        std::vector<Number> ARIMAModel::preFirDiff(std::vector<Number> preData)
        {
            std::vector<Number> res;
            for (size_t i = 0; i + 1 < preData.size(); i++)
            {
                Number tmpData = preData[i + 1] - preData[i];
                res.push_back(tmpData);
            }
            return res;
        }

        std::vector<Number> ARIMAModel::preSeasonDiff(std::vector<Number> preData)
        {
            std::vector<Number> res;

            for (size_t i = 0; i + 7 < preData.size(); i++)
            {
                Number tmpData = preData[i + 7] - preData[i];
                res.push_back(tmpData);
            }
            return res;
        }
        std::vector<Number> ARIMAModel::preDealDiff(int period)
        {
            if (period >= dataArray.size() - 1)
            {
                period = 0;
            }

            switch (period)
            {
            case 0:
            {
                return this->dataArray;
            }
            break;
            case 1:
            {
                std::vector<double> tmp(this->preFirDiff(this->dataArray));
                this->dataFirDiff.assign(tmp.begin(), tmp.end());
                return this->dataFirDiff;
            }
            break;
            default:
            {
                return preSeasonDiff(dataArray);
            }
            break;
            }
        }

        std::vector<int> ARIMAModel::getARIMAModel(int period, std::vector<std::vector<int>> notModel, bool needNot)
        {
            std::vector<double> data = this->preDealDiff(period);
            //for(int i=0;i<data.size();i++) std::cout<<data[i]<<std::endl;

            double minAIC = numeric_limits<double>::max();
            std::vector<int> bestModel(3);
            int type = 0;
            std::vector<std::vector<double>> coe;

            // model产生, 即产生相应的p, q参数
            int len = data.size();

            if (len > 5)
            {
                len = 5;
            }

            int size = ((len + 2) * (len + 1)) / 2 - 1;
            std::vector<std::vector<int>> model;
            model.resize(size);
            for (int i = 0; i < size; i++) model[i].resize(size);

            int cnt = 0;
            for (int i = 0; i <= len; ++i)
            {
                for (int j = 0; j <= len - i; ++j)
                {
                    if (i == 0 && j == 0)
                        continue;
                    model[cnt][0] = i;
                    model[cnt++][1] = j;
                }
            }
            //std::cout<<size<<std::endl;
            for (int i = 0; i < cnt; ++i)
            {
                // 控制选择的参数

                bool token = false;
                if (needNot)
                {
                    for (int k = 0; k < notModel.size(); ++k)
                    {
                        if (model[i][0] == notModel[k][0] && model[i][1] == notModel[k][1])
                        {
                            token = true;
                            break;
                        }
                    }
                }
                if (token)
                {
                    continue;
                }

                if (model[i][0] == 0)
                {
                    MAMoel* ma = new MAMoel(data, model[i][1]);

                    //std::vector<std::vector<double>>
                    coe = ma->solveCoeOfMA();
                    // std::cout<<i<<coe.size()<<std::endl;
                     //for(int ks=0;ks<ma->solveCoeOfMA().size();ks++) tmp.push_back(ma->solveCoeOfMA()[ks]);
                     //coe.assign(tmp.begin(),tmp.end());
                    type = 1;
                }
                else if (model[i][1] == 0)
                {
                    ARModel* ar = new ARModel(data, model[i][0]);
                    //std::vector<std::vector<double>> tmp(
                    coe = ar->solveCoeOfAR();
                    //   std::cout<<i<<coe.size()<<std::endl;
                       //for(int ks=0;ks<ar->solveCoeOfAR().size();ks++) tmp.push_back(ar->solveCoeOfAR()[ks]);
                       //coe.assign(tmp.begin(),tmp.end());
                    type = 2;
                }
                else
                {
                    //std::cout<<i<<model[i][0]<<" "<<model[i][1]<<std::endl;
                    ARMAModel* arma = new ARMAModel(data, model[i][0], model[i][1]);;

                    //std::vector<std::vector<double>> tmp(
                    coe = arma->solveCoeOfARMA();
                    //  std::cout<<i<<coe.size()<<std::endl;
                      //for(int ks=0;ks<arma->solveCoeOfARMA().size();ks++) tmp.push_back(arma->solveCoeOfARMA()[ks]);
                      //coe.assign(tmp.begin(),tmp.end());
                    type = 3;
                }
                ARMAMath ar_math;
                double aic = ar_math.getModelAIC(coe, data, type);
                //std::cout<<aic<<std::endl;
                // 在求解过程中如果阶数选取过长，可能会出现NAN或者无穷大的情况

                if (aic <= numeric_limits<double>::max() && !std::isnan(aic) && aic < minAIC)
                {
                    minAIC = aic;
                    // std::cout<<aic<<std::endl;
                    bestModel[0] = model[i][0];
                    bestModel[1] = model[i][1];
                    bestModel[2] = (int)std::round(minAIC);
                    this->arima = coe;
                }
            }
            return bestModel;
        }

        int ARIMAModel::aftDeal(int predictValue, int period)
        {
            if (period >= dataArray.size())
            {
                period = 0;
            }

            switch (period)
            {
            case 0:
                return (int)predictValue;
            case 1:
                return (int)(predictValue + dataArray[dataArray.size() - 1]);
            case 2:
            default:
                return (int)(predictValue + dataArray[dataArray.size() - 7]);
            }
        }

        double ARIMAModel::gaussrand()
        {
            static double V1, V2, S;
            static int phase = 0;
            double X;

            if (phase == 0) {
                do {
                    double U1 = (double)rand() / RAND_MAX;
                    double U2 = (double)rand() / RAND_MAX;

                    V1 = 2 * U1 - 1;
                    V2 = 2 * U2 - 1;
                    S = V1 * V1 + V2 * V2;
                } while (S >= 1 || S == 0);

                X = V1 * sqrt(-2 * log(S) / S);
            }
            else
                X = V2 * sqrt(-2 * log(S) / S);

            phase = 1 - phase;

            return X;
        }

        int ARIMAModel::predictValue(int p, int q, int period)
        {
            std::vector<double> data(this->preDealDiff(period));
            int n = data.size();
            int predict = 0;
            double tmpAR = 0.0, tmpMA = 0.0;
            std::vector<double> errData(q + 1);

            if (p == 0)
            {
                std::vector<double> maCoe(this->arima[0]);
                for (int k = q; k < n; ++k)
                {
                    tmpMA = 0;
                    for (int i = 1; i <= q; ++i)
                    {
                        tmpMA += maCoe[i] * errData[i];
                    }
                    //产生各个时刻的噪声
                    for (int j = q; j > 0; --j)
                    {
                        errData[j] = errData[j - 1];
                    }
                    errData[0] = gaussrand() * std::sqrt(maCoe[0]);
                }

                predict = (int)(tmpMA); //产生预测
            }
            else if (q == 0)
            {
                std::vector<double> arCoe(this->arima[0]);

                for (int k = p; k < n; ++k)
                {
                    tmpAR = 0;
                    for (int i = 0; i < p; ++i)
                    {
                        tmpAR += arCoe[i] * data[k - i - 1];
                    }
                }
                predict = (int)(tmpAR);
            }
            else
            {
                std::vector<double> arCoe(this->arima[0]);
                std::vector<double> maCoe(this->arima[1]);

                for (int k = p; k < n; ++k)
                {
                    tmpAR = 0;
                    tmpMA = 0;
                    for (int i = 0; i < p; ++i)
                    {
                        tmpAR += arCoe[i] * data[k - i - 1];
                    }
                    for (int i = 1; i <= q; ++i)
                    {
                        tmpMA += maCoe[i] * errData[i];
                    }

                    //产生各个时刻的噪声
                    for (int j = q; j > 0; --j)
                    {
                        errData[j] = errData[j - 1];
                    }

                    errData[0] = gaussrand() * std::sqrt(maCoe[0]);
                }

                predict = (int)(tmpAR + tmpMA);
            }

            return predict;
        }

        MAMoel::MAMoel(std::vector<double> data, int p) 
        {
            this->data = data;
            this->p = p;
        }

        std::vector<std::vector<double>> MAMoel::solveCoeOfMA() 
        {
            std::vector<std::vector<double> > vec;
            ARMAMath ar_math;
            std::vector<double>  maCoe(ar_math.computeMACoe(this->data, this->p));
            vec.push_back(maCoe);
            return vec;
        }
    }

    //BP神经网络
    namespace math
    {

    }
}

