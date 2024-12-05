#include "LightMath.h"

using namespace std;

#define rect_height(rect) (rect.top-rect.bottom)
#define rect_width(rect) (rect.right-rect.left)
#define t_of_rect_height(from,rect) ((from-rect.bottom)/static_cast<double>(rect_height(rect)))
#define t_of_rect_width(from,rect) ((from-rect.left)/static_cast<double>(rect_width(rect)))

namespace ld
{
	namespace math
	{
		template<typename _HowDraw>
		static bitmap_instance _draw_on_bitmap(
			const bitmap_instance& from,
			const vector<Number>& x,
			const vector<Number>& y,
			const _HowDraw& _how_draw= _HowDraw())
		{
			for (size_t i = 0, e = x.size(); i < e; i++)
			{

			}
			return from;
		}

		bitmap_instance scatters(
			const vector<Number>& x,
			const vector<Number>& y,
			const draw_bitmap_setting& setting)
		{
			bitmap_instance result(setting.size.height, setting.size.width);
			return scatters(result, x, y, setting);
		}
		bitmap_instance scatters(
			bitmap_instance from,
			const vector<Number>& x,
			const vector<Number>& y,
			const draw_bitmap_setting& setting)
		{
			for (size_t i = 0, e = x.size(); i < e; i++)
			{

			}
			return from;
		}
	}

	namespace math
	{
		FirstStep::FirstStep(const string& path) :my_csv(path)
		{

		}

		void FirstStep::DisplayRawDataStats()
		{
			size_t empty_cell = 0;
			for (auto& row : my_csv.get_ref())
			{
				for (auto& cell : row)
				{
					if (cell.empty())
						empty_cell++;
				}
			}
		}
	}
}
