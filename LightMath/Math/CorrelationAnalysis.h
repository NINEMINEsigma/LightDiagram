#ifndef __FILE_CORRELATION_ANALYSIS
#define __FILE_CORRELATION_ANALYSIS

#include<Math/MathConfig.h>
#include<boost/math/statistics/linear_regression.hpp>

namespace ld
{
	namespace math
	{
		/*
		r = S / M.
		S = Σ((Ai - Average(A))(Bi - Average(B))).
		 This is the sum of the product of the difference between the corresponding elements
		 in the two vectors A and B. This product represents the strength of the relationship 
		 between the corresponding elements in the two vectors.
		M = sqrt((Σ(Ai - Average(A))^2) * (Σ(Bi - Average(B))^2)).
		 This is the sum of the squares of the difference between the elements in the two
		 vectors A and B. This sum of squares indicates the degree of change in the strength
		 of the relationship between the corresponding elements in the two vectors. By opening
		 the square root, we can get the degree to which the strength of the relationship 
		 between each element changes relative to the mean value.
		 */
		Number _LF_C_API(Func) Pearson(const std::vector<Number>& sorted_data1,const std::vector<Number>& sorted_data2, long Length);
		Number _LF_C_API(Func) Pearson_T_value(const Number& r, const Integer& n);

		/*
		r = S / M.
		 The implementation of this function takes a very simple hierarchical difference strategy
		 and abandons the principle of averaging the same values.
		 Therefore, when the repetition value exceeds 10%, the implementation of this function should
		 be abandoned.When the value is repeated and is lower than this value, this function provides
		 both high performance and a large degree of accuracy.
		S = 6Σ(d_x-d_y)^2.
		M = n(n^2 - 1).
		*/
		Number _LF_C_API(Func) Spearman(const std::vector<Number>& x, const std::vector<Number>& y);

		std::pair<Eigen::VectorXd, Eigen::MatrixXd> _LF_C_API(Func) PCA(const Eigen::MatrixXd& mat);
		std::pair<Eigen::VectorXd, Eigen::MatrixXd> _LF_C_API(Func) PCA(const std::vector<std::vector<Number>>& normalizeData);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="mat">可用于ld::math::PCA的矩阵</param>
		/// <param name="alpha">关键重要水平</param>
		/// <param name="uppen">是否能够允许越过alpha</param>
		/// <returns>累计贡献率[特征值,特征向量]</returns>
		std::map<Number, std::pair<Number, std::vector<Number>>> DimensionalityReduction_PCA(const Eigen::MatrixXd& mat, const Number& alpha = 0.85, const bool& uppen = true);
	}
}

#endif // !__FILE_CORRELATION_ANALYSIS


