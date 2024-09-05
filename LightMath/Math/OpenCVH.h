#ifndef __FILE_OPENCVH
#define __FILE_OPENCVH

#include<Math/MathConfig.h>
#include<opencv2/opencv.hpp>

namespace ld
{
	namespace math
	{
		template<typename _MatTy = cv::Mat>
		_LF_C_API(OClass) tool_opencv
		{
		public:
			using string = cv::String;

			enum class draw_stats
			{
				point
			};
#pragma region default functions

			tool_opencv() :
				mat(nullptr),
				my_draw_stats(draw_stats::point)
			{

			}
			instance<_MatTy> mat;
			void save(
				const string & filename = "opencv plot.png")
			{
				cv::imwrite(filename, mat.get_ref());
			}
			void save(
				const string & filename,
				const std::vector<int>&params)
			{
				cv::imwrite(filename, mat.get_ref(), params);
			}
			void show(
				const string & name = "plot")
			{
				cv::imshow(name, mat.get_ref());
			}
			void wait(
				int delay = 0)
			{
				cv::waitKey(delay);
			}

#pragma endregion

			draw_stats my_draw_stats;

#pragma region draw point

			void draw_points()
			{
				my_draw_stats = draw_stats::point;
			}

#pragma endregion


		};
	}
}

#endif // !__FILE_OPENCVH
