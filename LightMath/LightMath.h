#ifndef __FILE_LIGHTMATH
#define __FILE_LIGHTMATH

#include "MathConfig.h"
#include "CorrelationAnalysis.h"
#include "DistributionCheck.h"
#include "Pretreatment.h"
#include "Predict.h"
#include "Fourier.h"
#include "DecisionTree.h"
#include "Graph.h"
#include "OpenCVH.h"

namespace ld
{
	namespace math
	{
		_LF_C_API(Struct) draw_bitmap_rect
		{
			size_t top, bottom, left, right;
		};

		_LF_C_API(Struct) draw_bitmap_size
		{
			size_t height, width;
		};

		_LF_C_API(Struct) draw_bitmap_color
		{
			Number r, g, b;
		};

		_LF_C_API(Struct) draw_bitmap_setting
		{
			draw_bitmap_rect rect;
			draw_bitmap_color color;
			draw_bitmap_size size;
		};

		bitmap_instance scatters(
			const std::vector<Number>& x,
			const std::vector<Number>& y,
			const draw_bitmap_setting& setting);
		bitmap_instance scatters(
			bitmap_instance from,
			const std::vector<Number>& x,
			const std::vector<Number>& y,
			const draw_bitmap_setting& setting);
	}

	namespace math
	{
		_LF_C_API(Struct) EmptyFillRule
		{
			enum class EmptyFillType
			{
				//使用empty_fill_value填充
				Default = 0,
				//使用平均值填充
				Mean = 1,
				//使用中位数填充
				Median
			};

			Number empty_fill_value = 0;
			EmptyFillType type = EmptyFillType::Default;
		};

		//通过读取csv获取全部数据
		//使用之前需要将csv最后可能存在的完全空缺的无用行数删除
		_LF_C_API(Class) FirstStep
		{
			csv_instance<char> my_csv;
			std::vector<std::vector<Number>> my_database;
		public:
			FirstStep(const std::string& path);
		private:
			EmptyFillRule empty_fill_rule;
			void DisplayRawDataStats();
		};
	}
}

#endif // !__FILE_LIGHTMATH
