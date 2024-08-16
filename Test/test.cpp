
//#include "test.h"
//#define __REF_BOOST;

#include <boost\math\distributions\normal.hpp>
#include <random>
#include <math.h>
#include<OpenXLSX.hpp>
#include<LightDiagram.h>
#include<MathConfig.h>
#include<DistributionCheck.h>
#include<CorrelationAnalysis.h>

using namespace ld::math;
using namespace std;

// 计算两个向量之间的相关性
double correlation(const vector<double>& x, const vector<double>& y)
{
    double sum_xy = 0.0;
    double sum_x = 0.0;
    double sum_y = 0.0;
    double n = x.size();

    for (int i = 0; i < n; ++i) {
        sum_xy += x[i] * y[i];
        sum_x += x[i];
        sum_y += y[i];
    }

    return (n * sum_xy - sum_x * sum_y) / (sqrt(n * sum_x * sum_y) + 1e-10);
}

// 计算斯皮尔曼秩相关系数
double spearman_rank_correlation(const vector<double>& x, const vector<double>& y)
{
    vector<pair<double, double>> data;
    for (int i = 0; i < x.size(); ++i) {
        data.push_back({ x[i], y[i] });
    }

    sort(data.begin(), data.end());

    vector<double> ranks_x(x.size());
    vector<double> ranks_y(y.size());

    int rank = 1;
    for (int i = 0; i < x.size(); ++i) {
        ranks_x[i] = rank++;
        ranks_y[i] = rank++;
    }

    return correlation(ranks_x, ranks_y);
}

int main() {
    vector<double> x = { 1, 2, 3, 4, 5 };
    vector<double> y = { 1, 2, 5, 5, 5 };

    double correlation = spearman_rank_correlation(x, y);
    cout << "Spearman rank correlation: " << correlation << endl;
    correlation = ld::math::Spearman(x, y);
    cout << "Spearman rank correlation: " << correlation << endl;
}
