#include<test.h>

Number getp(Number x)
{
	return sin(x);
}

int main()
{
	vector<vector<Number>> X =
	{
		{-5,getp(-5)},
		{-2,getp(-2)},
		{0,getp(0)},
		{2,getp(2)},
		{5,getp(5)},
	};
	X = NormalizeData(X);
	cout << "标准化:\n" << MatrixToMatrix(X).transpose();
	auto result = ld::math::DimensionalityReduction_PCA(MatrixToMatrix(X),0.85,false);
	for (auto& i : result)
	{
		cout << "\n特征值:" << i.first << "\n对应的特征向量:\n[";
		for (auto& j : i.second)
		{
			cout << j << " ";
		}
	}
}