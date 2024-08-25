#include<LightMath.h>

using namespace std;

namespace ld
{
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
