#include<LightDiagram.h>
#include<CorrelationAnalysis.h>
#include<iostream>

using namespace std;

namespace ld
{
	namespace math
	{
		Number Pearson(const vector<Number>& A, const vector<Number>& B, long Length)
		{
#ifdef _DEBUG
			if (A.size() != B.size())
				throw Error_Aligned;
#endif // _DEBUG

			Number
				sumA(std::accumulate(A.begin(), A.end(), 0.0)),
				sumB(std::accumulate(B.begin(), B.end(), 0.0));
			Number
				aveA(sumA / Number(Length)),
				aveB(sumB / Number(Length));

			Number R1(0), R2(0), R3(0);
			for (long i = 0; i < Length; i++)
			{
				R1 += (A[i] - aveA) * (B[i] - aveB);
				R2 += pow((A[i] - aveA), 2);
				R3 += pow((B[i] - aveB), 2);
			}

			return (R1 / sqrt(R2 * R3));
		}
	}
}
