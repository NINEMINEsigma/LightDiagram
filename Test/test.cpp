#include<test.h>

int main()
{
	csv_instance csv_m_reader("C:\\Users\\000\\Desktop\\sxjm l\\阿里云天池-幸福感\\happiness_train_abbr.csv");
	for (auto& i : csv_m_reader)
	{
		for (auto& j : i)
		{
			cout << j << " ";
		}
		break;
	}
}
