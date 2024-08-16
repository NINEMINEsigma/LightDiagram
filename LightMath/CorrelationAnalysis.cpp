#include<LightDiagram.h>
#include<CorrelationAnalysis.h>
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
}
