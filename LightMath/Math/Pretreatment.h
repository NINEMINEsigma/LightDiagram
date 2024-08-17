#ifndef _FILE_PRETREATMENT
#define _FILE_PRETREATMENT

#include<Math/MathConfig.h>

namespace ld
{
	namespace math
	{
		std::vector<std::vector<Number>> _LF_C_API(Func) NormalizeData(const std::vector<std::vector<Number>>& data);
		std::vector<std::vector<Number>> _LF_C_API(Func) NormalizeDataMinMax(const std::vector<std::vector<Number>>& data);
		std::vector<std::vector<Number>> _LF_C_API(Func) NormalizeDataSum(const std::vector<std::vector<Number>>& data);
	}
}

#endif // !_FILE_PRETREATMENT
