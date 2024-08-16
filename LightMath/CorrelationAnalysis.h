#ifndef __FILE_CORRELATION_ANALYSIS
#define __FILE_CORRELATION_ANALYSIS

#include<MathConfig.h>
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
		 between each element changes relative to the mean value
		 */
		Number Pearson(const std::vector<Number>& sorted_data1,const std::vector<Number>& sorted_data2, long Length);
		Number Pearson_T_value(const Number& r, const Integer& n);

		/*
		r = S / M.
		S = 6Σ(d_x-d_y)^2.
		M = n(n^2 - 1).
		*/
		Number Spearman(const vector<Number>& x, const vector<Number>& y);
	}
}

#endif // !__FILE_CORRELATION_ANALYSIS


