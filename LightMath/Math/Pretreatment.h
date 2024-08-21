#ifndef _FILE_PRETREATMENT
#define _FILE_PRETREATMENT

#include<Math/MathConfig.h>

namespace ld
{
	namespace math
	{
		std::vector<std::vector<Number>> _LF_C_API(Func) PretreatmentBy3sigmaRule(const std::vector<std::vector<Number>>& data);
		std::vector<std::vector<Number>> _LF_C_API(Func) PretreatmentBy3sigmaRule(
			const std::vector<std::vector<Number>>& data,
			std::vector<Number>& means,
			std::vector<Number>& stds,
			std::vector<size_t>& counts);
		std::vector<std::vector<Number>> _LF_C_API(Func) NormalizeData(const std::vector<std::vector<Number>>& data);
		std::vector<std::vector<Number>> _LF_C_API(Func) NormalizeData(
			const std::vector<std::vector<Number>>& data,
			std::vector<Number>& means,
			std::vector<Number>& stds);
		std::vector<std::vector<Number>> _LF_C_API(Func) NormalizeDataMinMax(const std::vector<std::vector<Number>>& data);
		std::vector<std::vector<Number>> _LF_C_API(Func) NormalizeDataMinMax(
			const std::vector<std::vector<Number>>& data,
			std::vector<std::pair<Number, Number>>& minmaxs);
		std::vector<std::vector<Number>> _LF_C_API(Func) NormalizeDataSum(const std::vector<std::vector<Number>>& data);
		std::vector<std::vector<Number>> _LF_C_API(Func) NormalizeDataSum(
			const std::vector<std::vector<Number>>& data,
			std::vector<Number>& sums);

		Number _LF_C_API(Func) get_sum(const std::vector<Number>& data);
		Number _LF_C_API(Func) get_mean(const std::vector<Number>& data);
		Number _LF_C_API(Func) get_variance(const std::vector<Number>& data);
		Number _LF_C_API(Func) get_std(const std::vector<Number>& data);
	}
}

#endif // !_FILE_PRETREATMENT
