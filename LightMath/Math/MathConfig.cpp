#include<Math/MathConfig.h>

using namespace std;
using namespace Eigen;

namespace ld
{
	namespace math
	{
		MatrixXd MatrixToMatrix(const vector<vector<Number>>& from)
		{
			MatrixXd mat(from.size(), from[0].size());
			for (size_t i = 0, e = from.size(); i < e; ++i)
			{
				for (size_t j = 0, es = from[i].size(); j < es; ++j)
				{
					mat(i, j) = from[i][j];
				}
			}
			return mat;
		}
		vector<vector<Number>> MatrixToMatrix(const MatrixXd& from)
		{
			vector<vector<Number>> mat(from.rows());
			for (size_t i = 0, e = from.rows(), es = from.cols(); i < e; ++i)
			{
				mat[i].reserve(es);
				mat[i].resize(es, 0);
				for (size_t j = 0; j < es; ++j)
				{
					mat[i][j] = from(i, j);
				}
			}
			return mat;
		}
	}
}