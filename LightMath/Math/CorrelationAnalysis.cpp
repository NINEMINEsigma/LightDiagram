#include<LightDiagram.h>
#include<Math/CorrelationAnalysis.h>
#include<iostream>

using namespace std;
using namespace Eigen;

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
		Number Pearson_T_value(const Number& r, const Integer& n)
		{
			return r / (sqrt(1 - r * r) / (double)(n - 2));
		}

		Number Spearman(const vector<Number>& x, const vector<Number>& y)
		{
			if (x.size() != y.size())
				throw Error_Aligned;
			int n = (int)x.size();

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
			return 1.0 - (6 * sum) / (Number)(n * (n * n - 1));
		}
		Number SpearmanEx(const vector<Number>& x, const vector<Number>& y)
		{
			int n = x.size();
			map<Number, int> rank_x, rank_y;

			// 计算x和y的排名
			for (int i = 0; i < n; ++i)
			{
				rank_x[x[i]] = i + 1;
				rank_y[y[i]] = i + 1;
			}

			// 计算斯皮尔曼相关性统计量
			Number sum_xy = 0, sum_x = 0, sum_y = 0;
			for (int i = 0; i < n; ++i)
			{
				sum_xy += rank_x[x[i]] * rank_y[y[i]];
				sum_x += rank_x[x[i]] * rank_x[x[i]];
				sum_y += rank_y[y[i]] * rank_y[y[i]];
			}

			return (n * sum_xy - sum_x * sum_y) / (sqrt(n * sum_x - sum_x * sum_x) * sqrt(n * sum_y - sum_y * sum_y));
		}
	}

	// 计算主成分
	namespace math
	{
		pair<VectorXd, MatrixXd> PCA(const MatrixXd& mat)
		{
			// 计算协方差矩阵
			// cov.ij = (1/n-1) Sigma_{k}^{n}( X_ki X_kj )
			// 协方差矩阵是一个对称矩阵
			MatrixXd cov = mat.transpose() * mat;

			// 计算对称矩阵(协方差矩阵)的特征值和特征向量
			SelfAdjointEigenSolver<MatrixXd> eig(cov);
			return make_pair(eig.eigenvalues(), eig.eigenvectors());
		}

		map<Number, pair<Number, vector<Number>>> DimensionalityReduction_PCA(const MatrixXd& mat, const Number& alpha, const bool& uppen)
		{
			auto aws = PCA(mat);
			decltype(DimensionalityReduction_PCA({}, {}, {})) result;
			Number sum(0), psc(0);
			for (auto i : aws.first)
			{
				sum += i;
			}
			for (int i = aws.first.size() - 1, e = -1; i != e && psc < alpha; i--)
			{
				psc += aws.first[i] / sum;
				if (psc > alpha && uppen == false)break;
				result[psc] = make_pair(aws.first[i], vector<Number>(aws.second.col(i).data(), aws.second.col(i).data() + aws.second.col(i).size()));
			}
			return result;
		}

	}
}
