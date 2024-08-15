#include<math.h>
#include<vector>

namespace ld
{
	namespace math
	{
		using ArithmeticBasicType = double;
		using Number = ArithmeticBasicType;
		using Integer = int;
		using uInteger = std::make_unsigned_t<Integer>;
		using exNumber = long double;
		using exInteger = long long;
		using uexInteger = std::make_unsigned_t< exInteger>;

		void TestMathLinking();
		/*
		r = S / M.
		S = Σ((Ai - Average(A))(Bi - Average(B))).
		 This is the sum of the product of the difference between the corresponding elements
		 in the two vectors A and B. This product represents the strength of the relationship 
		 between the corresponding elements in the two vectors.
		M = sqrt((Σ(Ai - Average(A))^2) * (Σ(Bi - Average(B))^2))
		This is the sum of the squares of the difference between the elements in the two
		 vectors A and B. This sum of squares indicates the degree of change in the strength
		 of the relationship between the corresponding elements in the two vectors. By opening
		 the square root, we can get the degree to which the strength of the relationship 
		 between each element changes relative to the mean value
		 */
		Number Pearson(const std::vector<Number>& A,const std::vector<Number>& B, long Length);
	}
}


