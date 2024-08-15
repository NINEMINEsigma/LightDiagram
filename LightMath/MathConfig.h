#include<math.h>
#include<LightDiagram.h>

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
		using uexInteger = std::make_unsigned_t<exInteger>;

		constexpr const char* Error_Aligned = "The size cannot be aligned";
		constexpr const char* Error_Empty = "The data cannot be empty";

		//Indicator Function is return ture when x > Y_i otherwise false

		// Cumulative Distribution Function
		Number cdf(const Number& x, const std::vector<Number>& sortedData)
		{
			Number n = sortedData.size();
			Number rank = std::distance(sortedData.begin(), std::lower_bound(sortedData.begin(), sortedData.end(), x)) + 1;
			return (rank - 0.5) / n;
		}

		Number normal_cdf(Number x, Number mu, Number sigma)
		{
			return 0.5 * (1 + erf((x - mu) / (sigma * sqrt(2))));
		}
	}
}

