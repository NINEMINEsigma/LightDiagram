#ifndef __FILE_MATHCONFIG
#define __FILE_MATHCONFIG

#include <math.h>
#include <boost/math/special_functions.hpp>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>

#include <LightDiagram.h>

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

	}
}

#endif // !__FILE_MATHCONFIG


