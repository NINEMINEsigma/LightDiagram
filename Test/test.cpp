
//#include "test.h"
#include<LightDiagram.h>

using namespace ld;
//using namespace std;
using namespace ld::container;

int main()
{
	int a[10] = { 99,99 };
	ld::container::accurate::stack<int> s(a);
	while (s.push())
	{
		*(int*)s.pick() = s.get_size();
	} 
	for(auto item : s)
	{
		std::cout << item << "\n";
	}
	return 0;
}